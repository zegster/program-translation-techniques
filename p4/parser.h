/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: parser.h
# Date: 5/10/2020
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
		ifstream file;            //File pointer
		string file_input;        //Keep track of the current line input of the file

		Token tk;                 //Token holder
		Token EMPTY_TK;           //Empty token holder

		Scanner scanner;          //Scanner object
		int scanner_status_code;  //Keep track of the scanner status wheter to grab a new line or use old line

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
		void nextScan();
		NodeT *createNode(string production_name);
		void parserError(string expected_token);

	public:
		Parser(string file_name);
		NodeT *parse();
};
#endif

