#include "COOKBOOK.h"

/* Driver dari COOKBOOK.h */

int main(){

    ListStatik daftarInformasi = readFileMakananListStatik("../../bin/menumakanan.txt");
    KumpulanTree daftarResep; 
    resepReader(&daftarResep, "../../bin/resepmakanan.txt");
    COOKBOOK(daftarResep,daftarInformasi);
    return 0;
}