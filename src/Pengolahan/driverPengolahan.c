
#include "../Cookbook/COOKBOOK.h"
#include "../Pemesanan/pemesanan.h"
#include "../Pengolahan/pengolahan.h"


int main(){
    
        
        /* Splash Screen dan START */

        /* Mendapatkan daftar makanan */
        ListStatik daftarMakanan = readFileMakananListStatik("../../bin/menumakanan.txt");
        
        /* Mendapatkan daftar makanan KHUSUS BUY */
        ListStatik buyAbleFood = isBuyAble(daftarMakanan);

        /* Mendapatkan daftar resep */
        KumpulanTree daftarResep; 
        resepReader(&daftarResep, "../../bin/resepmakanan.txt");
        KumpulanTree advancedResep = mergeAdvancedTree(daftarResep);
        
        /* Mendapatkan peta awal simulator */
        Matrix peta = getPeta("../../bin/peta_olah.txt");
        peta = createBorder(peta);

        /* Membentuk simulator */
        Simulator sim;
        printf("Please enter your name: ");
        STARTKALIMAT();
        createSimulator(&sim, kalimatToWord(currentKalimat), peta);

        /* Melakukan set time ke 00:00:00 */
        TIME realTime;
        CreateTime(&realTime,0,0,0);

        /* Deklarasi REKOMENDASI MAKANAN */
        Rekomendasi_STACK Rekomendasi_Makanan;

        /* Deklarasi DELIVERY */
        PrioQueueTime DELIVERY;
        MakeEmptyFood(&DELIVERY, 200);

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
        ListStatik daftar_Makanan = readFileMakananListStatik("../../bin/menumakanan.txt");
        Makanan val;
        FoodType vals;
        Info(vals) = val;
        TIME_LEFT(vals) = 50;

        /* Syarat mulai */
        for (int i = 0; i < 20; i++){
        val = ELMT_LIST_STATIK(daftar_Makanan, i);
        Info(vals) = val;
        TIME_LEFT(vals) = 50;
        EnqueueFood(&UserInventory(sim), vals);
        }

        /* PROGRAM UTAMA */

        MIX(&sim, daftarResep, daftarMakanan, &realTime, &Notifikasi, &isValid);
        printf("------------------------------------------------\n");
        CHOP(&sim, daftarResep, daftarMakanan, &realTime, &Notifikasi, &isValid);
        printf("------------------------------------------------\n");
        BOIL(&sim, daftarResep, daftarMakanan, &realTime, &Notifikasi, &isValid);
        printf("------------------------------------------------\n");
        FRY(&sim, daftarResep, daftarMakanan, &realTime, &Notifikasi, &isValid);
        printf("------------------------------------------------\n");

            
        


    return 0;
}