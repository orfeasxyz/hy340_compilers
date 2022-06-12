#include "../include/structs.h"
#include "../include/target.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;

typedef struct return_list_s{
    unsigned line;
    struct return_list_s* next;
} return_list_t;

typedef struct func_symbol_s{
    SymbolTableEntry *func;
    struct return_list_s* returnList;
} func_symbol_t;

typedef struct func_stack_s{
    struct func_symbol_s *entry;
    struct func_stack_s *next;
} func_stack_t;

static func_stack_t *__func_top = NULL;

static struct func_symbol_s* makeFuncSymbol(SymbolTableEntry *func){
    struct func_symbol_s *new = malloc(sizeof(struct func_symbol_s));
    new->func = func;
    new->returnList = 0;
    return new;
}

static void func_push(SymbolTableEntry *entry) {
    func_stack_t *new = malloc(sizeof(struct func_stack_s));
    new->entry = makeFuncSymbol(entry);
    new->next  = __func_top;
    __func_top = new;
}

static struct func_symbol_s* func_top() {
    assert(__func_top);
    return __func_top->entry;
}


static void append(func_symbol_t* entry, unsigned index);

static void func_pop() {
    assert(__func_top);
    func_stack_t *temp = __func_top;
    __func_top = __func_top->next;
    free(temp->entry);
    free(temp);
}

void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
    incomplete_jump* ij = (incomplete_jump*) malloc(sizeof(incomplete_jump));
    ij->instrNo = instrNo;
    ij->iaddress = iaddress;
    ij->next = ij_head;
    ij_head = ij;
    ij_total++;
}

static unsigned i;


unsigned currProcessedQuad() {
    return i;
}

instruction*	instructions = (instruction*) 0;
unsigned	total_instructions = 0;
unsigned	currInstruction = 0;

void expand_instruction(){
    assert(total_instructions == currInstruction);
    instruction *p = calloc(1, NEW_INSTRUCTION_SIZE);
    if (instructions) {
        memcpy(p, instructions, CURR_INSTRUCTION_SIZE);
        free(instructions);
    }
    instructions = p;
    total_instructions += EXPAND_INSTRUCTION_SIZE;
}

double* numConsts = (double*) 0;
unsigned totalNumConsts = 0;
unsigned currNumConsts = 0;
void expand_numconst(){
    assert(totalNumConsts == currNumConsts);
    double *p = calloc(1, NEW_NUMCONST_SIZE);
    if (numConsts) {
        memcpy(p, numConsts, CURR_NUMCONST_SIZE);
        free(numConsts);
    }
    numConsts = p;
    totalNumConsts += EXPAND_NUMCONST_SIZE;
}

unsigned consts_newnumber(double n){
    unsigned address;
    if (currNumConsts == totalNumConsts) expand_numconst();

    // Check if the number is already in the table
    for (address = 0; address < currNumConsts; address++) {
        if (numConsts[address] == n) return address;
    }

    address = currNumConsts;
    numConsts[currNumConsts++] = n;
    return address;
}

char** strConsts = (char**) 0;
unsigned totalStrConsts = 0;
unsigned currStrConsts = 0;
void expand_strconst(){
    assert(totalStrConsts == currStrConsts);
    char **p = calloc(1, NEW_STRCONST_SIZE);
    if (strConsts) {
        memcpy(p, strConsts, CURR_STRCONST_SIZE);
        free(strConsts);
    }
    strConsts = p;
    totalStrConsts += EXPAND_STRCONST_SIZE;
}

unsigned consts_newstring(char* s){
    unsigned address;
    if (currStrConsts == totalStrConsts) expand_strconst();

    // Check if the string is already in the table
    for (address = 0; address < currStrConsts; address++) if (strcmp(strConsts[address], s) == 0) return address;

    address = currStrConsts;
    strConsts[currStrConsts++] = (char*)strdup(s);
    return address;
}

char** nameLibfuncs = (char**) 0;
unsigned totalNameLibfuncs = 0;
unsigned currNameLibfuncs = 0;
void expand_namelibfuncs(){
    assert(totalNameLibfuncs == currNameLibfuncs);
    char **p = calloc(1, NEW_NAMELIBFUNCS_SIZE);
    if (nameLibfuncs) {
        memcpy(p, nameLibfuncs, CURR_NAMELIBFUNCS_SIZE);
        free(nameLibfuncs);
    }
    nameLibfuncs = p;
    totalNameLibfuncs += EXPAND_NAMELIBFUNCS_SIZE;
}

