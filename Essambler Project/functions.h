#ifndef FUNCTIONS
#define FUNCTIONS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_BIT 14
#define MAX_SYMBOLS 7
#include "linkedList.h"
#include "datatype.h"

int isLabel(char *);/*check if a word in the assembly code is a label, return 1 if yes, 0 otherwise*/
int isGuidance(char *);/*check if a word in the assembly code is a guidance word, return index in guidanceTypes array if yes, -1 otherwise. expects pointer to string*/
int isInstruction(char *);/*check if a word in the assembly code is an instruction, return index in instructionTypes array if yes, -1 otherwise. expects pointer to string*/
int isRegister(char *); 	/*check if a word in the assembly code is a register name, return register number if yes, -1 otherwise. expects pointer to string*/
int isLegitLabelName(char *); /*checks if label name is legal according to specifications. expects pointers to label name*/
int storeData(char *); /*saves data guidance information to dataImage. expects pointer to string representation of data value*/
int storeString(char *); /*saves string guidance information to dataImage. expects pointer to string value*/
int checkComma(char *); 	/*check correct comma placement in string, expects pointer to string*/
int processInstruction(int, char *); /*parse instruction, check if instruction is legal and save it to instructionImage. expects instruction type, pointer to instruction assembly code*/
int getOperandType(char *);  	/*checks operand type. expect pointer to string representation of operand*/
void removeRedundantSpaces(char *); /*removes redundant whitespaces from a given line fo assembly code. exspects a pointer to char array*/
int storeInstruction(int, int, int);	/*saves instruction to instructionImage array and saves space in array for its operand values. expects instruction type, source operand type, dest operand type*/
int isSourceOperand(int, int); 	/*checks if source operand type is compatible with instruction type, returns 1 if yes, 0 otherwise. expects instruction type and operand type*/
int isDestOperand(int, int);		/*checks if source and dest operands types are compatible with instruction type, returns 1 if yes, 0 otherwise. expects instruction type , source operand type and dest operand type*/
void removewhitespaces(char *); /*removes whitespaces from a given line fo assembly code. exspects a pointer to char array*/
int encodeOperator(lptr, char *, int, int, int);/*parse operator string and save its code to instructionImage. expects pointer to label list, pointer to operator string representation,
																operator type, is operator a source operator, should reg instruction be reused (in case source and dest operators are registers)*/
void convertfile(int input, int size, char *output);  /*converts object file, expects input, size and pointer to output */
int createobj(char *, int); 	/*creates object file. expects pointer to filename, memory offset value*/
int createEntriesFile(char *, lptr); /*creates entries file if needed. expects pointer to filename, pointer to label list*/
int createExternalsFile(char *, lptr, int);  /*creates externals file if needed. expects pointer to filename, pointer to label list, memory offset value*/
int encodeDestOper(lptr, char *); /*save code for destination operator in instructionmage array. expects pointer to label list, pointer to destination operator string representation*/
int encodeSourceAndDestOper(lptr labelPtr, char *oper1, char *oper2); /*save code for source and destination operators in instructionmage array. expects pointer to label list, pointer to source operator string representation,
																pointer to destination operator string representation*/

#endif