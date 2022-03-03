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
	#define X(val) #val,
	char *operator_type_str[] = {
		OPERATOR_TYPES
		"DUMMY_COMMENT"
	};

	char *keyword_type_str[] = {
		KEYWORD_TYPES
		"DUMMY_KEYWORD"
	};

	char *punct_type_str[] = {
		PUNCT_TYPES
		"DUMMY_PUNCT"
	};

	char *comment_type_str[] = {
		COMMENT_TYPES
		"DUMMY_COMMENT"
	};
	#undef X
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
		case IDENTIFIER:
			ylval->content.sval = strdup(yytext);
			break;
		case OPERATOR:
			ylval->content.oval = (enum operator_type) str_to_enum(operator_type_str, ARRSIZE(operator_type_str), yytext);
			break;
		case PUNCTUATION:
			ylval->content.pval = (enum punct_type) str_to_enum(punct_type_str, ARRSIZE(punct_type_str), yytext);
			break;
		case KEYWORD:
			ylval->content.kval = (enum keyword_type) str_to_enum(keyword_type_str, ARRSIZE(keyword_type_str), yytext);
			break;
		case COMMENT:
			ylval->content.cval = (enum comment_type) str_to_enum(comment_type_str, ARRSIZE(comment_type_str), yytext);
			break;
		default:
			assert(false); // if category is nothing from the above, there is logic error
	}
}
