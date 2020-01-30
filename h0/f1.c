#include <stdlib.h>     //exit()
#include <stdio.h>      //printf()
#include <stdbool.h>    //bool variable
#include <stdint.h>     //for uint32_t
#include <string.h>     //str function
#include <unistd.h>     //standard symbolic constants and types
#include "helper.h"
#include "f1.h"
#define M1a
static void f1a();
int global;


void f1()
{
	fprintf(stderr, "F1 Global: %d\n", global);
	global += 1;
	f1a();
}

static void f1a()
{
	fprintf(stderr, "Merp...\n");
}

