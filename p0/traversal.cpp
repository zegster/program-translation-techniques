/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: traversal.cpp
# Date: 2/10/20
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output
#include <cstdio>        //Input and Output operations can also be performed in C++ using the C Standard Input and Output Library
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include "traversal.h"


void printToken(int level, set<string> token)
{
	set<string>::iterator i;
	printf("%*s", level * 4, "");
	cout << (*token.begin()).substr(0, 2) << ": ";
	for(i = token.begin(); i != token.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}


void traverseInorder(NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	traverseInorder(root->left);
	printToken(root->level, root->words);
	traverseInorder(root->right);
}


