#ifndef LINKEDLIST
#define LINKEDLIST
#include "datatype.h"
#include "functions.h"

int addlabelToList(lptr *labelPtr, char *labelName,labelType labelType, int labelValue);  /*creates a new labelNode and adds to the end of the list.*/
									
									
int addOperNode(optr *, int);		/*creates a new operNode and adds to the end of the list.*/
									 
void updateDatalabels(lptr, int);	/*goes over the label list and adds for each DATA label the final value of IC counter after the first pass
									 expects pointer to label list*/
									 
int markEntrylabels(lptr, char *);  /*found in the second pass ,search for it in the label list and mark it as an entry label*/

label *findlabel(lptr , char *);		/*search for a label of a given name */

lptr findEntrylabel(lptr);			/*finds the next entry label in list from current position */

lptr findExternallabel(lptr);		/*finds the next external label in list from current position */
void freelabelList(lptr);			/* free memory allocation for labels data*/
#endif
