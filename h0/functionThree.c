#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "functionThree.h"
void f3()
{
	global = 3;
	fprintf(stderr, "F3 Global: %d\n", global);
	fprintf(stderr, "F3 Helper Global: %d\n", global23);
}

