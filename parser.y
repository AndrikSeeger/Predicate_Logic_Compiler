%{
    #include <stdio.h>
    #include "symboltable.h"
    #include "syntaxtree.h"

    int yylex();
    extern FILE *yyin;
    void yyerror(const char* msg) {
      fprintf(stderr, "YYError: %s\n", msg);
    }
    FILE *outputFile;
%}

%start prog
%token DECLARE PREDICATE FUNCTION VARIABLE TRUE FALSE COLON SEMICOLON COMMA ROUNDBR_S ROUNDBR_E SQUAREBR_S SQUAREBR_E BIJUNCTION IMPLICATION OR AND NOT ALLQUANTOR EXISTENZQUANTOR NUMBER IDENT INTEGER ARGUMENT

%left BIJUNCTION
%left IMPLICATION
%left OR
%left AND
%left NOT
%left ROUNDBR_S ROUNDBR_E
%left EXISTENZQUANTOR ALLQUANTOR SQUAREBR_S SQUAREBR_E
%left PREDICATE
%left FUNCTION

%type <string> IDENT
%type <number> NUMBER

%union{
  struct node *p;
  char *string;
  int number;
  struct entry *entry;
  int type;
  struct quantor_inf{ //2 Elements required of Union -> Additional Struct
    struct entry *entry;
    int type;
  } q_info;
}

%%
prog: //Types of complete Input Files
    declarations formulaterm SEMICOLON {print_tree_full($<p>2); generate_declarations(outputFile); generate_code($<p>2, outputFile); fprintf(outputFile, ";"); delete_tree($<p>2);}
    | formulaterm SEMICOLON {print_tree_full($<p>2); generate_code($<p>2, outputFile); fprintf(outputFile, ";"); delete_tree($<p>2);}
    | declarations {generate_declarations(outputFile);}
;

declarations:
    declaration declarations
    | declaration
;

declaration:
  DECLARE PREDICATE IDENT COLON NUMBER {fprintf(stderr, "PAR: Declaration: Predicate: -%s-, Arity: %d\n", $3, $5); add_symbol_entry(PREDICATE_TYP_NUM, $5, $3, NULL);}
  | DECLARE FUNCTION IDENT COLON NUMBER {fprintf(stderr, "PAR: Declaration: Function: -%s-, Arity: %d\n", $3, $5); add_symbol_entry(FUNCTION_TYP_NUM, $5, $3, NULL);}
  | DECLARE VARIABLE IDENT COLON INTEGER {fprintf(stderr, "PAR: Declaration: Variable: -%s- Type: int\n", $3); add_symbol_entry(VARIABLE_TYP_NUM, 0, $3, "Integer");}
  ;

formulaterm:
    atom {$<p>$ = $<p>1;}
    | boolean {$<p>$ = $<p>1;}
    | ROUNDBR_S formulaterm ROUNDBR_E {$<p>$ = $<p>2;}
    | NOT formulaterm {$<p>$ = make_node_unary(NOT, $<p>2);}
    | formulaterm junctor formulaterm {$<p>$ = make_node_binary($<type>2, $<p>1, $<p>3);}
    | quantor formulaterm {$<p>$ = make_node_quantor($<q_info.type>1, $<q_info.entry>1, $<p>2)}
;

atom:
    IDENT ROUNDBR_S ROUNDBR_E {fprintf(stderr, "PAR: ATOM: %s()\n", $1); check_type($1, PREDICATE_TYP_NUM, ONLY_ONE); $<p>$ = make_node_fp(get_symbol_entry($1), NULL);}
    | IDENT ROUNDBR_S terms ROUNDBR_E {fprintf(stderr, "PAR: ATOM: %s()\n", $1); check_type($1, PREDICATE_TYP_NUM, ONLY_ONE); $<p>$ = make_node_fp(get_symbol_entry($1), $<p>3);}
;

terms:
    term { $<p>$ = $<p>1;/*$<p>$ = make_node_args(ARGUMENT, $<p>1, NULL);*/}
    | term COMMA terms {$<p>$ = make_node_args(ARGUMENT, $<p>1, $<p>3);}
;

term:
    IDENT {fprintf(stderr, "PAR: TERM: Variable/Constant %s\n", $1); check_type($1, VARIABLE_TYP_NUM, FUNCTION_TYP_NUM); $<p>$ = make_node_var(IDENT, get_symbol_entry($1));}
    | NUMBER {fprintf(stderr, "PAR: TERM: Number %d\n", $1); $<p>$ = make_node_number(NUMBER, $1);}
    | IDENT ROUNDBR_S terms ROUNDBR_E {fprintf(stderr, "PAR: FUNCTION: %s()\n", $1); check_type($1, FUNCTION_TYP_NUM, ONLY_ONE); $<p>$ = make_node_fp(get_symbol_entry($1), $<p>3);}
;

junctor:
    BIJUNCTION {fprintf(stderr, "PAR: JUNCTOR: EQUIVALENT\n"); $<type>$ = BIJUNCTION;}
    | IMPLICATION {fprintf(stderr, "PAR: JUNCTOR: IMPLICATION\n"); $<type>$ = IMPLICATION;}
    | OR {fprintf(stderr, "PAR: JUNCTOR: OR\n"); $<type>$ = OR;}
    | AND {fprintf(stderr, "PAR: JUNCTOR: AND\n"); $<type>$ = AND;}
;

boolean:
    TRUE {fprintf(stderr, "PAR: BOOLEAN: TRUE\n"); $<p>$ = make_node_bool(TRUE);}
    | FALSE {fprintf(stderr, "PAR: BOOLEAN: FALSE\n"); $<p>$ = make_node_bool(FALSE);}
;

quantor:
    EXISTENZQUANTOR SQUAREBR_S IDENT SQUAREBR_E {fprintf(stderr, "PAR: QUANTOR: EXIST %s\n", $3); check_type($3, VARIABLE_TYP_NUM, ONLY_ONE); $<q_info.type>$ = EXISTENZQUANTOR; $<q_info.entry>$ = get_symbol_entry($3);}
    | ALLQUANTOR SQUAREBR_S IDENT SQUAREBR_E {fprintf(stderr, "PAR: QUANTOR: ALL %s\n", $3); check_type($3, VARIABLE_TYP_NUM, ONLY_ONE); $<q_info.type>$ = ALLQUANTOR; $<q_info.entry>$ = get_symbol_entry($3); printf("Test");}
;

%%