unsigned libfuncs_newused(char* name){
    unsigned i, address;
    if (currNameLibfuncs == totalNameLibfuncs) expand_namelibfuncs();
    for(i=0; i<currNameLibfuncs; i++)  if (strcmp(nameLibfuncs[i], name) == 0) return i;

    // Check if the string is already in the table
    for(address=0; address<currNameLibfuncs; address++) if (strcmp(nameLibfuncs[address], name) == 0) return address;

    address = currNameLibfuncs;
    nameLibfuncs[currNameLibfuncs++] = (char*)strdup(name);
    return address;
}

userfunc* userFuncs = (userfunc*) 0;
unsigned totalUserFuncs = 0;
unsigned currUserFuncs = 0;
void expand_userFuncs(){
    assert(totalUserFuncs == currUserFuncs);
    userfunc* p = calloc(1, NEW_USERFUNCS_SIZE);
    if (userFuncs) {
        memcpy(p, userFuncs, CURR_USERFUNCS_SIZE);
        free(userFuncs);
    }
    userFuncs = p;
    totalUserFuncs += EXPAND_USERFUNCS_SIZE;
}

unsigned userfuncs_newfunc(SymbolTableEntry *func){
    unsigned address, i;
    if (currUserFuncs == totalUserFuncs) expand_userFuncs();
    address = currUserFuncs;
    for(i = 0; i < currUserFuncs; i++){
        if (userFuncs[i].address == func->iadress)
           return i;
    }
    userfunc* newFunc = userFuncs + currUserFuncs++;
    newFunc->address =  func->iadress;
    newFunc->localSize = func->totalLocals;
    newFunc->id = (char*)strdup(func->name);
    return address;
}


unsigned nextInstructionLabel(void){
    return currInstruction;
}

void emit_instruction(instruction inst){
    // If the vector of quad is full, expand length
    if (currInstruction == total_instructions) {
        expand_instruction();
    }

    // Consturct new quad
    instruction* p = instructions + currInstruction++;
    *p = inst;
}

void make_operand(Expr* e, vmarg* arg){
    if(!e) return;
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithmexpr_e:
        case boolexpr_e:
        case assignexpr_e:
        case newtable_e: {
            arg->val = e->sym->offset;

            switch(e->sym->space){
                case programvar:    arg->type = global_a; break;
                case functionlocal: arg->type = local_a;  break;
                case formalarg:     arg->type = formal_a; break;
                default:            assert(0);
            }

            break;
        }
        case constbool_e: {
            arg->val = e->boolConst;
            arg->type = bool_a;
            break;
        }
        case conststring_e: {
            arg->val = consts_newstring(e->strConst);
            arg->type = string_a;
            break;
        }
        case constnum_e: {
            arg->val = consts_newnumber(e->numConst);
            arg->type = number_a;
            break;
        }
        case nil_e: {
            arg->type = nil_a;
            break;
        }
        case programfunc_e: {
            arg->val = userfuncs_newfunc(e->sym);
            arg->type = userfunc_a;
            break;
        }
        case libraryfunc_e: {
            arg->val = libfuncs_newused(e->sym->name);
            arg->type = libfunc_a;
            break;
        }
        default: assert(0);
    }
}

void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned char val){
    arg->val = val;
    arg->type = bool_a;
}

void make_revaloperand(vmarg* arg){
    arg->type = retval_a;
}

void reset_operand(vmarg* arg){
    arg = (vmarg*) 0;
}

void generate(vmopcode op, quad* q){
    instruction inst;
    inst.op = op;
    make_operand(q->result, &inst.result);
    make_operand(q->arg1, &inst.arg1);
    make_operand(q->arg2, &inst.arg2);
    inst.srcLine = q->line;
    q->taddress = nextInstructionLabel();
    emit_instruction(inst);
}

void generate_relational(vmopcode op, quad* q){
    instruction inst;
    inst.op = op;
    make_operand(q->arg1, &inst.arg1);
    make_operand(q->arg2, &inst.arg2);
    
    inst.result.type = label_a;
    if (q->label < currProcessedQuad()){
        inst.result.val = quads[q->label].taddress;
    } else {
        add_incomplete_jump(nextInstructionLabel(), q->label);    
    }

    q->taddress = nextInstructionLabel();
    emit_instruction(inst);
}

void generate_ADD(quad* q){
    generate(add_v, q);
}

void generate_SUB(quad* q){
    generate(sub_v, q);
}

void generate_MUL(quad* q){
    generate(mul_v, q);
}

void generate_DIV(quad* q){
    generate(div_v, q);
}

void generate_MOD(quad* q){
    generate(mod_v, q);
}

void generate_NEWTABLE(quad* q){
    generate(newtable_v, q);
}

void generate_TABLEGETELEM(quad* q){
    generate(tablegetelem_v, q);
}

