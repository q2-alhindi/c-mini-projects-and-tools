#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_num, guess, numOfguesses; //declare these variables as integers
int main(){
    srand(time(NULL)); 
    rand_num = rand() % 5000 + 1; //generate a random number between 1 and 5000
    printf("Welcome to the guessing game.");
    printf("\nAnytime you wish to end the game enter '0'\n");
    
    do{
        printf("Guess any number between 1 and 5000: ");
        scanf("%d", &guess);//ask the user to enter their guess which will be assigned to the variable 'guess'
        if(guess==0){ //if statement which allows u to end game if enters '0'
            printf("Thank you for playing");
            break; // ends the game if the user enters 0
        }
        numOfguesses++; //add 1 in each iteration to know the number of attempts of user
        // Compare the user's guess with the random number and provide feedback
        if(rand_num==guess){  
            printf("fantastic! you guessed the number correctly\n");
            break; // ends the game if the user guesses the correct number
        }else if(rand_num>guess){ //if guess is lower than the number this is what it prints and the loop continues
             printf("Wrong, its higher try again\n");
        }else if(rand_num<guess){
            printf("Wrong, its lower try again\n"); //if guess is higher than the number this is what it prints and the loop continues
        }else{
            printf("Number out of range"); //if guess is out of range this is what it prints and the loop continues
        }
     }while(1); // loop continues until the user correctly guesses the number or enters '0' to end the game
     if(guess!=0){ 
        printf("You guessed the number in %d attempts", numOfguesses); //prints this line only if user guesses number correctly
     }
}