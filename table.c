#include "table.h"

int init_table(char name[9], Table** t,int block)
{
	(*t) = (Table*)malloc(sizeof(Table));
	if(!(*t))
		return 0;
	strcpy((*t)->name,name);
	(*t)->first_field_block = block;
	return 1;
}
int init_field(char name[9], Field** f,int block_cur, int block_next)
{
	(*f) = (Field*)malloc(sizeof(Field));
	if(!(*f))
		return 0;
	strcpy((*f)->name,name);
	(*f)->first_registry_block = block_cur;
	(*f)->next_field_block = block_next;
	return 1;
}
