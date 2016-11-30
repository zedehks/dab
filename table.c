#include "table.h"

int init_table(table** t, int c, char name[TABLE_NAME_LENGTH])
{
	(*t) = malloc(sizeof(table));	
	(*t)->capacity = c;
	//(*t)->name = name;
	strcpy((*t)->name,name);
	(*t)->first_field = NULL;
	//(*t)->next = NULL;
	if(!(*t) == '\0')
		return RETURN_OK;
	return RETURN_ERROR;
}

field* init_field(char name[FIELD_NAME_LENGTH], char type[DATA_TYPE_LENGTH])
{
	field* f = malloc(sizeof(field));
	strcpy(f->name, name);
	strcpy(f->data_type, type);
	f->next_field = NULL;
	f->first_registry = NULL;
	return f;
}

void Add_field(field *f,table *t)
{
	if(t->first_field = NULL)
		t->first_field = f;
	else{
		field *h = t->first_field;
		while(h->next_field != NULL){
			h = h->next_field;
		}
		h->next_field = f;
	}
	printf("Field added! \n");
}

registry *init_registry(char type[DATA_TYPE_LENGTH], char str[REGISTRY_NAME_LENGTH], char integer)
{
	registry *r = malloc(sizeof(registry));
	strcpy(r->type,type);
	if(!strcmp(r->type, "int"))
		r->INTEGER = integer;
	else
		strcpy(r->STR, str);
	r->next_registry = NULL;
	return r;
}	

void Add_registry_field(field * f)
{
	char command_registry[20];
	int command_int;

	if(!strcmp(f->data_type, "int")){
		printf("Type registry %d", f->name);
		scanf("%d", &command_int);
	}
	else{
		printf("Type registry %s", f->name);
		scanf("%s", &command_registry);
	}

	registry *r = init_registry(r->type,command_registry,command_int);

	if(f->first_registry == NULL){
		f->first_registry = r;
	}

	else{
		registry *tmp = f->first_registry;
		while(tmp->next_registry != NULL){
			tmp = tmp->next_registry;
		}

		tmp->next_registry = r;
	}
}

void Add_registry_Table(table *t)
{
	field *f = t->first_field;
	while(f->next_field != NULL){
		Add_registry_field(f);
		f = f->next_field;
	}
}

void print_registry(registry* r)
{
	if(strcmp(r->type,"int")){
		printf("%d",r->INTEGER);
	}
	else{
		printf("%s",r->STR);
	}
}

void print_field(field *f)
{
	registry *r = f->first_registry;
	while(r->next_registry != NULL){
		r = r->next_registry;
	}
	print_registry(r);
	printf("\t");
}

void print_table(table *t)
{
	field *f = malloc(sizeof(field));

	f = t->first_field;
	while(f->next_field != NULL){
		printf("%s \t", f->name);
		f = f->next_field;
	}

	printf("%s \n", f->name);

	for(int i=0; i < 2; i++){
		f = t->first_field;
		while(f->next_field != NULL){
			print_field(f);
			f = f->next_field;
		}
		printf("\n");
	}
}
