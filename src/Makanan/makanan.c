#include "makanan.h"

/* Driver untuk makanan.h */

int main(){

    Makanan A,B,C;

    /* Membentuk makanan A */
    CreateMakanan(&A, strToWord("Makanan Uji."), MinuteToTIME(15), MinuteToTIME(20), strToWord("Dibacok."));
    ID(A) = 10;
    CreateMakanan(&C, strToWord("Makanan Uji."), MinuteToTIME(15), MinuteToTIME(20), strToWord("Dibacok."));

    /* Membentuk makanan B */
    B = createEmptyFood();

    isEmptyFood(B) ?
        printf("Food B kosong\n"):
        printf("Tulisan ini tidak mungkin keluar\n");

    printf("\n===============================\n");

    isEmptyFood(A) ?
        printf("Tulisan ini tidak mungkin keluar\n"):
        printf("Makanan A tidak kosong\n");

    printf("\n===============================\n");

    DisplayMakanan(A);

    printf("\n===============================\n");

    isFoodEqual(A,B) ?
        printf("Tulisan ini tidak mungkin keluar\n"):
        printf("A dan B tidak sama\n");

    printf("===============================\n");

    isFoodEqual(A,C) ?
        printf("A dan C sama\n"):
        printf("Tulisan ini tidak mungkin keluar\n");


    return 0;
}