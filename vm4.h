#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define VERSTR "VM4 v0.1"
#define IOMEM 3
#define BOOTMEM 1024
#define RESERVEMEM (1+IOMEM+BOOTMEM)
#define NOERR 0
#define MEMALLOCERR 1
#define UNKNOWNERR -1
#define BIGEND -1
#define LITTLEEND 1
#define MEMADDRSIZE 16
#define MEMMODSIZE 4
#define INSTLEN 10
#define MAXLINELEN 255
#define MAXARGS 5
#define MEMSIZE 65536

#define PLATEND LITTLEEND

//Changes made
#define NUMREG 4
#define REGSIZE 4 //We have 2 that are 16 also
#define PC 0
#define A 1
#define MEM 2
#define STAT 3


#define HLT 0
#define LOD 1
#define STR 2
#define ADD 3
#define NOP 4
#define NND 5
#define JMP 6
#define CXA 7

typedef struct _nib
{
	unsigned int data : 4;

} nib;

int initmem(uint16_t num);
int shutdown(int err);
void freemain(void);
char *tobitstr(size_t size, uint64_t data, char dir);
void walkmem(void);
int mainloop(void);
void writemem(uint16_t addr, uint8_t data);
int readinst(char *instr1, char *instr2, char *instr3, char *instr4, char *instr5);
void initreg(void);
void writereg(unsigned int reg, uint8_t data);
void walkreg(void);
uint8_t readmem(uint16_t addr);
uint8_t readreg(unsigned int reg);
uint16_t toaddr(char *str);
uint8_t todata(char *str);
unsigned int toreg(char *str);
void add(void);
void wm(void);
void mv(unsigned int to, unsigned int from);
void li(uint8_t data);
