/* Flex options */
%option yylineno

%{
    #include <stdlib.h>
    #include <stdio.h>
	#include <string.h>
	#include <assert.h>
	#include <stdbool.h>
    #include "../include/parser.h"
	#include "../include/lex.h"
	
	#ifdef __linux__
	#	define FILE_EOF '\0'
	#else
	#	define FILE_EOF EOF
	#endif
	
	// utility macros
	#ifdef DEBUG
	#	define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
	#else
	#	define DPRINTF(...)
	#endif

	#define ERROR(message) \
		fprintf(stderr, "%d : %s : %s\n", yylineno, yytext, message); \
		exit(0);
%}

/* Flex macros */
digit   [0-9]
space   [\r\n \t\v]
id      [a-zA-Z][a-zA-Z_0-9]*
string  \"[^\"\\]*(\\.[^\"\\]*)*\"
comment "//".*

%%

"if"            {return IF;}
"else"          {return ELSE;}
"while"         {return WHILE;}
"for"           {return FOR;}
"function"      {return FUNCTION;}
"return"        {return RETURN;}
"break"         {return BREAK;}
"continue"      {return CONTINUE;}
"and"           {return AND;}
"not"           {return NOT;}
"or"            {return OR;}
"local"         {return LOCAL;}
"true"          {return TRUE;}
"false"         {return FALSE;}
"nil"           {return NIL;}
"="             {return ASSIGN;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return MUL;}
"/"             {return DIV;}
"%"             {return MOD;}
"=="            {return EQUAL;}
"!="            {return NEQUAL;}
"++"            {return INC;}
"--"            {return DEC;}
">"             {return GT;}
"<"             {return LT;}
">="            {return GET;}
"<="            {return LET;}
"{"             {return CURLY_OPEN;}
"}"             {return CURLY_CLOSED;}
"["             {return SQUARE_OPEN;}
"]"             {return SQUARE_CLOSED;}
"("             {return PAR_OPEN;}
")"             {return PAR_CLOSED;}
";"             {return SEMI_COLON;}
","             {return COMMA;}
":"             {return COLON;}
"::"            {return DOUBLE_COLON;}
"."             {return DOT;}
".."            {return DOUBLE_DOT;}


"/\*" {
	block_comments();
}

{id} {
	yylval.sval = strdup(yytext);
	return IDENT;
}

{string} {
	yylval.sval = process_string(strdup(yytext));
	return STRING;
}

{comment} {}

{digit}+ {
	sscanf(yytext, "%lf", &yylval.nval);
	return NUM;
}

{digit}*\.{digit}+ {
	sscanf(yytext, "%lf", &yylval.nval);
	return NUM;
}

{space} {}

. {
	ERROR("Unrecognized token");
}

%%

int yywrap() {
    return 1;
}

char* process_string(char* string){
    size_t len = strlen(string);
	char *buffer = malloc(len);

	string[len-1] = '\0'; // ignore closing "
	
    int i = 1; // start from 1 to ignore opening "
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
	buffer[j] = '\0';
    return buffer;
}


void block_comments(){
	char curr, next;
	while((curr = input()) != FILE_EOF){
		switch(curr) {
		case '*':
			next = input();
			if(next == '/'){
				return;	
			}
			else {
				unput(next);
			}
			break;
		case '/':
			next = input();
			if(next == '*'){
				block_comments();
			}
			else {
				unput(next);
			}
			break;
		default:
			continue;
		}
	}
	ERROR("Unclosed comment.\n");	
}
