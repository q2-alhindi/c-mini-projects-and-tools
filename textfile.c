#include<stdio.h>

int main(){
    FILE *fptr;
    fptr = fopen("test.txt","w"); //open a file in read mode
    fprintf(fptr, "hi im qais"); //writing into the file
    fclose(fptr);
    fptr = fopen("test.txt","r"); //reading from the file
    char mystring[100];
    fgets(mystring,100,fptr); //read the content and store it inside my string
    printf("%s", mystring);
    fclose(fptr);
}