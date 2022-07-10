%option noyywrap

%{
    #include <stdlib.h>
    #include "parser.h"
    extern int yylex();
    extern void yyerror(char*);
%}

LETTER [a-zA-Z]
COMMENT \/\*.*\*\/
DECLARE DECLARE
PREDICATE PREDICATE
FUNCTION FUNCTION
VARIABLE VARIABLE
TRUE TRUE
FALSE FALSE
COLON :
SEMICOLON ;
COMMA \,
ROUNDBR_S \(
ROUNDBR_E \)
SQUAREBR_S \[
SQUAREBR_E \]
BIJUNCTION <->
IMPLICATION ->
OR \|
AND \&
NOT \~
ALLQUANTOR ALL
EXISTENZQUANTOR EXIST
NUMBER [0-9]+
IDENT [a-zA-Z][a-zA-Z0-9_]*
INTEGER int
ANYTHING .

%%
[ \t\n\r] ;
{COMMENT} {fprintf(stderr, "LEX: COMMENT: %s\n\n", yytext);}
{DECLARE} {
          fprintf(stderr, "LEX: KEY: DECLARE\n");
          return(DECLARE);}
{PREDICATE} {
            fprintf(stderr, "LEX: KEY: PREDICATE\n");
            return(PREDICATE);}
{FUNCTION} {
            fprintf(stderr, "LEX: KEY: FUNCTION\n");
            return(FUNCTION);}
{VARIABLE} {
            fprintf(stderr, "LEX: KEY: VARIABLE\n");
            return(VARIABLE);}
{TRUE} {
        fprintf(stderr, "LEX: KEY: TRUE\n");
        return(TRUE);}
{FALSE} {
        fprintf(stderr, "LEX: KEY: FALSE\n");
        return(FALSE);}
{COLON} {
        fprintf(stderr, "LEX: KEY: COLON\n");
        return(COLON);}
{SEMICOLON} {
            fprintf(stderr, "LEX: KEY: SEMICOLON\n");
            return(SEMICOLON);}
{COMMA} {
        fprintf(stderr, "LEX: KEY: COMMA\n");
        return(COMMA);}
{ROUNDBR_S} {
            fprintf(stderr, "LEX: KEY: ROUNDBR_S\n");
            return(ROUNDBR_S);}
{ROUNDBR_E} {
            fprintf(stderr, "LEX: KEY: ROUNDBR_E\n");
            return(ROUNDBR_E);}
{SQUAREBR_S} {
              fprintf(stderr, "LEX: KEY: SQUAREBR_S\n");
              return(SQUAREBR_S);}
{SQUAREBR_E} {
              fprintf(stderr, "LEX: KEY: SQUAREBR_E\n");
              return(SQUAREBR_E);}
{BIJUNCTION} {
              fprintf(stderr, "LEX: KEY: BIJUNCTION\n");
              return(BIJUNCTION);}
{IMPLICATION} {
              fprintf(stderr, "LEX: KEY: IMPLICATION\n");
              return(IMPLICATION);}
{ALLQUANTOR} {
              fprintf(stderr, "LEX: KEY: ALLQUANTOR\n");
              return(ALLQUANTOR);}
{EXISTENZQUANTOR} {
                  fprintf(stderr, "LEX: KEY: EXISTENZQUANTOR\n");
                  return(EXISTENZQUANTOR);}
{OR} {
      fprintf(stderr, "LEX: KEY: OR\n");
      return(OR);}
{AND} {
      fprintf(stderr, "LEX: KEY: AND\n");
      return(AND);}
{NOT} {
      fprintf(stderr, "LEX: KEY: NOT\n");
      return(NOT);}
{INTEGER} {
          fprintf(stderr, "LEX: KEY: INTEGER\n");
          return(INTEGER);}
{IDENT} {yylval.string = strdup(yytext);
          fprintf(stderr, "LEX: STRING: %s\n", yylval.string);
          return(IDENT);}
{NUMBER} {int num_int = atoi(yytext);
          fprintf(stderr, "LEX: NUMBER: %d\n", num_int);
          yylval.number = num_int; return(NUMBER);}

. {fprintf(stderr, "NOT RECOGNIZED: %s\n", yytext);}

%%
