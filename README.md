<!--Copyright Andrik Seeger 2022-->

# Compiler for first-order predicate calculus


## Usage

* Flex 
* Bison
* GCC
* Make

## Language
### Semantics
Operands  | PREDLOG1
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
