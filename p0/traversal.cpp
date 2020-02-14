/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: traversal.cpp
# Date: 2/10/20
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output.
#include <cstdio>        //Input and Output operations can also be performed in C++ using the C Standard Input and Output Library.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <fstream>       //Input and output stream class to operate on files.
#include "traversal.h"


/* ====================================================================================================
* Function    :  printToken()
* Definition  :  Print the content of the current node to the terminal and write it to a file.
* Parameter   :  Reference of output stream for the output file. Root node of BST. 
* Return      :  none.
==================================================================================================== */
void printToken(ofstream &file, int level, set<string> token)
{
	//Print out spacing
	for(int i = 0; i < level; i++)
	{
		cout << "----";
		file << "----";
	}

	//Print out the token of the node
	set<string>::iterator iter;
	cout << "[" << (*token.begin()).substr(0, 2) << "]: ";
	file << "[" << (*token.begin()).substr(0, 2) << "]: ";
	for(iter = token.begin(); iter != token.end(); iter++)
	{
		cout << *iter << " ";
		file << *iter << " ";
	}
	cout << endl;
	file << endl;
}


/* ====================================================================================================
* Function    :  traversePreorder()
* Definition  :  Preorder traversal of the BST.
* Parameter   :  Reference of output stream for the output file. Root node of BST. 
* Return      :  none.
==================================================================================================== */
void traversePreorder(ofstream &file, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	printToken(file, root->level, root->words);
	traversePreorder(file, root->left);
	traversePreorder(file, root->right);
}


/* ====================================================================================================
* Function    :  traverseInorder()
* Definition  :  Inorder traversal of the BST.
* Parameter   :  Reference of output stream for the output file. Root node of BST. 
* Return      :  none.
==================================================================================================== */
void traverseInorder(ofstream &file, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	traverseInorder(file, root->left);
	printToken(file, root->level, root->words);
	traverseInorder(file, root->right);
}


/* ====================================================================================================
* Function    :  traversePostorder()
* Definition  :  Postorder traersal of the BST.
* Parameter   :  Reference of output stream for the output file. Root node of BST. 
* Return      :  none.
==================================================================================================== */
void traversePostorder(ofstream &file, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	traversePostorder(file, root->left);
	traversePostorder(file, root->right);
	printToken(file, root->level, root->words);
}

