#include "stackNotif.h"

/* Driver untuk stackNotif.h */

int main(){

    NOTIF_STACK NS;;
    CreateEmptyNotif(&NS);

    IsEmptyNotif(NS) ?
        printf("Saat ini notif kosong\n"):
        printf("Tulisan ini tidak mungkin keluar\n");

    IsFullNotif(NS) ?
        printf("Tulisan ini tidak mungkin keluar\n"):
        printf("Saat ini notif tidak penuh\n");

    printf("Masukkan beberapa kata sampai titik: \n>> ");
    STARTWORDINPUT();

    while (!endWord)
    {   
        PushNotif(&NS,currentWord);
        ADVWORD();
    }

    displayNotif(&NS);
    
    PushNotif(&NS,currentWord);
    clearNotif(&NS);

    displayNotif(&NS);
    
    return 0;
}