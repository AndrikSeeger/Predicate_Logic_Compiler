#include <stdlib.h>
#include <stdio.h>

#include "syntaxtree.h"
#include "symboltable.h"

//Make Node of Symboltable-Entry
node *make_node_var(NUMDEFS type, entry  *entry)
{
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.variable = entry;

  printf("SYT: Variable Node created\n");

  return newnode;
}

//Make Node of Numerical Value
node *make_node_number(NUMDEFS type, int value)
{
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.value = value;

  printf("SYT: Number Node created\n");

  return newnode;
}

//Make Node of Boolean (True/False)
node *make_node_bool(NUMDEFS type) //make boolean, then value = -1
{
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type; //Defines if true or false
  newnode->types.value = -1; //Value not needed (only for number), set to default

  printf("SYT: Boolean Node created\n");

  return newnode;
}

//Make Node of Function or Predicate depending on Entrytype in Input
node *make_node_fp(entry *entry_ptr, node *arglist){
  node *newnode = (node*)malloc(sizeof(node));
  newnode->types.pred_function.ptr_entry = entry_ptr;
  newnode->types.pred_function.args = arglist;
  if(entry_ptr->type == FUNCTION_TYP_NUM)
  {
    newnode->nodeType = FUNCTION;
    printf("SYT: Function Node created\n");
  }else{
    if(entry_ptr->type == PREDICATE_TYP_NUM)
    {
      newnode->nodeType = PREDICATE;
      printf("SYT: Predicate Node created\n");
    }
    else{
      fprintf(stderr, "ERROR: Node is not from type FUNCTION or PREDICATE!\n");
      exit(1);
    }
  }
  return newnode;
};

//Make Node of two Nodes -> Argument Lists
node *make_node_args(NUMDEFS type, node *current, node *next)
{
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.arguments.current = current;
  newnode->types.arguments.next = next;

  printf("SYT: Argument Node created\n");

  return newnode;
}

//Make binary Node
node *make_node_binary(NUMDEFS type, node *left, node *right){
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.binaryType.formel_l = left;
  newnode->types.binaryType.formel_r = right;

  printf("SYT: Binary Node created\n");

  return newnode;
};

//Make unary Node
node *make_node_unary(NUMDEFS type, node *formel){
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.unaryType.formel = formel;

  printf("SYT: Unary Node created\n");

  return newnode;
};

//Make Node of Quantor
node *make_node_quantor(NUMDEFS type, entry *var, node *formel){
  node *newnode = (node*)malloc(sizeof(node));
  newnode->nodeType = type;
  newnode->types.quantorType.var = var;
  newnode->types.quantorType.formel = formel;

  printf("SYT: Quantor Node created\n");

  return newnode;
};

//Generate Output-Code with Roundbrackets arround every formula
void generate_code(node *node, FILE *filePointer)
{
    if (!node)
    {
        return;
    }
    switch (node->nodeType)
    {
    case TRUE:
        fprintf(filePointer, "TRUE");
        break;
    case FALSE:
        fprintf(filePointer, "FALSE");
        break;
    case NUMBER:
        fprintf(filePointer, "%d", node->types.value);
        break;
    case FUNCTION:
        fprintf(filePointer, "%s(", node->types.pred_function.ptr_entry->identifier);
        generate_code(node->types.pred_function.args, filePointer);
        fprintf(filePointer, ")");
        break;
    case PREDICATE:
        fprintf(filePointer, "%s(", node->types.pred_function.ptr_entry->identifier);
        generate_code(node->types.pred_function.args, filePointer);
        fprintf(filePointer, ")");
        break;
    case IDENT: //case VARIABLE
        fprintf(filePointer, "%s", node->types.variable->identifier);
        break;
    case ARGUMENT:
        generate_code(node->types.arguments.current, filePointer);
        if (node->types.arguments.next)
        {
            fprintf(filePointer, ", ");
			      generate_code(node->types.arguments.next, filePointer);
        }
        break;
    case EXISTENZQUANTOR:
        fprintf(filePointer, "EXIST[%s](", node->types.quantorType.var->identifier);
        generate_code(node->types.quantorType.formel, filePointer);
        fprintf(filePointer, ")");
        break;
    case ALLQUANTOR:
        fprintf(filePointer, "ALL[%s](", node->types.quantorType.var->identifier);
        generate_code(node->types.quantorType.formel, filePointer);
        fprintf(filePointer, ")");
        break;
    case IMPLICATION:
        fprintf(filePointer, "(");
        generate_code(node->types.binaryType.formel_l, filePointer);
        fprintf(filePointer, " -> ");
        generate_code(node->types.binaryType.formel_r, filePointer);
        fprintf(filePointer, ")");
        break;
    case BIJUNCTION:
        fprintf(filePointer, "(");
        generate_code(node->types.binaryType.formel_l, filePointer);
        fprintf(filePointer, " <-> ");
        generate_code(node->types.binaryType.formel_r, filePointer);
        fprintf(filePointer, ")");
        break;
    case AND:
        fprintf(filePointer, "(");
        generate_code(node->types.binaryType.formel_l, filePointer);
        fprintf(filePointer, " & ");
        generate_code(node->types.binaryType.formel_r, filePointer);
        fprintf(filePointer, ")");
        break;
    case OR:
        fprintf(filePointer, "(");
        generate_code(node->types.binaryType.formel_l, filePointer);
        fprintf(filePointer, " | ");
        generate_code(node->types.binaryType.formel_r, filePointer);
        fprintf(filePointer, ")");
        break;
    case NOT:
        fprintf(filePointer, "~(");
        generate_code(node->types.unaryType.formel, filePointer);
        fprintf(filePointer, ")");
        break;
    default:
        break;
    }
}

