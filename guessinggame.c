#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_num, guess, numOfguesses; //declare these variables as integers
int main(){
    srand(time(NULL)); 
    rand_num = rand() % 5000 + 1;
    printf("Welcome to the guessing game.");
    printf("\nAnytime you wish to end the game enter '0'\n");
    
    do{
        printf("Guess any number between 1 and 5000: ");
        scanf("%d", &guess);
        if(guess==0){
            printf("Thank you for playing");
            break;
        }
        numOfguesses++;
        // printf("%d", rand_num);
        if(rand_num==guess){
            printf("fantastic! you guessed the number correctly\n");
            break;
        }else if(rand_num>guess){
             printf("Wrong, its higher try again\n");
        }else if(rand_num<guess){
            printf("Wrong, its lower try again\n");
        }else{
            printf("Number out of range");
        }
     }while(1);
     if(guess!=0){
        printf("You guessed the number in %d attempts", numOfguesses);
     }
}