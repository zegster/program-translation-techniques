# Project 2 - Parser
> Note: program implemented using FSA table and driver.

Assume the project grammar is LL(1). You need to compute First() sets as needed (for any non-terminal that has multiple productions). If a token doesn't match any of the sets in the function for the non-terminal, issue error; however, if there is the empty production then instead of error, use the production - return from the function.  

Implement the parser in a separate file (parser.c and parser.h) including the initial auxiliary parser() function and all non-terminal functions. Call the parser function from main after all the checks on the main arguments and anything needed to initiate the scanner. 

The parser function generates error or returns the parse tree to main. In testTree.c (and testTree.h) implement a printing function using preorder traversal with indentations as before for testing purposes (2 spaces per level, print the node's label and any tokens from the node, then children left to right; one node per line). Call this printing function from 
main immediately after calling the parser, on the returned tree. The printing function call must be later removed for P3. 

The project P2 will be tested assuming white spaces separate all tokens. 

#### Invocation: 
```
    frontEnd [file] 
```
* To read from stdin or file file.sp2020 
* Arguments are the same as P0
##

#### Suggestions
* Make sure to implement the parser() auxiliary function as in the notes, and then a function for each non-terminal in the grammar.
* The grammar is LL(1), which means:
    1. Each non-terminal with multiple productions will have the First() sets disjoint to make the correct prediction looking at the next token from the scanner.
    2. If the token doesn't match any First() sets in this function (this non-terminal) then
        * If the non-terminal has the empty production, use it (return from the function)
        * Otherwise, issue error and exit
    3. Note that some non-terminals with common prefixes will not have disjoint First() sets but can be implemented using the delay as in the notes. For example, \<expr\> can be implemented as (could also be factored out of desired)
```
void expr () {
    call N() ; // always
    if (next token is minusTk) 
	    then assume you are processing "<N> - <expr>" AND 
	    thus must continue with "- <expr>"
    else return
```
 
Note that the parser should be calling the scanner for each new token. This should happen always when (and if and only if) the current token in the production was matched with the next token from the scanner.
##

#### Implement the parser in two iterations (as illustrated in the notes):
1. Starting without the parse tree. Have the parser generate error (detailed, including involved tokens and their line number of processed) or print OK message upon successful parse.  The OK message will later be replaced with call to back end processing. For each \<non-terminal\>, use a void function named after the non-terminal and use only explicit returns. Decide how to pass the token. Have the main program call the parser after all the preliminary work needed there.
	* Be systematic: assume each function starts with unconsumed token (not matched yet) and returns unconsumed token. Use version control and be ready to revert if something gets messed up.
2. Only after completing and testing the above to satisfaction, modify each function to build a subtree, and return its root node. Assume each function builds just its root node and connects its subtrees. Modify the main function to receive the tree built in the parser, and then display it (for testing) using the preorder tree printing.

**Some hints for tree:**
* Every node should have a label consistent with the name of the function creating it (can be string with function name)
* Every function creates exactly one tree node (or possibly none if going into the empty production)
* The number of children seems as 3 or 4 max (depending on some choices, it is the maximum non-terminals listed in any production)
* All syntactic tokens can be thrown away, all other tokens (operators, IDs, Numbers) need to be stored in the node processing them.
* When storing a token, you may need to make a copy depending on our interface (is there just one global token or each token has separate memory)
##

**BNF Grammar**
```
<program> ->  <vars> <block> 
<block>   ->  { <vars> <stats> } 
<vars>    ->  empty | declare Identifier :=  Integer ; <vars>  
<expr>    ->  <N> - <expr>  | <N> 
<N>       ->  <A> / <N> | <A> * <N> | <A> 
<A>       ->  <M> + <A> | <M> 
<M>       ->  * <M> | <R> 
<R>       ->  ( <expr> ) | Identifier | Integer 
<stats>   ->  <stat> <mStat> 
<mStat>   ->  empty | <stat> <mStat> 
<stat>    ->  <in> ; | <out> ; | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; | <block>
<in>      ->  in Identifier   
<out>     ->  out <expr> 
<if>      ->  iffy [ <expr> <RO> <expr> ] then <stat> 
<loop>    ->  loop [ <expr> <RO> <expr> ] <stat> 
<assign>  ->  Identifier  := <expr>   
<label>   ->  label Identifier 
<goto>    ->  goto Identifier 
<RO>      ->  < | << (two tokens) | > | >> (two tokens) | == (one token ==) | <> (two tokens) 
```
##

**Testing**
Create files using the algorithm to generate programs from the grammar, starting with simplest programs one different statement at a time and then building sequences of statements and then nested statements, expressions, etc. You may skip comments but then test a comment in some files. Make sure to have sequences of statements, nested statements (blocks), nested ifs and loops, variables in various blocks, expressions, and to test all operators.
##

#### HOW TO RUN
1. In your command prompt, type: make
2. This will generate .o file and executable file
3. To use the program, type: ./frontEnd [file] (or the name of your a.out)

**Examples of invocations**
```
    ./frontEnd 
    ./frontEnd < P2_test1.sp2020
    ./frontEnd P2_test3.sp2020
    ./frontEnd P2_test5
```

