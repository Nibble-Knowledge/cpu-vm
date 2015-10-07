/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: fileIO.c
* Description: Contains file IO functions
*
* Original Creator:  Colton Schmidt
* Date of Creation:  06/10/15
* Last Editor:       Colton Schmidt
* Date of Last Edit: 06/10/15
*/

//Includes
#include "vm4B.h"


int readBin(char* fileName){

	nibble buffer;
	uint16_t  memLocation = 1025;

	FILE *binFilePtr;

	//Open the Bin File
	binFilePtr = fopen( fileName, "rb");

	if(!binFilePtr){
		printf("Unable to open .bin file");
		return 1;
	}

	while(!feof(stdin)){

	//Read a nibble at a time
	fread( buffer.data, sizeof(buffer.data), 1, binFilePtr );

	//Store in Mem
	writeMem( buffer, memlocation );

	memLocation += 1;

	}

	return 0;

}
