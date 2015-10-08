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
	
	printf("test/n");
	unsigned char buffer = 0;
	nibble temp;
	uint16_t  memLocation = 1025;

	FILE *binFilePtr;

	printf("Reading Boot file.../n");

	//Open the Bin File
	binFilePtr = fopen( fileName, "rb");

	if(!binFilePtr){
		printf("Unable to open .bin file/n");
		return 1;
	}

	while(1){

		//Read a nibble at a time
		fread( buffer, sizeof(buffer), 1, binFilePtr );

		temp.data = buffer;

		//Check for end of File
		if(feof(binFilePtr))
			break;

		//Store in Mem
		writeMem( temp, memLocation );

		memLocation += 1;

	}

	fclose(binFilePtr);
	
	printf("Finished Boot/n");
	return 0;

}
