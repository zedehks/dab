#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "block.h"

char* get_tagline();
int interpret_input(char* input);
int parse_command(char command[32], char* comparison);
void print_h();
int first_available_block(int output);
int add_table(char* name);
int extract_int(char* command);
void clear();
void reset();
void print_tables();
void update_metadata(int block);
// in functions, tape = the file
// should have renamed it, but ¯\_(°_°)_/¯
int write_tape();
int read_tape();

//contiene info sobre los bloques disponibles
//si un bloque en el char = 0 esta disponible
//si == algun numero pero no 'f' esta parcialmente lleno de tablas
//f means ur fugged, it's full
//TODO: hacer que se creen nuevos metablocks cuando estos esten llenos
struct metadata
{
	char blocks[62];
	short next_metablock;
}Metadata;
Block* head_block;
FILE* f;

int main()
{
	srand(time(NULL));
	// Initialize Block list header
	//init_block('t',0,&head_block);

	// File I/O
	f = fopen("database.dab","rb+");
	if(!f)
	{
		// File not found! let's make it!
		reset();
		if(write_tape())
			printf("\nCreated Database file\n");
	}
	else	
	{
		printf("\nDatabase found\n");
		read_tape();
	}
	//length = ftell (f);     // get the length of the file
	//fseek (f, 64, SEEK_SET); // go to location of first block in file
	//fread(tape,1,length,f);

	// Initial greeting preparations & printing
	char* tagline = get_tagline();
	printf("\n~~DaB: The DataBase~~\n%s\n",tagline);
	int exit = 0;
	char input[32];
	print_h();

	//main loop
	while(exit == 0)
	{
		//clear input 
		for(int i = 0;i<32;i++)  
			input[i] = '\0';
		//print prompt
		printf("\n$ ");
		//yank input and add null byte at end
		fgets(input,32,stdin);
		int len = strlen(input);
		if(len > 0 && input[len-1] == '\n') 
		       	input[len-1] = '\0';
		exit = interpret_input(input);
	}
	write_tape();
	free(head_block);
	fclose(f);
	return 0;
}

int read_tape()
{
	fseek(f,0,SEEK_SET);	
	fread(Metadata.blocks,1,62,f);
	fread(&(Metadata.next_metablock),sizeof(short),1,f);
	printf("Reading blocks... ");
	for(int i = 0;i<62;i++)
		printf("%d ",Metadata.blocks[i]);
	printf("\nDone\n");
	Block* tmp;// = head_block;
	while(tmp)
	{
		int t_int;
		char t_char;
		int table_block;
		char table_name[9];
		
		fread(&t_int,1,sizeof(int),f);
		fread(&t_char,1,sizeof(char),f);
		if(init_block(t_char,t_int,&tmp) != 1)
		{
			printf("Cannot read block.\n");
			return 0;
		}
		
		printf("Read block %d.\n",tmp->n_block);
		for(int i = 0;i<4;i++)
		{
			fread(table_name,9,sizeof(char),f);
			fread(&table_block,1,sizeof(int),f);
			if(table_name[0] == 0)
			{
				tmp->tables[i] = 0;
				fseek(f,13,SEEK_CUR);
				break;
			}
			init_table(table_name,&(tmp->tables[i]),table_block);
			//strcpy(tmp->tables[i]->name,table_name);
			//tmp->tables[i]->first_field_block;
		}
		if(tmp->n_block == 0)
			head_block = tmp;
		tmp = tmp->next;
	}
	//head_block = tmp;
	if(!head_block)
		return 1;
	printf("Cannot read block.\n");
	return 0;
}
int write_tape()
{
	fseek(f,0,SEEK_SET);	
	fwrite(Metadata.blocks,1,62,f);
	fwrite(&(Metadata.next_metablock),sizeof(short),1,f);

	//write first block
	Block* tmp = head_block;
	while(tmp)
	{
		int t_int = tmp->n_block;	
		char t_char = tmp->type;	
		char table_name[9];
		
		fwrite(&t_int,1,sizeof(int),f);
		fwrite(&t_char,1,sizeof(char),f);
		for(int i = 0;i<4;i++)
		{
			if(tmp->tables[i])
			{
				strcpy(table_name,tmp->tables[i]->name);
				t_int = tmp->tables[i]->first_field_block; 
				fwrite(table_name,9,sizeof(char),f);
				fwrite(&t_int,1,sizeof(int),f);
			}
			else
			{
				t_char = 0;
				fwrite(&t_char,13,sizeof(char),f);
			}
		}
		t_char = 0;			  //write crap 
		fwrite(&t_char,7,sizeof(char),f);//so block reaches 64 Bytes
		tmp = tmp->next;
	}
	return 1;
}
int first_available_block(int output)
{
	for(int i = 0; i<62;i++)
	{
		if(Metadata.blocks[i] != 'f')//o for 'occupied'
		{
			if(output != 0)
				printf("\nBlock available: %d",i);
			return i;
		}
	}	
	printf("\nBlock not available");
	return -1;//TODO: make it so it continues with next metablock
}
void reset()
{
	f = fopen("database.dab","wb+");
	Metadata.next_metablock = -1;
	for(int i = 0;i<62;i++)
		Metadata.blocks[i] = 0;
	Metadata.next_metablock = -1;
	init_block('t',first_available_block(0),&head_block);
	printf("\nReset database\n");
}
int interpret_input(char* input)
{
	//command parsing tree (sorry for all the if/elses) :(	
	if(parse_command(input,"h") == 1) 
		print_h();  
	else if(parse_command(input,"c") == 1) 
		clear();
	else if(parse_command(input,"quit") == 1) 
		printf("\nNO ESCAPE\n");
	else if(parse_command(input,"q") == 1) 
		return -1;
	else if(parse_command(input,"a") == 1) 
	{
		add_table(input);
	}
	else if(parse_command(input,"r") == 1) 
	{
		reset();
	}
	else if(parse_command(input,"l") == 1) 
		print_tables();
	
	
	//just for fun
	//these were already made for another program no I didnt waste time making these
	else if(parse_command(input,"?") == 1) 
		printf("Right back at ya.\n");
	else if(parse_command(input,"¿") == 1) 
		printf("You have to go back.\n");
	else if(parse_command(input,"cyka") == 1) 
		printf("Ah, I see you're a good friend of president Trump.\n");
	else if(parse_command(input,"fug") == 1) 
		printf(":D\n");
	else if(parse_command(input,"blyat") == 1) 
		printf("The CIA would like to have a word with you.\n");
	else if(parse_command(input,"日本語") == 1) 
		printf("お前の母は馬の顔有る。\n");
	else
		printf("?");
	return 0;
}
int parse_command(char command[32], char* comparison)
{
	if(command[0] == ' ') return 0;
	for(int i = 0;i<32;i++)
	{
		if(comparison[i] == '\0' || command[i]==' ') 
			break;
		if(command[i] != comparison[i]) 
		       	return 0;
	}
	return 1;
}

