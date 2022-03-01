/* Flex options */
%option yylineno
%option noyywrap

%{
    #include <stdlib.h>
    #include <stdio.h>
    
    #define YY_DECL int alpha_yylex(alpha_token_t *ylval);
%}
/* Flex macros */
digit   [0-9]
alpha   [a-zA-Z]
space   [\r\n \t\v]
id      [a-zA-Z][a-zA-Z_0-9]*
string  \"[^\n"]*\"
comment "//".*

%%

{id}                { yylval.ival = 5; fprintf(stderr, "Recognized id with value: %d | %s\n", yylineno, yytext); }
{string}            { fprintf(stderr, "Recognized string with value: %s\n", yytext); }
{comment}           { fprintf(stderr, "Recognized comment with value: %s\n", yytext); }
{digit}+            { return NUM; fprintf(stderr, "Recognized INTCONST with value: %s\n", yytext); }
{digit}*.{digit}+   { fprintf(stderr, "Recognized FLOAT with value: %s\n", yytext); }
{space}             { ; }
.                   { fprintf(stderr, "Unrecognized token: %s\n", yytext); }

%%

// int yywrap() {
//     return 1;
// }

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

    yylex();
    printf("%d\n", yylval.ival);
    return 0;
}
