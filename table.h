#ifndef TABLE_H
#define TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define B_CAPACITY 3// 3 tables at most per block

typedef struct table Table;

struct table
{
	char name[9]; //9 bytes
	int first_field_block;//4 bytes
};

typedef struct field Field;

struct field
{
	char name[9]; //9 bytes
	int first_registry_block;//4 bytes
	int next_field_block;//4 bytes
};

//Sugeriria que los registros hasheados tambien sean definidos aca, por simplicitud
int init_table(char name[9], Table** t, int block); 
int init_field(char name[9], Field** f, int block_cur, int block_next); 
#endif /* TABLE_H  */
