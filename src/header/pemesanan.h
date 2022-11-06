#include "queuefood.h"
#include "listStatikFood.h"
#include "matrix.h"
#include "simulator.h"
#include "wordmachine.h"
#include "time.h"
#include "string.h"



void buy(Simulator sim,ListStatik *daftar, PrioQueueTime *belanjaan, TIME globalTime){
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
        STARTWORDINPUT();
        FoodType x
        Info(x) = ELMT_LIST_STATIK(*daftar, (strToInt(currentWord.TabWord)-1))
        x.time_left = DTIME(Info(x));
        EnqueueFood(belanjaan, ELMT_LIST_STATIK(*daftar, (strToInt(currentWord.TabWord)-1)));
        printf("Makanan berhasil dicheckout!\n");
        printf("Silahkan menunggu makanan sampai di lokasi Anda!\n");

    }
    else{
        printf("Anda tidak berada di toko!\n");
    }
}

void displayDelivery(PrioQueueTime *belanjaan){

    PrintPrioQueueTimeFood(*belanjaan);

}
