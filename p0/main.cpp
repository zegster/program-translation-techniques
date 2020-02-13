/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: main.cpp
# Date: 2/10/20
# Purpose:
	Programming refreshment, practice with standards and header files, practice with trees, 
	traversals, command line arguments, and file IO. Write a program to build a tree and print it 
	using different traversals. 
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <fstream>       //Input/output stream class to operate on files.
#include "node.h"
#include "tree.h"
#include "traversal.h"
using namespace std;


/* ====================================================================================================
MAIN
==================================================================================================== */
int main(int argc, char *argv[])
{
	/* File Variable */
	string file_name;
		
	/* Binary Search Tree Variable */
	NodeT *root = NULL;

	switch(argc)
	{
		case 1:
		{
			//Initialize variable for temporary file
			string user_input;
			ofstream temp_file;

			//Set file name for temporary file
			file_name = "temp.dat";
			temp_file.open(file_name.c_str());

			//Writing user input into a temporary file and close the file when done
			cout << "[NOTICE] Reading from the keyboard." << endl;
			cout << "Please enter alphanumeric characters (enter an empty line to finsh)" << endl;
			do
			{
				getline(cin, user_input);
				temp_file << user_input << " ";
			}
			while(!user_input.empty());	
			temp_file.close();
			break;
		}

		case 2:
		{
			cout << "[NOTICE] Reading from file." << endl;
			break;
		}
		
		default:
		{
			cout << "[ERROR] Too many arguments!" << endl;
			cout << "Usage: ./main [file]" << endl;
		}
	}


	return 0;
}

