/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: inst.c
* Description: Contains the decode function definition and function
*	       definitions for each instruction of the instruction
*	       set
* Original Creator:  Colton Schmidt
* Date of Creation:  01/10/15
* Last Editor:	     Colton Schmidt
* Date of Last Edit: 01/10/15
*/


#include "vm4.h"

uint16_t regPC = 0;
nibble regA;
uint16_t regMEM = 0;
nibble regSTAT;



// Decode fuction
// Decodes the OP code and calls the appropiate fuction
int decode(const char* op_code, uint16_t address)
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
	regSTAT.data |= 0x2;
}

void lod(uint16_t addressFrom){
	regMEM = addressFrom;
	regA = MAINMEM[addressFrom];

}

void str(uint16_t addressTo){
	regMEM = addressTo;
	MAINMEM[addressTo] =  regA;
}

void add(uint16_t addAddress){
	regMEM = addAddress;
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
	else{
		regSTAT.data &= 0x7;
		regSTAT.data ^= (result & 0x8);
	}

	//If there was a carry out
	if(result & 0x10){
		regSTAT.data |= 0x1;
	}
	else{
		regSTAT.data &= 0xE;
	}


}

void nop(void){

}

void nnd(uint16_t nndAddress){
	regMEM = nndAddress;
	regA.data &= MAINMEM[nndAddress].data;
	regA.data = ~regA.data;

}

void cxa(void){
	regA.data = regSTAT.data;
}

void jmp(uint16_t jumpAddress){
	regMEM = jumpAddress;
	if(regA.data == 0)
		regPC = jumpAddress;
}


void printReg(void){

	printf("A:\t 0x%x \t= %d\n", regA.data, regA.data);
	printf("PC:\t 0x%x \t= %d\n", regPC, regPC);
	printf("MEM:\t 0x%x \t= %d\n", regMEM, regMEM);
	printf("STAT:\t 0x%x \t= %d\n", regSTAT.data, regSTAT.data);

}



void setIOMem(int mode){

	



}


void initGPIOs(void){
	INP_GPIO(CLKPIN);
	OUT_GPIO(CLKPIN);
	INP_GPIO(P0);
	OUT_GPIO(P0);
	INP_GPIO(P1);
	OUT_GPIO(P1);	
	INP_GPIO(P2);
	OUT_GPIO(P2);
	INP_GPIO(P3);
	OUT_GPIO(P3);
	INP_GPIO(P4);
	OUT_GPIO(P4);
	INP_GPIO(P5);
	OUT_GPIO(P5);	
	INP_GPIO(P6);
	OUT_GPIO(P6);
	INP_GPIO(P7);
	OUT_GPIO(P7);
	INP_GPIO(P8);
	OUT_GPIO(P8);
	INP_GPIO(P9);
	OUT_GPIO(P9);
	INP_GPIO(P10);
	OUT_GPIO(P10);	
	INP_GPIO(P11);
	OUT_GPIO(P11);
}
