all: wordhash clean

wordhash: getWord.o  hashtable.o 
	gcc  -std=c99 -Wall -pedantic -g getWord.o hashtable.o -o wordhash


getWord.o: getWord.c hashtable.c hashtable.h
	gcc -c -Wall -pedantic -g -std=c99 getWord.c


hashtable.o: hashtable.c hashtable.h
	gcc -c -Wall -pedantic -g -std=c99 hashtable.c

clean:
	rm *.o
	rm *~