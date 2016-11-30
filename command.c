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
		print_help(0);
	else if(parse_command(input,"exit") == TRUE)
		return	CODE_EXIT;
	else if(parse_command(input,"add") == TRUE)
		add_table(input, b);
	else if(parse_command(input,"clear") == TRUE)
		clear();
	else if(parse_command(input,"list") == TRUE)
		list_tables(b);
	else if(parse_command(input,"edit") == TRUE)
		edit_table(b);
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
			printf("\nNo tables have been created.\n");
			return;
		}
		printf("Table %s\n", tmp->tables[i]->name);
	}
	
	list_tables( &(tmp->header->next) );
}

void edit_table(block_t** b)
{
	table *t;
	field *f;

	char f_name[32];
	char f_type[32];

	char input[32];
	char search_t[32];
	for(int i = 0;i<32;i++){
		input[i] = '\0';
		search_t[i] = '\0';
	}


	printf("\nWhat table do you wanna edit.\n");
	fgets(search_t,32,stdin);
	int len_t = strlen(search_t);
	if (len_t > 0 && search_t[len_t-1] == '\n')
		  search_t[len_t-1] = '\0';

	t = search_tables(search_t, b);

	if(t == NULL){
		printf("Table not found\n");
		return;
	}
	else{
	//printf("%s\n\t\t\t\t\n", t->name);

		print_help(1);

		/*printf("\nReady.\n");
		fgets(input,32,stdin);
		int len = strlen(input);
		if (len > 0 && input[len-1] == '\n')
			  input[len_t-1] = '\0';
		
		char input[32];
		for(int i = 0;i<32;i++)
			input[i] = '\0';*/


		printf("\nReady.\n");
		fgets(input,32,stdin);
		int len = strlen(input);
		if (len > 0 && input[len-1] == '\n')
			  input[len-1] = '\0';

		int exit = 0;
		while(exit == 0){

			if(parse_command(input,"print") == TRUE)
				print_table(t);

			else if(parse_command(input,"field") == TRUE){

				printf("Name of the new field: ");
				//scanf("%s", &f_name);
				fgets(f_name,32,stdin);

				printf("Type of field: ");
				//scanf("%s", &f_type);
				fgets(f_type,32,stdin);

				f = init_field(f_name,f_type);
				Add_field(f,t);
				printf("\nField added succesfully!\n");
			}

			else if(parse_command(input,"registry") == TRUE)
				Add_registry_Table(t);

			else if(parse_command(input,"back") == TRUE)
				exit = 1;	
			else
				printf("?\n");
		}
	}
}

table* search_tables(char* name, block_t** b)
{
	/*char* command;
	command = strtok(name," ");
	command = strtok(NULL," ");
	if(command == NULL) 
	{
		printf("\nPlease enter a name.\n");
		return NULL;
	}*/
	
	block_t* tmp = (*b);

	if((tmp) == NULL) 
	{
		return NULL;
	}
	for(int i=0;i< BLOCK_CAPACITY;i++)
	{	
		if(i >= tmp->header->amount_tables) 
			break;
		if(!strcmp((tmp->tables[i]->name), name))
		{
			printf("\nEncontrado...");
			return tmp->tables[i];
		}
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

void print_help(int option)
{

	if(option == 0){
		printf("\n\nUsage: [COMMAND] (PARAMETER)\n");
		printf("Note the space between the command and the parameter (if needed).");
		//printf("\nArguments choose the data structure:");
		printf("\n\nadd [NAME]\tAdd a table with the given name (maximum length %d)\n",TABLE_NAME_LENGTH);
		printf("\nedit\tgoes directly to edit's submenu\n");
		printf("\nlist\tList all available tables\n");
		printf("\nclear\tclears screen, may -not- work in non-POSIX terminals.\n");
		printf("\nhelp\tPrint this help page\n");
		printf("\nexit\tThis does something iunno what\n\n\n");
	}
	else{
		printf("\n\nUsage: [COMMAND] (PARAMETER)\n");
		printf("Note the space between the command and the parameter (if needed).");
		//printf("\nArguments choose the data structure:");
		printf("\n\nfield [NAME]\tadds a fields within the table (maximum length %d)\n",FIELD_NAME_LENGTH);
		printf("\nregistry [NAME]\tadds a registry within a field (maximum length %d)\n",REGISTRY_NAME_LENGTH);
		printf("\nprint\tprints all tables, fields & registry available on the table\n");
		printf("\nback\tgoes back to main screen.\n");
	}
}
