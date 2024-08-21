#include<stdio.h>
int main () {
    for (int A = 0; A < 9; A++) {
        printf ("____");
    }
    for (int A = 0; A < 9; A++) {
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf (" 0 |");
        }
        printf ("\n|");
        for (int B = 0; B < 9; B++) {
            printf ("___|");
        }
    }
    return 0;
}