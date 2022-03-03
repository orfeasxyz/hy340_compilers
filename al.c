#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

// enum to string mapping for printing
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

void display_token(alpha_token_t *token) {
}

int main(int argc, char* argv[]){
    FILE* input_file; 
    alpha_token_t token;

    // File checking, arguments should always be either 2 or 3 (in case of optional output file)
    if(argc == 1 || argc > 3){
        printf("Invalid argument format\nUsage: %s <input_file> (<output_file>)", argv[0]);
        exit(0);
    } else {
        if(!(input_file = fopen(argv[1], "r"))){
            printf("There was an error reading the input file, make sure it exists and the path is written correnctly");
            exit(0);
        }

        // If an output file was given, redirect what would be printed in stdout to that file
        if(argc == 3 && !freopen(argv[3], "w", stdout)) {
            printf("There was an error reading the output file, make sure it exists and the path is written correnctly");
            exit(0);
        }
    }

    alpha_token_t *alpha_token = (alpha_token_t*) malloc(sizeof(alpha_token_t));

    alpha_yylex(alpha_token);

    while(alpha_token){
        display_token(alpha_token);
        alpha_token = alpha_token->next;
    }

    return 0;
}
