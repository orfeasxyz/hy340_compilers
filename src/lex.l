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
	#define ERROR(message) \
		fprintf(stderr, "%d : %s : %s\n", yylineno, yytext, message); \
		exit(0);
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

<<<<<<< HEAD
"/\*" {
	block_comments(ylval, BLOCK_COMMENT);
}

{keyword} { 
	add_token(ylval, KEYWORD, 0, 0);
}

{operator} { 
	add_token(ylval, OPERATOR, 0, 0);
}

{id} {
	add_token(ylval, IDENTIFIER, 0, 0);
}

{string} {
	add_token(ylval, STRING, 0, 0);
}

{comment} { 
	add_token(ylval, COMMENT, 0, 0);
}

{digit}+ {
	add_token(ylval, INTCONST, 0, 0);
}

{digit}*\.{digit}+ {
	add_token(ylval, REALCONST, 0, 0);
=======
{keyword} { 
	add_token(ylval, KEYWORD);
}

{operator} { 
	add_token(ylval, OPERATOR);
}

{id} {
	add_token(ylval, IDENTIFIER);
}

{string} {
	add_token(ylval, STRING);
}

{comment} { 
	add_token(ylval, COMMENT);
}

{digit}+ {
	add_token(ylval, INTCONST);
}

{digit}*\.{digit}+ {
	add_token(ylval, REALCONST);
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb
}

{space} {
	;
<<<<<<< HEAD
	}
=======
}
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb

. {
	ERROR("Unrecognized token");
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

char* process_string(char* string){
    char buffer[1024] = {0};
	string[strlen(string)-1] = '\0';
	
    int i = 1;
	int j = 0;

    while(string[i]){
        if(string[i] == '\\'){
			++i;
            switch(string[i]){
                case '\0': // e.g. "unclosedstring\" <- closing double quote is getting escaped by backslash
                    ERROR("Unclosed string");
                case 'a':
                    buffer[j] = '\a';
                    break;
                case 'b':
                    buffer[j] = '\b';
                    break;
                case 'f':
                    buffer[j] = '\f';
                    break;
                case 'n':
                    buffer[j] = '\n';
                    break;
                case 'r':
                    buffer[j] = '\r';
                    break;
                case 't':
                    buffer[j] = '\t';
                    break;
                case 'v':
                    buffer[j] = '\v';
                    break;
                case '\'':
                    buffer[j] = '\'';
                    break;
                case '"':
                    buffer[j] = '\"';
                    break;
                case '?':
                    buffer[j] = '\?';
                    break;
                case '\\':
                    buffer[j] = '\\';
                    break;
                default:
					ERROR("Unrecognized escape character");
            }
        } else {
            buffer[j] = string[i];
        }
		++j;
        ++i;
    }
    return strdup(buffer);
}

<<<<<<< HEAD
void add_token(alpha_token_t *ylval, enum token_category category, int line, enum comment_type ctype) {
=======
void add_token(alpha_token_t *ylval, enum token_category category) {
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb
	static int token_cnt = 1;
	alpha_token_t *new_token;

	if(token_cnt == 1) { // first token
		new_token = ylval;
	}
	else{ 
		new_token = malloc(sizeof(alpha_token_t));
		alpha_token_t *prev = ylval;
		ylval = ylval->next;
		while(ylval) {
			prev = ylval;
			ylval = ylval->next;
		}
		prev->next = new_token;
	}

	new_token->next = NULL;
<<<<<<< HEAD
	new_token->no = token_cnt++;
	if(!line){
		new_token->text = strdup(yytext);
		new_token->line_no = yylineno;
	}
	else{
		new_token->line_no = line;
		char temp[1024];
		sprintf(temp, "%d - %d", line, yylineno);
		new_token->text = strdup(temp);
	}
=======
	new_token->line_no = yylineno;
	new_token->no = token_cnt++;
	new_token->text = strdup(yytext);
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb
	new_token->category = category;

	switch(category){
		case INTCONST:
			new_token->content.ival = atoi(yytext);
			break;
		case REALCONST:
			new_token->content.fval = atof(yytext);
			break;
		case STRING:
			new_token->content.sval = process_string(yytext);
			break;
		case IDENTIFIER:
			new_token->content.sval = strdup(yytext);
			break;
		case OPERATOR:
			new_token->content.oval = (enum operator_type) str_to_enum(operator_enum_map, ARRSIZE(operator_enum_map), yytext);
			break;
		case PUNCTUATION:
			new_token->content.pval = (enum punct_type) str_to_enum(punct_enum_map, ARRSIZE(punct_enum_map), yytext);
			break;
		case KEYWORD:
			new_token->content.kval = (enum keyword_type) str_to_enum(keyword_enum_map, ARRSIZE(keyword_enum_map), yytext);
			break;
		case COMMENT:
<<<<<<< HEAD
			if(yytext[1] == '/') new_token->content.cval = LINE_COMMENT;
			else new_token->content.cval = ctype;
=======
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb
			break;
		default:
			assert(false); // if category is nothing from the above, there is logic error
	}
}
<<<<<<< HEAD

void block_comments(alpha_token_t *ylval, enum comment_type type){
	char next;
	int starting_line = yylineno;
	int closed = 0;
	while(!closed){
		next = input();
		if(next == -1){
			printf("Not closing comment in line %d", starting_line);
			exit(0);
		}
		char look_ahead;
		if(next == '*'){
			look_ahead = input();
			if(look_ahead == -1){
				printf("Not closing comment in line %d", starting_line);
				exit(0);
			}
			if(look_ahead == '/'){
				add_token(ylval, COMMENT, starting_line, type);
				closed = 1;
			}
		} else if (next == '/'){
			look_ahead = input();
			if(look_ahead == -1){
				printf("Not closing comment in line %d", starting_line);
				exit(0);
			}
			if(look_ahead == '*'){
				block_comments(ylval, NESTED_COMMENT);
			}
		}
	}
}
=======
>>>>>>> d3709d2626e53df5fc5e61abf68a1f3b8862deeb
