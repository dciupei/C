cypher: A simple text encryption algorithm that uses a short one-time pad.

Author: David Ciupei ciupei_david@yahoo.com
Modification History:
  D. Ciupei (3/30/2015) .... created
  D. Ciupei (4/3/2015) .... added test, targets to Makefile


Build: 
	A makefile is provided which helps build the program. Just simply type in make and the program will be ready to be executed.

Usage:
	To encrypt ./cypher e ‘phrase’
  		where ‘phrase’ is the "secret" encryption key.

  	To decrypt ./cypher d ‘phrase’
  		where ‘phrase’ is the same key used for encryption

Example:
 ./cypher e ‘What time is it?’ < poem.txt > secret.txt
 ./cypher d ‘What time is it?’ < secret.txt > original.txt

Files in archive:

README........ this file
Makefile ..... makefile for building app
cypher.c ..... encryption C99 source code
hello.txt ..... a file with a random phrase
test.sh ...... bash test script