void print_tables()
{
	Block* tmp = head_block;
	while(tmp)// && !tmp->content)
	{
		if(tmp->tables[0])
		{
			printf("Table is NULL\n");
			tmp=tmp->next;
			continue;
		}
		printf("Table %s\n",tmp->tables[0]->name);
		printf("Table %s\n",tmp->tables[1]->name);
		printf("Table %s\n",tmp->tables[2]->name);
		tmp = tmp->next;
	}
}
int add_table(char* name)
{
	//we gotta grab the name from the command first
	char* tmp;
	tmp = strtok(name," ");
	tmp = strtok(NULL," ");
	if(tmp == NULL) 
	{
		printf("\nPlease enter an eight-character name.\n");
		return 0;
	}
	//if(strlen(tmp > 8)) I'll look into why this aint needed later lol
	{
		char tmp2[7+1];//max name pointer size, plus the null char
		for(int i =0;i<=7;i++)
		{
			tmp2[i] = tmp[i];
		}
		tmp2[8] = '\0';
		strcpy(tmp,tmp2);
	}
	int block = first_available_block(0);
	printf("Attempting to add table at block %d.\n",block);

	if(block != -1 && block != 0)// did this kinda backwards but it matters not at this point
	{	
		printf("Error adding table at block %d.\n",block);
		return 0;
	}
	else if(block == 0 && head_block)// no table created yet
	{
		init_table(tmp,&(head_block->tables[0]),block);
		update_metadata(block);
		printf("\nCreated a new table \"%s\"",head_block->tables[0]->name);
		printf(" at block %d.\n",head_block->n_block);
		return 1;
	}

	printf("(end)Error adding table.\n");
	return 0;
}
void print_h()
{
	printf("\nCommands:\na [name]\t Add a new table [name] (max 8 char name).");
	printf("\nr [name]\t Remove table [name].");
	printf("\n\tNote: [int] in previous commands must be positive.\n");
	printf("\nl\t Print out tree.");
	printf("\nc\t Clear your troubles away.");
	printf("\nr\t Reset everything to a blank slate.");
	printf("\nh\t This thing is just spitting ?'s at me HELP.");
	printf("\nq\t End it all.\n");
}
void update_metadata(int block)
{
	Metadata.blocks[block] += 1;
	if(Metadata.blocks[block] == 3)
		Metadata.blocks[block] = 'f';
}
int extract_int(char* command)
{
	char *tmp;
	tmp = strtok(command," ");
	tmp = strtok(NULL," ");
	if(tmp == NULL)
	{
		printf("? Missing/incorrect parameter\n");
		return -1;
	}

	return atoi(tmp);
}

char* get_tagline()
{
	char* tagline;
	switch(rand()%10) 
	{
		case 0:
		tagline = "\"You getting tired of debugging yet?\"";
		break;
		case 1:
		tagline = "\"Is it really just a \'dance\'?\"";
		break;
		case 2:
		tagline = "\"You kids and your memes are incomprehensible these days.\"";
		break;
		case 3:
		tagline = "\"I sometimes wish we could go back to those days,\nwhere pointers were just that scary C thing Java ain't got no need of.\"";
		break;
		case 4:
		tagline = "\"Gesundheit. Oh wait, you weren't sneezing?\"";
		break;
		case 5:
		tagline = "\"You know, you should probably be writing actual code right about now.\"";
		break;
		case 6:
		tagline = "\"100% Russian proof. Looking at you, Clinton.\"";
		break;
		case 7:
		tagline = "\"日本語は話しません。でも、楽しい、ね？\"";
		break;
		case 8:
		tagline = "\"Can confirm, rubber ducky debugging is incredibly useful.\nNothing beats anime figure debugging, though.\"";
		break;
		case 9:
		tagline = "\"Don't worry, this tagline is actually about the program itself, I swear!\"";
		break;
	}
	return tagline;
}
void clear()
{
	#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	system("clear");
    	#endif
	#if defined(_WIN32) || defined(_WIN64)
	system("cls");
	#endif
}//Solution by nbro, stolen from https://stackoverflow.com/questions/2347770/how-do-you-clear-console-screen-in-c

