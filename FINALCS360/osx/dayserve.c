//David Ciupei
//CS360 Assignment #9

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define MY_PORT_NUMBER 49999

int Listening(){
	int listenfd, connectfd;
	char *hostName;
	struct hostent *hostEntry;
	struct sockaddr_in clientAddr;
	struct sockaddr_in servAddr;

	socklen_t length = sizeof(struct sockaddr_in);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(MY_PORT_NUMBER);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error with socket");
		exit(1);
	}
	if(bind(listenfd, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0){
		perror("Error with bind");
		exit(1);
	}

	listen(listenfd, 1);

	while(1){	//keep listening till program is stopped

		//The flag WNOHANG specifies that waitpid 
		//should return immediately instead of waiting, 
		//if there is no child process ready to be noticed.
		waitpid(-1, NULL, WNOHANG);

		if((connectfd = accept(listenfd, (struct sockaddr*) &clientAddr, &length)) < 0){
			perror("Error with accept");
			exit(1);
		}
		if(fork()){
			close(connectfd); //parent closes the connect
		}else{
			close(listenfd);  //child closes the listen
			break;
		}
	}
	
	if((hostEntry = gethostbyaddr(&(clientAddr.sin_addr), sizeof(struct in_addr), AF_INET)) == NULL){
		herror(NULL);
		fprintf(stderr, "Error with hostEntry");
		exit(1);
	}

	hostName = hostEntry->h_name;
	printf("%s\n", hostName);

	return connectfd;
}

void getDate(int connectfd){
	time_t seconds;
	char *date;
	seconds = time(NULL);
	date = ctime(&seconds);
	write(connectfd, date, strlen(date));
	close(connectfd);

	return;
}

int main(int argc, char *argv[]){
	int connectfd = Listening();
	getDate(connectfd);
	
	return 0;
}

