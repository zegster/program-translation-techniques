# Project 4 - Code Generation 
> Note: program implemented using FSA table and driver.

The program is to parse the input, generate a parse tree, perform static semantics, and then generate a target file. Any error should display a detailed message, including line number if available (depending scanner).  

**The target should be:**
* `kb.asm` if keyboard input 
* `file.asm` if `file.sp2020` is input, with the base name matches that of the input file. That is, if input basename is ++test2++, then output should be `test2.asm` 

The program should do code generation as well as do global storage allocation in our assembly language. The resulting .asm program should be able to run on the virtual machine. 

**NOTE:** Upon success, only display the name of the target file generated and no other output. Upon error and the error message, no other display should be generated and no target should be generated. 

#### Invocation: 
```
    comp [file] 
```
* To read from stdin or file file.sp2020 
* Arguments are the same as P0
##

#### About
* The parse tree is equivalent to the program in left-to-right traversal (skipping syntactic tokens if not stored in the tree). Therefore, perform left to right traversal to generate the target code
    * The traversal can follow static semantics traversal or be combined
* When visiting a node - some nodes are:
    * Code generating - most likely only those that have a token(s)
    * Not code generating - most likely without tokens but consider one at a time
* When visiting a node not generating any code:
    * If no children, return
    * If children, continue traversal (likely left to right) then return
* When visiting a code generating node:
    * Some actions can be preorder, some inorder, some postorder
    * If value is produced, always leave the result in the ACCumulator
    * If value was produced by another node, find it in the ACCumulator
    * If value in the ACCumulator needs to be saved, store it in a new temporary variable with proper name
        * To simplify, let us assume users never use variables starting with V or T so we can use them for temporary variables without conflicts with user variables
    * Each node with a given label always generates the same code
        * Regardless of parents and children
        * May be one of multiple cases, one per production
        * The only difference may come from the token(s) found in the node
* At the end of the traversal, print STOP to target
    *  To be followed by global variables+temporaries in storage allocation
*  Variables will require
    *  Variable creation upon definition - see storage allocation
    *  Variable access upon use - global option or temporary variable, just uses the variable name
##

#### Storage allocation
* All storage is 2-byte signed
* Storage is needed for
    * Program variables used in the input
    * Temporaries (e.g., if accumulator needs to be saved for later use)
        * We can assume input programs do not use variables named T# or V# in the source, reserving such names for temporary variables
        * There is no need to optimize reducing the number of temporaries
* Global option (only option for this project)
    * Storage allocation should follow static semantics and code generation
    * Issue target storage directive for every variable and then every temporary, using the global storage directive in the virtual machine after the STOP instruction
##

#### Runtime Semantics
* Basic semantics as in C - program executes sequentially from the beginning to the end, one statement at a time
* Conditional statement is like the else-less if statement in C
* Loop statement is like the while loop in C
* `Goto \<ID\>` and `Label` is an unconditional branch from the goto statement to the associated label
* Assignment evaluates the expression on the right and assigns to the ID on the left
* `+ - * /` are standard arithmetic
* All expressions are evaluated before being used
* Relational and arithmetical operators have the standard meaning except:
	* `<` and `>` are less than and greater than
	* `< <` is less equal
	* `> >`  is greater equal
	* `< >` is NOT equal
	* `==` is equal
* IO reads/prints a 2-byte signed integer
* All data is 2-byte signed integer
##

#### Data
* All data is 2-byte signed integers
* Assume no overflow in operations
##

#### Target Language
* VM ACCumulator assembly language as given (in this project folder)
* [VirtMach IDE](https://comp.umsl.edu/assembler/index)
##

#### Testing
* All sample test files is located in the `tests` folder/directory
* When invoking `run.sh [test_directory]`, it will invoke code generation to all test files and all the `.asm` files will be save in the `tests` folder/directory
* For example: `sh run.sh test1`
* To remove all `.asm`, run `make dump`
* [OPTIONAL] to execute all test files, invoke `sh exec.sh test1` (must call `sh run.sh test1` first)
* `P4_1.sp2020` should only print out 2
* `P4_2.sp2020` should print 5 to 11
* `P4_3.sp2020` should print the sequence of number you enter and finish with 100
* `P4_4.sp2020` should print out 1 2 3 4 5
* `P4_5.sp2020` should print out 1 2 3
* `P4_6.sp2020` should print out 1
* `P4_7.sp2020` should print out 1 to 100
* `P4_8.sp2020` should only print out 2
* `P4_9.sp2020` should print 3 inputs in reverse
* `P4_10.sp2020` should print out 3 inputs in reverse
* `P4_11.sp2020` should print input then input-1, ..., down to 1
* `P4_12.sp2020` should print input and input-2 down to 1, then input-1 and input-3 down to 1, ...
* `P4_13.sp2020` should print out 1 to 10
* `P4_14.sp2020` should print out 1 to 10
* `P4_15.sp2020` should print out 1 to 5 then 10 to 1 and then print out your input
* `P4_16.sp2020` should print out 1 2 3
* `test2` bonus test files (all expected output is commented inside the test file)
##

#### HOW TO RUN
1. In your command prompt, type: make
2. This will generate .o file and executable file
3. To use the program, type: ./comp [file] (or the name of your a.out)

**Examples of invocations (Code Generation/Compiler)**
```
    ./comp 
    ./comp < P4_test1.sp2020
    ./comp P4_test3.sp2020
    ./comp P4_test5
```

**Examples of invocations (VirtMach)**

**NOTE:** `.asm` file can also be run on the [VirtMach IDE](https://comp.umsl.edu/assembler/index)
```
    ./VirtMach P4_1.asm 
    ./VirtMach tests/P4_1.asm
```

