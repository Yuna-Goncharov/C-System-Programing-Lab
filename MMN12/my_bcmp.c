
#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*for exit() func*/
#define SIZE 512 /*max size of string*/


int my_bcmp (const void *b1, const void *b2, size_t len);

int main()
{	

		int len, id1, id2, str_len, err=-1;
		double len_d, indexp1_d, indexp2_d; 
		char str[SIZE+1];/* in order to be able to look at last index in string we need to add +1 */
		const void *b1, *b2;
    
		/*ask byte len from user*/
		printf("\n Please enter how many bytes you would like to compare :\n");
		if (scanf("%lf", &len_d) != 1){
			printf("\nERROR: The length was incorrect\n"); exit(0);}
			len = (int)len_d;
		if ((double)(len) != len_d){/*checking if len is an integer*/
			printf("\n ERROR: Please onsert an intiger  \n");
			err=0;}
		if (len_d < 0){/*checking if len>0*/
			printf("\n ERROR: please inser an positive number\n");
			err=0;} 
		if (err==0)/*testing if we have error the program should be closed*/
			exit(0);
           
           
           
		/*first index from user*/
		printf("\n Please enter the first index you would like to compare len bytes from :\n");
		if (scanf("%lf", &indexp1_d) != 1){
			printf("\nERROR: You inserted wrong value\n"); exit(0);}
    		id1 = (int)indexp1_d;
    	if ((double)(id1) != indexp1_d){
			printf("\nERROR: You inserted value that is not an intiger\n");
			err=0;}
		if (indexp1_d < 0){
			printf("\nERROR: You need to inser positive number\n");
			err=0;}
		if (err==0)/*checking if Errors were printed, then end the program*/
			exit(0);
   

   
   
		/*second index from user*/
		printf("\n Please enter the second index you would like to compare len bytes from :\n");
		if (scanf("%lf", &indexp2_d) != 1){
			printf("\nERROR: The index was not received\n"); exit(0);}
			getchar();/*clean the buffer from '\n' before using fgets() func*/
    		id2 = (int)indexp2_d;
		if ((double)(id2) != indexp2_d){
            printf("\nERROR: You should insert an intiger only\n");   
            err=0;}
    	if (indexp2_d < 0){/*checking if index2<0*/
    	  	printf("\nERROR: You should insert only positive number \n");
			err=0;}
		if (err==0)/*closing program if there is errors*/
			exit(0);
    
    
    
		/*string from user*/    
		printf("\n Please enter a string :\n");
		if (fgets(str, SIZE+1, stdin)==NULL)
	    	{printf("\nERROR: String was not received\n\n"); exit(0);} 
		str_len  = strlen(str);
		printf("\nthe length of the string is %d",str_len);
		if (id1 > str_len)
			{printf("\nERROR: First index is bigger than the length of the string \n"); exit(0);}
		if (id2 > str_len)
			{printf("\nERROR: Second index is bigger than the length of the string \n"); exit(0);}
		if (len > str_len)
			{printf("\nERROR: len is bigger than the length of the string \n"); exit(0);}
		if (id1+len > str_len)
			{printf("\nERROR: string -testing %d bytes from index %d is longer than the length of the string \n",len,id1); err=0;}
        if (id2+len > str_len)
        	{printf("\nERROR: string -testing %d bytes from index %d is longer than the length of the string \n",len,id2); err=0;}
    	if (err==0)/*if we have errors the program should be closed*/
			exit(0);
   
        
    printf("\nThe program testing if %d bytes from both %d and %d indexes are equal in the string:\n%s\n",len,id1,id2,str); 
	
    b1= (void *)(str+id1); 
    b2= (void *)(str+id2);
	/*printing the result after comparing*/
    printf("\n\nThe result from function: %d\n\n",my_bcmp(b1,b2,len));

    

  	 return 0;
 }/*end of main*/






int my_bcmp (const void *b1, const void *b2, size_t len)
{
	char *array1  = (char *)b1;
	char *array2  = (char *)b2;
	size_t i=0;
	
		for (i=0; i<len ; i++)
		{
			if (*(array1+i) != *(array2+i)) 
				printf("the parts dont match");
				return -1;
		}
	    printf("the parts match");
	return 0;
		
 }/*end function*/















