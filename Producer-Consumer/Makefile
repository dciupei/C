HEADERS = buffer.h 

default: Producer-Consumer

Producer-Consumer.o: Producer-Consumer.c $(HEADERS)
	gcc -c Producer-Consumer.c -o Producer-Consumer.o


Producer-Consumer: Producer-Consumer.o
	gcc Producer-Consumer.o -o Producer-Consumer

clean:
	-rm -f Producer-Consumer.o
	-rm -f Producer-Consumer
