
#include "../header/COOKBOOK.h"
#include "splash.c"
#include "quit.c"
#include "../header/pemesanan.h"
#include "../header/pengolahan.h"



int main(){

        /* Mendapatkan daftar makanan */
        ListStatik daftarMakanan = readFileMakananListStatik("../../bin/menumakanan.txt");
        
        /* Mendapatkan daftar makanan KHUSUS BUY */
        ListStatik buyAbleFood = isBuyAble(daftarMakanan);

        /* Mendapatkan daftar resep */
        KumpulanTree daftarResep; 
        resepReader(&daftarResep, "../../bin/resepmakanan.txt");
        KumpulanTree advancedResep = mergeAdvancedTree(daftarResep);
        
        /* Mendapatkan peta awal simulator */
        Matrix peta = getPeta("../../bin/peta_buy.txt");
        peta = createBorder(peta);

        /* Membentuk simulator */
        Simulator sim;
        printf("Please enter your name: ");
        STARTKALIMAT();
        createSimulator(&sim, kalimatToWord(currentKalimat), peta);

        /* Melakukan set time ke 00:00:00 */
        TIME realTime;
        CreateTime(&realTime,0,0,0);

        /* Melakukan pembuatan kalimat pembanding */
        Kalimat start = wordToKalimat(strToWord("START."));
        Kalimat exit = wordToKalimat(strToWord("EXIT."));
        Kalimat buy = wordToKalimat(strToWord("BUY."));
        Kalimat delivery = wordToKalimat(strToWord("DELIVERY."));
        Kalimat mix = wordToKalimat(strToWord("MIX."));
        Kalimat chop = wordToKalimat(strToWord("CHOP."));
        Kalimat boil = wordToKalimat(strToWord("BOIL."));
        Kalimat fry = wordToKalimat(strToWord("FRY."));
        Kalimat undo = wordToKalimat(strToWord("UNDO."));
        Kalimat redo = wordToKalimat(strToWord("REDO."));
        Kalimat catalog = wordToKalimat(strToWord("CATALOG."));
        Kalimat cookbook = wordToKalimat(strToWord("COOKBOOK."));
        Kalimat rekomendasi = wordToKalimat(strToWord("REKOMENDASI."));
        Kalimat kulkas = wordToKalimat(strToWord("KULKAS."));
        Kalimat inventory = wordToKalimat(strToWord("INVENTORY."));

        /* Deklarasi REKOMENDASI MAKANAN */
        Rekomendasi_STACK Rekomendasi_Makanan;

        /* Deklarasi DELIVERY */
        PrioQueueTime DELIVERY;
        MakeEmptyFood(&DELIVERY, 200);

        /* Deklarasi STACK UNDO REDO */        
        Stack_Undo_Redo stack_UTAMA;
        Stack_Undo_Redo stack_REDO;
        CreateEmptyUndoRedo(&stack_UTAMA);
        CreateEmptyUndoRedo(&stack_REDO);

        /* Deklarasi PROSES AWAL */
        UndoRedoType proses;
        createUndoRedoType(&proses,sim,realTime,DELIVERY);
        PushUndoRedo(&stack_UTAMA,proses);

        /* Deklarasi Validitas Proses */
        boolean isValid;

        /* Deklarasi STACK NOTIFIKASI */
        NOTIF_STACK Notifikasi;
        CreateEmptyNotif(&Notifikasi);

        /* Deklarasi jam dan menit untuk WAIT */
        int hh;
        int mm;

        /* Deklarasi frontNotif untuk menampilkan notifikasi maju */
        /*           backNotif untuk menampilkan notifikasi mundur */
        boolean frontNotif;
        boolean backNotif;

        /* Syarat mulai */
        boolean x = true;

        BUY(sim, &buyAbleFood, &DELIVERY, realTime, &isValid);

        printf("-----------------------------------------\n");

        displayDelivery(DELIVERY, realTime);
        printf("-----------------------------------------\n");

        WAIT(&realTime, 0, 30);
        printf("-----------------------------------------\n");
            
            /* Pengecekan DELIVERY dan TIME */
        removeDelivery(&sim,&DELIVERY,realTime,&Notifikasi);
        printf("wait 30 menit\n");

        displayInventory(UserInventory(sim), realTime);
        printf("-----------------------------------------");
        

    return 0;
}