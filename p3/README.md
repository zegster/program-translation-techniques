
# Project 3 - Static Semantics
> Note: program implemented using FSA table and driver.

Do not display the tree at this point, instead simply display any violations of the static semantics. 

The project P3 will be tested assuming white spaces separate all tokens.  

#### Invocation: 
```
    statSem [file] 
```
* To read from stdin or file file.sp2020 
* Arguments are the same as P0
##

#### Static Semantics Definition
* The only static semantics that we impose on by the compiler is proper use of variables.
* Variables are defined by the declare statement. Any time that identifier appears in any other \<stat\> is the use of that identifier.
* Variables can only be defined once in a scope. All variables have global scope.
##

#### Suggestions
* Modify the main function so that after calling parser and receiving the tree, in main you will call the static semantic function on the tree. It should only require a single traversal of your tree to build the symbol table and check for illegal semantics.
##

#### Software Support
* Use any container (called ST here)  for names such as array, list, etc. with the following interface. It shows String as the parameter, which is the ID token instance, but it could include line number or the entire token for more detailed error reporting. This contained will process identifier tokens only.
	* **insert(String)** - insert the string if not already there or error if already there (you may return fail indication or issue detailed error here and exit)
	* **Bool verify(String)** - return true if the string is already in the container variable and false otherwise (I suggest you return false indicator rather than issue detailed error here with exit but either way could possibly work if you assume that no one checks verify() unless to process variable use)
##

#### Static Semantics
* Instantiate ST as STV for variables
* Traverse the tree and perform the following (looks like preorder traversal) based on the subtree you are visiting
	* If visiting \<vars\> and you find identifier token (variable definition) then call STV.insert(String) on the token - this is variable definition
	* Otherwise (you are not in \<vars\>)  if you find identifier token call STV.verify(String) - this is variable use
##

#### HOW TO RUN
1. In your command prompt, type: make
2. This will generate .o file and executable file
3. To use the program, type: ./statSem [file] (or the name of your a.out)

**Examples of invocations**
```
    ./statSem 
    ./statSem < P3_test1.sp2020
    ./statSem P3_test3.sp2020
    ./statSem P3_test5
```

