#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"

#define CODE_EXIT 1
#define FALSE 0
#define TRUE 1

int get_command(block_t** b);
void add_table(char* name,block_t** b);
void print_help();
int parse_command(char command[32], char* comparison);
void list_tables(block_t**b);
block_t* search_tables(char* name, block_t** b);
#endif /* COMMAND_H */
