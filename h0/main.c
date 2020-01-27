//Global live in the main file
#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "functionOne.h"
#include "functionTwo.h"
int global = 11;
int global23 = 23;

int main(int argc, char *argv[])
{
	f1();
	f2();
	return 0;
}