void generate_TABLESETELEM(quad* q){
    generate(tablesetelem_v, q);
}

void generate_ASSIGN(quad* q){
    generate(assign_v, q);
}

void generate_NOP(quad* q){
    instruction inst;
    inst.op = nop_v;
    emit_instruction(inst);
}

void generate_JUMP(quad* q){
    generate_relational(jump_v, q);
}

void generate_IF_EQ(quad* q){
    generate_relational(jeq_v, q);
}

void generate_IF_NOTEQ(quad* q){
    generate_relational(jne_v, q);
}

void generate_IF_GREATER(quad* q){
    generate_relational(jgt_v, q);
}

void generate_IF_GREATEREQ(quad* q){
    generate_relational(jge_v, q);
}

void generate_IF_LESS(quad* q){
    generate_relational(jlt_v, q);
}

void generate_IF_LESSEQ(quad* q){
    generate_relational(jle_v, q);
}

void generate_NOT(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;

    inst.op = jeq_v;
    make_operand(q->arg1, &inst.arg1);
    make_booloperand(&inst.arg2, 0);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 3;
    emit_instruction(inst);

    inst.op = assign_v;
    make_revaloperand(&inst.result);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);

    inst.op = jump_v;
    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 2;
    emit_instruction(inst);

    inst.op = assign_v;
    make_booloperand(&inst.arg1, 1);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);
}

void generate_OR(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;

    inst.op = jeq_v;
    make_operand(q->arg1, &inst.arg1);
    make_booloperand(&inst.arg2, 1);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 4;
    emit_instruction(inst);

    make_operand(q->arg2, &inst.arg1);
    inst.result.val = nextInstructionLabel() + 3;
    emit_instruction(inst);

    inst.op = assign_v;
    make_booloperand(&inst.arg1, 0);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);

    inst.op = jump_v;
    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 2;
    emit_instruction(inst);

    inst.op = assign_v;
    make_booloperand(&inst.arg1, 1);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);
}

void generate_AND(quad* q) {
    q->taddress = nextInstructionLabel();
    instruction inst;

    inst.op= jeq_v;
    make_operand(q->arg1, &inst.arg1);
    make_booloperand(&inst.arg2, 1);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 4;
    emit_instruction(inst);

    make_operand(q->arg2, &inst.arg1);
    inst.result.val = nextInstructionLabel() + 3;
    emit_instruction(inst);

    inst.op = assign_v;
    make_booloperand(&inst.arg1, 0);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);
    inst.op = jump_v;

    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    inst.result.type = label_a;
    inst.result.val = nextInstructionLabel() + 2;
    emit_instruction(inst);

    inst.op = assign_v;
    make_booloperand(&inst.arg1, 1);
    reset_operand(&inst.arg2);
    make_operand(q->result, &inst.result);
    emit_instruction(inst);
}

void generate_PARAM(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;
    inst.op = pusharg_v;
    make_operand(q->arg1, &inst.arg1);
    emit_instruction(inst);
}

void generate_CALL(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;
    inst.op = call_v;
    make_operand(q->arg1, &inst.arg1);
    emit_instruction(inst);
}

void generate_GETRETVAL(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;
    inst.op = assign_v;
    make_operand(q->result, &inst.result);
    make_revaloperand(&inst.arg1);
    emit_instruction(inst);
}

void generate_FUNCSTART(quad *quad) {
    SymbolTableEntry *f = quad->result->sym;
    f->iadress = nextInstructionLabel() + 1;
    quad->taddress = nextInstructionLabel() + 1;

    func_push(f);
    instruction inst = {0};

    append(func_top(), nextInstructionLabel());
    inst.op = jump_v;
    inst.result.type = label_a;
    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    reset_operand(&inst.result);
    emit_instruction(inst);

    inst.srcLine   = quad->line;
    inst.op        = funcenter_v;
    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    make_operand(quad->result, &inst.result);
    emit_instruction(inst);
}

void patch_incomplete_jumps() { 
    for (incomplete_jump *ij = ij_head; ij; ij = ij->next) {
        instructions[ij->instrNo].result.type = label_a;
        instructions[ij->instrNo].result.val = 
            (ij->iaddress == nextQuadLabel()) ? 
            nextInstructionLabel() :
            quads[ij->iaddress].taddress;
    }
}

static void backPatchReturnList(return_list_t* rl, unsigned label) {
    for (; rl->next; rl = rl->next) {
        instructions[rl->line].result.val = label;
    }
    instructions[rl->line].result.val = label + 1;
}

