### HY340 Project

##### Building

Both compiler and virtual machine follow same procedure for building.
On the respective project directory run:
`$ make`

##### Running
Compiler: 
`./alpha.exe [input_file, [output_file]]`
If no output file is supplied then stout is used for output instead.
If no input file is supplied then stdin is used for input instead.

##### Testing

We have created a **tests/** directory under each module, which contains all the test files that we used to
assert the functionality of our code. Tests have been executed on the remote computers of our university (CSD@UoC).

/-----------------------------------------------------------------------------------------------------------------/

#### Known Issues

- Compiler
  - Continue command not backpatched correctly
- Virtual Machine
  - Poblems with object/table reference count
  - Unexpected behavior while executed some library functions
  - "()" as an object key doesn't call the corresponding function properly
  
#### Future Upgrades

Future potential upgrades include:
- Adding more library functions
- Supporting <string> + <string> operation
- Supporting more types as legal keys in object (currently supporting only strings and integers)

#### Acquired Knowledge/Skills

During this project we acquired the following knowledge:
- In general:
  - Understanding how a **shift/reduce parser** works
  - Designing a **dynamically-typed programming language**
  - Working as a team (3 members) to conduct a large-scale project in a limited amount of time (one semester)
  - Writing tests that excessively test each part and (edge) case of our project
- Using the **C language (Compiler)**:
  - Using Lex for **lexicographical analysis**
  - Using Yacc/Bison for **syntactical analysis**
  - Embedding code into **Context-Free grammar** through Yacc/Bison
  - Translating source code into quads and furthermore into ASM instructions
  - Converting ASM instructions into bytecode
- Using the **C++ language (Virtual Machine)**:
  - Building a **Virtual Machine** that reconstructs quads based on **bytecode** given by the compiler
  - Reserving and manipulating memory based on user commands
  - Implementing **Garbage collection** for objects/tables
  - Executing code given by the compiler
