<!--Copyright Andrik Seeger 2022-->

# Compiler for first-order predicate calculus
This project is the development of a new compiler that reliably interprets and optimizes first-order predicate calculus. Therefor a new language (PREDLOG1) was created to define the logic terms as code in UTF-8.

## Process

The abstract compilation process goes as follows: 

1. Lexical analysis (Scanner)
2. Syntactical analysis (Parser and syntaxtree)
3. Semantical analysis
4. Code optimization
5. Final code generation

## Usage

To compile the code you need:

* Flex 
* Bison
* GCC
* Make

With those prerequisites met you can simply run ```make``` for the ```main.c``` file and build the compiler program. You can use the compiler to analyze your PREDLOG1-code, when using your desired file as the first input argument executing the compiled program.

## Language

The language used is a new creation called "PREDLOG1" short for first-order predicate logic. The following paragraphs describe the syntax used to translate first-order predicate calculus terms to PREDLOG1.

### Comments
Comments are declared using `/*` as in front the start of the comment and `*/` after the end of the comment. The comments are limited to one line per declaration.

### Declarations
Every predicate, function and variable needs to be declared as follows before used: 

* **Predicate:** ```DECLARE PREDICATE <id> : <arity>```
* **Function:** ```DECLARE FUNCTION <id> : <arity>```
* **Variable:** ```DECLARE VARIABLE <id> : int```

```<id>``` declares the identifier and ```<arity>``` declares the number of arguments.

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

### Priority

The order of priority is structured as follows with decreasing priority top down:

1. function
2. predicate
3. ∀,∃ 
4. ¬
5. ∧
6. ∨
7. →
8. &hArr;
  
### Example
```
/* Example PREDLOG1 */

DECLARE PREDICATE Buys : 2
DECLARE PREDICATE Pumpkin : 1
DECLARE PREDICATE Person : 1
DECLARE FUNCTION Eats : 2
DECLARE FUNCTION Carves : 2
DECLARE FUNCTION John : 0
DECLARE VARIABLE x : int
DECLARE VARIABLE y : int

EXIST[x] (Buys(John,x) & Pumpkin(x)) & ALL[x] ALL[y] (Buys(x,y) & Pumpkin(y) -> Eats(x,y) | Carves(x,y)) 
&
ALL[x] (Person(x) -> ALL[y] (Pumpkin(y) -> ~Eats(x,y))) & ~(Person(John) -> EXIST[x] Carves(John,x)) ;
```
