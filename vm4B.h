
/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: vm4B.h.c
* Description: Contains the definitions and constants used thoughout
*	       the VM
* Original Creator: Bailey Tye
* Last Editor:      Bailey Tye
* Date of Last Edit: 03/10/15
* Date of Creation:  01/10/15
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
	uint8_t data : 4;
} nibble;

// Global Variables

extern uint16_t regPC;
extern nibble   regA;
extern uint16_t regMEM;
extern nibble	regSTAT;

extern nibble*	MAINMEM;

//--------------------Prototypes----------------------//


int mainloop(void);



// inst.c Prototypes
// -----------------------------------------------

// Decodes the OP code and Calls the appropiate instruction
void decode(char* op_code, unsigned int address);

// Halt Instruction
void hlt(void);

// Load Instruction
void lod(unsigned int addressFrom);

// Store Instruction
void str(unsigned int addressTo);

// Add Instruction
void add(unsigned int addAddress);

// No Operation Instruction
void nop(void);

// NAND Instruction
void nnd(unsigned int nndAdress);

// Copies the XOR bit and the Carry into the
// Acummulator and sets the other bits to 0
void cxa(void);

// Jump instruction
void jmp(unsigned int jumpAddress);

// mem.c Prototypes
// ----------------------------------------------

// Initilizes Memory of size MEMSIZE
void initMem(void);

// Prints all of Memory
void printMem(void);

// Writes a nibble of data to an address in Memory
void writeMem(nibble data, uint16_t address);

// Reads a nibble of data from an address in Memory
nibble readMem(uint16_t address);

// Releases the memory
void freeMem(void);

// reg.c Prototypes
// ----------------------------------------------

