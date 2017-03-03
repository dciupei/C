INCDIRS = -I$(GET_WORD)/include
LIBDIRS = -L$(GET_WORD)/lib

Wordpair: Words.o Hash.o
	gcc $(LIBDIRS) Words.o Hash.o -o Wordpair -lget

Words.o: Words.c Hash.h
	gcc -c $(INCDIRS) Words.c -o Words.o

Hash.o: Hash.c Hash.h
	gcc -c Hash.c -o Hash.o
