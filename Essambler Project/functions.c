#include "functions.h"


int isLabel(char *p){ /* a function which checks if it is a label*/
	while(*p){
		if(*p == ':')
				return 1;
		p++;
	}
	return 0;
}


int isGuidance(char *p){
	int i=0;
	while( guidanceTypes[i] != NULL){
		if(!strcmp(guidanceTypes[i], p)){
			return i;
		}
		i++;
	}
	return -1;
}


int isInstruction(char *p){
	int i=0;
	while(instructionNames[i] != NULL){
		if(!strcmp(instructionNames[i], p)){
			return i;
		}
		i++;
	}
	return -1;
}


int isRegister(char *p){
	int regNum;
	char *endChar = NULL;
	if(p[0] == 'r'){
		regNum = (int) strtol(p+1, &endChar, MAX_BIT);
		if(*endChar != '\0' || endChar == p+1){
			return -1;
		}
		if(regNum>=0 && regNum<=7){
			return regNum;
		}
	}
	return -1;
}


int isLegitLabelName(char *p){
	char temp[MAX_LABEL_SIZE];
	int i=0;
	if(!isalpha(*p)){
		printf("Error in line %d: Label name starts with a digit\n", lineNumber);
		return 0;
	}
	while(*p != ':' && *p != '\0'){
		if(i>30){
			printf("Error in line %d: Label name too long\n", lineNumber);
			return 0;
		}
		if(!isalpha(*p) && !isdigit(*p)){
			printf("Error in line %d: Label name contains a char which is not a digit nor a letter\n", lineNumber);
			return 0;
		}
		temp[i] = *p;
		p++;i++;
	}
	if(isRegister(temp)>=0 || isInstruction(temp)>=0){
		printf("Error in line %d: Label name cannot be register or instruction name\n", lineNumber);
		return 0;
	}
	return i;
}


int storeData(char *p){
	char *token;
	char *endChar = NULL;
	int tempDC = DC;
	int tempNum;
	if(!checkComma(p)){
		printf("Error in line %d: Data guidance parameter is incorrect, aborting storage action\n", lineNumber);
		DC = tempDC;
		return 1;
	}
	token = strtok(p,",");
	while(token){
		tempNum = (int) strtol(token, &endChar, 10);
		if(*endChar != '\0'){
			printf("Error in line %d: Could not parse natural number in parameter %s\n", lineNumber, token);
			DC = tempDC;
			return 1;
		}
		if(tempNum >= 512 || tempNum< -512){
			printf("Error in line %d: Natural number parameter %s is too large to fit in memory\n", lineNumber, token);
			DC = tempDC;
			return 1;
		}
		dataImage[DC] = tempNum;
		DC++;
		token = strtok(NULL,",");
	}
	return 0;

}


int storeString(char *p){
	int i=0;

	while(p[i] != '\0'){
		dataImage[DC] = p[i];
		i++;DC++;
	}
	dataImage[DC] = '\0';
	DC++;
	return 0;
}


int checkComma(char *p){
	if(*p == ','){
		printf("Error in line %d: Comma is dispositioned\n", lineNumber);
		return 0;
	}
	p++;
	while(*p){
		if(*p == ','){
			if(*(p+1) == '\0'){
				printf("Error in line %d: Comma is dispositioned\n", lineNumber);
				return 0;
			}
			if(*(p+1) == ','){
				printf("Error in line %d: Multiple consecutive commas\n", lineNumber);
				return 0;
			}
		}
		p++;
	}
	return 1;
}


