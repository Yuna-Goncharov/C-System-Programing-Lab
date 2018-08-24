#include<stdlib.h>
#define MAX_PROGRAM_SIZE 1000

int lineNumber;
int IC ,DC , L ;
int dataImage[MAX_PROGRAM_SIZE];
int instructionImage[MAX_PROGRAM_SIZE];/* this array will hold all the machine instructions */

typedef struct 
{
    unsigned int labelType : 2;
    unsigned int destination : 2;
    unsigned int source : 2;
    unsigned int opcode : 4;
    unsigned int parm1: 2;
    unsigned int parm2: 2;
}registers;
registers r0,r1,r2,r3,r4,r5,r6,r7; 

 const char* guidanceTypes[] =
{ /* Name Function */ 
".data",
".string", 
".extern",
".entry",
NULL}; /* represent the end of the array */ 

/* This array will give the info about the parameters number for each command (instruction type) */
const char* instructionNames[] =
{ /* Name instruction*/ 
"mov",
"cmp", 
"add",
"sub", 
"lea", 
"not",
"clr", 
"inc", 
"jmp",
"bne", 
"red", 
"prn",
"jsr", 
"rts",
"stop",
NULL}; /* represent the end of the array */ 




