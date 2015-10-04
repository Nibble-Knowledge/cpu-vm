/*
* Nibble Knowledge
* ------------------------------------------------------
* Filename: memB.c
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
		printf("Memory Initialized\n");
		return 1;
	}

	return -1;
}

// Print all of Memory
void printMem(void)
{
	uint16_t loc = 0;

	if(MAINMEM == NULL || MEMSIZE == 0)
	{
		puts("No allocated memory");
		return;
	}

	puts("Memory contents:");
	for(loc = 0; loc < MEMSIZE; loc++)
	{
		printf("%s: %s", tobitstr(MEMADDRSIZE, loc, PLATEND), tobitstr(MEMMODSIZE, MAINMEM[loc].data, PLATEND));
		if(loc == 0)
		{
			printf(" (zero)");
		}
		else if(loc < IOMEM + 1 && loc > 0 && IOMEM > 0) 
		{
			printf(" (I/O)");
		}
		else if(loc >= (IOMEM + 1) && loc < (1 + IOMEM + BOOTMEM) && BOOTMEM > 0)
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
	return 0;
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
