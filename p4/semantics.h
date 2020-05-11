/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: semantics.h
# Date: 5/10/2020
==================================================================================================== */
#ifndef SEMANTICS_H
#define SEMANTICS_H
#include <fstream>       //Input and output stream class to operate on files.
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
#include "node.h"
#include "token.h"
using namespace std;

typedef struct symbol_table
{
	Token identifier;
	Token value;
	//Can add more expansion later...
} SymbolTable;

class Semantics: public Language
{
	private:
		ofstream file;
		string output_file_name;

		SymbolTable st_holder;
		vector<SymbolTable> st;

		unsigned int tempvars_num = 0;
		unsigned int templabels_num = 0;

		void checkDeclare(Token id, Token val);
		void checkDefined(Token tk);
		void validate(NodeT *node);
		void generate(NodeT *node);

	public:
		Semantics(string file_name);
		void codeGeneration(NodeT *node);
};

#endif

