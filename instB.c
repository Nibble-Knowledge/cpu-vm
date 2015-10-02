/*
Nibble Knowlege
------------------------------------------------------
FileName: instB.c
Description: Contains the decode function definition and function
	     definitions for each instruction of the instruction
	     set
Original Creator: Colton Schmidt
Last Editor:	  Colton Schmidt
Date of Last Edit: 01/10/15
*/


#include "vm4B.h"


// Decode fuction
// Decodes the OP code and calls the appropiate fuction
int decode( char* op_code, unsigned int address)
{

	if(!strcmp(op_code, "HLT"))
	{
		hlt();
	}
	else if(!strcmp(op_code, "LOD"))
	{
		lod(address);
	}
	else if(!strcmp(op_code, "STR"))
	{
		str(address);
	}
	else if(!strcmp(op_code, "ADD"))
	{
		add(address);
	}
	else if(!strcmp(op_code, "NOP"))
	{
		nop();
	}
	else if(!strcmp(op_code, "NND"))
	{
		nnd(address);
	}
	else if(!strcmp(op_code, "JMP"))
	{
		jmp(address);
	}
	else if(!strcmp(op_code, "CXA"))
	{
		cxa();
	}
	return 0;
}


void hlt(void){
	//Exit program, will figure out how to do that later
}

void lod(unsigned int addrFrom){
	
}

void str(unsigned int addrTo){

}

void add(unsigned int addrToAddFrom){

}

void nop(void){

}

void nnd(void){

}

void cxa(void){

}

void jmp(unsigned int addrToJumpTo){

}



//TO BE REMOVED
void add(void)
{
	uint8_t val;
	uint16_t memaddr = 0;
	val = readreg(A);
	memaddr = readreg(M1);
	memaddr += (readreg(M2) << 4);
	memaddr += (readreg(M3) << 8);
	memaddr += (readreg(M4) << 12);
	val = (val + readmem(memaddr) % (2 << REGSIZE));
	writereg(A, val);
}

void wm(void)
{
	uint8_t val;
	uint16_t memaddr = 0;
	
	val = readreg(A);
	memaddr = readreg(M1);
	memaddr += (readreg(M2) << 4);
	memaddr += (readreg(M3) << 8);
	memaddr += (readreg(M4) << 12);
	writemem(memaddr, val);
}

void mv(unsigned int from, unsigned int to)
{
	uint8_t val;

	if(from < NUMREG && to < NUMREG)
	{
		val = readreg(to);
		writereg(from, val);
	}
}

void li(uint8_t val)
{
	writereg(A, val);
}
