%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
    #include "../include/symtable.h" #include "../include/structs.h" #include "../include/stack.h"
	#include "../include/rule_handler.h"
	#include "../include/parser.h"

    int yyerror(char* message);
    int yylex(void);
    
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
%}

// Declarations

%start program

%union {
    unsigned labelval;
    double nval;
    char* sval;
	unsigned int func_addr;
	char* lib_addr;
    struct ForLoopPrefix* forprefixval;
    struct SymbolTableEntry* symval;
    struct Expr* exprval;
    struct Call* callval;
}

%token<nval> NUM
%token<sval> IDENT STRING IF ELSE WHILE FOR FUNCTION RETURN BREAK
             CONTINUE AND NOT OR LOCAL TRUE FALSE NIL ASSIGN PLUS
             MINUS MUL DIV MOD EQUAL NEQUAL INC DEC GT LT GET LET
             CURLY_OPEN CURLY_CLOSED SQUARE_OPEN SQUARE_CLOSED
             PAR_OPEN PAR_CLOSED SEMI_COLON COMMA COLON DOUBLE_COLON
             DOT DOUBLE_DOT UMINUS
%type<symval> funcdef funcprefix 
%type<sval> funcname
%type<func_addr> funcbody
%type<exprval> lvalue expression term assignexpr prim member call 
               objectdef const elist indexed indexedelem objectarg
%type<callval> callsuffix normcall methodcall 
%type<labelval> ifprefix elseprefix whileprefix whileargs M N
%type<forprefixval> forprefix


%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NEQUAL
%nonassoc GT GET LT LET
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%left PLUS MINUS
%left MUL DIV MOD
%right NOT INC DEC
%left DOT DOUBLE_DOT
%left SQUARE_OPEN SQUARE_CLOSED 
%left PAR_OPEN PAR_CLOSED
%left UMINUS

%%

program:        statements ;


statements:     statements {resetTemp();} statement 
                |
                ;

statement:      expression SEMI_COLON
                | ifstmt
                | whilestmt
                | forstmt
                | returnstmt
                | BREAK SEMI_COLON
                | CONTINUE SEMI_COLON
                | block
                | funcdef
                | SEMI_COLON
                ;

expression:     assignexpr                      {$$ = $1;}
                | expression PLUS expression    {$$ = HANDLE_ARITH_OP(add, $1, $3);}
                | expression MINUS expression   {$$ = HANDLE_ARITH_OP(sub, $1, $3);}
                | expression MUL expression     {$$ = HANDLE_ARITH_OP(mul, $1, $3);}
                | expression DIV expression     {$$ = HANDLE_ARITH_OP(mydiv, $1, $3);}
                | expression MOD expression     {$$ = HANDLE_ARITH_OP(mod, $1, $3);}
                | expression GT expression      {$$ = HANDLE_REL_OP(if_greater, $1, $3);}
                | expression GET expression     {$$ = HANDLE_REL_OP(if_geatereq, $1, $3);}
                | expression LT expression      {$$ = HANDLE_REL_OP(if_less, $1, $3);}
                | expression LET expression     {$$ = HANDLE_REL_OP(if_lesseq, $1, $3);}
                | expression EQUAL expression   {$$ = HANDLE_REL_OP(if_eq, $1, $3);}
                | expression NEQUAL expression  {$$ = HANDLE_REL_OP(if_noteq, $1, $3);}
                | expression AND expression     {$$ = HANDLE_BOOL_OP(and, $1, $3);}
                | expression OR expression      {$$ = HANDLE_BOOL_OP(or, $1, $3);}
                | term                          {$$ = $1;}
                ;

term:           PAR_OPEN expression PAR_CLOSED  {$$ = $2;}
                | UMINUS expression             {$$ = HANDLE_TERM_TO_UMINUS_EXPR($2);}
                | NOT expression                {$$ = HANDLE_TERM_TO_NOT_EXPR($2);}
                | INC lvalue                    {$$ = HANDLE_TERM_TO_INC_LVALUE($2, yylineno);}
                | lvalue INC                    {$$ = HANDLE_TERM_TO_LVALUE_INC($1, yylineno);}
                | DEC lvalue                    {HANDLE_TERM_TO_DEC_LVALUE($2, yylineno);}
                | lvalue DEC                    {HANDLE_TERM_TO_LVALUE_DEC($1, yylineno);}
                | prim                          {$$ = $1;}
                ;

