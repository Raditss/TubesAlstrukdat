#include "../header/charmachine.h"

/* Driver untuk charmachine.h */

int main(){

    printf("================================================\n");

    START("../../bin/ujiCharMachine.txt");
    printf("Karakter pertama setelah di start: %c\n", currentChar);
    printf("Kata yang terbentuk adalah: ");
    while (!EOP)
    {
        printf("%c", currentChar);
        ADV(); // untuk next huruf
    }
    printf("\n");

    printf("================================================\n");

    return 0;
}