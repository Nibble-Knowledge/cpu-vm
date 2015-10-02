/* 
* Nibble Knowledge CPU VM
* Header file container deffinitions and constants
* used throughout the VM
* 
* Author: Bailey Tye
* Last edit: October 1, 2015
* Created: October 1, 2015
*/



#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define VERSTR "VM4 v0.1"
#define IOMEM 3
#define BOOTMEM 1024
#define RESERVEMEM (1 + IOMEM + BOOTMEM)
#define NOERROR 0
#define MEMALLOCERROR 1
#define UNKOWNERROR -1
#define MEMADDRSIZE 16
#define MEMSIZE 65536

#define NUMREG 4
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


/*
* Structure of a nibble
*/
typedef struct _nibble{
	unsigned int data : 4;
} nibble;
