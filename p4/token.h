/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: token.h
# Date: 5/10/2020
==================================================================================================== */
#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>      //For cout and cin; input and output.
#include <map>           //Dictionary like data structure.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
using namespace std;

/* Enumeration */
enum token_id { idTk, keywordTk, intTk, opTk, eofTk };

/* Token Structure */
typedef struct token
{
	token_id id;        //The id that represent the token category
	int line_number;    //Line location of where the token reside
	string data;        //The actual scan value of the token
	string type;	    //The type of the token
	string value;       //The value of the token
} Token;

/* Language Class */
class Language
{
	protected:
		//Operator Map & Keyword Map
		map<string, string> operator_map;
		map<string, string> keyword_map;

		//Token Categories (should match with token_id enum)
		const vector<string> token_names = { 
			"Identfier", "Keyword", "Integer", "Operator", "End Of File"
		};

		//Reserved Keyword
		const vector<string> keywords = {
			"label", "goto", "loop", "void", "declare", 
			"return", "in", "out", "program", "iffy", 
			"then", "assign", "data"
		};

		//Delimiter
		const char COMMENT_DELIMITER = '#';

		//Operator (single and non-single)
		const vector<char> operators = {
			'=', '<', '>', ':',
			'+', '-', '*', '/', '%',
			'.', ',', ';', '(', ')',
			'{', '}', '[', ']'
		};
		const vector<string> ns_operators = {
			":=", "=="
		};
	
		void initOperatorMap();
		void initKeywordMap();
		int isOperator(char ch);
		int isNonSingleOperator(string str);
		int getOperator(Token &tk);
		int getKeyword(Token &tk);

	public:
		void tokenToString(Token tk);
};
#endif

