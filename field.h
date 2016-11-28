#ifndef FIELD_H
#define FIELD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 1
#define ERROR -1
typedef struct field field;

struct field
{
	int first_field_block;
	int first_registry_block;
	int capacity;	
	char name[TABLE_NAME_LENGTH];
};

int init_field(field** f, int c, char name[TABLE_NAME_LENGTH]);
#endif 
