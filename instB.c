/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: instB.c
* Description: Contains the decode function definition and function
*	       definitions for each instruction of the instruction
*	       set
* Original Creator:  Colton Schmidt
* Date of Creation:  01/10/15
* Last Editor:	     Colton Schmidt
* Date of Last Edit: 01/10/15
*/


#include "vm4B.h"

uint16_t regPC = 0;
nibble regA;
uint16_t regMEM = 0;
nibble regSTAT;



// Decode fuction
// Decodes the OP code and calls the appropiate fuction
int decode( char* op_code, uint16_t address)
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
	shutdown(NOERROR);
}

void lod(uint16_t addressFrom){
	regA = MAINMEM[addressFrom];
	//setXOR(); No longer doing this in load
}

void str(uint16_t addressTo){
	MAINMEM[addressTo] =  regA;
}

void add(uint16_t addAddress){
	uint8_t temp1 = regA.data;
	uint8_t temp2 = MAINMEM[addAddress].data;
	uint8_t result = temp1 + temp2;
	regA.data = result & 0xF;

	//Set overflow bit
	if((temp1 & 0x8) && (temp2 & 0x8) && !(result & 0x8)){
		regSTAT.data |= 0x8;
		regSTAT.data ^= (result & 0x8);
		}
	else if(!(temp1 & 0x8) && !(temp2 & 0x8) && (result & 0x8)){
		regSTAT.data |= 0x8;
		regSTAT.data ^= (result & 0x8);
		}
	else
		regSTAT.data &= 0x7;
 
	//If there was a carry out
	if(result & 0x10)
		regSTAT.data |= 0x2;
	else
		regSTAT.data &= 0xD;

}

void nop(void){

}

void nnd(uint16_t nndAddress){
	regA.data &= MAINMEM[nndAddress].data;
	regA.data = ~regA.data;
	//setXOR();
}

void cxa(void){
	regA.data = regSTAT.data;
}

void jmp(uint16_t jumpAddress){
	if(regA.data == 0)
		regPC = jumpAddress;
}


void printReg(void){

	printf("A: %x\n", regA.data);
	printf("PC: %x\n", regPC);
	printf("MEM: %x\n", regMEM);
	printf("STAT: %x\n", regSTAT.data);

}

void setXOR(void){

        nibble temp;
        temp.data = regA.data ^ regSTAT.data;
        temp.data &=  0x8;
        if(temp.data == 0x8)
      		regSTAT.data |= 0x2;
        else
        	regSTAT.data &= 0xD;
}


