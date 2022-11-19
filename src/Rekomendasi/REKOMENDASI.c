#include "REKOMENDASI.h"

/* Driver untuk REKOMENDASI.h */

int main(){

    ListStatik daftar_Makanan = readFileMakananListStatik("../../bin/menumakanan.txt");
    KumpulanTree daftar_Resep;
    resepReader(&daftar_Resep, "../../bin/resepmakanan.txt");
    Simulator sim;
    Matrix peta = getPeta("../../bin/peta.txt");
    peta = createBorder(peta);
    createSimulator(&sim, strToWord("Willy."), peta);

    Makanan val;
    FoodType vals;
    Info(vals) = val;
    TIME_LEFT(vals) = 20;

    for (int i = 0; i < 20; i++){
        val = ELMT_LIST_STATIK(daftar_Makanan, i);
        Info(vals) = val;
        TIME_LEFT(vals) = 20;
        EnqueueFood(&UserInventory(sim), vals);
    }

    Rekomendasi_STACK daftar_Rekomendasi = getRekomendasi(daftar_Resep,sim);

    displayRekomendasi(daftar_Rekomendasi, daftar_Makanan);


    return 0;
}