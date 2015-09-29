#include "vm4.h"

nib REGBANK[NUMREG];

void initreg(void)
{
	int i = 0;
	for(i = 0; i < NUMREG; i++)
	{
		REGBANK[i].data = 0;
	}
}

void writereg(unsigned int reg, uint8_t data)
{
	if(reg < NUMREG)
	{
		REGBANK[reg].data = data % 16;		
	}		
}

void walkreg(void)
{
	int i;
	puts("Register contents:");
	for(i = 0; i < NUMREG; i++)
	{
		if(i == A)
		{
			printf("Accumulator: %s\n", tobitstr(REGSIZE, REGBANK[A].data, PLATEND));
		}
		else if(i == M1)
		{

			printf("Memory pointer lowest nibble: %s\n", tobitstr(REGSIZE, REGBANK[M1].data, PLATEND));
		}	
		else if(i == M2)
		{

			printf("Memory pointer low-mid nibble: %s\n", tobitstr(REGSIZE, REGBANK[M2].data, PLATEND));
		}	
		else if(i == M3)
		{

			printf("Memory pointer high-mid nibble: %s\n", tobitstr(REGSIZE, REGBANK[M3].data, PLATEND));
		}	
		else if(i == M4)
		{

			printf("Memory pointer highest nibble: %s\n", tobitstr(REGSIZE, REGBANK[M4].data, PLATEND));
		}
	}
}

uint8_t readreg(unsigned int reg)
{
	if(reg < NUMREG)
	{
		return REGBANK[reg].data;
	}
	return 0;
}
