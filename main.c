/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: main.c
* Description: Contains the main function to initialize everything,
*	       and the mainloop to run the VM
* Original Creator:  Bailey Tye
* Date of Creation:  01/10/15
* Last Editor:       Colton Schmidt
* Date of Last Edit: 03/10/15
*/


//Includes
#include "vm4.h"



/*
* Main function initializes registers and memory, then starts the main loop
*/
int main(int argc, char** argv){


        int status;
	uint16_t loadLocation = 1025;
	regPC = loadLocation;
	int mode;

        printf("%s starting up...\n", VERSTR);
        printf("Command line arguments:\n");
        printf("~q: Quit, ~pm lower upper: Prints mem between lower and upper\n");
        printf("~pr: Prints register contents\n");
	printf("Enter user input mode (0), or file mode(1)?\n");
	scanf( "%d", &mode);

        for(int i = 1; i < argc; i++)
        {
                if(argv[i] != NULL)
                {
                        printf(" %s", argv[i]);
                }
        }

	initMem();
	puts("");

        char fileName[100];
        if(mode  == 1){
        	printf("Enter file name: ");
        	scanf("%s", fileName);
		if(readBin(fileName, loadLocation) == -1){
			printf("Entering User Input Mode");
			mode = 0;
		}
	}

        status = mainloop(mode);
        return status;

}


/*
* Main loop used to continuously ask for user input
*/
int mainloop(int mode){

	char op_code[100];
	uint16_t instAddr;
	uint16_t topAddr;
	char run = 1;
	char in[100];
	regA.data = 0;
	regSTAT.data = 0;
	setBoot();
	char counter = 0;
	nibble currentInst;
	int tempAddress = 0;
	int instrRun = 0;

/*
	struct timespec gettime_now;
	double firstTime;
	double secondTime;
*/
	while(run){

		if(mode == 0)
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
			if(mode == 0)
				decode(op_code, instAddr);
		}

		if(mode == 1){
			puts("Program started");
			while(!(regSTAT.data & 0x1)){
				//Start of file code
/*
				clock_gettime(CLOCK_REALTIME, &gettime_now);
				firstTime = gettime_now.tv_nsec;
				currentInst = readMem(regPC);
*/
				instrRun++;
				printReg();
				instAddr = 0;
				tempAddress = 0;
				tempAddress = readMem(++regPC).data;
				instAddr |= (tempAddress << 12);

	                        tempAddress = readMem(++regPC).data;
       		                instAddr |= (tempAddress << 8);

                        	tempAddress = readMem(++regPC).data;

                        	instAddr |= (tempAddress << 4);
                      		tempAddress = readMem(++regPC).data;
	                        instAddr |= (tempAddress);
				regPC++;

	                        if(currentInst.data == HLT)
        	                        decode("HLT", instAddr);
                	        else if(currentInst.data == LOD)
                        	        decode("LOD", instAddr);
	                        else if(currentInst.data == STR)
        	                       	decode("STR", instAddr);
                	        else if(currentInst.data == ADD)
                        	        decode("ADD", instAddr);
	                        else if(currentInst.data == NOP)
        	                        decode("NOP", instAddr);
                	        else if(currentInst.data == NND)
                        	        decode("NND", instAddr);
	                        else if(currentInst.data == CXA)
        	                       	decode("CXA", instAddr);
                	        else if(currentInst.data == JMP)
                        	        decode("JMP", instAddr);
	                        else
        	                        shutdown(UNKNOWNINSTRUCTIONERROR);

/*				clock_gettime(CLOCK_REALTIME, &gettime_now);
				secondTime = gettime_now.tv_nsec - firstTime;
				printf("Time taken for instruction: %f", secondTime);
*/			}
		mode = 0;
		puts("Program finished");
		printf("Instructions run %d\n", instrRun);

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
		exit(0);
	}
	else if(err == MEMALLOCERROR)
	{
		puts("Error allocating main memory");
		exit(0);
	}
	else if(err == UNKNOWNINSTRUCTIONERROR)
	{
		puts("Unknown instruction");
		exit(0);
	}
	else
	{
		puts("Unknown error");
		exit(0);
	}
	return -1;
}

