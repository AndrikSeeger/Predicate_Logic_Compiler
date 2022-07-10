<!--Copyright Andrik Seeger 2022-->

# Compiler for first-order predicate calculus


## Usage

* Flex 
* Bison
* GCC
* Make

## Language

The language used is a new creation called "PREDLOG1" short for first-order predicate logic. The following paragraphs descripe the syntax used to translate first-order predicate calculus terms to PREDLOG1.

### Comments
Comments are declared using `/*` as in front the start of the comment and `*/` after the end of the comment. The comments are limited to one line per declaration.

### Operands
Operand  | PREDLOG1 equivalent
:-------------: | :-------------:
&hArr; | <->
→  | ->
∨  | \\|
∧  | &
¬  | ~
∀<var>  | ALL[\<var\>] or ALL [\<var\>]
∃<var>  | EXIST[\<var\>] or EXIST [\<var\>]
0  | FALSE
1  | TRUE
