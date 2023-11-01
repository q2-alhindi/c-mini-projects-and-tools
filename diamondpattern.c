#include <stdio.h>  
#include <math.h>   

float numrows;      // declare a float variable to store the number of rows.
int i, j, x, numrows_int;  // declare integer variables i, j, x, and numrows_int.
int mid;    // declare an integer variable to store the middle value.

int main() {
    printf("Specify number of rows: ");  // ask the user to specify the number of rows the diamond
    scanf("%f", &numrows);  // read the input value for the number of rows as a float and store it in "numrows"
    numrows_int = numrows;  // convert 'numrows' to an integer and store it in 'numrows_int'.

    mid = numrows / 2 + 0.5;  // calculate the middle row value based on the number of rows.

    if (numrows_int % 2 == 1) {  // check if the number of rows is odd.
        //for loop for rows
        for (i = 1; i <= numrows; i++) {
            if (i <= mid) {
                //for loop to print spaces or asterisks in the upper part of the pattern(the middle row and rows above it)
                for (j = mid; j >= 1; j--) {
                    if (i >= j) {
                        printf("* ");  // print an asterisk
                    } else {
                        printf(" ");   // print a space
                    }
                }
            } else {
                // for loop to print spaces or asterisks in the lower part of the pattern(below the middle row)
                for (x = mid; x < mid * 2; x++) {
                    if (i <= x && x < mid * 2) {
                        printf("* ");  // print an asterisk
                    } else if (x <= mid * 2) {
                        printf(" ");   // print a space
                    }
                }
            }
            printf("\n");  // move to the next line after each row is printed
        }
        return 0;  // exit the program.
    } else {
        // for even numbers
        mid = numrows / 2 + 1;  // calculate the updated middle value.

        // the rest of the code is identical to the above

        for (i = 1; i <= numrows; i++) {
            if (i <= mid) {
                for (j = mid; j >= 1; j--) {
                    if (i >= j) {
                        printf("* ");
                    } else {
                        printf(" ");
                    }
                }
            } else {
                for (x = mid; x < mid * 2; x++) {
                    if (i <= x && x < mid * 2) {
                        printf("* ");
                    } else if (x <= mid * 2) {
                        printf(" ");
                    }
                }
            }
            printf("\n");
        }
    }
}
