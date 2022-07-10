#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symboltable.h"

entry *start = NULL;
entry *last = NULL;

int check_exist(char *identifier){
  entry *curr = start; //Init Entry with Start
  while(curr){ //Iterate over all Entries
    if(!strcmp(curr->identifier, identifier)){ //strcmp is 0 if equal
      fprintf(stderr, "\nERROR: IDENTIFIER ALREADY EXISTS!\n");
      return 1;
    }
    curr = curr->next;
  }
  return 0;
}

int check_type(char *identifier, int type1, int type2){
  entry *curr = start; //Init Entry with Start
  while(curr){ //Iterate over all Entries
    if(!strcmp(curr->identifier, identifier) && (curr->type == type1 || curr->type == type2)){ //Same Ident and Type -> Atom exists
      return 0;
    }
    curr = curr->next;
  }
  fprintf(stderr, "\nERROR: IDENTIFIER %s WAS NOT DECLARED!\n\n\n", identifier);
  return 1;
}

int add_symbol_entry(int type, int arity, char *identifier, char *vartype){
  entry *newone = (entry *) malloc(sizeof(entry));

  //Save properties
  newone->type = type;
  newone->arity = arity;
  newone->identifier = strdup(identifier);
  if(vartype){ //Only set for Integer
    newone->vartype = strdup(vartype);
  }else{
    newone->vartype = NULL;
  }
  newone->next = NULL; //Init Next

  if(!start){ //When no start is saved (start of table) save current newone as start and last
    start = newone;
    last = newone;
    fprintf(stderr, "SymT: Added Entry '%s' with Type %d, Arity %d and Vartype %s \n\n\n", identifier, type, arity, vartype);
  }else{
    if(check_exist(identifier)==0){ //Identifier doesnt exist already
      //Save created Entry as new Last
      last->next = newone;
      last = last->next;
      fprintf(stderr, "SymT: Added Entry '%s' with Type %d, Arity %d and Vartype %s \n\n\n", identifier, type, arity, vartype);
    }
    else{
      fprintf(stderr, "\n\n");
    }
  }
  return 0;
}

entry *get_symbol_entry(char *identifier){
  entry *curr = start;
  while(curr){ //Iterate over all Elements till Element with identifier is found or or all Elements are searched
    if(!strcmp(curr->identifier, identifier)){
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

void print_symbol_entry(){
  entry *curr = start;
  fprintf(stderr, "\n\nSymboltable: \n");
  while(curr){ //Print all Entries of the List
    fprintf(stderr, "ENTRY: Identifier: %s, Arity: %d, Type: %d, Vartype: %s\n", curr->identifier, curr->arity, curr->type, curr->vartype);
    curr = curr->next;
  }
}

void generate_declarations(FILE *outputFile){
  entry *curr = start;
  while(curr){ //Write all Entries of the List in File
    fprintf(outputFile, "DECLARE ");
    switch(curr->type)
    {
      case PREDICATE_TYP_NUM:
        fprintf(outputFile, "PREDICATE");
        break;
      case FUNCTION_TYP_NUM:
        fprintf(outputFile, "FUNCTION");
        break;
      case VARIABLE_TYP_NUM:
        fprintf(outputFile, "VARIABLE");
        break;
    }
    fprintf(outputFile, " %s : ", curr->identifier);
    if(!(curr->vartype))
    {
      fprintf(outputFile, "%d", curr->arity);
    } else {
      fprintf(outputFile, "int");
    }
    fprintf(outputFile, "\n");

    curr = curr->next;
  }
  fprintf(outputFile, "\n");
}
