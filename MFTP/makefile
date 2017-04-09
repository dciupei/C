
CC=gcc
COPTS=-std=c99 -Wall -pedantic

all: mftp.c mftpserve.c
	$(CC) $(COPTS) mftp.c -o mftp
	$(CC) $(COPTS) mftpserve.c -o mftpserve

time: mftp.c mftp.h
	$(CC) $(COPTS) mftp.c -o mufti

serve: mftpserve.c mftp.h
	$(CC) $(COPTS) mftpserve.c -o mftpserve