int processInstruction(int insType, char *p){
	char *token1, *token2, *token3;
	instAddressType oper1 = NONE,oper2 = NONE;
	if(insType > 13){
			if(p){
				printf("Error in line %d: Redundant parameters\n",lineNumber);
			}else{
				return(storeInstruction(insType, -1, -1));
			}
	}else if(p){
		if(!checkComma(p)){
			return 1;
		}
		token1 = strtok(p, ",");
		token2 = strtok(NULL, ",");
		token3 = strtok(NULL, ",");
		if(token1 && !token3){
			oper1 = getOperandType(token1);
			if((insType>3 && insType != 6)){
				if(token2){
					printf("Error in line %d: Too many operands\n",lineNumber);
				}else{
					if( isDestOperand(oper1, insType)){
						return(storeInstruction(insType, -1, oper1));
					}else{
						printf("Error in line %d: Destination operand is not compatible with instruction\n",lineNumber);
					}
				}
			}else{
				if(token2){
					if(isSourceOperand(oper1, insType)){
						oper2 = getOperandType(token2);
						if( isDestOperand(oper2, insType)){
							return(storeInstruction(insType, oper1, oper2));
						}else{
							printf("Error in line %d: Destination operand is not compatible with instruction\n",lineNumber);
						}
					}else{
						printf("Error in line %d: Source operand is not compatible with instruction\n",lineNumber);
					}
				}else{
					printf("Error in line %d: Destination operand is missing\n",lineNumber);
				}
			}
		}else{
			printf("Error in line %d: Incorrect number of operands\n",lineNumber);
		}
	}else{
		printf("Error in line %d: Missing operands\n",lineNumber);
	}
	return 1;
}


int getOperandType(char *p)
{
	if(p[0] == '#')
		return IMM;
	if(isRegister(p) >= 0)
		return REG;
	return 0;
}


void removeRedundantSpaces(char *buf){
	char *temp = buf;
	int comma = 0; int space = 0;
	while(*buf != EOF && *buf != '\n'){
		if(*buf == ' ' || *buf == '\t'){
			space = 1;
		}else if(*buf == ','){
			if(comma == 0){
				comma = 1;
			}else{
				*temp = ',';
				temp++;
				space = 0;
			}
		}else{
			if(comma == 1){
				*temp = ',';
				temp++;
				comma = 0; space = 0;
			}else if(space == 1){
				*temp = ' ';
				temp++;
				space = 0;
			}
			if(*buf == '"'){
				*temp = *buf;
				buf++;temp++;
				while(*buf != '"'){
					*temp = *buf;
					buf++;temp++;
				}
			}
			*temp = *buf;
			temp++;
		}
		buf++;
	}
	if(comma == 1){
		*temp = ',';
		temp++;
	}
	*(temp) = '\0';
}


int storeInstruction(int insType, int source, int dest){
	int instruction = 0;
	int operandOffset = 0;

	instruction |= (insType << 6);

	if(dest >= 0){
		instruction |= (dest << 1);
		if(dest == JMP){
			operandOffset += 2;
		}else{
			operandOffset += 1;
		}
		if(source >= 0){
			 instruction |= (source << 1);
			if(source == JMP){
				operandOffset += 2;
			}else if(source != REG){
				operandOffset += 1;
			}else if(dest != REG){
				operandOffset += 1;
			}
		}
	}
	instructionImage[IC] = instruction;
	IC++;
	IC += operandOffset;
	return 0;
}

int isSourceOperand(int oper, int insType){ /* checks if its a source operand*/
	if((oper == IMM || oper == REG)){
		return 0;
	}
	return 1;
}

int isDestOperand(int oper, int insType){
	if(oper == IMM && (insType != 1 && insType != 12)){
		return 0;
	}
	return 1;
}

void removewhitespaces(char *buf){
	char *temp = buf;
	int comma = 0; int space = 0;
	while(*buf != EOF && *buf != '\n'){
		if(*buf == ' ' || *buf == '\t'){
			space = 1;
		}else if(*buf == ','){
			if(comma == 0){
				comma = 1;
			}else{
				*temp = ',';
				temp++;
				space = 0;
			}
		}else{
			if(comma == 1){
				*temp = ',';
				temp++;
				comma = 0; space = 0;
			}else if(space == 1){
				*temp = ' ';
				temp++;
				space = 0;
			}
			if(*buf == '"'){
				*temp = *buf;
				buf++;temp++;
				while(*buf != '"'){
					*temp = *buf;
					buf++;temp++;
				}
			}
			*temp = *buf;
			temp++;
		}
		buf++;
	}
	if(comma == 1){
		*temp = ',';
		temp++;
	}
	*(temp) = '\0';
}

