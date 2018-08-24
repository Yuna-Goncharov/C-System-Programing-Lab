#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "datatype.h"
#include "functions.h"

int addlabelToList(lptr *labelPtr, char *labelName,labelType labelType, int labelValue){
 lptr p1,p2;
 lptr t;

 t = (lptr) malloc(sizeof(labelNode));
 if(!t){
	printf("\n Space allocation error");
	return 1;
 }
 p1 = *labelPtr;
 strcpy(t->label.name, labelName);
 t->label.isEntry = 0;
 t->label.labelType = labelType;
 t->label.counterValue = labelValue;
 t->label.operatorNodePtr = NULL;
 t->next = NULL;

 if(!p1){
	*labelPtr = t;
 }else {
	while (p1){
		if(!strcmp(p1->label.name, t->label.name)){
			printf("Error in line %d: label %s already exist in labels table, action aborted\n",lineNumber, t->label.name);
			free(t);
			return 1;
		}
		p2 = p1;
		p1 = p1->next;
	}
	p2->next = t;
 }
	return 0;
}


void updateDatalabels(lptr h, int IC){
	while(h){
		if(h->label.labelType == Absolute){
			h->label.counterValue += IC;
		}
		h = h->next;
	}
}

int markEntrylabels(lptr h, char *labelName){
	while(h){
		if(!strcmp(h->label.name, labelName)){
			if(h->label.labelType != External){
				h->label.isEntry = 1;
				return 1;
			}
		}
		h = h->next;
	}
	return 0;
}

label *findlabel(lptr h, char *labelName){
	while(h){
		if(!strcmp(h->label.name, labelName)){
			return &(h->label);
		}
		h = h->next;
	}
	return 0;
}

lptr findEntrylabel(lptr h){
	while(h){
		if(h->label.isEntry){
			return h;
		}
		h = h->next;
	}
	return 0;
}

lptr findExternallabel(lptr h){
	while(h){
		if(h->label.labelType == External){
			return h;
		}
		h = h->next;
	}
	return 0;
}

int addOperNode(optr *operPtr, int memAddr){
     optr p1,p2;
	 optr t;

	 t = (optr) malloc(sizeof(operandNode));
	 if(!t){
		printf("\n Space allocation error");
		return 1;
	 }
	 t->operMemAddress = memAddr;
	 t->next = NULL;

	 p1 = *operPtr;
	 if(!p1){
		*operPtr = t;
	 }else {
		while (p1){
			p2 = p1;
			p1 = p1->next;
		}
		p2->next = t;
	 }
	return 0;
}

void freeOperNodes(optr h){
	optr t;
	while(h){
		t = h->next;
		free(h);
		h = t;
	}
}

void freelabelList(lptr h){
	lptr t;
	while(h){
		t = h->next;
		freeOperNodes(h->label.operatorNodePtr);
		free(h);
		h = t;
	}
}