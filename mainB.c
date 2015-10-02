/*
* Nibble Knowledge CPU VM
* main.c
* 
*
* Author: Bailey Tye
* 
*/


#include "vm4B.h"



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


int mainloop(void){

	char op_code[100];
	unsigned int inst_addr;
	char run = 1;
	char in[100];
	char garbage;

	while(1){

		printf("Input: ");
		fgets(in, 99, stdin);
		sscanf(in, "%s %u", op_code, &inst_addr);


		printf("Retrieved: \n OPCode: %s \n Instruction Address: %u\n Decoding...\n", op_code, inst_addr);
		decode(op_code, inst_addr);

	}

	return 1;
}




