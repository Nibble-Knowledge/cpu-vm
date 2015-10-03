/*
Nibble Knowlege
------------------------------------------------------
FileName: mainB.c
Description: Contains the main function to initialize everything,
	     and the mainloop to run the VM
Original Creator: Bailey Tye
Last Editor:      Bailey Tye
Date of Last Edit: 03/10/15
Date of Creation:  01/10/15
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
        printf("Command line arguments:");
        for(i = 1; i < argc; i++)
        {
                if(argv[i] != NULL)
                {
                        printf(" %s", argv[i]);
                }
        }
        puts("");
        status = mainloop();
        return status;

}


/*
* Main loop used to continuously ask for user input
*/
int mainloop(void){

	char op_code[100];
	unsigned int inst_addr;
	char run = 1;
	char in[100];

	while(1){

		printf("Input: ");
		fgets(in, 99, stdin);
		sscanf(in, "%s %u", op_code, &inst_addr);


		printf("Retrieved: \n OPCode: %s \n Instruction Address: %u\n Decoding...\n", op_code, inst_addr);
		decode(op_code, inst_addr);

	}

	return 1;
}




