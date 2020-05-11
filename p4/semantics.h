/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: semantics.h
# Date: 5/10/2020
==================================================================================================== */
#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
#include "node.h"
#include "token.h"
using namespace std;

typedef struct symbol_table
{
	Token identifier;
	//Token value;
	//Can add more expansion later...
} SymbolTable;

class Semantics
{
	private:
		ofstream file;
		string output_file_name;

		SymbolTable st_holder;
		vector<SymbolTable> st;

		void checkDeclare(Token tk);
		void checkDefined(Token tk);

	public:
		Semantics(string file_name);
		void validate(NodeT *node);
};

#endif

