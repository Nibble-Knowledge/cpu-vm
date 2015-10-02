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

	

}




