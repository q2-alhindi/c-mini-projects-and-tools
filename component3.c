#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> //for the open function
#include <unistd.h>
#include <sys/types.h>

 int main(int argc, char *argv[]){
    if (argc==1){ //if its 1 not enough arguements were passed for the command
        printf("Not enough arguements entered! The correct way: cp <src> <dest>\n");
    }else if(argc==3){ //if its 3 then enough arguements were passed
        int src = open(argv[1], O_RDONLY); //opens source file and assigns the file id value to the integer src
        if(src==-1){ //if source file is not a valid file print this
            printf("Source error! File doesnt exist");
            return 0;
        }
        int dest = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0766); // open the destination file for writing, creating it if it doesn't exist, truncating it if it does

        if(!dest){ //if destination file is not valid
            printf("File creation error! Do you have permissions");
        }
        int size = 8192; //the bytes of data we want to read in at a time
        char *buf = malloc(sizeof(char) * size); //allocate memory to store all the information
        int amt = 0; //declare amt as an integer
        while((amt = read(src, buf, size))>0){ //the read function reads data from source file into 'buf' with a max of 'size', this while loops keeps going as long as the read is more than 0
            write(dest, buf, amt); //write data in the destination file from the 'buf'
        }
        //close source and destination files
        close(src);
        close(dest);
        //free the allocated memory
        free(buf);    
    }else {
        printf("Incorrect usage! The correct way: cp <src> <dest>");
    }
    return 0;
 }

    
    
