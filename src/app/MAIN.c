
#include "../header/COOKBOOK.h"
#include "../Function/splash.c"
#include "../header/pemesanan.h"


int main(){
    
        
        /* Splash Screen dan START */
        splash();
        printf("Welcome to Diner Dash CLI Edition!\n");

        /* Mendapatkan daftar makanan */
        ListStatik daftarMakanan = readFileMakananListStatik("../../bin/menumakanan.txt");
        
        /* Mendapatkan daftar makanan KHUSUS BUY */
        ListStatik buyAbleFood = isBuyAble(daftarMakanan);

        /* Mendapatkan daftar resep */
        KumpulanTree daftarResep; 
        resepReader(&daftarResep, "../../bin/resepmakanan.txt");
        KumpulanTree advancedResep = mergeAdvancedTree(daftarResep);
        
        /* Mendapatkan peta awal simulator */
        Matrix peta = getPeta("../../bin/peta.txt");
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
        Kalimat undo = wordToKalimat(strToWord("UNDO."));
        Kalimat redo = wordToKalimat(strToWord("REDO."));
        Kalimat catalog = wordToKalimat(strToWord("CATALOG."));
        Kalimat cookbook = wordToKalimat(strToWord("COOKBOOK."));
        Kalimat rekomendasi = wordToKalimat(strToWord("REKOMENDASI."));
        Kalimat kulkas = wordToKalimat(strToWord("KULKAS."));

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

        /* Syarat mulai */
        boolean x = true;
        while (x){
            printf("Please write START to start the game or EXIT to exit!\n");
            printf(">> ");
            STARTKALIMAT();
            if (isKalimatEqual(currentKalimat,start)){
                break;
            } else if (isKalimatEqual(currentKalimat,exit)){
                x = false;
            }
        }
        

        /* PROGRAM UTAMA */
        while (x){

            /* Display bentuk simulator saat ini */
            printf("============================================================================\n");
            displayBasic(sim,realTime,&Notifikasi);
            printf("============================================================================\n");
            isValid = false;

            printf("Masukkan command: ");
            STARTKALIMAT();
            if (isMoveCommand(currentKalimat)){
                // Menjalankan fungsi MOVE
                moveCommandV2(&UserPeta(sim),&realTime,currentKalimat,&isValid);

            } else if (isWaitCommand(currentKalimat) && isWaitCommandValid(currentKalimat)){
                // Menjalankan fungsi wait
                getWaitHour(currentKalimat, &hh, &mm);
                WAIT(&realTime,hh,mm);
            
            } else if (isKalimatEqual(currentKalimat,exit)){
                // Menjalankan fungsi EXIT
                break;

            } else if (isKalimatEqual(currentKalimat,buy)){
                // Menjalankan fungsi BUY
                BUY(sim, &buyAbleFood, &DELIVERY, realTime);
                realTime = NextMinute(realTime);

            } else if (isKalimatEqual(currentKalimat,delivery)){
                // Menjalankan fungsi DELIVERY
                displayDelivery(DELIVERY);


            } else if (isKalimatEqual(currentKalimat,mix)){
                // Menjalankan fungsi MIX


            } else if (isKalimatEqual(currentKalimat,chop)){
                // Menjalankan fungsi CHOP


            } else if (isKalimatEqual(currentKalimat,undo)){
                // Menjalankan fungsi UNDO
                UNDO(&stack_UTAMA,&stack_REDO);
                getProses(stack_UTAMA,&realTime,&sim,&DELIVERY);

            } else if (isKalimatEqual(currentKalimat,redo)){
                // Menjalankan fungsi REDO
                REDO(&stack_UTAMA, &stack_REDO);
                getProses(stack_UTAMA,&realTime,&sim,&DELIVERY);
            
            } else if (isKalimatEqual(currentKalimat,catalog)) { 
                // Menjalankan fungsi CATALOG
                CATALOG(daftarMakanan);
            
            } else if (isKalimatEqual(currentKalimat,cookbook)){
                // Menjalankan fungsi COOKBOOK
                COOKBOOK(daftarResep,daftarMakanan);

            } else if (isKalimatEqual(currentKalimat,rekomendasi)){
                // Menjalankan fungsi REKOMENDASI
                Rekomendasi_Makanan = getRekomendasi(daftarResep, sim);
                displayRekomendasi(Rekomendasi_Makanan, daftarMakanan);

            } else if (isKalimatEqual(currentKalimat,kulkas)){
                // Menjalankan fungsi KULKAS

            
            } else {
                printf("== Masukan Tidak Valid == \n");
            }

            /* Penyimpanan Undo-able proses dalam STACK */
            /* Jika ada proses VALID maka stack REDO lenyap */
            if (isValid){
                createUndoRedoType(&proses,sim,realTime,DELIVERY);
                PushUndoRedo(&stack_UTAMA,proses);
                clearProses(&stack_REDO);
            }

            /* Pengoperasian STACK NOTIFIKASI */

            /* Pengecekan time disini */

        }

        // command exit
        
        


    return 0;
}