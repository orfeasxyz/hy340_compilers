#ifndef LEX_H
#define LEX_H

#include <stdio.h>

/*
// define x-macros for all enum types
#define TOKEN_CATEGORIES \
	X(INTCONST) \
	X(REALCONST) \
	X(STRING) \
	X(IDENTIFIER) \
	X(OPERATOR) \
	X(PUNCTUATION) \
	X(KEYWORD) \
	X(COMMENT)

#define KEYWORD_TYPES \
	X(IF) \
	X(ELSE) \
	X(WHILE) \
	X(FOR) \
	X(FUNCTION) \
	X(RETURN) \
	X(BREAK) \
	X(CONTINUE) \
	X(AND) \
	X(NOT) \
	X(OR) \
	X(LOCAL) \
	X(TRUE) \
	X(FALSE) \
	X(NIL)

#define OPERATOR_TYPES \
	X(ASSIGN) \
	X(PLUS) \
	X(MINUS) \
	X(MUL) \
	X(DIV) \
	X(MOD) \
	X(EQUAL) \
	X(NEQUAL) \
	X(INC) \
	X(DEC) \
	X(GT) \
	X(LT) \
	X(GET) \
	X(LET)

#define PUNCT_TYPES \
	X(CURLY_OPEN) \
	X(CURLY_CLOSED) \
	X(SQUARE_OPEN) \
	X(SQUARE_CLOSED) \
	X(PAR_OPEN) \
	X(PAR_CLOSED) \
	X(SEMI_COLON) \
	X(COMMA) \
	X(COLON) \
	X(DOUBLE_COLON) \
	X(DOT) \
	X(RANGE)

#define COMMENT_TYPES \
	X(BLOCK_COMMENT) \
	X(NESTED_COMMENT) \
	X(LINE_COMMENT)

#define X(val) val,
// add dummy value to complete the expansion of the macro
enum operator_type {
	OPERATOR_TYPES
	DUMMY_OPERATOR 
};

enum punct_type {
	PUNCT_TYPES
	DUMMY_PUNCT
};

enum keyword_type {
	KEYWORD_TYPES
	DUMMY_KEYWORD
};

enum comment_type {
	COMMENT_TYPES
	DUMMY_COMMENT
};

enum token_category {
	TOKEN_CATEGORIES
	DUMMY_TOKEN
};
#undef X

union token_content {
	int ival;
	float fval;
	char *sval;
	enum operator_type	oval;
	enum punct_type		pval;
	enum keyword_type	kval;
	enum comment_type	cval;
};

typedef struct alpha_token_t {
	int line_no;
	int no;
	char *text;
	enum token_category category;
	union token_content content;
	struct alpha_token_t *next;
} alpha_token_t;

void add_token(struct alpha_token_t *ylval, enum token_category category, int line, enum comment_type ctype);

int alpha_yylex(alpha_token_t *ylval);

*/

void block_comments();

char* process_string(char*);

#endif // LEX_H
