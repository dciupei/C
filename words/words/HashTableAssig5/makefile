all: wordhash clean

wordhash: words.o  hash.o 
	gcc  -std=c99 -Wall -pedantic -g words.o hash.o -o wordhash


words.o: words.c hash.c hash.h
	gcc -c -Wall -pedantic -g -std=c99 words.c


hash.o: hash.c hash.h
	gcc -c -Wall -pedantic -g -std=c99 hash.c

clean:
	rm *.o
	rm *~