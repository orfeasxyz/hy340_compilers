#include "../include/structs.h"
#include "../include/target.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

incomplete_jump* ij_head = (incomplete_jump*) 0;
unsigned ij_total = 0;

typedef struct func_stack_s{
    SymbolTableEntry *entry;
    struct func_stack_s *next;
} func_stack_t;

static func_stack_t *__func_top = NULL;

static void func_push(SymbolTableEntry *entry) {
    func_stack_t *new = malloc(sizeof(struct func_stack_s));
    new->entry  = entry;
    new->next   = __func_top;
    __func_top  = new;
}

static SymbolTableEntry* func_top() {
    assert(__func_top);
    return __func_top->entry;
}

static void func_pop() {
    assert(__func_top);
    func_stack_t *temp = __func_top;
    __func_top = __func_top->next;
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

void generate_all(void){
    for(i = 0; i < total; i++) (*generators[quads[i].op])(quads + i);
}

unsigned currProcessedQuad() {
    return i;
}

instruction*	instructions = (instruction*) 0;
unsigned	total_instructions = 0;
unsigned	currInstruction = 0;

void expand_instruction(){
    assert(total_instructions == currInstruction);
    instruction *p = malloc(NEW_INSTRUCTION_SIZE);
    if (instructions) {
        memcpy(p, instructions, CURR_INSTRUCTION_SIZE);
        free(instructions);
    }
    instructions = p;
    total_instructions += EXPAND_INSTRUCTION_SIZE;
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
    switch(e->type){
        case var_e:
        case tableitem_e:
        case arithmexpr_e:
        case boolexpr_e:
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
            arg->val = e->sym->iadress;
            arg->type = userfunc_a;
            break;
        }
        case libraryfunc_e: {
            arg->val = e->sym->iadress;
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
    f->iadress = nextInstructionLabel();
    quad->taddress = nextInstructionLabel();

    func_push(f);
    instruction instr = {0};
    instr.srcLine   = quad->line;
    instr.op        = funcenter_v;
    make_operand(quad->result, &instr.result);
    make_booloperand(&instr.arg2, 1);
    emit_instruction(instr);
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

void backPatchReturnList() {
    // TODO
}

void generate_FUNCEND(quad *quad) {
    SymbolTableEntry *f = func_top();
    func_pop();
    backPatchReturnList();
}


void generate_RETURN(quad* q){

}

unsigned consts_newstring(char* ss){
    return 0;
}
unsigned consts_newnumber(double dd){
    return 0;
}

/*  TODO

    generate_FUNCEND(quad* q)
    generate_RETURN(quad* q)

*/