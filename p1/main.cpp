/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: main.cpp
# Date: 3/8/20
# Purpose:
	We will be implementing a scanner for the provided lexical definitions. 
	The scanner is embedded and thus it will return one token every time it is called. 
	Since the parser is not available yet, we will use a tester program to call the scanner. 
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <cstdio>        //Input and Output operations can also be performed in C++ using the C Standard Input and Output Library.
#include <fstream>       //Input and output stream class to operate on files.
#include "testScanner.h"
using namespace std;


/* ====================================================================================================
MAIN
==================================================================================================== */
int main(int argc, char *argv[])
{
	/* File Variable */
	string file_name;
	string output_file_name;
		
	/* Processing program given arguments */
	switch(argc)
	{
		case 1:/* Reading from the keyboard */
		{
			cout << "[NOTICE] Reading from the keyboard." << endl;
			string user_input;
			ofstream temp_file;

			//Set file name for temporary file
			file_name = "temp.dat";
			temp_file.open(file_name.c_str());

			//Writing user input into a temporary file and close the file when done
			cout << "Enter token (return an empty line to finish).";
			do
			{
				cout << endl << ">>: ";
				getline(cin, user_input);
				temp_file << user_input << endl;
			}
			while(!user_input.empty());	

			//Close file when done
			cout << "[NOTICE] Finish inputting! Proceeding..." << endl << endl;
			temp_file.close();
			output_file_name = "output";
			break;
		}

		case 2:/* Reading from file */
		{
			cout << "[NOTICE] Reading from file." << endl << endl;

			//Construct output file name
			file_name = argv[1];
			size_t extension_index = file_name.find(".");

			//Check if there is extension. If not, append the implicit extension. As well as grabbing the file name for the output file
			if(extension_index == string::npos)
			{
				output_file_name = file_name;
				file_name.append(".sp2020");
			}
			else
			{
				output_file_name = file_name.substr(0, extension_index);
			}
			break;
		}
		
		default:/* Invalid Usage */
		{
			cout << "[ERROR] Too many arguments!" << endl;
			cout << "Usage: " << argv[0] << " [file]" << endl;
			return 1;
		}
	}

	/* Invoking Test Program */
	testScanner(file_name);

	return 0;
}