int encodeOperator(lptr labelPtr, char *oper, int operType, int isSourceOper, int reuseRegField){
	label *myLabel;
	char *p1, *p2, *p3;
	int tempNum;
	char *endChar;
	switch(operType){
				case 0:
					tempNum = (int) strtol(oper+1, &endChar, 10);
					if(*endChar != '\0'){
						printf("Error in line %d: Could not parse natural number in parameter %s\n", lineNumber, oper);
						IC++;
						return 1;
					}
					if(tempNum >= 0 || tempNum< 256){
						printf("Error in line %d: IMM operand value %s is too large to fit in memory\n", lineNumber, oper);
						IC++;
						return 1;
					}
					instructionImage[IC] = tempNum << 2;
					IC++; 
					break;
					
					case 1:
					if(!isLegitLabelName(oper)){
						printf("Error in line %d: Use of illegal label name %s\n", lineNumber, oper);
						IC++;
						return 1;
					}
					myLabel = findlabel(labelPtr, oper);
					if(!myLabel){
						printf("Error in line %d: Label %s was not found\n", lineNumber, oper);
						IC++;
						return 1;
					}
					if(myLabel->labelType == External){
						instructionImage[IC] = 1;
						if(addOperNode(&myLabel->operatorNodePtr, IC)){
							printf("Error in line %d: Failure while saving operand address for external label\n", lineNumber);
							IC++;
							return 1;
						}
					}else{
						instructionImage[IC] = (myLabel->counterValue << 2 | 2);
					}
					IC++;
					break;
					
					case 2 : 
						if(*oper == '('){
						printf("Error in line %d: Missing label name\n", lineNumber);
						IC+=2;
						return 1;
					}
					
						p1 = strtok(oper, '(');
						p2 = strtok(getOperandType(oper),oper);
						 p1 = strtok(oper,",");
						 p3 = strtok (getOperandType(oper),oper);
						if(strtok(NULL, "()")){
						printf("Error in line %d: Redundant chars\n", lineNumber);
						IC+=2;
						return 1;
		
					    if(strtok(NULL,",")){
					        printf("Error in line %d: missing comma\n",lineNumber);
					        IC+=2;
					        return 1;
					    }
					}
						myLabel = findlabel(labelPtr, p1);
					if(!myLabel){
						printf("Error in line %d: Label %s was not found\n", lineNumber, p1);
						IC+=2;
						return 1;
					}
					if(myLabel->labelType == External){
						instructionImage[IC] = 1;
						if(addOperNode(&myLabel-> operatorNodePtr, IC)){
							printf("Error in line %d: Failure while saving operand address for external label\n", lineNumber);
							IC+=2;
							return 1;
						}
					}else{
						instructionImage[IC] = (myLabel->counterValue << 2 | 2);
					}
					IC++;
					if(!p2 || !p3){
						printf("Error in line %d: Mat parameters missing\n", lineNumber);
						IC+=2;
						return 1;
					}
					if(isRegister(p2)<0 || isRegister(p3)<0){
						printf("Error in line %d: Mat parameters are not register values\n", lineNumber);
						IC+=2;
						return 1;
					}
					instructionImage[IC] = atoi(p2+1) << 6;
					instructionImage[IC] |= atoi(p3+1) << 2;
					IC++;
					break;
					
					case 3: 
					if(reuseRegField){
						instructionImage[IC-1] |=  atoi(oper+1) << 2;
					}else{
						if(isSourceOper){
							instructionImage[IC] =  atoi(oper+1) << 7;
						}else{
							instructionImage[IC] =  atoi(oper+1) << 2;
						}
						IC++;
					}
					break;
}
	return 0;
}			
	
	
	int encodeDestOper(lptr labelPtr, char *oper){
	int maskDest = 12;
	int currentInstruction = instructionImage[IC];
	IC++;
	return encodeOperator(labelPtr, oper, (currentInstruction & maskDest) >> 2, 0, 0);
}

