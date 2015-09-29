#include "vm4.h"

int readinst(char *instr1, char *instr2, char *instr3, char *instr4, char *instr5)
{

	if(!strncmp(instr1, "add", INSTLEN - 1))
	{
		add();
	}
	else if(!strncmp(instr1, "wm", INSTLEN - 1))
	{
		wm();
	}
	else if(!strncmp(instr1, "mv", INSTLEN - 1))
	{
		mv(toreg(instr2), toreg(instr3));
	}
	else if(!strncmp(instr1, "li", INSTLEN - 1))
	{
		li(todata(instr2));
	}
	return 0;
}

void add(void)
{
	uint8_t val;
	uint16_t memaddr = 0;
	val = readreg(A);
	memaddr = readreg(M1);
	memaddr += (readreg(M2) << 4);
	memaddr += (readreg(M3) << 8);
	memaddr += (readreg(M4) << 12);
	val = (val + readmem(memaddr) % (2 << REGSIZE));
	writereg(A, val);
}

void wm(void)
{
	uint8_t val;
	uint16_t memaddr = 0;
	
	val = readreg(A);
	memaddr = readreg(M1);
	memaddr += (readreg(M2) << 4);
	memaddr += (readreg(M3) << 8);
	memaddr += (readreg(M4) << 12);
	writemem(memaddr, val);
}

void mv(unsigned int from, unsigned int to)
{
	uint8_t val;

	if(from < NUMREG && to < NUMREG)
	{
		val = readreg(to);
		writereg(from, val);
	}
}

void li(uint8_t val)
{
	writereg(A, val);
}
