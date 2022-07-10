#ifndef SYNTAXTREE_H
#define SYNTAXTREE_H

#include "symboltable.h"
#include "parser.h"

typedef enum yytokentype NUMDEFS; //Auto create Enum

typedef struct node
{
  int nodeType; //Type as Number always needed
  union types{
    struct qType //Quantor
    {
      struct entry *var;
      struct node *formel;
    } quantorType;

    struct uType //Unary
    {
      struct node *formel;
    } unaryType;

    struct bType //Binary
    {
      struct node *formel_l;
      struct node *formel_r;
    } binaryType;

    struct predFunction{ //Predicate or Function
      struct entry *ptr_entry;
      struct node *args;
    } pred_function;

    struct args{ //Arguments
      struct node *current;
      struct node *next;
    } arguments;

    struct entry *variable; //Variable
    int value; //Numerical Value
  } types;
} node;

node *make_node_var(NUMDEFS type, entry  *entry);
node *make_node_number(NUMDEFS type, int value);
node *make_node_fp(entry *entry_ptr, node *arglist);
node *make_node_args(NUMDEFS type, node *current, node *next);
node *make_node_bool(NUMDEFS type);
node *make_node_unary(NUMDEFS type, node *formel);
node *make_node_binary(NUMDEFS type, node *left, node *right);
node *make_node_quantor(NUMDEFS type, entry *var, node *formel);

void generate_code(node *node, FILE *filePointer);
void print_tree_full(node *node);
void delete_tree(node *node);
#endif
