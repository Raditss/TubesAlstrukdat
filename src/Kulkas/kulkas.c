#include "../Cookbook/COOKBOOK.h"
#include "../Pemesanan/pemesanan.h"
#include "../Pengolahan/pengolahan.h"

/* Driver untuk kulkas.h */

int main()
{

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
    Matrix peta = getPeta("../../bin/peta_kulkas.txt");
    peta = createBorder(peta);

    /* Membentuk simulator */
    Simulator sim;
    printf("Please enter your name: ");
    STARTKALIMAT();
    createSimulator(&sim, kalimatToWord(currentKalimat), peta);

    /* Melakukan set time ke 00:00:00 */
    TIME realTime;
    CreateTime(&realTime, 0, 0, 0);

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

    /* Deklarasi Kulkas pada Simulasi */
    Kulkas realKulkas;
    createKulkas(&realKulkas);

    /* Deklarasi PROSES AWAL */
    UndoRedoType proses;
    createUndoRedoType(&proses, sim, realTime, DELIVERY, realKulkas);
    PushUndoRedo(&stack_UTAMA, proses);

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
    // displayKulkas(realKulkas);
    /* Syarat mulai */


    /* PROGRAM UTAMA */

    /* Display bentuk simulator saat ini */
    printf("============================================================================\n");
    displayBasic(sim, realTime, &Notifikasi, frontNotif);
    printf("============================================================================\n");

    frontNotif = true;
    backNotif = !frontNotif;
    isValid = false;

    Makanan val;
    FoodType vals;
    Info(vals) = val;
    TIME_LEFT(vals) = 50;

    /* Syarat mulai */
    for (int i = 0; i < 20; i++){
        val = ELMT_LIST_STATIK(daftarMakanan, i);
        Info(vals) = val;
        TIME_LEFT(vals) = 50;
        EnqueueFood(&UserInventory(sim), vals);
    }

    for (int L = 0; L < 5; L++)
        KULKAS(&sim, &realKulkas, &realTime, &isValid, &Notifikasi);


    return 0;
}