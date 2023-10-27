#include <stdio.h>
#include <math.h>

float numrows;
int i, j, x, numrows_int;
int mid;

int main() {
    printf("Specify number of rows: ");
    scanf("%f", &numrows);
    numrows_int=numrows;
    mid = numrows / 2 + 0.5;
    
    if(numrows_int%2==1){
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
            for (x = mid; x < mid*2; x++) {
                if (i <= x && x<mid*2) {
                    printf("* ");
                } else if (x <= mid*2) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}else{
    mid=numrows/2+1;
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
            for (x = mid; x < mid*2; x++) {
                if (i <= x && x<mid*2) {
                    printf("* ");
                } else if (x <= mid*2) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    
}
}
