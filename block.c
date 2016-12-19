#include "block.h"

int init_block(char type,int number, Block** b)
{
	(*b) = (Block*) malloc(sizeof(Block));
	if(!(*b))
		return 0;
	(*b)->n_block = number;
	(*b)->type = type;
	
	//TODO, must calculate type size first
	switch(type)
	{
		case 't':
		for(int i = 0;i<4;i++)
			(*b)->tables[i] = 0;
		break;
		case 'f':
		for(int i = 0;i<3;i++)
			(*b)->fields[i] = 0;
		break;
		case 'k':
		for(int i = 0;i<12;i++)
			(*b)->keys[i] = 0;
		break;
		//NOTE: aqui iria la definicion de registros hasheados
		//el numero de ellos depende del tamaño
		//todo el bloque (menos el pointer al siguiente) debe pesar
		//menos de 64 bytes
		//lo que falte se le agrega al archivo como 0's (int, no '0' o '\0'; 0)

	}
	(*b)->next = 0;// Remember! not included in binary file!
	return 1;
}
int append_block(Block** first, Block** second)
{
	(*first)->next = (*second);
	if(!((*first)->next))
		return 0;
	return 1;
}

//memory leaks be damned, this is not important atm
void free_block(Block** b)
{
	//free((*b)->content);
	free((*b)->next);
	free (*b);
}