static void append(func_symbol_t* entry, unsigned index){
    return_list_t* new_entry = (return_list_t*) malloc(sizeof(return_list_t));
    new_entry->line = index;
    new_entry->next = entry->returnList;
    entry->returnList = new_entry;
}

void generate_FUNCEND(quad *q) {
    func_symbol_t *f = func_top();
    backPatchReturnList(f->returnList, nextInstructionLabel());
    func_pop();

    q->taddress = nextInstructionLabel();
    instruction inst = {0};
    inst.op = funcexit_v;
    make_operand(q->result, &inst.result);
    emit_instruction(inst);
}

void generate_RETURN(quad* q){
    q->taddress = nextInstructionLabel();
    instruction inst;

    inst.op = assign_v;
    make_revaloperand(&inst.result);
    make_operand(q->result, &inst.arg1);
    if(!q->result){
        inst.arg1.type = nil_a;
        inst.arg1.val = 0;
    }
    emit_instruction(inst);

    func_symbol_t* f = func_top();
    append(f, nextInstructionLabel());

    inst.op = jump_v;
    reset_operand(&inst.arg1);
    reset_operand(&inst.arg2);
    inst.result.type = label_a;
    emit_instruction(inst);
}

void generate_UMINUS(quad* q){
    q->arg2 = newExprConstNum(-1);
    generate_MUL(q);
}

generate_func_t generators[] = {
    generate_ASSIGN,       generate_JUMP,      generate_MUL,
    generate_UMINUS,       generate_NOT,       generate_IF_LESSEQ,
    generate_IF_GREATER,   generate_RETURN,    generate_FUNCEND,
    generate_TABLEGETELEM, generate_ADD,       generate_DIV,
    generate_AND,          generate_IF_EQ,     generate_IF_GREATEREQ,
    generate_CALL,         generate_GETRETVAL, generate_NEWTABLE,
    generate_TABLESETELEM, generate_SUB,       generate_MOD,
    generate_OR,           generate_IF_NOTEQ,  generate_IF_LESS,
    generate_PARAM,        generate_FUNCSTART, generate_NOP};



//vmopcode to string_printer
char* vmopcodeToString[] = {
    "assign_v",
    "add_v",
    "sub_v",
    "mul_v",
    "div_v",
    "mod_v",
    "jump_v",
    "jeq_v",
    "jne_v",
    "jle_v",
    "jge_v",
    "jlt_v",
    "jgt_v",
    "call_v",
    "pusharg_v",
    "funcenter_v",
    "funcexit_v",
    "newtable_v",
    "tablegetelem_v",
    "tablesetelem_v",
    "nop_v"
 };

char* vmarg_t_to_string[] = {
    "label_a",
    "global_a",
    "formal_a",
    "local_a",
    "number_a",
    "string_a",
    "bool_a",
    "nil_a",
    "userfunc_a",
    "libfunc_a",
    "retval_a"
};

void print_vmarg(vmarg arg){
    fprintf(stdout," [%s: %d ] ", vmarg_t_to_string[arg.type], arg.val);
}

void print_target() {
    int i;
    instruction inst;
    for(i = 0; i < currInstruction; i++) {
        inst = instructions[i];
        printf("%d: %s ", i, vmopcodeToString[inst.op]);
        switch(inst.op) {
            case jump_v:
            case funcenter_v:
            case funcexit_v:
                print_vmarg(inst.result);
                break;
            case pusharg_v:
            case call_v:
                print_vmarg(inst.arg1);
                break;
            case newtable_v:
                print_vmarg(inst.result);
                break;
            case assign_v:
                print_vmarg(inst.result);
                print_vmarg(inst.arg1);
                break;
            default:
                print_vmarg(inst.result);
                print_vmarg(inst.arg1);
                print_vmarg(inst.arg2);
        }
        printf("\n");
    }
}

void print_arrays(){
    int i;
    printf("Num Consts:\n");
    for(i=0; i<currNumConsts; i++){
        printf("%d: %f\n", i, numConsts[i]);
    }
    printf("Str Consts:\n");
    for(i=0; i<currStrConsts; i++){
        printf("%d: %s\n", i, strConsts[i]);
    }
    printf("User Funcs:\n");
    for(i=0; i<currUserFuncs; i++){
        printf("%d: Name: %s Address: %d\n", i, userFuncs[i].id, userFuncs[i].address);
    }
    printf("Lib Funcs:\n");
    for(i=0; i<currNameLibfuncs; i++){
        printf("%d: Name: %s\n", i, nameLibfuncs[i]);
    }

}

void generate_all(void){
    for(i = 1; i < nextQuadLabel(); i++) (*generators[quads[i].op])(quads + i);
    patch_incomplete_jumps();
    print_arrays();
    printf("\n\n");
    print_target();
}