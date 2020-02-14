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


void printToken(string output_file_name, int level, set<string> token)
{
	//Print out spacing
	for(int i = 0; i < level; i++)
	{
		cout << "----";
	}

	//Print out the token of the node
	set<string>::iterator iter;
	cout << "[" << (*token.begin()).substr(0, 2) << "]: ";
	for(iter = token.begin(); iter != token.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}


void traversePreorder(string output_file_name, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	printToken(output_file_name, root->level, root->words);
	traversePreorder(output_file_name, root->left);
	traversePreorder(output_file_name, root->right);
}


void traverseInorder(string output_file_name, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	traverseInorder(output_file_name, root->left);
	printToken(output_file_name, root->level, root->words);
	traverseInorder(output_file_name, root->right);
}


void traversePostorder(string output_file_name, NodeT *root)
{
	if(root == NULL)
	{
		return;
	}

	traversePostorder(output_file_name, root->left);
	traversePostorder(output_file_name, root->right);
	printToken(output_file_name, root->level, root->words);
}

