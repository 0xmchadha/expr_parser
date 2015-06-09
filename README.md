# Compilers

This repository contains some interesting code for different subsystems of compilers.

What is inside it currently?

1) Expression parser using recursive descent parsing. It currently supports either an interpreter or directly generates code for a simple stack based virtual machine. Once a parser is developed for some more interesting features of a programming language I will write the virtual machine as well for this.

2) Interpreter for brainfuck: This is an interesting interpreter for an esoteric language called brainfuck. I wanted to use the stdin buffering mechanism, hence the code turned out to be very interesting as it uses recursion. 
