//David Ciupei
//CS360 Final

#include "mftp.h" 

//displays the the contents in the file 20 lines at a time in mftp
void ls(){
	system("ls -l | more -20");
	return;
}


//changes the directory of the client
void cd(char* path){
	if(chdir(path) < 0){
		perror("Error: cd");
	}
	return;
}

//changes the directory of the server
void rcd(char* pathname, int controlfd){
	char* send = (char*)calloc(256, sizeof(char));
	char reply[256];
	strcpy(send, "C");
	strcat(send, pathname);
	strcat(send, "\n");
	write(controlfd, send, strlen(send));
	read(controlfd, reply, 256);
	if(reply[0] == 'E'){
		printf("error: %s", reply+1);
	}
	free(send);
	return;
}

int PortN(int fd){
	int port;
	char reply[256];
	write(fd, "D\n", 2);
	read(fd, reply, 256);
	if(reply[0] == 'E'){
		printf("error: %s", reply+1);
		return(-1);
	}else{
		sscanf(reply, "A%d", &port);
	}
	return port;
}

//shows the working directory of the server
void rls(int datafd, int controlfd){
	char reply[256];
	write(controlfd, "L\n", 2);
	read(controlfd, reply, 256);
	if(reply[0] == 'E'){
		printf("%s", &reply[1]);
	}else{
		int pid;
		if((pid = fork())){
			wait(NULL);
		}else{
			close(0);
			dup2(datafd, 0);
			close(datafd);
			execlp("more", "more", "-20", NULL);
		}
	}
	return;
}

//gets the file from the server and puts where the client is located
void get(char* path, char* fileName, int datafd, int controlfd){
	char* GetPath = (char*)calloc(256, sizeof(char));	
	char* FileTemp[512];
	char reply[256];	
	int fileB, filefd;

	strcpy(GetPath, "G");
	strcat(GetPath, path);
	strcat(GetPath, "\n");
	write(controlfd, GetPath, strlen(GetPath));
	read(controlfd, reply, 256);


	if(reply[0] == 'E'){
		printf("error: %s", reply+1);
		return;
	}else if((filefd = open(fileName, O_CREAT | O_EXCL | O_WRONLY, S_IRUSR | S_IWUSR )) < 0){
			perror("get file open error");
			//write(controlfd, "E\n", 2);
			return;
	}else{
		//write(controlfd, "A\n", 2);
		while((fileB = read(datafd, FileTemp, 512)) > 0){
			write(filefd, FileTemp, fileB);
		}
		close(filefd);
	}
	return;
}

//shows the file from where the server is located or if in server
void show(char *path, int datafd, int controlfd){
	char reply[256];
	char *GetPath = (char*)calloc(256, sizeof(char));

	strcpy(GetPath, "G");
	strcat(GetPath, path);
	strcat(GetPath, "\n");
	write(controlfd, GetPath, strlen(GetPath));
	read(controlfd, reply, 256);

	if(reply[0] == 'E'){
		printf("%s", &reply[1]);
	}else{
		int pid;
		if((pid = fork())){
			wait(NULL);
		}else{
			close(0);
			dup2(datafd, 0);
			close(datafd);
			execlp("more", "more", "-20", NULL);
		}
	}
	free(GetPath);
	return;
}

//put a file from the client and into the server location
void put(char *path, int fileName, int datafd, int controlfd){
	int fileB;
	char reply[256];
	char *FileTemp = (char*)calloc(4096, sizeof(char));

	write(controlfd, "P", 1);
	write(controlfd, path, strlen(path));
	write(controlfd, "\n", 1);
	read(controlfd, reply, 256);
	if(reply[0] == 'E'){
		printf("%s", &reply[1]);
	}else{
		while((fileB = read(fileName, FileTemp, 4096)) > 0){
			write(datafd, FileTemp, fileB);
		}
	}
	free(FileTemp);
	return;
}

