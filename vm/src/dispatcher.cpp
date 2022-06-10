#include "../include/dispatcher.h"
#include "../include/environment.h"
#include <cassert>
#include <cstdarg>
#include <cstdio>

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

#define execute_jle execute_comparison
#define execute_jlt execute_comparison
#define execute_jgt execute_comparison
#define execute_jge execute_comparison

// TODO CHECK ORDER
execute_func_t executeFuncs[] = {
    execute_assign      ,
    execute_add         ,
    execute_sub         ,
    execute_mul         ,
    execute_div         ,
    execute_mod         ,
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
    if (executionFinished) {
        return;
    }
    if (pc == codeSize) {
        executionFinished = 1;
        return;
    }

    assert(pc < codeSize);
    instruction i = instructions.at(pc);

    assert(
        i.op >= 0 and
        i.op < sizeof(executeFuncs) / sizeof(executeFuncs[0])
    );

    if (i.srcLine) {
        currLine = i.srcLine;
    }
    unsigned oldpc = pc;
    executeFuncs[i.op](i);
    if (pc == oldpc) {
        ++pc;
    }
}

void execute_assign (instruction &i) {
    avm_memcell *lv = avm_translate_operand(&i.result, 0);
    avm_memcell *rv = avm_translate_operand(&i.arg1, &ax);

    // TODO not sure about those checks
    assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    assert(rv and (&stack[bp] >= rv and rv > &stack[sp]));
    avm_assign(lv, rv);
}

void execute_call (instruction &i) {
    avm_memcell *func = avm_translate_operand(&i.result, &ax);
    assert(func);
    avm_callsaveenv();

    switch (func->type) {
        case userFunc_m:
            pc = func->data.userFuncVal;
            assert(
                pc < codeSize and
                instructions[pc].op == funcenter_v
            );
            break;
        case string_m:  avm_calllibfunc(func->data.strVal);
        case libFunc_m: avm_calllibfunc(func->data.libFuncVal);

        default: {
            char *s = avm_tostring(func);
            avm_error("Cannot bind '%s' to function\n", s);
            free(s);
            executionFinished = true;
        }
    }
}

void execute_funcexit(instruction &i) {
    unsigned savedsp = sp;
    sp = avm_getenvval(bp + AVM_SAVEDSP_OFFSET);
    pc = avm_getenvval(bp + AVM_SAVEDPC_OFFSET);
    bp = avm_getenvval(bp + AVM_SAVEDBP_OFFSET);

    while (savedsp <= sp) {
        avm_memcellclear(&stack[savedsp]);
    }
}

void execute_pusharg(instruction &i) {
    avm_memcell *arg = avm_translate_operand(&i.arg1, &ax);
    assert(arg);

    avm_assign(&stack[sp], arg);
    ++totalActuals;
    avm_decsp();
}

double add_impl(double x, double y){return x + y;}
double sub_impl(double x, double y){return x - y;}
double mul_impl(double x, double y){return x * y;}
double div_impl(double x, double y){   
                                    if(y == 0) avm_error("Can't divide by 0\n");
                                    return x / y;
                                   }
double mod_impl(double x, double y){
                                    if(y == 0) avm_error("Can't divide by 0\n");
                                    return ((unsigned) x) % ((unsigned) y);
                                   }


typedef double (*arithmetic_func_t)(double x, double y);

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

void execute_arithmetic(instruction & instr){
    avm_memcell* lv = avm_translate_operand(&instr.result, NULL);
    avm_memcell* rv1 = avm_translate_operand(&instr.arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr.arg2, &bx);

    assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    assert(rv1 and rv2);

    if(rv1->type != number_m or rv2->type != number_m){
        avm_error("Not a number\n");
        executionFinished = 1;
        return;
    }

    arithmetic_func_t op = arithmeticFuncs[instr.op - add_v];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = op(rv1->data.numVal, rv2->data.numVal);
}

double jge_impl(double x, double y){ return x >= y;  }
double jgt_impl(double x, double y){ return x >  y;  }
double jle_impl(double x, double y){ return x <= y;  }
double jlt_impl(double x, double y){ return x <  y;  }

arithmetic_func_t comparisonFuncs[] = {
    jge_impl,
    jgt_impl,
    jle_impl,
    jlt_impl
};

void execute_comparison(instruction & instr){
    avm_memcell* lv = avm_translate_operand(&instr.result, NULL);
    avm_memcell* rv1 = avm_translate_operand(&instr.arg1, &ax);
    avm_memcell* rv2 = avm_translate_operand(&instr.arg2, &bx);

    assert(lv and (&stack[bp] >= lv and lv > &stack[sp]) or lv == &retval);
    assert(rv1 and rv2);

    if(rv1->type != number_m or rv2->type != number_m){
        avm_error("Not a number");
        executionFinished = 1;
        return;
    }

    arithmetic_func_t op = comparisonFuncs[instr.op - add_v];
    avm_memcellclear(lv);
    lv->type = number_m;
    lv->data.numVal = op(rv1->data.numVal, rv2->data.numVal);
}

