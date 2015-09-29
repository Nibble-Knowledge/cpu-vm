#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define VERSTR "VM4 v0.0"
#define IOMEM 2
#define BOOTMEM 4
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

#define PLATEND LITTLEEND

#define NUMREG 5
#define REGSIZE 4
#define A 0
#define M1 1
#define M2 2
#define M3 3
#define M4 4

#define HLT 0
#define NOP 1
#define ADD 2
#define WM 3
#define LI 4

typedef struct _nib
{
	unsigned int data : 4;
	unsigned int pad : 4;

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
