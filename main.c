#include "vm4.h"

/*test*/

int main(int argc, char **argv)
{
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

int shutdown(int err)
{
	puts("Shutting down...");
	if(err == NOERR)
	{
		puts("No errors");
		freemain();
		return 0;
	}
	else if(err == MEMALLOCERR)
	{
		puts("Error allocating main memory");
	}
	else
	{
		puts("Unknown error");
	}
	return -1;
}

int mainloop(void)
{
	char instr[MAXARGS][INSTLEN];
	char in[MAXLINELEN];
	char run = 1;	

	while(run)
	{
		int i;
		for(i = 0; i < MAXARGS; i++)
		{
			instr[i][0] = '\0';
		}
		printf("Input: ");
		fgets(in, MAXLINELEN - 1, stdin);
		sscanf(in, "%9s %9s %9s %9s %9s", instr[0], instr[1], instr[2], instr[3], instr[4]);
		if(!strncmp(instr[0], "~q", INSTLEN - 1))
		{
			puts("Halting");
			run = 0;
			return shutdown(NOERR);
		}
		else if(!strncmp(instr[0], "~mc", INSTLEN - 1))
		{
			walkmem();
		}
		else if(!strncmp(instr[0], "~mw", INSTLEN - 1))
		{
			writemem(toaddr(instr[1]),todata(instr[2]));
		}
		else if(!strncmp(instr[0], "~mi", INSTLEN - 1))
		{	
			int memout = initmem(toaddr(instr[1]));
			if(memout < 1)
			{
				return shutdown(MEMALLOCERR);
			}
		}
		else if(!strncmp(instr[0], "~rc", INSTLEN - 1))
		{
			walkreg();
		}
		else if(!strncmp(instr[0], "~rw", INSTLEN - 1))
		{
			writereg(toreg(instr[1]),todata(instr[2]));
		}
		else if(!strncmp(instr[0], "~ri", INSTLEN - 1))
		{	
			initreg();
		}
		else
		{
			readinst(instr[0], instr[1], instr[2], instr[3], instr[4]);
		}
	}
	return shutdown(UNKNOWNERR);
}
