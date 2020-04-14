/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testScanner.cpp
# Date: 3/8/2020
==================================================================================================== */
#include "token.h"
#include "scanner.h"
#include "testScanner.h"
#include "parser.h"

/* ====================================================================================================
* Function    :  testScanner()
* Definition  :  a simple function to test out the scanner.
* Parameter   :  an input file_name (string)
* Return      :  status code where error will return -1.
==================================================================================================== */
int testScanner(string file_name)
{
	//Init Scanner Object
	Scanner scanner;
	Parser parser;	

	//Check if the file is open and associated with the stream object
	ifstream file(file_name.c_str());
	//unsigned int current_line = 1;  //Keep track of the current line number of the file
	Token token;                    //Token holder for displaying purpose (can be useful later in the future...)
	if(file.is_open()) {
		string input;
		while(getline(file, input)) {

			//Invoke scanner() until each token in the current line has been identified
			while(scanner.scan(input, token) == 0) {
				scanner.tokenToString(token);
			}
			//current_line++;  //Increment the currnet line in the file when finish reading the current input
		}
		
		//Check for any open comment tag
		scanner.isCommentMode();
	}
	else {
		cout << "[ERROR] Can't open file!" << endl;
		return -1;
	}

	//Once all lines of the files has been traverse, return EOF token
	if(file.eof()) {
		scanner.invokeEOF(token);
		scanner.tokenToString(token);
	}

	//Close the reading file
	file.close();
	return 0;
}

