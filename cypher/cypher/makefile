all: cypher 

cypher: cypher.o 
	gcc -std=c99 -Wall -pedantic -g cypher.o cypher

cypher.o: cypher.c
	gcc -std=c99 -Wall -pedantic -g cypher.c

clobber: 
	rm -rf *.o *~ *.dSYM cypher *.tar.gz

test: 
	gcc -c -g -Wall -std=c99 cypher.c
	gcc -g -Wall -std=c99 cypher.o -o cypher
	./test.sh


