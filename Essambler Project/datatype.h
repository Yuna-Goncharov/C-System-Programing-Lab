#ifndef DATATYPES
#define DATATYPES
#define ASSEMBLER_SOURCE_FILENAME_SUFFIX ".as"		/*assembly source file suffix*/
#define ASSEMBLER_OBJECT_FILENAME_SUFFIX ".ob"		/*assembly object file suffix*/
#define ASSEMBLER_ENTRIES_FILENAME_SUFFIX ".ent"	/*assembly entries file suffix*/
#define ASSEMBLER_EXTERNALS_FILENAME_SUFFIX ".ext"	/*assembly externals file suffix*/
#define MAX_FILE_NAME 1000							/*max file path length for source assembly files*/
#define MAX_LINE_LENGTH 80							/*max line size in assembly source file*/
#define MEMORY_OFFSET 100							/*memory address of the assembled program after it was loaded to memory*/
#define MAX_LABEL_SIZE 31                           /*max char count for labe name*/
#include "linkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern const char* guidanceTypes[];
extern const char* instructionNames[];
extern int lineNumber;
extern int dataImage[];
extern int instructionImage[];
extern int IC,DC,L;
typedef enum instAddressType {IMM,DIRECT,JMP,REG,NONE} instAddressType; /*enum for operand types*/
typedef enum labelType  {Absolute,External,Relocatable} labelType; 



typedef struct operandNode* optr; /*pointer opernd */
typedef struct operandNode/*sturct opernd*/
{	  
 int operMemAddress;             /*number address*/
 optr next;                        
}operandNode;


typedef struct label{			 /* struct label*/   
									
	char name[MAX_LABEL_SIZE];
	int counterValue;
	labelType labelType;
	int isEntry;
	optr operatorNodePtr;
} label;


typedef struct labelNode * lptr; /*pointer to labelNode*/
typedef struct labelNode {		 /*labelNode data type*/
label label;
 lptr next;
} labelNode;

#endif

    
    