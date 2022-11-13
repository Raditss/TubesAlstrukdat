#ifndef _BUY_H_
#define _BUY_H_

#include "UNDO_REDO.h"


void BUY(Simulator sim,ListStatik *daftar, PrioQueueTime *belanjaan, TIME globalTime){
    /* Membeli makanan dengan id tertentu */
    /* I.S daftar dan belanjaan terdefinisi */
    /* F.S daftar dan belanjaan terdefinisi */
    /* Proses: menghapus makanan dengan id tertentu dari daftar dan menambahkannya ke belanjaan */

    if (isClose((sim).LokasiPengguna,'B')){
        printf("======================\n");
        printf("=        BUY         =\n");
        printf("======================\n");
        printf("List Bahan Makanan:\n \n");
        printListStatikFood(*daftar);
        printf("Masukkan ID makanan yang ingin dibeli: ");
        STARTKALIMAT();
        int ini_ID = strToIntV2(kalimatToWord(currentKalimat));
        FoodType x;
        if (findMakananByID(*daftar, ini_ID)){
            Info(x) = searchFoodByID(*daftar, ini_ID);
            x.time_left = TIMEToMinute(DTIME(Info(x))) + TIMEToMinute(globalTime);
            EnqueueFood(belanjaan, x);
            printf("Makanan berhasil dicheckout!\n");
            printf("Silahkan menunggu makanan sampai di lokasi Anda!\n");
        } else {
            printf("ID tidak ditemukan\n");
        }


    }
    else{
        printf("Anda tidak berada di toko!\n");
    }
}

void displayDelivery(PrioQueueTime belanjaan){

    PrintPrioQueueTimeFood(belanjaan);

}


#endif