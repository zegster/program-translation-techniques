/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: node.h
# Date: 5/10/20
==================================================================================================== */
#ifndef NODE_H
#define NODE_H
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
#include "token.h"
using namespace std;

typedef struct node_t
{
	int level;                         //The level of this node
	string label;                      //The label of this node (for corresponding to the nonterminal)(i.e. node.label = "<program>")
	vector<Token> tokens;              //The token of this node (store operators, identifiers, etc...)
	struct node_t *c1, *c2, *c3, *c4;  //This can be dynamic if need to (i.e. vector<struct node_t> child)
}NodeT;

#endif

