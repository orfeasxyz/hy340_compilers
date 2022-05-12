%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
    #include "../include/symtable.h"
    #include "../include/structs.h"
    #include "../include/stack.h"
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
	int bval;
    double nval;
    char* sval;
	unsigned int func_addr;
	char* lib_addr;
    struct SymbolTableEntry* symval;
    struct Expr* exprval;
}

%token<nval> NUM
%token<sval> IDENT STRING IF ELSE WHILE FOR FUNCTION RETURN BREAK
             CONTINUE AND NOT OR LOCAL TRUE FALSE NIL ASSIGN PLUS
             MINUS MUL DIV MOD EQUAL NEQUAL INC DEC GT LT GET LET
             CURLY_OPEN CURLY_CLOSED SQUARE_OPEN SQUARE_CLOSED
             PAR_OPEN PAR_CLOSED SEMI_COLON COMMA COLON DOUBLE_COLON
             DOT DOUBLE_DOT UMINUS
%type<exprval> funcdef funcprefix
%type<sval> funcname
%type<func_addr> funcbody
%type<exprval> lvalue expression term assignexpr 


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


statements:     statements statement 
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

expression:     assignexpr
                | expression PLUS expression
                | expression MINUS expression
                | expression MUL expression
                | expression DIV expression
                | expression MOD expression
                | expression GT expression
                | expression GET expression
                | expression LT expression
                | expression LET expression
                | expression EQUAL expression
                | expression NEQUAL expression
                | expression AND expression
                | expression OR expression
                | term
                ;

term:           PAR_OPEN expression PAR_CLOSED
                | UMINUS expression
                | NOT expression
                | INC lvalue            {HANDLE_TERM_TO_INC_LVALUE($2, yylineno);}
                | lvalue INC            {HANDLE_TERM_TO_LVALUE_INC($1, yylineno);}
                | DEC lvalue            {HANDLE_TERM_TO_DEC_LVALUE($2, yylineno);}
                | lvalue DEC            {HANDLE_TERM_TO_LVALUE_DEC($1, yylineno);}
                | prim
                ;

assignexpr:     lvalue ASSIGN expression{HANDLE_ASSIGNEXPR_TO_LVALUE_ASSIGN_EXPRESSION($1, yylineno);};

prim:           lvalue                  {HANDLE_PRIM_TO_LVALUE($1, yylineno);}
                | call
                | objectdef
                | PAR_OPEN funcdef PAR_CLOSED
                | const
                ;

lvalue:         IDENT                   {$$ = HANDLE_LVALUE_TO_IDENT($1, yylineno);}
                | LOCAL IDENT           {$$ = HANDLE_LVALUE_TO_LOCAL_IDENT($2, yylineno);}
                | DOUBLE_COLON IDENT    {$$ = HANDLE_LVALUE_TO_GLOBAL_IDENT($2, yylineno);}
                | member                {}
                ;

member:         lvalue DOT IDENT
                | lvalue SQUARE_OPEN expression SQUARE_CLOSED
                | call DOT IDENT
                | call SQUARE_OPEN expression SQUARE_CLOSED
                ;

call:           call PAR_OPEN elist PAR_CLOSED
                | lvalue callsuffix     
                | PAR_OPEN funcdef PAR_CLOSED PAR_OPEN elist PAR_CLOSED
                ;

callsuffix:     normcall
                | methodcall
                ;

normcall:       PAR_OPEN elist PAR_CLOSED;

methodcall:     DOUBLE_DOT IDENT PAR_OPEN elist PAR_CLOSED ;

elist:          expression elist_alt
                |
                ;

elist_alt:      COMMA expression elist_alt
                | 
                ;

objectdef:      SQUARE_OPEN expression SQUARE_CLOSED
                | SQUARE_OPEN expression COMMA elist SQUARE_CLOSED
                | SQUARE_OPEN indexedelem SQUARE_CLOSED
                | SQUARE_OPEN indexedelem COMMA indexed SQUARE_CLOSED
                | SQUARE_OPEN SQUARE_CLOSED
                ;

indexed:        indexedelem indexed_alt
                |
                ;

indexed_alt:    COMMA indexedelem indexed_alt
                |
                ;

indexedelem:    CURLY_OPEN expression COLON expression CURLY_CLOSED ;

block:          CURLY_OPEN {scope++; current_table = SymTable_next(current_table);} statements CURLY_CLOSED {scope--; SymTable_hide(current_table); current_table = SymTable_prev(current_table);};

funcdef:        funcprefix funcargs funcbody {$$ = HANDLE_FUNCDEF($1, $3, yylineno);} ;

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
                    stack_push(functionScopeStack, scope);
                } 
                PAR_CLOSED
                {
                    enterScopeSpace();
                    resetFunctionLocalOffset();
                };

funcname:       IDENT          {$$ = HANDLE_FUNCTION_WITH_NAME($1, yylineno);}
                |              {$$ = HANDLE_FUNCTION_WITHOUT_NAME(yylineno);}
                ;

const:          NUM | STRING | NIL | TRUE | FALSE ;

idlist:         IDENT idlist_alt        {HANDLE_IDLIST_IDENT($1, yylineno);}
                |
                ;

idlist_alt:     COMMA IDENT idlist_alt  {HANDLE_IDLIST_IDENT($2, yylineno);}
                |
                ;

ifstmt:         IF PAR_OPEN expression PAR_CLOSED statement %prec LOWER_THAN_ELSE
                | IF PAR_OPEN expression PAR_CLOSED statement ELSE statement
                ;

whilestmt:      WHILE PAR_OPEN expression PAR_CLOSED statement       

forstmt:        FOR PAR_OPEN elist SEMI_COLON expression SEMI_COLON elist PAR_CLOSED statement ;

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

	yyparse();
    SymTable_print(head);
    return 0;	
}
