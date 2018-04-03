#include <stdio.h>

/*To use fgets and printf I need to include stdio header*/

#include <string.h>
/*To use strlen I need to include string header*/

#define MAXLINE 80 /* maximum input line length */

int suffix(char str[], char c);

/*
  The function suffix prints all the substrings that 
  (1) starts with the letter stored in the variable 'c' 
  (2) included in the string str[]
  (3) returns the number of substrings
 */


int main()
{
    char user_input[MAXLINE]; /* current input line */
    char ch = 0;
    int counter = 0;
    int i=0;
    for (i=0; i < MAXLINE-1 ; ++i)
      user_input[i] = 0;


    printf(" \nPlease enter a string not bigget then 80 characters) and then press enter\n ");


    for (i=0; i < MAXLINE-1 && ( ch=getchar())!= EOF && ch !='\n'; ++i)
      user_input[i] = ch;

    user_input[i] ='\0';

    printf(" \nPlease enter a character and then press enter\n");
    scanf(" %c", &ch);

    counter = suffix(user_input,ch);

    printf("substring counter is = %d ", counter);

    printf("\n");

    return 0;
}


int suffix(char str[], char ch){
	
	int j, i,count;
	
	for (i=0;i<strlen(str);i++){
		if (str[i]== ch){
			for(j=i;j<strlen(str);j++){
		 	      printf("%c" ,str[j]);
		        }

			    count++;
			    printf("\n");
		}
	}
	
	return count;
}


