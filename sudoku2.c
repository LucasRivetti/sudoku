#include<stdio.h>
int main () {
    for (int A = 0; A < 9; A++) {
        printf ("________");
    }
    for (int A = 0; A < 9; A++) {
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf ("       |");
        }
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf ("   0   |");
        }
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf ("_______|");
        }
    }
    return 0;
}