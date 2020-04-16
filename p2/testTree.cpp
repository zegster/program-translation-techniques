/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testTree.cpp
# Date: 4/13/2020
==================================================================================================== */
#include "testTree.h"

/* ====================================================================================================
* Function    :  printToken()
* Definition  :  Print the content of the current node to the terminal.
* Parameter   :  level of the tree. 
* Return      :  none.
==================================================================================================== */
void printToken(NodeT *node, int level)
{
	string line;

	//Spacing
	line.append("|");
	for(int i = 0; i < level; i++)
	{
		line.append("____");
	}

	//Label production
	line.append(node->label + " ");

	//Append the tokens of a node to the output line
	for(unsigned int i = 0; i < node->tokens.size(); i++) {
		line.append(node->tokens[i].value);

    	//Separate multiple tokens on a node by a comma
    	if(((i + 1) != node->tokens.size()) && (node->tokens[i].id != opTk)) {
      		line.append(",");
		}
		line.append(" ");
	}

	cout << line << endl;
}


/* ====================================================================================================
* Function    :  ()
* Definition  :  .
* Parameter   :  .
* Return      :  .
==================================================================================================== */
void traversePreorder(NodeT *node, int level)
{
	if(node == NULL) {
		return;
	}

	printToken(node, level);
	traversePreorder(node->c1, level + 1);
	traversePreorder(node->c2, level + 1);
	traversePreorder(node->c3, level + 1);
	traversePreorder(node->c4, level + 1);
}