assignexpr:     lvalue ASSIGN expression        {HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION($1, $3, yylineno);};

prim:           lvalue                          {HANDLE_PRIM_TO_LVALUE($1, yylineno);}
                | call                          {$$ = $1;}
                | objectdef                     {$$ = $1;}
                | PAR_OPEN funcdef PAR_CLOSED   {$$ = HANDLE_PRIM_TO_FUNCDEF($2);}
                | const                         {$$ = $1;}
                ;   

lvalue:         IDENT                   {$$ = HANDLE_LVALUE_TO_IDENT($1, yylineno);}
                | LOCAL IDENT           {$$ = HANDLE_LVALUE_TO_LOCAL_IDENT($2, yylineno);}
                | DOUBLE_COLON IDENT    {$$ = HANDLE_LVALUE_TO_GLOBAL_IDENT($2, yylineno);}
                | member                {$$ = $1;}
                ;

member:         lvalue DOT IDENT                                {$$ = HANDLE_MEMBER_TO_LVALUE_DOT_IDENT($1, $3);}
                | lvalue SQUARE_OPEN expression SQUARE_CLOSED   {$$ = HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR($1, $3);}
                | call DOT IDENT                                {$$ = HANDLE_MEMBER_TO_LVALUE_DOT_IDENT($1, $3);}
                | call SQUARE_OPEN expression SQUARE_CLOSED     {$$ = HANDLE_MEMBER_TO_LVALUE_SQUARE_EXPR($1, $3);}        
                ;

call:           call PAR_OPEN elist PAR_CLOSED                              {$$ = HANDLE_CALL_ELIST($1, $3);}
                | lvalue callsuffix                                         {$$ = HANDLE_CALL_LVALUE_SUFFIX($1, $2);}
                | PAR_OPEN funcdef PAR_CLOSED PAR_OPEN elist PAR_CLOSED     {$$ = HANDLE_CALL_FUNCDEF_ELIST($2, $5);}
                ;

callsuffix:     normcall        {$$ = $1;}
                | methodcall    {$$ = $1;}
                ;

normcall:       PAR_OPEN elist PAR_CLOSED                      {$$ = HANDLE_NORMCALL($2);};

methodcall:     DOUBLE_DOT IDENT PAR_OPEN elist PAR_CLOSED     {$$ = HANDLE_METHODCALL($2, $4);};

elist:          expression                  {$$ = $1; $$->next = NULL;}
                | expression COMMA elist    {$$ = HANDLE_ELIST_ADD($1, $3);}
				|                           {$$ = (Expr*) 0;}
                ;

objectdef:      SQUARE_OPEN objectarg SQUARE_CLOSED  {$$ = $2;};

objectarg:      elist       {$$ = HANDLE_OBJECTDEF_TO_ELIST($1);}
                | indexed   {$$ = HANDLE_OBJECTDEF_TO_INDEXED($1);}
                ;

indexed:        indexedelem                     {$$ = $1;}
                | indexedelem COMMA indexed     {$$ = HANDLE_INDEXED_ADD($1, $3);}
                ;

indexedelem:    CURLY_OPEN expression COLON expression CURLY_CLOSED {$$ = HANDLE_INDEXELEM($2, $4);};

block:          CURLY_OPEN {scope++; current_table = SymTable_next(current_table);} statements CURLY_CLOSED {scope--; SymTable_hide(current_table); current_table = SymTable_prev(current_table);};

funcdef:        funcprefix
				{
					funcCounter++;
					loopCounterStack = stack_push(loopCounterStack, loopCounter);
					loopCounter = 0;
				}
				funcargs
				funcbody
				{
					$$ = HANDLE_FUNCDEF($1, $4, yylineno);
					funcCounter--;
					loopCounter = stack_top(loopCounterStack);
					loopCounterStack = stack_pop(loopCounterStack);
				};

funcbody:       block {
                    $$ = currScopeOffset();
                    exitScopeSpace();
                };

funcprefix:     FUNCTION funcname {$$ = HANDLE_FUNCPREFIX($2, yylineno);};

