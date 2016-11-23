#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RETURN_OK 1
#define RETURN_ERROR -1
#define TABLE_NAME_LENGTH 16
typedef struct table table;
struct table
{
	//ZQtable* next;
	int first_field_block;
	int first_registry_block;
	int capacity;	
	char name[TABLE_NAME_LENGTH];
};

int init_table(table** t, int c, char name[TABLE_NAME_LENGTH]);
#endif /* TABLE_H */
