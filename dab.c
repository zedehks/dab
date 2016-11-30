#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include  "table.h"
#include "command.h"
#include "block.h"

int main()
{
	/*table* t = NULL;
	int i = init_table(&t,69);

	if(i == RETURN_OK) //printf("lol\n");
		printf("\n%d capacity\n",t->capacity);
	free(t);*/
	srand(time(NULL));
	block_t* b;
	b = init_block_t(NULL);
	char* tagline = "The DatABase";
	if(rand()%10 >=8) tagline = "Because Memes";

	printf("\n~~DAB: %s~~\n",tagline);
	print_help(0);

	int exit=0;
	while(exit == 0)
	{
		exit = get_command(&b); 
	}
	free_block(&b);
}
