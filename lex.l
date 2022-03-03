/* Flex options */
%option yylineno

%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <assert.h>
    #include "lex.h"
	#ifdef DEBUG
	#	define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
	#else
	#	define DPRINTF(...)
	#endif

    #define YY_DECL int alpha_yylex(struct alpha_token_t *ylval)

	void add_token(struct alpha_token_t *ylval, enum token_category category) {
		static int token_cnt = 1;
		
		if(ylval == NULL) { // empty list
			assert(token_cnt == 1); // assert thats the first token processed
			ylval = malloc(sizeof(struct alpha_token_t)); // allocate memory for head
		}

		ylval->line_no = yylineno;
		ylval->no = token_cnt++;
		ylval->text = strdup(yytext);
		ylval->category = category;
	}
%}

/* Flex macros */
digit   [0-9]
alpha   [a-zA-Z]
space   [\r\n \t\v]
id      [a-zA-Z][a-zA-Z_0-9]*
string  \"[^\n"]*\"
comment "//".*
keyword if|else|while|for|function|return|break|continue|and|not|or|local|true|false|nil
operator =|\+\+|-|\*|\/|%|==|!=|\+|--|>|<|>=|<=

%%

{keyword} { 
	DPRINTF("keyword\n");
}

{operator} { 
	DPRINTF("operator\n");
}

{id} {
	DPRINTF("id\n");
}

{string} {
	DPRINTF("string\n");
}

{comment}           { fprintf(stderr, "Recognized comment with value: %s\n", yytext); }
{digit}+            { fprintf(stderr, "Recognized INTCONST with value: %s\n", yytext); }
{digit}*\.{digit}+   { fprintf(stderr, "Recognized FLOAT with value: %s\n", yytext); }
{space}             { ; }
.                   { fprintf(stderr, "Unrecognized token: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if(argc > 1){
        if(!(yyin = fopen(argv[1], "r"))){
            fprintf(stderr, "Cannot open file : %s\n", argv[1]);
            return 1;
        }
    }
    else{
        yyin = stdin;
    }

	struct alpha_token_t *list = NULL;
    alpha_yylex(list);
    return 0;
}
