#include<stdio.h>

int main(){
    FILE *fptr; //
    fptr = fopen("test.txt","w"); //open a file in read mode
    fprintf(fptr, "hi im qais"); //writing into the file
    fclose(fptr); //close file
    fptr = fopen("test.txt","r"); //open and reading from the file
    char mystring[100]; //created variable mystring to store contents of file in
    fgets(mystring,100,fptr); //read the content and store it inside my string
    printf("%s", mystring); //print the content of the file
    fclose(fptr); //close the file
}