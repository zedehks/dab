#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RETURN_OK 1
#define RETURN_ERROR -1
#define TABLE_NAME_LENGTH 16
#define FIELD_NAME_LENGTH 10
#define REGISTRY_NAME_LENGTH 10
#define DATA_TYPE_LENGTH 5

typedef struct field field;
typedef struct table table;
typedef struct registry registry;

struct table
{
	//ZQtable* next;
	field *first_field;
	int capacity;	
	char name[TABLE_NAME_LENGTH];
};

struct field
{
	char data_type[DATA_TYPE_LENGTH];
	char name[FIELD_NAME_LENGTH];
	field *next_field;
	registry *first_registry; 
};

struct registry
{
	char type[DATA_TYPE_LENGTH];
	char STR[REGISTRY_NAME_LENGTH];
	int INTEGER;
	registry *next_registry;
};


int init_table(table** t, int c, char name[TABLE_NAME_LENGTH]);
field* init_field(char name[TABLE_NAME_LENGTH], char* type);
registry *init_registry(char type[DATA_TYPE_LENGTH], char str[REGISTRY_NAME_LENGTH], char integer);

void Add_field(field *f,table *t);
void Add_registry_Table(table *t);
void Add_registry_field(field * f);

void print_table(table *t);
void print_field(field *f);
void print_registry(registry* r);

#endif /* TABLE_H */
