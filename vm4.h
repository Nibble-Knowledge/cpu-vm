/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: vm4.h.c
* Description: Contains the definitions and constants used thoughout
*	       the VM
* Original Creator: Bailey Tye
* Last Editor:      Bailey Tye
* Date of Last Edit: 03/10/15
* Date of Creation:  01/10/15
*/

#ifndef _VM4_H_
#define _VM4_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

#define VERSTR "VM4 v0.3"
#define BOOTBIN "test.bin"
#define IOMEM 3
#define BOOTMEM 1024
#define RESERVEMEM (1 + IOMEM + BOOTMEM)
#define NOERROR 0
#define MEMALLOCERROR 1
#define UNKNOWNINSTRUCTIONERROR 2
#define UNKOWNERROR -1
#define MEMADDRSIZE 16
#define MEMSIZE 65536
#define BIGEND -1
#define LITTLEEND 1
#define MEMMODSIZE 4

#define PLATEND LITTLEEND

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


	// inst.c Prototypes
	// ------------------------------------------------//


	//Decodes the OP code and Calls the appropriate instruction
	int decode(const char* op_code, uint16_t address);

	//Halt Instruction
	void hlt(void);

	//Load Instruction
	void lod(uint16_t);

	//Store Instruction
	void str(uint16_t);

	//Add Instruction
	void add(uint16_t);

	//No Operation Instruction
	void nop(void);

	//NAND Instruction
	void nnd(uint16_t);

	//Carry XOR into Accumulator
	void cxa(void);

	//Jump Instruction
	void jmp(uint16_t);

	//Prints registers to screen
	void printReg(void);


	// mem.c Prototypes
	// ------------------------------------------------//

	//Initialize Memory
	int initMem(void);


	nibble readMem(uint16_t);

	//Stores data into memory
	void writeMem(nibble data, uint16_t address);

	//Prints all of Memory
	void printMem(uint16_t, uint16_t);

	//Frees Memory allocation
	void freeMem(void);

	//Sets data table values for 1 to 15
	void setBoot(void);



	//main.c Prototypes
	// ------------------------------------------------//

	//Superloop
	int mainloop(int mode);

	//Shuts down the virtual machine
	int shutdown(int);


	//util.c Prototypes
	//-------------------------------------------------//


	char *tobitstr(size_t,uint64_t,char);


	//fileIO.c Prototypes
	//------------------------------------------------//

	//Reads file into memory
	int readBin(const char*, uint16_t);


	//ASSEMBLY TIMING NOT BEING USED RIGHT NOW

	//extern inline void init_perfcounters (int32_t do_reset, int32_t enable_divider);


	//extern inline unsigned int get_cyclecount (void);



#endif
