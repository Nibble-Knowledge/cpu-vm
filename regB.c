/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: regB.c
* Description: Contains the functions used to initialize, read
* 	       and write to and from registers
* Original Creator:  Bailey Tye
* Date of Creation:  01/10/15
* Last Editor:       Colton Schmidt
* Date of Last Edit: 03/10/15
*/


#include "vm4.h

//Register Array
reg REGISTERS[NUMREG];

void initReg(void){

	//Initialize register types in array
	REGISTERS[PC].regType = REGISTER16BIT;
	REGISTERS[A].regType = REGISTER4BIT;
	REGISTERS[MEM].regType = REGISTER16BIT;
	REGISTERS[STAT].regType = REGISTER4BIT;

	//Set data of registers to 0
	for(int i = 0; i < NUMREG; i++){
		REGISTERS[i].contents16 = 0;
		REGISTERS[i].contents4 = 0;
	}

}
