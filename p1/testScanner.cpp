/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testScanner.cpp
# Date: 3/8/2020
==================================================================================================== */
#include "token.h"
#include "scanner.h"
#include "testScanner.h"
#include <unistd.h>

int testScanner(string file_name)
{
	//Init operator and keyword map
	initOperatorMap();
	initKeywordMap();
	
	//Check if teh file is open and associated with the stream object
	ifstream file(file_name.c_str());
	unsigned int current_line = 1;  //Keep track of the current line number of the file
	Token token;                    //Token holder for displaying purpose (can be useful later in the future...)
	if(file.is_open()) {
		string input;
		while(getline(file, input)) {
			//Filter input by removing comments and whitespace

			//Invoke scanner() until each token in the current line has been identified
			resetScannerPointer();
			while(scanner(current_line, input, token) == 0) {
				tokenToString(token);
				sleep(1);
			}

			//Increment the currnet line in the file
			current_line++;
		}
	}
	else {
		cout << "[ERROR] Can't open file!" << endl;
		return -1;
	}

	//Once all lines of the files has been traverse, print the EOF token
	if(file.eof()) {
		//Check if the current line is the initial line. If not, reduce by 1
		if(current_line > 1) {
			current_line--;
		}

		//Display EOF token
		token.line_number = current_line;
		token.id = eofTk;
		token.value = "EOF";
		tokenToString(token);
	}

	file.close();
	return 0;
}