funcargs:       PAR_OPEN 
                {
                    scope++; 
                    current_table = SymTable_next(current_table);
                } 
                idlist 
                {
                    scope--;
                    current_table = SymTable_prev(current_table); 
                    functionScopeStack = stack_push(functionScopeStack, scope);
                } 
                PAR_CLOSED
                {
                    enterScopeSpace();
                    resetFunctionLocalOffset();
                };

funcname:       IDENT          {$$ = HANDLE_FUNCTION_WITH_NAME($1, yylineno);}
                |              {$$ = HANDLE_FUNCTION_WITHOUT_NAME(yylineno);}
                ;

const:          NUM         {$$ = newExprConstNum($1);}
                | STRING    {$$ = newExprConstString($1);}
                | NIL       {$$ = (struct Expr*) 0;}
                | TRUE      {$$ = newExprConstBool(1);}
                | FALSE     {$$ = newExprConstBool(0);}
                ;

idlist:         IDENT                   {HANDLE_IDLIST_IDENT($1, yylineno);}
                | IDENT COMMA idlist    {HANDLE_IDLIST_IDENT($1, yylineno);} 
                |
                ;

ifprefix:       IF PAR_OPEN expression PAR_CLOSED   {$$ = HANDLE_IFPREFIX($3);}

elseprefix:     ELSE                                {$$ = HANDLE_ELSEPREFIX(yylineno);}

ifstmt:         ifprefix statement {patchLabel($1, nextQuadLabel());} %prec LOWER_THAN_ELSE
                | ifprefix statement elseprefix statement {
                    patchLabel($1, $3 + 1);
                    patchLabel($3, nextQuadLabel());
                }
                ;

whileprefix:    WHILE                               {$$ = nextQuadLabel(); loopCounter++;};

whileargs:      PAR_OPEN expression PAR_CLOSED      {$$ = HANDLE_WHILEARGS($2);}

whilestmt:      whileprefix whileargs statement		{HANDLE_WHILE($1, $2); loopCounter--;}

N:              {$$ = nextQuadLabel(); emit(jump, NULL, NULL, NULL, 0, yylineno);};
M:              {$$ = nextQuadLabel();};

forprefix:      FOR {loopCounter++;} PAR_OPEN elist SEMI_COLON M expression SEMI_COLON {$$ = HANDLE_FORPREFIX($6, $7); loopCounter--;};

forstmt:        forprefix N elist PAR_CLOSED N statement N {HANDLE_FORSTMT($1, $2, $5, $7);};

returnstmt:     RETURN SEMI_COLON
                | RETURN expression SEMI_COLON
                ;

%%

int yyerror(char *message){
    printf("Error on line %d: %s\n", yylineno, message);
    return -1;
}



int main(int argc, char **argv) {
    head = SymTable_new();
    current_table = head;

    libFunc(head, "print");
    libFunc(head, "input");
    libFunc(head, "objectmemberkeys");
    libFunc(head, "objecttotalmembers");
    libFunc(head, "objectcopy");
    libFunc(head, "totalarguments");
    libFunc(head, "argument");
    libFunc(head, "typeof");
    libFunc(head, "strtonum");
    libFunc(head, "sqrt");
    libFunc(head, "cos");
    libFunc(head, "sin");

	if(argc > 3) {
		fprintf(stderr, "Invalid argument format\nUsage: %s <input_file> [<output_file>]", argv[0]);
		exit(0);
	}

    if(argc == 1) {
		yyin = stdin;
    }
	else {
		if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "There was an error reading the input file, make sure it exists and the path is written correnctly");
            exit(0);
        }
	}

	// If an output file was given, redirect what would be printed in stdout to that file
	if(argc == 3 && !freopen(argv[2], "w", stdout)) {
		fprintf(stderr, "There was an error reading the output file, make sure it exists and the path is written correnctly");
		exit(0);
	}

	FILE *fptr = fopen(argv[1], "r");
	char c;

	printf("Source: \n");
	c = fgetc(fptr);
    while (c != EOF) {
        printf ("%c", c);
        c = fgetc(fptr);
	}
	printf("\n");

	yyparse();
    SymTable_print(head);
    printQuads();
    return 0;	
}
