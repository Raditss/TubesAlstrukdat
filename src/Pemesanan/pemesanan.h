#ifndef _BUY_H_
#define _BUY_H_

#include "../UndoRedo/UNDO_REDO.h"



void BUY(Simulator sim,ListStatik *daftar, PrioQueueTime *belanjaan, TIME globalTime, boolean *isValid){
    /* Membeli makanan dengan id tertentu */
    /* I.S daftar dan belanjaan terdefinisi */
    /* F.S daftar dan belanjaan terdefinisi */
    /* Proses: menghapus makanan dengan id tertentu dari daftar dan menambahkannya ke belanjaan */
    boolean toko_buka = (Hour(globalTime) * 60 + Minute(globalTime)) > 8*60-1 &&
                        (Hour(globalTime) * 60 + Minute(globalTime)) < 22*60;

    if (isClose((sim).LokasiPengguna,'T') && toko_buka){
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
            *isValid = true;
        } else {
            printf("ID tidak ditemukan\n");
        }


    } else if (!isClose((sim).LokasiPengguna,'T')){
        printf("Anda tidak berada di toko!\n");
    } else {
        printf("Toko tutup\n");
        printf("Toko mulai buka pukul 08:00 dan tutup pukul 22:00\n");
    }
}



#endif