#include "../include/dispatcher.h"
#include "../include/environment.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_comparison
#define execute_jlt execute_comparison
#define execute_jgt execute_comparison
#define execute_jge execute_comparison

// ----- Instruction dispatcher -----
typedef void (*execute_func_t)(instruction*);

// TODO CHECK ORDER
static execute_func_t executeFuncs[] = {
    execute_assign      ,
    execute_add         ,
    execute_sub         ,
    execute_mul         ,
    execute_div         ,
    execute_mod         ,
    execute_jump        ,
    execute_jeq         ,
    execute_jne         ,
    execute_jle         ,
    execute_jge         ,
    execute_jlt         ,
    execute_jgt         ,
    execute_call        ,
    execute_pusharg     ,
    execute_funcenter   ,
    execute_funcexit    ,
    execute_newtable    ,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
};

void execute_cycle (void) {
    if (pc >= codeSize) {
        executionFinished = 1;
        return;
    }

    assert(pc < codeSize);
    instruction *i = &instructions.at(pc);

    assert(
        i->op >= 0 and
        i->op < sizeof(executeFuncs) / sizeof(executeFuncs[0])
    );

    if (i->srcLine) {
        currLine = i->srcLine;
    }
    unsigned oldpc = pc;
    executeFuncs[i->op](i);
    if (pc == oldpc) {
        ++pc;
    }
}

void execute_assign (instruction *instr) {
    avm_memcell *lv = avm_translate_op(&instr->result, 0);
    avm_memcell *rv = avm_translate_op(&instr->arg1, &ax);

    // TODO not sure about those checks
    // assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    // assert(rv and (&stack[bp] >= rv and rv > &stack[sp]));
    avm_assign(lv, rv);
}

// ----- Arithmetic operations dispatcher -----
typedef double (*arithmetic_func_t)(double x, double y);

static double add_impl(double x, double y) {
    return x + y;
}

static double sub_impl(double x, double y) {
    return x - y;
}

static double mul_impl(double x, double y) {
    return x * y;
}

static double div_impl(double x, double y) {   
    if(y == 0) {
        avm_error("Can't divide by 0\n");
    }
    return x / y;
}

static double mod_impl(double x, double y){
    if(y == 0) {
        avm_error("Can't divide by 0\n");
    }
    return ((unsigned) x) % ((unsigned) y);
}

static arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void execute_arithmetic(instruction *instr){
    avm_memcell* lv = avm_translate_op(&instr->result, NULL);
    avm_memcell* rv1 = avm_translate_op(&instr->arg1, &ax);
    avm_memcell* rv2 = avm_translate_op(&instr->arg2, &bx);

//    assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    assert(rv1 and rv2);

    if(rv1->type != number_m or rv2->type != number_m){
        avm_error("Not a number\n");
        executionFinished = 1;
        return;
    }

    arithmetic_func_t op = arithmeticFuncs[instr->op - add_v];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = op(rv1->data.numVal, rv2->data.numVal);
}

void execute_jump(instruction *instr) {
    assert(instr->result.type == label_a);
    if (!executionFinished) {
        pc = instr->result.val;
    }
}

// ----- Equaulity operations dispatcher -----
typedef bool (*equality_func_t)(avm_memcell*, avm_memcell*);

static bool num_equal (avm_memcell *lhs, avm_memcell *rhs) {
    return lhs->data.numVal == rhs->data.numVal;
}

static bool str_equal (avm_memcell *lhs, avm_memcell *rhs) {
    return strcmp(lhs->data.strVal, rhs->data.strVal) == 0;
}

static bool bool_equal (avm_memcell *lhs, avm_memcell *rhs) {
    assert(0);
    return false;
}

