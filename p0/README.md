# Project 0 - Programming Refreshment
Programming refreshment, practice with standards and header files, practice with trees, traversals, command line arguments, and file IO.

> **Note:** command line arguments and keyboard input can directly be reused in the later compiler project so make sure to do it well and modular.

Write a program to build a tree and print it using different traversals. The program will be invoked as:
```
	user@host~/p0 $: ./P0 [file]
```
1. Where file is an optional argument.
2. If the file argument is not given, the program reads data from the keyboard as a device (15%).
3. If the argument is given, the program reads data file file.sp2020. (note that file is any name and the extension is implicit).
4. Programs improperly implementing file name or executable will not be graded.
5. 15% is for style. 15% interactive input. 70% performance.

##

#### Example invocations:
```
P0               //(read from the keyboard until simulated EOF)
P0 < somefile    //(same as above except redirecting from somefile instead of keyboard, this tests keyboard input)
P0 somefile      //(read from somefile.sp2020)
```
1. Assume you do not know the size of the input file
2. Assume the input data is all strings separated with standard WS separators (space, tab, new line)
3. If the input file is not readable for whatever reason, or command line arguments are not correct, the program must abort with an appropriate message
4. The program will read the data left to right and put them into a tree, which is a binary search tree (BST) with respect to the first two letters of the string , that is all strings that start with the same first two letters fall into the same node in the BST.
5. Tree is never balanced nor restructured other than growing new nodes.
6. A node should contain all data that falls into the node except that literally the same strings will show up only once (the node contains the set of data falling into the node).
7. The program will subsequently output 3 files corresponding to 3 traversals, named file.preorder, file.inorder and file.postorder. Note that file is the base name of the input file if given, and it is output if not given.

##

#### Traversals:
1. preorder
2. inorder
3. postoder

##### Printing in traversal: 
1. A node will print the node's first two letters 
2. (The first two letters of all the strings in that node) intended by 2 x depth of the node, 
3. Followed by the list of strings from the node set (the root is considered level 0).

##

#### Example will be elaborated in class
##### File xxx.sp2020 contains:
```
george adam ala 12 ada 125 john haus geode
```
- Invocation: > P0 xxx
- Output files: xxx.inorder xxx.preorder xxx.postorder
- Invocation: > P0 < xxx.sp2020
	- //(or > P0, followed by typing the data followed by EOF)
- Output files: ouput.inorder output.preorder output.postorder

##
	
#### Standards related requirements:
Have the following functions/methods minimum (the types and arguments are up to you, the names are required as given)
1. buildTree()
2. printInorder()
3. printPreorder()
5. printPostorder()
6. These must be in one file called tree.c or appropriately based on your language, with tree.h or as appropriate for your language
7. Define the node type in node.h
8. Keep the main function in a separate file (regardless of language)

##

#### Traversals taken from the CS3130 textbook:
**Preorder:**
- process root
- process children left to right

**Inorder:**
- process left child
- process root
- proccess right child
		
**Postorder:**
- process children left to right
- process root

##

#### More suggestions
##### Using top-down decomposition you have 3 tasks in main:
1. Process command arguments, set up file to work regardless of source, check if file readable, set the basename for the output file, etc.
2. Build the tree
3. Traverse the tree three different ways generating outputs

##### The main function should handle the 3 functionalities. 
- #1 should be handled inside of main, 
- functions for #2 and #3 should be in another separate source as indicated. 
- Any node types should be defined in a separate header file.   

##### For development purposes...
- Do either 1 or 2 first. 3 should follow 2, first with one traversal only.

##### Processing either keyboard or file input can be done one of these two ways:
- If keyboard input, read the input into temporary file, after which the rest of the program always processes file input
- If keyboard input, set file pointer to stdin otherwise set file pointer to the actual file, then process always from the file pointer

##### Files:
- node.h, tree.c + tree.h (or as appropriate for your language)
- main.c
- makefile

##

#### Sample structure for main.c
```
#include "node.h"
#include "tree.h"
int main(int argc, char* argv[]) 
{
	// process command line arguments first and error if improper
	// if filename given, make sure file is readable, error otherwise
	// set up keyboard processing so that below this point there is only one version of the code

	node_t *root = buildTree(file);
	printPreorder(root);
	printInorder(root);
	printPostorder(root);
	return 0;
}
```

#### Ideas for printing tree with indentations
```
static void printPreorder(nodeType *rootP,int level) 
{
	if (rootP==NULL) return;
	printf("%*c%d:%-9s ",level*2,' ',level,NodeId.info); // assume some info printed as string
	printf("\n");
	printPreorder(rootP->left,level+1);
	printPreorder(rootP->right,level+1);
}
```

##

#### Testing - This section is non-exhaustive testing of P0
##### Create test files:
- P0_test1.sp2020 containing empty file
- P0_test2.sp2020 containing one string: adam
- P0_test3.sp2020 containing some strings with the first two letters the same (some repeats) but doing it over different lines, e.g., use the example from above

##### For each test file, draw by hand the tree that should be generated. For example:
- Using P0_test2.sp2020 should create just one node printing:  ad adam

##### Decide on invocations and what should happen, what should be output filenames if no error, and what the output files should look like - using the hand drawn trees for each file
##### Run the invocations and check against predictions
- P0 < P0_test1
	- Error
- P0 < P0_test3.sp2020
	- Outputs output.inorder output.preorder output.postorder, each containing the strings (no repetitions)
- P0 P0_test3
	- Outputs P0_test3.inorder P0_test3.preorder P0_test3.postorder containing as above
	

--------------------------------------------------------------------------------
##### HOW TO RUN:
1. In your command prompt, type: make
2. This will generate .o file and executable file
3. To use the program, type: ./main (or the name of your a.out)
4. You build a tree and print it using different traversals.
5. Examples of invocations:
	- ./main
	- ./main < P0_test3.sp2020
	- ./main P0_test5
--------------------------------------------------------------------------------

