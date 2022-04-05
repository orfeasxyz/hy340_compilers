%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
    #include "symtable.h"
    #include "structs.h"

    int yyerror(char* message);
    int yylex(void);
    
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;

    SymTable_T head;
    SymTable_T current_table;

    int scope = 0;
%}

// Declarations

%start program

%union {
    double nval;
    char* sval;
    struct SymbolTableEntry* exprval;
}

%token<nval> NUM
%token<sval> IDENT STRING IF ELSE WHILE FOR FUNCTION RETURN BREAK
             CONTINUE AND NOT OR LOCAL TRUE FALSE NIL ASSIGN PLUS
             MINUS MUL DIV MOD EQUAL NEQUAL INC DEC GT LT GET LET
             CURLY_OPEN CURLY_CLOSED SQUARE_OPEN SQUARE_CLOSED
             PAR_OPEN PAR_CLOSED SEMI_COLON COMMA COLON DOUBLE_COLON
             DOT DOUBLE_DOT UMINUS
%type<exprval> lvalue


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
                | INC lvalue
                | lvalue INC
                | DEC lvalue
                | lvalue DEC
                | prim
                ;
    
assignexpr:     lvalue ASSIGN expression ;

prim:           lvalue
                | call
                | objectdef
                | PAR_OPEN funcdef PAR_CLOSED
                | const
                ;

lvalue:         IDENT
                | LOCAL IDENT
                | DOUBLE_COLON IDENT
                | member
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

block:          CURLY_OPEN statements CURLY_CLOSED;

funcdef:        FUNCTION PAR_OPEN idlist PAR_CLOSED block
                | FUNCTION IDENT PAR_OPEN idlist PAR_CLOSED block
                ;

const:          NUM | STRING | NIL | TRUE | FALSE ;

idlist:         IDENT idlist_alt
                |
                ;

idlist_alt:     COMMA IDENT idlist_alt
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
    printf("Error: %s\n", message);
    return -1;
}

int main(int argc, char **argv) {
	return 0;
}
