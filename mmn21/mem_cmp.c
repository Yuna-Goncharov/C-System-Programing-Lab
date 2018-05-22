#include <stdio.h>
#include <string.h>

/*The function receives two pointers to different arrays and number (counter), and compares lexicographic between 2 ascii chars sequence (byte after byte). If the sequence in the first array bigger than the sequence in the second array, the function returns 1 and if the sequence is smaller, the function returns -1. If sequences are equal, returns 0.
Pay attantion that i changed the name of the function to memcmpp instead of memcmp*/

int memcmpp(const void *p1, const void *p2, int count){
	int i;
	char *cp1 = (char*) p1;/*casting to char*/
	char *cp2 = (char*) p2;/*casting to char*/
	for(i = 0; i < count; i++){
		if (*cp1 > *cp2)
			return 1;
		if (*cp1 < *cp2)
			return -1;
		/*incrementing*/
		cp1++;
		cp2++;
	}
	return 0;
}




int main(){
	int count;
	char arr1 [100];
	char arr2 [100];
	printf("Please enter tow words and number\n");
	/*reading from user two strings and number*/
	scanf("%s %s %d", arr1, arr2, &count);
	/*calling to funcation 'memcmpp' and printing the results*/
	printf("%d\n", memcmpp(arr1, arr2, count));
	return 0;
}
