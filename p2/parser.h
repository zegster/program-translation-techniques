/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: parser.h
# Date: 4/13/2020
==================================================================================================== */
#ifndef PARSER_H
#define PARSER_H
#include <cstdio>        //Input and Output operations can also be performed in C++ using the C Standard Input and Output Library.
#include <cstdlib>       //Defines several general purpose functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <fstream>       //Input and output stream class to operate on files.
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include "node.h"
#include "scanner.h"
using namespace std;

/* Parser Class */
class Parser: public Scanner
{
	private:
		ifstream file;
		string file_input;
		Token tk;
		string expected_token;
		Scanner scanner;
		int scanner_status_code;

		//BNF of the program
		NodeT *program();
		NodeT *block();
		NodeT *vars();
		NodeT *expr();
		NodeT *N();
		NodeT *A();
		NodeT *M();
		NodeT *R();
		NodeT *stats();
		NodeT *mStat();
		NodeT *stat();
		NodeT *in();
		NodeT *out();
		NodeT *iffy();
		NodeT *loop();
		NodeT *assign();
		NodeT *label();
		NodeT *goTo();
		NodeT *RO();

		//Parser Function
		void nextParse();
		NodeT *createNode(string production_name);
		void parserError();

	public:
		Parser(string file_name);
		NodeT *parse();
};
#endif

