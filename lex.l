/* Flex options */
%option yylineno

%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
    #include "lex.h"
	
	// utility macros
	#ifdef DEBUG
	#	define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
	#else
	#	define DPRINTF(...)
	#endif
	#define STREQ(a, b) strcmp(a, b) == 0
	#define ARRSIZE(arr) sizeof(arr) / sizeof(arr[0])

    #define YY_DECL int alpha_yylex(alpha_token_t *ylval)
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
	add_token(ylval, KEYWORD);
}

{operator} { 
	DPRINTF("operator\n");
	add_token(ylval, OPERATOR);
}

{id} {
	DPRINTF("id\n");
	add_token(ylval, IDENTIFIER);
}

{string} {
	DPRINTF("string\n");
	add_token(ylval, STRING);
}

{comment} { 
	DPRINTF("comment\n");
	add_token(ylval, COMMENT);
}

{digit}+ {
	DPRINTF("intconst\n");
	add_token(ylval, INTCONST);
}

{digit}*\.{digit}+ {
	DPRINTF("realconst\n");
	add_token(ylval, REALCONST);
}

{space} {
	;
}

. {
	fprintf(stderr, "%d: Unrecognized token %s.", yylineno, yytext);
	exit(0);
}

%%

int yywrap() {
    return 1;
}

static char *operator_enum_map[] = {
	"=",
	"+",
	"-",
	"*",
	"/",
	"%",
	"==",
	"!=",
	"++",
	"--",
	">",
	"<"
	">=",
	"<="
};

static char *keyword_enum_map[] = {
	"if",
	"else",
	"while",
	"for",
	"function",
	"return",
	"break",
	"continue",
	"and",
	"not",
	"or",
	"local",
	"true",
	"false",
	"nil"
};

static char *punct_enum_map[] = {
	"{",
	"}",
	"[",
	"]",
	"(",
	")",
	";",
	",",
	":",
	"::",
	".",
	".."
};

int str_to_enum(char **hay, size_t sz, char *needle) {
	for(size_t i = 0; i < sz; ++i) {
		if(STREQ(hay[i], needle)) return i;	
	}
	assert(false); // if we don't find the given string in the table, there is a logic error
}

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

	switch(category){
		case INTCONST:
			ylval->content.ival = atoi(yytext);
			break;
		case REALCONST:
			ylval->content.fval = atof(yytext);
			break;
		case STRING:
			ylval->content.sval = strdup(yytext);
			break;
		case IDENTIFIER:
			ylval->content.sval = strdup(yytext);
			break;
		case OPERATOR:
			ylval->content.oval = (enum operator_type) str_to_enum(operator_enum_map, ARRSIZE(operator_enum_map), yytext);
			break;
		case PUNCTUATION:
			ylval->content.pval = (enum punct_type) str_to_enum(punct_enum_map, ARRSIZE(punct_enum_map), yytext);
			break;
		case KEYWORD:
			ylval->content.kval = (enum keyword_type) str_to_enum(keyword_enum_map, ARRSIZE(keyword_enum_map), yytext);
			break;
		case COMMENT:
			break;
		default:
			assert(false); // if category is nothing from the above, there is logic error
	}
}
