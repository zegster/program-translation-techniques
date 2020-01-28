//Global live in the main file
#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "functionOne.h"
#include "functionTwoThree.h"

int main(int argc, char *argv[])
{
	f1();
	f2();
	f3();
	f1();
	f3();
	return 0;
}

