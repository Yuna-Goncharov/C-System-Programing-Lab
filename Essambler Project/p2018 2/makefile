assembler: linkedList.o functions.o datatype.o main.o 
	gcc -g -ansi -Wall -pedantic linkedList.o functions.o datatype.o main.o -o assembler
main.o: main.c linkedList.h datatype.h functions.h
	gcc -g -c -ansi -Wall -pedantic main.c -o main.o
functions.o: functions.c linkedList.h datatype.h functions.h
	gcc -g -c -ansi -Wall -pedantic functions.c -o functions.o
linkedList.o: linkedList.c linkedList.h datatype.h
	gcc -g -c -ansi -Wall -pedantic linkedList.c -o linkedList.o
datatype.o: datatype.c datatype.h
	gcc -g -c -ansi -Wall -pedantic datatype.c -o datatype.o
	
	

