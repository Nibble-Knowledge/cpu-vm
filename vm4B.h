
/*
Nibble Knowlege
------------------------------------------------------
FileName: vm4B.h.c
Description: Contains the definitions and constants used thoughout
	     the VM
Original Creator: Bailey Tye
Last Editor:      Bailey Tye
Date of Last Edit: 03/10/15
Date of Creation:  01/10/15
*/



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define VERSTR "VM4 v0.1"
#define IOMEM 3
#define BOOTMEM 1024
#define RESERVEMEM (1 + IOMEM + BOOTMEM)
#define NOERROR 0
#define MEMALLOCERROR 1
#define UNKOWNERROR -1
#define MEMADDRSIZE 16
#define MEMSIZE 65536

#define NUMREG 4
#define PC 0
#define A 1
#define MEM 2
#define STAT 3

#define HLT 0
#define LOD 1
#define STR 2
#define ADD 3
#define NOP 4
#define NND 5
#define JMP 6
#define CXA 7


#define REGISTER16BIT 0
#define REGISTER4BIT 1


// Structure of a nibble

typedef struct _nibble{
	unsigned int data : 4;
} nibble;

// Structure of the registers
typedef struct _register{
	unsigned int reg_type;
	uint16_t contents16;
	unsigned int contents4: 4;
} reg;

//--------------------Prototypes----------------------//


int mainloop(void);

/*
*  Decode function
*  Decodes the OP code and Calls the appropiate instruction
*/
void decode(char* op_code, unsigned int address);


