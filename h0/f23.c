#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "helper.h"
#include "f23.h"

static int global23 = 0;
void f2()
{
	fprintf(stderr, "F2 Helper Global: %d\n", global23);
	global23 += 2;	
}
void f3()
{
	fprintf(stderr, "F3 Helper Global: %d\n", global23);
	global23 += 3;	
}

