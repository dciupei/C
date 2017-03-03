//David Ciupei
//CS360 Assignment #9

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MY_PORT_NUMBER 49999

int MConnect(char *argv){
    int socketfd;
    struct sockaddr_in servAddr;
    struct hostent *hostEntry;
    struct in_addr **pptr;
    
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(MY_PORT_NUMBER);
    
    if((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("Error with socket");
        exit(1);
    }
    
    if((hostEntry = gethostbyname(argv)) == NULL){ //(“lx.encs.vancouver.wsu.edu”);
        fprintf(stderr, "Error with hostEntry");
        exit(1);
    }
    
    pptr = (struct in_addr**) hostEntry->h_addr_list;
    memcpy(&servAddr.sin_addr, *pptr, sizeof(struct in_addr));
    
    if((connect(socketfd, (struct sockaddr*) &servAddr, sizeof(servAddr))) < 0){
        perror("Error with connect");
        exit(1);
    }
    
    return socketfd;
}


int main(int argc, char *argv[]){
    int socketfd = MConnect(argv[1]);
    char date[25];
    read(socketfd, date, 25);	//read the date into the date array
    printf("%s", date);
    close(socketfd);
    
    return 0;
}
