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


// Initailize Memory Function
int initMemory(void)
{
	uint16_t num = 65536 / 4;
	if(num > RESERVEMEM)
	{
		if(MAINMEM != NULL && MEMSIZE > 0)
		{
			freemain();
		}
		MAINMEM = (nib *)calloc(num, sizeof(nib));
		if(MAINMEM != NULL)
		{
			MEMSIZE = num;
			printf("Initialised %i nibbles of memory\n", MEMSIZE);
			printf("Address %s reserved for zeromem\n", tobitstr(16, 0, PLATEND));
			if(IOMEM > 0)
			{
				printf("Bottom addresses %s to %s of memory used for I/O\n", tobitstr(16, 1, PLATEND), tobitstr(16, IOMEM, PLATEND));
			}
			if(BOOTMEM > 0)
			{
				printf("Bottom addresses %s to %s used for boot rom\n", tobitstr(16, 1+IOMEM, PLATEND), tobitstr(16, IOMEM+BOOTMEM, PLATEND));
			}
			return num;
		}	
	}
	return -1;
}

// To Be Removed ?????
void walkmem(void)
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

void writemem(uint16_t addr, uint8_t data)
{
	if(MAINMEM == NULL || MEMSIZE == 0)
	{
		return;
	}
	else if(addr == 0)
	{
		return;
	}
	MAINMEM[addr % MEMSIZE].data = data;
}

uint8_t readmem(uint16_t addr)
{
	if(addr < MEMSIZE)
	{
		return MAINMEM[addr].data;
	}
	return 0;
}

void freemain(void)
{
	if(MAINMEM == NULL || MEMSIZE == 0)
	{
		return;
	}
	free(MAINMEM);
	return;
}
