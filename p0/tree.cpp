/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: tree.cpp
# Date: 2/10/20
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include "node.h"
#include "tree.h"
using namespace std;


static const int BUFFER_SIZE = 256;
static int tree_size = 0;
static int max_token_length = 0;


NodeT *buildTree(istream &in)
{
	NodeT *root = NULL;

	if(in.eof())
	{	
		cout << "Test" << endl;
		return NULL;
	}
	else
		cout << "Merp" << endl;

	return root;
}

