<!-- Copyright Andrik Seeger 2022-->

# Compiler for First-Order Predicate Calculus

This project introduces a custom-built compiler that interprets and optimizes **first-order predicate logic** through a new language called **PREDLOG1**. The language is written in UTF-8 and allows formal logical terms to be defined as readable and structured code.

---

## 🛠️ Compilation Process

The compiler follows a classical, multi-stage compilation pipeline:

1. **Lexical Analysis** — Tokenizes the input (Scanner via Flex)
2. **Syntactic Analysis** — Parses tokens into a syntax tree (Parser via Bison)
3. **Semantic Analysis** — Checks for logical consistency and type rules
4. **Code Optimization** — Improves structure and reduces redundancy
5. **Code Generation** — Produces a compiled, internal representation

---

## 🚀 Usage

To compile and run the compiler, ensure the following tools are installed:

* `flex`
* `bison`
* `gcc`
* `make`

Once installed, build the compiler by running:

```bash
make
```

This will compile `main.c` and output the executable. Use the compiled program by passing a PREDLOG1 source file as the first argument:

```bash
./compiler yourfile.predlog1
```

---

## 🧠 Language Overview: PREDLOG1

PREDLOG1 (Predicate Logic Level 1) is a domain-specific language designed for expressing first-order predicate logic in a structured and parseable syntax.

### Comments

Use `/* comment */` for single-line comments. Multiline comments must be split.

---

### Declarations

All symbols must be explicitly declared before usage:

| Type      | Syntax                             |
| --------- | ---------------------------------- |
| Predicate | `DECLARE PREDICATE <id> : <arity>` |
| Function  | `DECLARE FUNCTION <id> : <arity>`  |
| Variable  | `DECLARE VARIABLE <id> : int`      |

* `<id>`: Name/identifier of the symbol
* `<arity>`: Number of arguments

---

### Operators and Equivalents

| Logic Symbol | PREDLOG1 Equivalent |
| ------------ | ------------------- |
| ↔            | `<->`               |
| →            | `->`                |
| ∨            | `\|`                |
| ∧            | `&`                 |
| ¬            | `~`                 |
| ∀ *var*      | `ALL[*var*]`        |
| ∃ *var*      | `EXIST[*var*]`      |
| false        | `FALSE`             |
| true         | `TRUE`              |

Both `ALL[var]` and `ALL [var]` are accepted syntaxes (same for `EXIST`).

---

### Operator Precedence

From highest to lowest:

1. Function
2. Predicate
3. Quantifiers (∀, ∃)
4. Negation (¬)
5. Conjunction (∧)
6. Disjunction (∨)
7. Implication (→)
8. Biconditional (↔)

---

## 📄 Example

```text
/* Example PREDLOG1 */

DECLARE PREDICATE Buys : 2
DECLARE PREDICATE Pumpkin : 1
DECLARE PREDICATE Person : 1
DECLARE FUNCTION Eats : 2
DECLARE FUNCTION Carves : 2
DECLARE FUNCTION John : 0
DECLARE VARIABLE x : int
DECLARE VARIABLE y : int

EXIST[x] (Buys(John,x) & Pumpkin(x)) 
& ALL[x] ALL[y] (Buys(x,y) & Pumpkin(y) -> Eats(x,y) | Carves(x,y)) 
& ALL[x] (Person(x) -> ALL[y] (Pumpkin(y) -> ~Eats(x,y))) 
& ~(Person(John) -> EXIST[x] Carves(John,x)) ;
```

This expresses a mix of existential and universal quantifiers, logical implications, conjunctions, and negations—all handled cleanly through the PREDLOG1 syntax.
