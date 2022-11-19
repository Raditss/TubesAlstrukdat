#include "queueFood.h"
#include "../ListStatikFood/listStatikFood.h"

/* Driver untuk queueFood.h */

int main(){

    PrioQueueTime contohInventory;
    FoodType contohIsi;

    ListStatik daftarMenu = readFileMakananListStatik("../../bin/menumakanan.txt");

    MakeEmptyFood(&contohInventory, 200);
    makeFoodType(&contohIsi, 100, ELMT_LIST_STATIK(daftarMenu,1));

    IsEmptyFood(contohInventory) ?
        printf("Saat ini contoh Inventory kosong\n"):
        printf("Tulisan ini tidak mungkin keluar\n");

    printf("=======================================\n");

    EnqueueFood(&contohInventory,contohIsi);

    IsEmptyFood(contohInventory) ?
        printf("Tulisan ini tidak mungkin keluar\n"):
        printf("Saat ini contoh Inventory tidak kosong\n");

    printf("=======================================\n");

    printf("Isi Inventory saat ini adalah berjumlah: %d\n", NBElmtFood(contohInventory));
    
    printf("=======================================\n");

    IsFullFood(contohInventory) ?
        printf("Tulisan ini tidak mungkin keluar\n"):
        printf("Saat ini contoh Inventory tidak penuh\n");

    printf("=======================================\n");

    PrintPrioQueueTimeFood(contohInventory);
    
    printf("=======================================\n");

    TIME realTime = MakeTIME(1,2,5);
    printf("Format display time: ");
    displayTime(realTime);

    printf("\n=======================================\n");

    displayInventory(contohInventory,realTime);

    printf("=======================================\n");

    PrioQueueTime copyInventory = copyPrioQueue(contohInventory);

    displayInventory(copyInventory,realTime);


    return 0;
}