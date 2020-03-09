/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: token.cpp
# Date: 3/8/2020
==================================================================================================== */
#include "token.h"

/* Extern Variable from token.h */
map<string, string> operator_map;
map<string, string> keyword_map;

void initOperatorMap()
{
	operator_map.insert(make_pair(":=", "colonEqualTk"));
	operator_map.insert(make_pair("==", "equalEqualTk"));
	operator_map.insert(make_pair("=", "equalTk"));
	operator_map.insert(make_pair("<", "lessThanTk"));
	operator_map.insert(make_pair(">", "greaterThanTk"));
	operator_map.insert(make_pair(":", "colonTk"));
	operator_map.insert(make_pair("+", "plusTk"));
	operator_map.insert(make_pair("-", "minusTk"));
	operator_map.insert(make_pair("*", "multiplyTk"));
	operator_map.insert(make_pair("/", "divideTk"));
	operator_map.insert(make_pair("%", "modulusTk"));
	operator_map.insert(make_pair(".", "dotTk"));
	operator_map.insert(make_pair(",", "commaTk"));
	operator_map.insert(make_pair(";", "semiColonTk"));
	operator_map.insert(make_pair("(", "leftParenTk"));
	operator_map.insert(make_pair(")", "rightParenTk"));
	operator_map.insert(make_pair("{", "leftCurlyTk"));
	operator_map.insert(make_pair("}", "rightCurlyTk"));
	operator_map.insert(make_pair("[", "leftBracketTk"));
	operator_map.insert(make_pair("]", "rightBracketTk"));
}


void initKeywordMap()
{
	keyword_map.insert(make_pair("label", "labelTk"));
	keyword_map.insert(make_pair("goto", "gotoTk"));
	keyword_map.insert(make_pair("loop", "loopTk"));
	keyword_map.insert(make_pair("void", "voidTk"));
	keyword_map.insert(make_pair("declare", "declareTk"));
	keyword_map.insert(make_pair("return", "returnTk"));
	keyword_map.insert(make_pair("in", "inTk"));
	keyword_map.insert(make_pair("out", "outTk"));
	keyword_map.insert(make_pair("program", "programTk"));
	keyword_map.insert(make_pair("iffy", "iffyTk"));
	keyword_map.insert(make_pair("then", "thenTk"));
	keyword_map.insert(make_pair("assign", "assignTk"));
	keyword_map.insert(make_pair("data", "dataTk"));
}

void tokenToString(Token tk)
{
	cout << "Line #" << tk.line_number << ": " << token_names[tk.id] << " | " << tk.value << endl; 
}


int isOperator(char ch)
{
	//Return 1 when input character is an operator
	for(unsigned int i = 0; i < OPERATOR_SIZE; i++)
	{
		if(ch == operators[i])
			return 1;
	}
	
	//Return -1 when input character is not an operator
	return -1;
}


int isKeyword(Token &tk)
{
	for(unsigned int i = 0; i < KEYWORD_SIZE; i++)
	{
		if(tk.value.compare(keywords[i]) == 0)
		{
			tk.value = keyword_map[tk.value];
			return i;
		}
	}

	return -1;
}
