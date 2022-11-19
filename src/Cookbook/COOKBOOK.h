#include "tree.h"
#include "listStatikFood.h"

int searchID(ListStatik daftarInformasi, int IDfood){
    /* mengembalikan indeks ID yang dicari berada */
    /* Mengembalikan -1 jika tidak ditemukan */
    for (int i = 0; i < CAPACITY_LIST_FOOD; i++){
        if (ID(ELMT_LIST_STATIK(daftarInformasi,i)) == IDfood){
            return i;
        }
    }
    return -1;
}

void COOKBOOK(KumpulanTree daftarResep, ListStatik daftarInformasi){
    /* Menampilkan daftar resep yang ada */
    /*     List Resep
            (aksi yang diperlukan - bahan...)
               1.  Ayam Goreng
                FRY - Ayam Potong - Minyak Goreng */
    int i = 0;
    int IDfood;
    int lokasiIDFOOD;
    int IDanakan;
    Address walkers;
    while (ELMT_TREE(daftarResep, i) != NULL){
        walkers = ELMT_TREE(daftarResep,i);
        IDfood = INFO_TREE(ELMT_TREE(daftarResep,i));
        lokasiIDFOOD = searchID(daftarInformasi, IDfood);
        if (lokasiIDFOOD == -1){
            i++;
            continue;
        } else {
            i < 9 ? 
                printf("0%d. ", i+1): 
                printf("%d. ", i+1);

            DisplayWord(NAMA(ELMT_LIST_STATIK(daftarInformasi, lokasiIDFOOD)));
            printf("\t");
            DisplayWordNoEnter(LOC(ELMT_LIST_STATIK(daftarInformasi, lokasiIDFOOD)));
            if (CHILD(walkers) == NULL){
                printf(" ----- ");
                printf("Tidak ada resep yang diperlukan\n");
            } else {
                walkers = CHILD(walkers);
                while (walkers != NULL){
                    printf(" ----- ");
                    IDanakan = searchID(daftarInformasi, INFO_TREE(walkers));
                    DisplayWordNoEnter(NAMA(ELMT_LIST_STATIK(daftarInformasi,IDanakan)));
                    walkers = SIBLING(walkers);
                }
                printf("\n");

            }
            i++;

        }

    }

}