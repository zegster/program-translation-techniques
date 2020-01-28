#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "helper.h"
#include "functionOne.h"
void f1()
{
	fprintf(stderr, "F1 Global: %d\n", global);
	global += 1;
	f1a();
}

void f1a()
{
	fprintf(stderr, "Merp...\n");
}

