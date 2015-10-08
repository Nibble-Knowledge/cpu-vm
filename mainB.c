/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: mainB.c
* Description: Contains the main function to initialize everything,
*	       and the mainloop to run the VM
* Original Creator:  Bailey Tye
* Date of Creation:  01/10/15
* Last Editor:       Colton Schmidt
* Date of Last Edit: 03/10/15
*/


//Includes
#include "vm4B.h"


/*
* Main function initializes registers and memory, then starts the main loop
*/
int main(int argc, char** argv){

	int i;
        int status;

        printf("%s starting up...\n", VERSTR);
        printf("Command line arguments:\n");
        printf("~q: Quit, ~pm lower upper: Prints mem between lower and upper\n");
        printf("~pr: Prints register contents\n"); 
        for(i = 1; i < argc; i++)
        {
                if(argv[i] != NULL)
                {
                        printf(" %s", argv[i]);
                }
        }
	initMem();
        puts("");
        readBin("test.bin");
        status = mainloop();
        return status;

}


/*
* Main loop used to continuously ask for user input
*/
int mainloop(void){

	char op_code[100];
	uint16_t instAddr;
	uint16_t topAddr;
	char run = 1;
	char in[100];
	regA.data = 0;
	regSTAT.data = 0;
	setBoot();

	while(run){

		printf("Input: ");
		fgets(in, 99, stdin);
		sscanf(in, "%s %hu %hu", op_code, &instAddr, &topAddr);


		//Process input
		if(!strcmp(op_code, "~q")){
			printf("Halting\n");
			run = 0;
		}
		else if(!strcmp(op_code, "~pm")){
			printMem(instAddr, topAddr);
		}
		else if(!strcmp(op_code, "~pr")){
			printReg();
		}
		else {
			decode(op_code, instAddr);
		}


	}

	return 1;
}

/*
* Used to display to the user if there was an error
*/
int shutdown(int err)
{
	puts("Shutting down...");
	if(err == NOERROR)
	{
		puts("No errors");
		freeMem();
		return 0;
	}
	else if(err == MEMALLOCERROR)
	{
		puts("Error allocating main memory");
	}
	else
	{
		puts("Unknown error");
	}
	return -1;
}