static bool table_equal (avm_memcell *lhs, avm_memcell *rhs) {
    avm_table *t1 = lhs->data.tableVal;
    avm_table *t2 = rhs->data.tableVal;
    if (t1->numIndexed.size() != t2->numIndexed.size() or 
        t1->strIndexed.size() != t2->strIndexed.size()) {
            return false;
    }
    /*  
     *  Itarate respective numIndexed and strIndexed tables. 
     *  When a disparity is found, either by different keys
     *  or by equal keys with different values, then return false
     */
    for (const auto &p : t1->numIndexed) {
        if (!t2->numIndexed.count(p.first) or /* != keys */
            t2->numIndexed.at(p.first) != p.second) { // == keys, != values
                return false;
        }
    }
    for (const auto &p : t1->strIndexed) {
        if (!t2->strIndexed.count(p.first) or /* != keys */
            t2->strIndexed.at(p.first) != p.second) { // == keys, != values
                return false;
        }
    }
    return true;
}

static bool userFunc_equal (avm_memcell *lhs, avm_memcell *rhs) {
    return lhs->data.userFuncVal == rhs->data.userFuncVal;
}

static bool libFunc_equal (avm_memcell *lhs, avm_memcell *rhs) {
    return strcmp(lhs->data.libFuncVal, rhs->data.libFuncVal) == 0;
}

static bool nil_equal (avm_memcell *lhs, avm_memcell *rhs) {
    assert(0);
    return false;
}

static bool undef_equal (avm_memcell *lhs, avm_memcell *rhs) {
    assert(0);
    return false;
}

static equality_func_t equalityFuncs[] = {
    num_equal,
    str_equal,
    bool_equal,
    table_equal,
    userFunc_equal,
    libFunc_equal,
    nil_equal,
    undef_equal
};