int MConnect(char* argv, int portNum){
	int controlfd;
	struct sockaddr_in servAddr;
	struct hostent *hostEntry;
	struct in_addr **pptr;

	if((controlfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("Error with socket");
		exit(1);
	}

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(portNum);

	if((hostEntry = gethostbyname(argv)) == NULL){ //(“lx.encs.vancouver.wsu.edu”);
		fprintf(stderr, "Error with hostEntry");
		exit(1);
	}

	pptr = (struct in_addr**) hostEntry->h_addr_list;
	memcpy(&servAddr.sin_addr, *pptr, sizeof(struct in_addr));
	
	if((connect(controlfd, (struct sockaddr*) &servAddr, sizeof(servAddr))) < 0){
		perror("Error with connect");
		exit(1);
	}

	return controlfd;
}

int isregular(char *path){
	struct stat area, *s = &area;
	return (lstat(path, s) == 0) && S_ISREG(s->st_mode);
}

int PortandConnect(char* argv, int controlfd){
	int port; 
	int datafd;
	port = PortN(controlfd);
	datafd = MConnect(argv, port);

	return datafd;
}



int main(int argc, char *argv[]){
	if(argc < 2){
		printf("Missing HostName!\n\n");
		exit(1);
	}

	int controlfd = MConnect(argv[1], MY_PORT_NUMBER);
	char* delim = " \n\t\v\f\r";
	char* token = (char*)calloc(4096, sizeof(char));
	char* pathname = (char*)calloc(4096, sizeof(char));

	while(1){
		printf("MFTP> ");
		fgets(token, sizeof(char) * 4096, stdin);
		if(token[0] == '\n'){continue;} //if enter is pressed
		token = strtok(token, delim);

		if(strcmp(token, "ls") == 0){
			ls();
			continue;


		}else if(strcmp(token, "rls") == 0){
			int datafd = PortandConnect(argv[1], controlfd);
			rls(datafd, controlfd);
			close(datafd);


		} else if(strcmp(token, "cd") == 0){
			pathname = strtok(NULL, "\n");
			if(pathname == NULL){
				printf("No <pathname> was given for cd!\n");
				continue;
			}
			cd(pathname);
			continue;



		}else if (strcmp(token, "rcd") == 0){
			pathname = strtok(NULL, delim);
			if(pathname == NULL){
				printf("No <pathname> was given for rcd!\n");
				continue;
			}
			rcd(pathname, controlfd);
			continue;



		}else if (strcmp(token, "get") == 0){
			int filefd;
			pathname = strtok(NULL, "\n");
			if(pathname == NULL){
				printf("No <pathname> was given for get!\n");
				continue;
			}
			char* tempFileName = strtok(pathname, "/");
			char* fileName = tempFileName;

			while((tempFileName = strtok(NULL, "/")) != NULL){
				fileName = tempFileName;
			}

			int datafd = PortandConnect(argv[1], controlfd);
			get(pathname, fileName, datafd, controlfd);
			close(datafd);
			continue;


		}else if(strcmp(token, "show") == 0){
			pathname = strtok(NULL, delim);
			if(pathname == NULL){
				printf("No <pathname> was given for show!\n");
				continue;
			}
			int datafd = PortandConnect(argv[1], controlfd);
			show(pathname, datafd, controlfd);
			close(datafd);
			continue;


		}else if (strcmp(token, "put") == 0){
			int filefd;
			pathname = strtok(NULL, delim);
			if(pathname == NULL){
				printf("No <pathname> was given for put!\n");
				continue;
			}
			char *filename = strtok(pathname, "/");
			char *lastname = filename;
			while((filename = strtok(NULL, "/")) != NULL){
				lastname = filename;
			}	
			if((filefd = open(pathname, O_RDONLY)) < 0){
				perror("Error: cant't open file");
				continue;
			}
			if(isregular(pathname)){
				int datafd = PortandConnect(argv[1], controlfd);
				put(lastname, filefd, datafd, controlfd);
				close(filefd);
				close(datafd);
			}else{
				close(filefd);
				perror("File not regular");
			}
			continue;



		}else if (strcmp(token, "exit") == 0){
			char buf[100];
			write(controlfd, "Q\n", sizeof(char) * 2);
			read(controlfd, buf, 100); 
			close(controlfd);
			exit(0);

		}else{
			printf("Unknown Command!\n");
		}
	}
	free(pathname);
	free(token);
	return 0;
}