int encodeSourceAndDestOper(lptr labelPtr, char *oper1, char *oper2){
	int maskDest = 12;
	int maskSource = 48;
	int currentInstruction = instructionImage[IC];
	int errorFlag = 0;
	IC++;
	errorFlag |= encodeOperator(labelPtr, oper1, (currentInstruction & maskSource) >> 4, 1, 0);

	if(((currentInstruction & maskSource) >> 4) == 3 && ((currentInstruction & maskDest) >> 2) == 3){
		errorFlag|= encodeOperator(labelPtr, oper2, (currentInstruction & maskDest) >> 2, 0, 1);
	}else{
		errorFlag |= encodeOperator(labelPtr, oper2, (currentInstruction & maskDest) >> 2, 0, 0);
	}
	return errorFlag;
}



	
void convertfile(int input, int size, char* output)
{
   int mask = 1; 
   int shift = 2*(size-1); 
   mask <<= shift;
   while(shift >= 0){
		switch((input & mask) >> shift){
		case 0:
			output = '.'; 
			break;
		case 1:
			output = '/'; 
			break;
		}
		output++;
		mask >>=2;
		shift -=2;
	}
	*output = '\n';
	*(output+1) = '\0';
}



int createobj(char *fileName, int memoryOffset){
    
    int i;
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	
		fp=fopen(fileName, "w");
	if(!fp){
		printf("File %s creation failed\n",fileName);
		return 1;
	}
	
       fputs(IC,fp);
       fputs(DC,fp);
       convertfile(IC,line, MAX_LINE_LENGTH);
		line[MAX_LINE_LENGTH] = '\t';
       convertfile(DC,line+5,MAX_LINE_LENGTH);
       fputs(line , fp);

	for(i=0; i<IC; i++){
	convertfile(memoryOffset+i, line, MAX_LINE_LENGTH);
		line[MAX_LINE_LENGTH] = '\t';
		convertfile(instructionImage[i], line+5,MAX_LINE_LENGTH+1 );
		fputs(line , fp);
	}
	for(i=0; i<DC; i++){
		convertfile(memoryOffset+IC+i, line, MAX_LINE_LENGTH);
		line[MAX_LINE_LENGTH] = '\t';
		convertfile(dataImage[i], line+5, MAX_LINE_LENGTH);
		fputs(line , fp);
	}
	fclose(fp);
	return 0;
}	
    
    
    
    int createEntriesFile(char *fileName, lptr labelPtr){
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	char funny4MemAddr[MAX_SYMBOLS];

	labelPtr =   findEntrylabel(labelPtr);
	if(labelPtr){
		fp=fopen(fileName, "w");
		if(!fp){
			printf("File %s creation failed\n",fileName);
			return 1;
		}
		do{
			strcpy(line, labelPtr->label.name);
			strcat(line, "\t");
			convertfile(labelPtr->label.counterValue, 4, funny4MemAddr);
			strcat(line, funny4MemAddr);
			fputs(line, fp);
			labelPtr =   findEntrylabel(labelPtr->next);
		}while(labelPtr);
		fclose(fp);
	}
	return 0;
}


int createExternalsFile(char *fileName, lptr labelPtr, int memoryOffset){
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	char funny4MemAddr[6];
	optr operPtr;

	labelPtr =   findExternallabel(labelPtr);
	if(labelPtr){
		operPtr = labelPtr->label.operatorNodePtr;
		if(operPtr){
		fp=fopen(fileName, "w");
			if(!fp){
				printf("File %s creation failed\n",fileName);
				return 1;
			}
			do{
				operPtr = labelPtr->label.operatorNodePtr;
				while(operPtr){
					strcpy(line, labelPtr->label.name);
					strcat(line, "\t");
					convertfile((operPtr->operMemAddress) + memoryOffset,4, funny4MemAddr);
					strcat(line, funny4MemAddr);
					fputs(line, fp);
					operPtr = operPtr->next;
				}
				labelPtr =   findExternallabel(labelPtr->next);
			}while(labelPtr);
			fclose(fp);
		}
	}
	return 0;
}
