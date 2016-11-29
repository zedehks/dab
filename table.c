#include "table.h"

int init_table(table** t, int c, char name[TABLE_NAME_LENGTH])
{
	(*t) = malloc(sizeof(table));	
	(*t)->capacity = c;
	//(*t)->name = name;
	strcpy((*t)->name,name);
	//(*t)->next = NULL;
	if(!(*t) == '\0')
		return RETURN_OK;
	return RETURN_ERROR;
}

/*int append_table(table** original,int c)
{
	table* t = NULL;
	if(init_table(&t,c) == RETURN_ERROR) 
		return RETURN_ERROR;
	table* tmp = (*original);
	//while(tmp->next != NULL)


}
*/