//Print Spacers for Tree
void width(int depth)
{
  for(int dots=0; dots<depth; dots++){
    fprintf(stderr, ".");
  }
}

void print_tree(node *node, int depth)
{
  if(!node){
    return;
  }

  if(node->nodeType == ARGUMENT){
    print_tree(node->types.arguments.current, depth);
    if (node->types.arguments.next)
    {
        print_tree(node->types.arguments.next, depth);
    }
  return;
  }

  width(depth);

  switch (node->nodeType)
  {
  case TRUE:
      fprintf(stderr, "Boolean: true\n");
      break;
  case FALSE:
      fprintf(stderr, "Boolean: false\n");
      break;
  case NUMBER:
      fprintf(stderr, "Number: %d\n", node->types.value);
      break;
  case FUNCTION:
      fprintf(stderr, "Function: %s\n", node->types.pred_function.ptr_entry->identifier);
      print_tree(node->types.pred_function.args, ++depth);
      break;
  case PREDICATE:
      fprintf(stderr, "Predicate: %s\n", node->types.pred_function.ptr_entry->identifier);
      print_tree(node->types.pred_function.args, ++depth);
      break;
  case IDENT: //case VARIABLE
      fprintf(stderr, "Variable: %s\n", node->types.variable->identifier);
      break;
  case ARGUMENT:
      //Never reached
      break;
  case EXISTENZQUANTOR:
      fprintf(stderr, "EXIST\n");
      width(++depth);
      fprintf(stderr, "Variable: %s\n", node->types.quantorType.var->identifier);
      print_tree(node->types.quantorType.formel, ++depth);
      break;
  case ALLQUANTOR:
      fprintf(stderr, "ALL\n");
      width(++depth);
      fprintf(stderr, "Variable: %s\n", node->types.quantorType.var->identifier);
      print_tree(node->types.quantorType.formel, ++depth);
      break;
  case IMPLICATION:
      fprintf(stderr, "IMPLICATION\n");
      print_tree(node->types.binaryType.formel_l, ++depth);
      print_tree(node->types.binaryType.formel_r, ++depth);
      break;
  case BIJUNCTION:
      fprintf(stderr, "BIJUNCTION\n");
      print_tree(node->types.binaryType.formel_l, ++depth);
      print_tree(node->types.binaryType.formel_r, ++depth);
      break;
  case AND:
      fprintf(stderr, "AND\n");
      print_tree(node->types.binaryType.formel_l, ++depth);
      print_tree(node->types.binaryType.formel_r, ++depth);
      break;
  case OR:
      fprintf(stderr, "OR\n");
      print_tree(node->types.binaryType.formel_l, ++depth);
      print_tree(node->types.binaryType.formel_r, ++depth);
      break;
  case NOT:
      fprintf(stderr, "NOT\n");
      print_tree(node->types.unaryType.formel, ++depth);
      break;
  default:
      break;
  }
}

void print_tree_full(node *node)
{
  fprintf(stderr, "\n\nSyntaxtree:\n");
  print_tree(node, 0);
}

void delete_tree(node *node){
  if(!node){
    return;
  }

  if(node->nodeType == ARGUMENT){
    delete_tree(node->types.arguments.current);
    if (node->types.arguments.next)
    {
        delete_tree(node->types.arguments.next);
    }
  return;
  }

  switch (node->nodeType)
  {
  case FUNCTION:
  case PREDICATE:
      delete_tree(node->types.pred_function.args);
      break;
  case ARGUMENT:
      //Never reached
      break;
  case EXISTENZQUANTOR:
  case ALLQUANTOR:
      delete_tree(node->types.quantorType.formel);
      break;
  case IMPLICATION:
  case BIJUNCTION:
  case AND:
  case OR:
      delete_tree(node->types.binaryType.formel_l);
      delete_tree(node->types.binaryType.formel_r);
      break;
  case NOT:
      delete_tree(node->types.unaryType.formel);
      break;
  default:
      break;
  }
  free(node);
}
