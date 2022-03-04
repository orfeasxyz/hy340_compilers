#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

// enum to string mapping for printing
#define X(val) #val,

char *token_category_str[] = {
	TOKEN_CATEGORIES
	"DUMMY_CATEGORY"
};

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

void display_token(alpha_token_t*);

int main(int argc, char* argv[]){
    // File checking, arguments should always be either 2 or 3 (in case of optional output file)
	if(argc > 3) {
		fprintf(stderr, "Invalid argument format\nUsage: %s <input_file> (<output_file>)", argv[0]);
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
	if(argc == 3 && !freopen(argv[3], "w", stdout)) {
		fprintf(stderr, "There was an error reading the output file, make sure it exists and the path is written correnctly");
		exit(0);
	}

    alpha_token_t *alpha_token = (alpha_token_t*) malloc(sizeof(alpha_token_t));
    alpha_yylex(alpha_token);

    while(alpha_token){
        display_token(alpha_token);
        alpha_token = alpha_token->next;
    }

    return 0;
}

void keyword_printer(alpha_token_t* token){
    printf("%s <- enumerated", keyword_type_str[token->content.kval]);
}

void operator_printer(alpha_token_t* token){
    printf("%s <- enumerated", operator_type_str[token->content.oval]);
}

void punctuation_printer(alpha_token_t* token){
    printf("%s <- enumerated", punct_type_str[token->content.pval]);
}

void comment_printer(alpha_token_t* token){
	printf("%s <- enumerated", comment_type_str[token->content.cval]);
}
void string_printer(alpha_token_t* token){
    printf("\"%s\" <- char*", token->content.sval);
}

void int_printer(alpha_token_t* token){
    printf("%d <- int", token->content.ival);
}

void float_printer(alpha_token_t* token){
    printf("%f <- real", token->content.fval);
}

void (*printer[8])(alpha_token_t*) = {
	int_printer,
	float_printer,
	string_printer,
	string_printer,
	operator_printer,
	punctuation_printer,
	keyword_printer,
	comment_printer
};
    
void display_token(alpha_token_t* token){
	printf("%d: #%d \"%s\" %s ", token->line_no, token->no, token->text, token_category_str[token->category]);
    printer[token->category](token);
	putchar('\n');
}
