/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: token.h
# Date: 3/8/2020
==================================================================================================== */
#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <map>           //Dictionary like data structure.
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
using namespace std;


/* Language Class */
class Language
{
	public:
	string merp = "merp";
};


/* Token Categories */
enum token_id { idTk, keywordTk, intTk, opTk, eofTk };
const vector<string> token_names = { 
	"Identfier", "Keyword", "Integer", "Operator", "End Of File"
};


/* Reserved Keyword */
const vector<string> keywords = {
	"label", "goto", "loop", "void", "declare", "return",
	"in", "out", "program", "iffy", "then", "assign",
	"data"
};


/* Operator */
const vector<char> operators = {
	'=', '<', '>', ':',
	'+', '-', '*', '/', '%',
	'.', ',', ';', '(', ')',
	'{', '}', '[', ']'
};
const vector<string> ns_operators = {
	":=", "=="
};


/* Delimiter */
const char COMMENT_DELIMITER = '#';


/* Token Structure */
typedef struct token
{
	token_id id;        //The id that represent the token category
	int line_number;    //Line location of where the token reside
	string value;       //The description value of the token
} Token;


/* Operator Map & Keyword Map */
//map<string, string> operator_map;
//map<string, string> keyword_map;
extern map<string, string> operator_map;
extern map<string, string> keyword_map;


/* Token Function Prototype */
void initOperatorMap();
void initKeywordMap();
void tokenToString(Token tk);
int isOperator(char ch);
int isNonSingleOperator(string str);
int getOperator(Token &tk);
int getKeyword(Token &tk);
#endif

