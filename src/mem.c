/*
* Nibble Knowledge
* ------------------------------------------------------
* Filename: mem.c
* Description: Contains all the functions to intialize, read,
*              and write to memory
* Original Creator:  Colton Schmidt
* Date of Creation:  03/10/15
* Last Editor:       Colton Schmidt
* Date of Last Edit: 03/10/15
*/

#include "vm4.h"

nibble *MAINMEM = NULL;

// Initailize Memory Function
int initMem(void)
{
	MAINMEM = (nibble*)calloc(MEMSIZE, sizeof(nibble));
	if (MAINMEM != NULL)
	{
		setBoot();
		printf("Memory Initialized\n");
		return 1;
	}

	return -1;
}

// Print all of Memory
void printMem(uint16_t lower, uint16_t upper)
{


	if(MAINMEM == NULL)
	{
		puts("No allocated memory");
		return;
	}

	puts("Memory contents: ");
	for(int i = lower; i < upper ; i++)
	{
		printf("%s: %s", tobitstr(MEMADDRSIZE, i, PLATEND), tobitstr(MEMMODSIZE, MAINMEM[i].data, PLATEND));

		if(i < IOMEM && IOMEM > 0) 
		{
			printf(" (I/O)");
		}
		else if(i >= (IOMEM) && i < (IOMEM + BOOTMEM) && BOOTMEM > 0)
		{
			printf(" (Boot ROM)");
		}
		puts("");
	}

}


// Writes to Memory
void writeMem(nibble value, uint16_t address)
{
	if(MAINMEM == NULL)
	{
		return;
	}
	else if(address < 3)
	{
		return;
	}
	MAINMEM[address % MEMSIZE].data = value.data;
}

// Reads from Memory
nibble readMem(uint16_t address)
{
	if(address < MEMSIZE)
	{
		return MAINMEM[address];
	}
	printf("WARNING Address accessed was negative");
	nibble n;
	return n;
}

// Frees used Memory
void freeMem(void)
{
	if(MAINMEM == NULL || MEMSIZE == 0)
	{
		return;
	}
	free(MAINMEM);
	return;
}


void setBoot(void){
	for(int i = 0; i < 16; i++){
		MAINMEM[i+IOMEM].data = i;
	}

}
