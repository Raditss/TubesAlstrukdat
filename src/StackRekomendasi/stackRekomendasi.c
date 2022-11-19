#include "stackRekomendasi.h"

/* Driver untuk stackRekomendasai.h */

int main(){

    Rekomendasi_STACK stackRekomendasi;
    CreateEmptyRekomendasi(&stackRekomendasi);

    IsEmptyRekomendasi(stackRekomendasi) ? 
        printf("Saat ini stack kosong\n"):
        printf("Tidak mungkin tulisan ini keluar\n");
    
    for (int i = 0; i < MaxRekomendasi; i++){
        PushRekomendasi(&stackRekomendasi, i);
    }

    IsFullRekomendasi(stackRekomendasi) ?
        printf("Stack saat ini full\n"): 
        printf("Tidak mungkin tulisan ini keluar\n");

    RekomendasiType buangan;
    for (int i = 0; i < MaxRekomendasi; i++){
        PopRekomendasi(&stackRekomendasi, &buangan);
    }

    IsEmptyRekomendasi(stackRekomendasi) ? 
        printf("Saat ini stack kosong\n"):
        printf("Tidak mungkin tulisan ini keluar\n");

    return 0;
}