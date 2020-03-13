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
#include <map>           //Dictionary like data structure
using namespace std;

/* Token Categories */
const int TOKEN_SIZE = 5;
enum token_id { idTk, keywordTk, intTk, opTk, eofTk };
const string token_names[TOKEN_SIZE] = { 
	"Identfier", "Keyword", "Integer", "Operator", "End Of File"
};


/* Reserved Keyword */
const int KEYWORD_SIZE = 13;
const string keywords[KEYWORD_SIZE] = {
	"label", "goto", "loop", "void", "declare", "return",
	"in", "out", "program", "iffy", "then", "assign",
	"data"
};


/* Operator (note that "operator" is a reserve word for C++) */
const int OPERATOR_SIZE = 18;
const char operators[OPERATOR_SIZE] = {
	'=', '<', '>', ':',
	'+', '-', '*', '/', '%',
	'.', ',', ';', '(', ')',
	'{', '}', '[', ']'
};
const int NS_OPERATOR_SIZE = 2;
const string ns_operators[NS_OPERATOR_SIZE] = {
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
/* Allow scanner to access from it */
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

