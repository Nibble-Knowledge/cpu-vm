/*
* Nibble Knowlege
* ------------------------------------------------------
* FileName: main.c
* Description: Contains the main function to initialize everything,
*	       and the mainloop to run the VM
* Original Creator:  Bailey Tye
* Date of Creation:  01/10/15
* Last Editor:       Bailey Tye
* Date of Last Edit: 15/10/15
*/


//Includes
#include "vm4.h"



/*
* Main function initializes registers and memory, then starts the main loop
*/
int main(int argc, char** argv){

	//Local Variables
        int status;

	//Initializations
	initMem();
	setup_io();
	initGPIOs();

	//Setup
        printf("%s starting up...\n", VERSTR);
        printf("Command line arguments:\n");
        printf("~q: Quit, ~pm lower upper: Prints mem between lower and upper\n");
        printf("~pr: Prints register contents, ~rm: reset memmory to 0s\n");
	printf("~cp: Changes the period of the clock to given number in nano seconds\n");
	printf("~in: Prompt for file input\n");
	printf("~run <start location>: runs program starting at <Start location>\n");


        for(int i = 1; i < argc; i++)
        {
                if(argv[i] != NULL)
                {
                        printf(" %s", argv[i]);
                }
        }

        status = mainloop();
        return status;

}


/*
* Main loop used to continuously ask for user input
*/
int mainloop(){

	//Local variables
	int mode = 0;
	char op_code[100];
	uint16_t instAddr;
	uint16_t topAddr;
	uint16_t baseAddr;
	char fileName[100];
	char run = 1;
	char in[100];
	regA.data = 0;
	regSTAT.data = 0;
	nibble currentInst;
	int tempAddress = 0;
	int instrRun = 0;
	struct timespec gettime_now;
	struct timespec newTime = {0, 0};
	long totalFirstTime;
	long totalSecondTime;
	long firstTime;
	long secondTime;
	long period = 200000;




	while(run){

		if(mode == USERMODE)
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
		else if(!strcmp(op_code, "~in")){
			printf("Enter file name, followed by an address to load at: ");
        	        scanf("%s %hu", fileName, &baseAddr);
			puts("WARNING, make sure the base address is set correctly when assembling file");
			while(getchar()!= '\n');
			if(readBin(fileName, baseAddr) == -1){
                        	printf("Entering User Input Mode");
   				mode = USERMODE;
			}
		}
		else if(!strcmp(op_code, "~run")){
			regPC = instAddr;
			instrRun = 0;
			regSTAT.data &= 0xD;
			mode = FILEMODE;
		}
		else if(!strcmp(op_code, "~cp")){
                        printf("Enter period: ");
                        scanf("%li", &period);
                        while(getchar()!= '\n');
		}
		else if(!strcmp(op_code, "~rm")){
			freeMem();
			initMem();
		}
		else {
			if(mode == USERMODE)
				decode(op_code, instAddr);
		}

		if(mode == FILEMODE){
			puts("Program started...");

			//Runs while HLT is off
			while(!(regSTAT.data & 0x2)){

				//Start of file code

//				printf("Current clock value: %li\n", firstTime);

				//EXECUTE FIRST 4 BITS
				currentInst = readMem(regPC);

                                clock_gettime(CLOCK_REALTIME, &gettime_now);
                                firstTime = gettime_now.tv_nsec;
				totalFirstTime = firstTime;
                                waitForPeriod(firstTime,gettime_now,period );

                                GPIO_CLR = 1<<CLKPIN;

				//EXECUTE SECOND 4 BITS
				instAddr = 0;
				tempAddress = 0;
				tempAddress = readMem(++regPC).data;
				instAddr |= (tempAddress << 12);

                                clock_gettime(CLOCK_REALTIME, &gettime_now);
				firstTime = gettime_now.tv_nsec;
				waitForPeriod(firstTime,gettime_now,period );
                                GPIO_SET = 1 <<CLKPIN;


				//EXECUTE THIRD 4 BITS
	                        tempAddress = readMem(++regPC).data;
       		                instAddr |= (tempAddress << 8);


                                clock_gettime(CLOCK_REALTIME, &gettime_now);
				firstTime = gettime_now.tv_nsec;
				waitForPeriod(firstTime,gettime_now,period );
                                GPIO_CLR = 1<<CLKPIN;


				//EXECUTE FOURTH 4 BITS
                        	tempAddress = readMem(++regPC).data;
                        	instAddr |= (tempAddress << 4);

                                clock_gettime(CLOCK_REALTIME, &gettime_now);
				firstTime = gettime_now.tv_nsec;
				waitForPeriod(firstTime,gettime_now,period );

				GPIO_SET = 1 <<CLKPIN;

				//EXECUTE FIFTH 4 BITS
                      		tempAddress = readMem(++regPC).data;
	                        instAddr |= (tempAddress);
				regPC++;

                                clock_gettime(CLOCK_REALTIME, &gettime_now);
                                firstTime = gettime_now.tv_nsec;
				waitForPeriod(firstTime,gettime_now,period );

                                GPIO_CLR = 1<<CLKPIN;

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

                                clock_gettime(CLOCK_REALTIME, &gettime_now);
                                firstTime = gettime_now.tv_nsec;
                                waitForPeriod(firstTime,gettime_now,period );
                                GPIO_SET = 1 <<CLKPIN;



				instrRun++;

				clock_gettime(CLOCK_REALTIME, &gettime_now);
				totalSecondTime = gettime_now.tv_nsec - totalFirstTime;
				printf("Time taken for instruction: %li\n", totalSecondTime);


			}
		mode = USERMODE;
		puts("Program finished");
		printf("Instructions run %d\n", instrRun);
		GPIO_CLR = 1 << CLKPIN;
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



void waitForPeriod(long firstTime,struct timespec gettime_now,long period ){

     while(1){
         if(firstTime > gettime_now.tv_nsec){
         	if(((1000000000 - firstTime) + (gettime_now.tv_nsec - 0))>= period)
                 	return;
         }
         else if(gettime_now.tv_nsec - firstTime >= period)
                 return;
         clock_gettime(CLOCK_REALTIME, &gettime_now);
     }




}
