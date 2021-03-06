#include "command.h"
//#define clear() printf("\033[H\033[J")
void clear()
{
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
    	#endif

	#if defined(_WIN32) || defined(_WIN64)
	system("cls");
	#endif
}//Solution by nbro, stolen from https://stackoverflow.com/questions/2347770/how-do-you-clear-console-screen-in-c

int get_command(block_t** b)
{
	char input[32];
	for(int i = 0;i<32;i++)
		input[i] = '\0';


	printf("\nReady.\n");
	fgets(input,32,stdin);
	int len = strlen(input);
	if (len > 0 && input[len-1] == '\n')
		  input[len-1] = '\0';

	if(parse_command(input,"help") == TRUE)
		print_help();
	else if(parse_command(input,"exit") == TRUE)
		return	CODE_EXIT;
	else if(parse_command(input,"add") == TRUE)
		add_table(input, b);
	else if(parse_command(input,"clear") == TRUE)
		clear();
	else if(parse_command(input,"list") == TRUE)
		list_tables(b);
	else if(parse_command(input,"search") == TRUE)
	{
		table *t = search_tables(input, b);
		if(t != NULL) printf("\nFound Table %s", t->name);
	}
	else
		printf("?\n");
	return 0;
}

void list_tables(block_t**b)
{
	block_t* tmp = (*b);
	if( (tmp) == NULL) return;
	for(int i = 0;i<BLOCK_CAPACITY;i++)
	{
		if(tmp->tables[i] == NULL) 
		{
			//printf("\nNo tables have been created.\n");
			return;
		}
		printf("Table %s\n", tmp->tables[i]->name);
	}
	
	list_tables( &(tmp->header->next) );
}
table* search_tables(char* name, block_t** b)
{
	char* command;
	command = strtok(name," ");
	command = strtok(NULL," ");
	if(command == NULL) 
	{
		printf("\nPlease enter a name.\n");
		return;
	}

	block_t* tmp = (*b);

	if((tmp) == NULL) 
	{
		return NULL;
	}
	for(int i=0;i< BLOCK_CAPACITY;i++)
	{	
		if(i >= tmp->header->amount_tables) break;
	//	printf("Table %s\n", tmp->tables[i]->name);
		if(!strcmp((tmp->tables[i]->name), command))
		{
			printf("\nEncontrado...");
			return tmp->tables[i];
		}
		//tmp = tmp->header->next;
	}
		printf("\nNo Encontrado...");
		return NULL;
}

void add_table(char* name, block_t** b)
{
	//we gotta grab the name from the command first
	char* tmp;
	tmp = strtok(name," ");
	tmp = strtok(NULL," ");
	if(tmp == NULL) 
	{
		printf("\nPlease enter an eight-character name.\n");
		return;
	}
	//if(strlen(tmp > 8)) I'll look into why this aint needed later lol
	{	
		char tmp2[TABLE_NAME_LENGTH+1];//max name size, plus the null char
		for(int i =0;i<=TABLE_NAME_LENGTH;i++)
		{
			tmp2[i] = tmp[i];
		}
		tmp2[TABLE_NAME_LENGTH] = '\0';
		strcpy(tmp,tmp2);
	}
	if(block_add_table(b,tmp) == 0)	
		printf("\nCreated a new table \"%s\".\n",tmp);
}


int parse_command(char command[32],char* comparison)
{
	//char buffer = command[0];
	

	for(int i = 0;i<32;i++)
	{
		if(comparison[i] == '\0' || command[i] == ' ') break;
		if(command[i] != comparison[i])
		{
			return FALSE;
		}
		//else
		//	printf("%c, %c ok\n",command[i],comparison[i]);
	}
	return TRUE;
}

void print_help()
{
	printf("\n\nUsage: [COMMAND] (PARAMETER)\n");
	printf("Note the space between the command and the parameter (if needed).");
	//printf("\nArguments choose the data structure:");
	printf("\n\nadd [NAME]\tAdd a table with the given name (maximum length %d)\n",TABLE_NAME_LENGTH);
	printf("\nsearch [NAME]\tsearch a table with the given name (maximum length %d)\n",TABLE_NAME_LENGTH);
	printf("\nlist\tList all available tables\n");
	printf("\nclear\tclears screen, may -not- work in non-POSIX terminals.\n");
	printf("\nhelp\tPrint this help page\n");
	printf("\nexit\tThis does something iunno what\n\n\n");

}

