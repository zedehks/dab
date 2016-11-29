#include "field.h"

int init_field(field** f, int c, char name[TABLE_NAME_LENGTH])
{
	(*f) = malloc(sizeof(field));	
	(*f)->capacity = c;
	strcpy((*f)->name,name);
	
	if(!(*f) == '\0')
		return OK;
	return ERROR;
}