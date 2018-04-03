#include <stdio.h>
#include <ctype.h>


char * shortenStr(char str[]);

int main(void)
{
	char str[81];
	puts ("\n Please enter string with limit of 80 char long \n");
	gets(str);
	printf("\n String input: \t\t\"%s\"\n\n",str);
	printf("Shorter String is:\t\"%s\"\n\n",shortenStr(str));
	return 0;
}

/*check if two chars are sequential letter */

int chSequence(char cr1 ,char cr2)
{
	return ((cr1-cr2 ==1) && isalpha(cr1) && isalpha(cr2));
}	

/* the shorter string*/

char * shortenStr(char str[])
{
	int r,w;
	for (r=1,w=1 ; str[w] !='\0'; r++,w++)
	{
		if (chSequence(str[r], str[r+1]) && chSequence(str[r-1],str[r]))
		{
			while(chSequence(str[r+1],str[r+2]))
				++r;
			str[w] ='-';
		}
		else
			str[w]= str[r];
	}
	return str;
}


