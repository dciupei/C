//David Ciupei
//CS360 Final

#include "mftp.h" 

int Listening(int port){
	int socketfd, length;
	length = sizeof(struct sockaddr_in);
	struct sockaddr_in servAddr;

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if( (socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket");
		exit(1);
	}
	if ( bind( socketfd, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0) {
		perror("bind error");
		exit(1);
	}
	return socketfd;	
}

//used for when calling rcd 
void C(int controlfd, char Cbuff[]){
	char reply[256];
	char path[1024];
	int i, FileB;
	i = 0;

	while((FileB = read(controlfd, Cbuff, 1)) > 0){
		if(Cbuff[0] == '\n'){
			path[i] = '\0';
			break;
		}else{
			path[i] = Cbuff[0];
			i++;
		}
	}
	if(chdir(path) < 0){
		strcpy(reply, "Edirectory change unsucessful\n");
		write(controlfd, reply, strlen(reply));
	}else{
		write(controlfd, "A\n", 2);
	}
	return;
}

//used for when calling rls
void L(int datafd, int controlfd){
	int pid;
	write(controlfd, "A\n", 2);
	if((pid = fork())){
		wait(NULL);
	}else{
		close(1);
		dup2(datafd, 1);
		execlp("ls", "ls", "-l",  NULL);
		exit(1);
	}						
	close(datafd);
	return;
}

//used when calling get and show
void G(int datafd, int controlfd, char Cbuff[]){
	char reply[256];
	char path[1024];
	char GetBuff[512];
	int i, FileB, filefd;
	i = 0;

	while((FileB = read(controlfd, Cbuff, 1)) > 0){
		if(Cbuff[0] == '\n'){
			path[i] = '\0';
			break;
		}else{
			path[i] = Cbuff[0];
			i++;
		}
	}
	if((filefd = open(path, O_RDONLY, S_IRUSR)) < 0){
		perror("error ");
		strcpy(reply, "Efile does not exist\n");
		write(controlfd, reply, strlen(reply));
		exit(-1);
	}else{
		write(controlfd, "A\n", 2);
		printf("%s getting file\n", path);
		while((FileB = read(filefd, GetBuff, 512)) > 0){
			write(datafd, GetBuff, FileB);
		}
	close(filefd);
	close(datafd);
	}
	return;
}

//used when calling put
void P(int datafd, int controlfd, char response[], char path[], char Cbuff[]){
	int FileB, filefd;
	int i = 0;
	char filebuf[4096];

	while((FileB = read(controlfd, Cbuff, 1)) > 0){
		if(Cbuff[0] == '\n'){
			path[i] = '\0';
			break;
		}else{
			path[i] = Cbuff[0];
			i++;
		}
	}
	printf("Writing file %s\n", path);
	if((filefd = open(path, O_CREAT | O_APPEND | O_EXCL | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)) < 0){
		sprintf(&response[0], "E%s\n", strerror(errno));
		write(controlfd, response, strlen(response));
		close(datafd);
		exit(0);
	}
	write(controlfd, "A\n", 2);
	printf("Receiving file %s from client\n", path);
	while((FileB = read(datafd, filebuf, 4096)) > 0){
		write(filefd, filebuf, FileB);
	}
	close(filefd);
	close(datafd);
	return;	
}

//used when calling exit
void Q(int controlfd){
	write(controlfd, "A\n", 2);
	close(controlfd);
	printf("Client Has Successfully Quit!");
	exit(0);
	return;
}


int main(int argc, char *argv[]){
	int listenfd, controlfd, data_listenfd, datafd, pid;
	char Cbuff[1];
	char* hostName;
	struct hostent *hostEntry;
	struct sockaddr_in clientAddr;
	socklen_t length = sizeof(struct sockaddr_in);

	length = sizeof(struct sockaddr_in);
	listenfd = Listening(MY_PORT_NUMBER);
	listen(listenfd, 4);
	printf("Listening for connection on port\n");

	while(1){
		if( (controlfd = accept(listenfd, (struct sockaddr *) &clientAddr, (socklen_t *) &length) ) < 0) {
			perror("accept error");
			exit(1);
		}
		if( (hostEntry = gethostbyaddr(&(clientAddr.sin_addr), sizeof(struct in_addr), AF_INET)) == NULL){
			herror("gethostbyaddr error");
			exit(1);
		}else{
			hostName = hostEntry->h_name;						
			printf("%s connected\n", hostName);		
		}		
		if((pid = fork())){						// parent
			wait(NULL);
		}else{									//child
			while(1){		
				char path[4096];
				char response[256];
				read(controlfd, Cbuff, 1);	
				if(Cbuff[0] == 'D'){			//make the connection

					read(controlfd, Cbuff, 1);
					data_listenfd = Listening(0);
					char dataBuff[16];
					int port;

					struct sockaddr_in data_servAddr;
					struct sockaddr_in data_clientAddr;
					memset(&data_servAddr, 0, sizeof(data_servAddr));

					listen(data_listenfd, 1);
					getsockname(data_listenfd, (struct sockaddr*) &data_servAddr, &length);

					port = ntohs(data_servAddr.sin_port);
					printf("%s opened data port: %d\n",hostName, port);
					sprintf(&dataBuff[0], "A%d\n", port);
					write(controlfd, dataBuff, strlen(&dataBuff[0]));
					if((datafd = accept(data_listenfd, (struct sockaddr *) &data_clientAddr, (socklen_t *) &length)) < 0) {
						perror("accept error");
						exit(1);
					}
																	
				}else if (Cbuff[0] == 'C'){
					C(controlfd, Cbuff);
				}else if (Cbuff[0] == 'L'){
					if(!data_listenfd){
						printf("Error: Couldn't make connection!");
					}
					L(datafd, controlfd);
				}else if (Cbuff[0] == 'G'){
					if(!data_listenfd){
						printf("Error: Couldn't make connection!");
					}
					G(datafd, controlfd, Cbuff);
					continue; 
				}else if (Cbuff[0] == 'P'){
					if(!data_listenfd){
						printf("Error: Couldn't make connection!");
					}
					P(datafd, controlfd, response, path, Cbuff);
					continue;
				}else if (Cbuff[0] == 'Q'){
					Q(controlfd);
					break;
				}
			}
		}
	}
	return 0;
}
