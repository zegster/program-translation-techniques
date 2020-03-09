/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: token.h
# Date: 3/8/2020
==================================================================================================== */
#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <map>
using namespace std;

/* Token Categories */
const int TOKEN_SIZE = 5;
enum token_id { idTk, intTk, keywordTk, opTk, eofTk };
const string token_names[TOKEN_SIZE] = { 
	"Identfier", "Keyword", "Operator", "Integer", "End Of File"
};

/* Reserved Keyword Name */
const int KEYWORD_SIZE = 13;
const string keywords[KEYWORD_SIZE] = {
	"label", "goto", "loop", "void", "declare", "return",
	"in", "out", "program", "iffy", "then", "assign",
	"data"
};

/* Operator Name (note that "operator" is a reserve word for C++) */
const int OPERATOR_SIZE = 19;
const char COMMENT_DELIMITER = '#';
const char operators[OPERATOR_SIZE] = {
	'#', '=', '<', '>', ':',
	'+', '-', '*', '/', '%',
	'.', ',', ';', '(', ')',
	'{', '}', '[', ']'
};



/* Token Structure */
typedef struct Token
{
	token_id id;
	int line_number;
	string value;
} token;

/* Operator Map & Keyword Map */
/* Allow scanner to access from it */
extern map<string, string> operator_map;
extern map<string, string> keyword_map;



void initOperatorMap();
void initKeywordMap();
void tokenToString(token tk);
int isOperator(char ch);
int isKeyword(token &tk);

#endif

