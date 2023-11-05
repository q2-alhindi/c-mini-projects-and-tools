#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rand_num, guess, numOfguesses; //declare these variables as integers
int playerscores[3]={0}; //create an array named playerscores which can hold 3 integers
int randomnumber[3]={0}; //create an array named randomnumber which can hold 3 integers
int guessnumber[3]={0}; //create an array named guessnumber which can hold 3 integers
int currentplayer=1; 
int main(){
    srand(time(NULL)); 
    printf("Welcome to the guessing game.\n");
    printf("choose the number of players that wish to play: ");
    printf("\nAnytime you wish to end the game enter '0'\n");
    
    do{ //go through this after each player is done
        rand_num = rand() % 5000 + 1; //a random number is generated from 1 to 5000 and stored in this variable 'rand_num'
        numOfguesses=0;
        printf("Player %d guess a number between 1 and 5000: ", currentplayer);//ask the user to enter their guess which will be assigned to the variable 'guess'
        while(1){
            scanf("%d", &guess);
            if(guess==0){ //if statement which allows u to end game if enters '0'
                printf("player %d ended the game\n", currentplayer);
                randomnumber[currentplayer]=rand_num; //store the random number generated in the array
                guessnumber[currentplayer]=guess; //store the guess number in an array
                break; // ends the game if the user enters 0
            }
            numOfguesses++; //add 1 in each iteration to know the number of attempts of user
            // Compare the user's guess with the random number and provide feedback
            if(rand_num==guess){  
                printf("fantastic! player %d guessed the number in %d attempts\n", currentplayer, numOfguesses);
                playerscores[currentplayer]=numOfguesses; //add the number of attempts to the array for each player
                randomnumber[currentplayer]=rand_num; //store the random number generated in the array
                guessnumber[currentplayer]=guess; //store the guess number in an array

                break; // ends the game if the user guesses the correct number
            }else if(rand_num>guess){ //if guess is lower than the number this is what it prints and the loop continues
                printf("Wrong, its higher try again: ");
            }else if(rand_num<guess){//if guess is higher than the number this is what it prints and the loop continues
                printf("Wrong, its lower try again: ");  
            }else{//if guess is out of range this is what it prints and the loop continues
                printf("Number out of range, try again: "); 
            }
        }

        currentplayer++; //add 1 to the player number after the player finishes
        if (currentplayer==4){ //when the 3 players are done it prints this and exits the first while
            printf("Maximum number of players reached\n");
            break; //exits the first while loop
        }

        }while(1);
            currentplayer=currentplayer-1; 
            printf("Scoreboard\n");
                for(int i=1; i<=currentplayer; i++){ //loops over players that guessed number correctly
                    if(guessnumber[i]==randomnumber[i]){
                    printf("Player %d took %d attempts\n", i, playerscores[i]);
                }
                }
                    for(int i=1; i<=currentplayer; i++){ //loops over players that ended the game
                        if(randomnumber[i]!=guessnumber[i]){
                        printf("player %d ended the game\n", i);
                    }
                    }
                }
                
