#include <stdio.h>

#define BLUE   "\x1b[34m"
#define RESET  "\x1b[0m"

int main () {
    for (int A = 0; A < 9; A++) {
        printf (BLUE "____" RESET);
    }
    for (int A = 0; A < 9; A++) {
        printf (BLUE "\n|" RESET);
        for (int B = 0; B < 9; B++) {
            printf (" 0 ");
            if ((B - 2) % 3 == 0 || B == 8) {
                printf (BLUE "|" RESET);
            } else {
                printf ("|");
            }
        }
        printf (BLUE "\n|" RESET);
        for (int B = 0; B < 9; B++) {
            if ((A + 1) % 3 == 0 || A == 8) {
                printf (BLUE "___" RESET);
                if ((B + 1) % 3 == 0 || B == 8) {
                    printf (BLUE "|" RESET);
                } else {
                    printf ("|");
                }
            } else {
                printf ("___");
                if ((B + 1) % 3 == 0 || B == 8) {
                    printf (BLUE "|" RESET);
                } else {
                    printf ("|");
                }
            }
        }
    }
    return 0;
}