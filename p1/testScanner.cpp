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
	if(file.is_open()) {
		unsigned int current_line = 1;
		string input;
		Token token;
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

	file.close();
	return 0;
}




