#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#define PREDICATE_TYP_NUM 1
#define FUNCTION_TYP_NUM 2
#define VARIABLE_TYP_NUM 3
#define ONLY_ONE -1

typedef struct entry{
  int type; //Type as Number
  int arity; //Numerical Value
  char *identifier; //Name
  char *vartype; //If Integer set to Integer
  struct entry *next; //Next Entry
} entry;

int add_symbol_entry(int type, int arity, char *identifier, char *vartype);
entry *get_symbol_entry(char *identifier);
void print_symbol_entry();
int check_type(char *identifier, int type1, int type2);
void generate_declarations(FILE *outputFile);
#endif
