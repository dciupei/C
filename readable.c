//David Ciupei
//CS360 Assignment #3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

int isDirectory (char *pathname);
int isRegular (char *pathname);


void directory(char *pathName){
    DIR *dir;
    if(!(dir = opendir(pathName))){         //checks if it can open the directory
        fprintf(stderr, "\nError: Can't open directory!!\n\n");

    }
    struct dirent *entry;

    if(dir == NULL){                // returns if directory is null
        return;
    }
    
    while((entry = readdir(dir))){
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
        }
    
        char *path = (char*)malloc(sizeof(char)*4096);

        strcpy(path, pathName);
        if(strcmp(path, "/")!=0){                   // adds a "/" if one is not there
            strcat(path, "/");
        }
        strcat(path, entry->d_name);
        
        if(access(path, R_OK) != 0){
            continue;
        }else{
        
        if(isDirectory(path)){                  //checks if its a directory
            directory(path);                //recurses to next directory
            continue;
        }else{                                  //if not its regular
            if(isRegular(path)){
                printf("%s\n", path);           // prints the path name

            }
        }
    }
    }
    closedir(dir);
}

int isDirectory (char *pathname) {              //checks to see if its a directory
    struct stat area, *s = &area;
    return (lstat (pathname, s) == 0) && S_ISDIR (s->st_mode);
}

int isRegular (char *pathname) {                //checks to see if its a regular file
    struct stat area, *s = &area;
    return (stat (pathname, s) == 0) && S_ISREG (s->st_mode);
}

int main(int argc, char * argv[]) {
    char* path = (char*)malloc(sizeof(char) * 4096);

    if(argc != 1){
        path = argv[1];
        directory(path);
    }else{
        getcwd(path, 4096);
        directory(path);

    }
  
    
    return 0;
}

