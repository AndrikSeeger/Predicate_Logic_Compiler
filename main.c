#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "symboltable.h"
#define DELIM "_"
//#include "formelprinter.h"

//extern FILE *output;

extern FILE *yyin;
FILE *outputFile;

extern int yylex();
extern int yyparse();
extern void print_symbol_entry();

//int yyparse(void);

int main( int argc, char **argv )
{
  ++argv, --argc; /* skip over program name */
  if ( argc > 0 ){
    printf("%s\n", argv[0]);
    yyin = fopen( argv[0], "r" );
    char *result = strcat(strcat(strtok(argv[0], DELIM), DELIM), "outC.pl1");
    outputFile = fopen(result, "w");
    //outputFile = stderr;
  }
  else{
    yyin = stdin;
    outputFile = stderr;
  }
  fprintf(stderr, "\n\n");
  yyparse();
  print_symbol_entry();
  fclose(outputFile);
}