void execute_jeq (instruction *instr) {
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_op(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_op(&instr->arg2, &bx);

    bool res = false;

    if (rv1->type == undef_m or rv2->type == undef_m) {
        avm_error("Cannot perform equality comparison with 'undef' operands\n");
    }
    else if (rv1->type == nil_m or rv2->type == nil_m) {
        res = rv1->type == nil_m and rv2->type == nil_m;
    }
    else if (rv1->type == bool_m or rv2->type == bool_m) {
        res = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type) {
        avm_error(  "Cannot perform equality comparison %s == %s\n",
                    avm_tostring(rv1), avm_tostring(rv2));
    }
    else { // type can be: num, str, table, userFunc, libFunc
        res = equalityFuncs[rv1->type](rv1, rv2);
    }

    if (!executionFinished and res) {
        pc = instr->result.val;
    }
}

void execute_jne (instruction *instr) {
    assert(instr->result.type == label_a);

    avm_memcell *rv1 = avm_translate_op(&instr->arg1, &ax);
    avm_memcell *rv2 = avm_translate_op(&instr->arg2, &bx);

    bool res = false;

    if (rv1->type == undef_m or rv2->type == undef_m) {
        avm_error("Cannot perform equality comparison with 'undef' operands\n");
    }
    else if (rv1->type == nil_m or rv2->type == nil_m) {
        res = rv1->type == nil_m and rv2->type == nil_m;
    }
    else if (rv1->type == bool_m or rv2->type == bool_m) {
        res = (avm_tobool(rv1) == avm_tobool(rv2));
    }
    else if (rv1->type != rv2->type) {
        avm_error(  "Cannot perform equality comparison %s == %s\n",
                    avm_tostring(rv1), avm_tostring(rv2));
    }
    else { // type can be: num, str, table, userFunc, libFunc
        res = equalityFuncs[rv1->type](rv1, rv2);
    }

    if (!executionFinished and not res) {
        pc = instr->result.val;
    }
}

// ----- Comparison operations dispatcher -----
typedef double (*comparison_func_t)(double x, double y);

double jge_impl(double x, double y){ return x >= y;  }
double jgt_impl(double x, double y){ return x >  y;  }
double jle_impl(double x, double y){ return x <= y;  }
double jlt_impl(double x, double y){ return x <  y;  }

comparison_func_t comparisonFuncs[] = {
    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl
};

void execute_comparison (instruction *instr) {
    avm_memcell* rv1 =  avm_translate_op(&instr->arg1, &ax);
    avm_memcell* rv2 =  avm_translate_op(&instr->arg2, &bx);

    // assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    assert(rv1 and rv2);

    if(rv1->type != number_m or rv2->type != number_m){
        avm_error("Not a number");
        executionFinished = 1;
        return;
    }

    bool res = comparisonFuncs[instr->op - jle_v](rv1->data.numVal, rv2->data.numVal);
    
    if (!executionFinished and res) {
        pc = instr->result.val;
    }
}

void execute_pusharg (instruction *instr) {
    avm_memcell *arg = avm_translate_op(&instr->arg1, &ax);
    assert(arg);

    ++totalActuals;
    avm_assign(&stack[sp], arg);
    avm_decsp();
}

void execute_call (instruction *instr) {
    avm_memcell *func = avm_translate_op(&instr->arg1, &ax);
    assert(func);
    avm_callsaveenv();

    switch (func->type) {
        case userFunc_m: {
            pc = func->data.userFuncVal;
            assert(
                pc < codeSize and
                instructions[pc].op == funcenter_v
            );
            break;
        }
        case string_m:  {
            avm_calllibfunc(func->data.strVal);
            break;
        }
        case libFunc_m: {
            avm_calllibfunc(func->data.libFuncVal);
            break;
        }
        default: {
            std::string s(avm_tostring(func));
            avm_error("Cannot bind '%s' to function\n", s.c_str());
        }
    }
}

void execute_funcenter (instruction *instr) {
    userFunc funcInfo = avm_getfuncinfo(pc);
    totalActuals = 0;
    bp = sp;
    sp -= funcInfo.localSize;
    return;
}

void execute_funcexit (instruction *instr) {
    unsigned oldsp = sp;
    sp = avm_getenvval(bp + AVM_SAVEDSP_OFFSET);
    pc = avm_getenvval(bp + AVM_SAVEDPC_OFFSET);
    bp = avm_getenvval(bp + AVM_SAVEDBP_OFFSET);

    while (oldsp++ <= sp) {
        avm_memcellclear(&stack[oldsp]);
    }
}

void execute_newtable (instruction *instr) {
    avm_memcell *lv = avm_translate_op(&instr->result, NULL);
    // assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);

    avm_memcellclear(lv);
    lv->type            = table_m;
    lv->data.tableVal   = avm_tablenew();
    avm_tablerefinc(lv->data.tableVal);
}

void execute_tablegetelem (instruction *instr) {
    avm_memcell *lv = avm_translate_op(&instr->result, NULL);
    avm_memcell *table = avm_translate_op(&instr->arg1, NULL);
    avm_memcell *index = avm_translate_op(&instr->arg2, &ax);

    // assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    // assert(table and &stack[0] <= table and table < &stack[sp]);

    avm_memcellclear(lv);
    lv->type = nil_m;

    if (table->type != table_m) {
        avm_error("Illegal user of type %s as table\n", "TODO"); // TODO
    }
    avm_memcell *content = avm_tablegetelem(table->data.tableVal, index);
    if (content) {
        avm_assign(lv, content);
    }
    else {
        char *ts = avm_tostring(table);
        char *is = avm_tostring(index);
        avm_warning("%s[%s] not found\n", ts, is);
        free(ts);
        free(is);
    }
}

void execute_tablesetelem (instruction *instr) {
    avm_memcell *value = avm_translate_op(&instr->result, &bx);
    avm_memcell *table = avm_translate_op(&instr->arg1, NULL);
    avm_memcell *index = avm_translate_op(&instr->arg2, &ax);

    // assert(table and &stack[0] <= table and table < &stack[sp]);
    assert(index and value);

    if (table->type != table_m) {
        avm_error("Illegal user of type %s as table\n", "TODO"); // TODO
    }
    avm_tablesetelem(table->data.tableVal, index, value);
}

void execute_nop (instruction *instr) {
    return;
}