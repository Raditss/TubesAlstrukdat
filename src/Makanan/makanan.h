#ifndef MAKANAN_H
#define MAKANAN_H

#include "../Time/time.h"
#include "../WordMachine/wordmachine.h"

/* Definisi makanan: */
typedef struct {
    int id;
    Word nama;
    TIME expired;
    TIME deliveryTime;
    Word lokasiAksi; // lokasi dilakukannya aksi untuk mendapat makanan tsb.
} Makanan;

#define ID(M) (M).id
#define NAMA(M) (M).nama
#define EXP(M) (M).expired
#define DTIME(M) (M).deliveryTime
#define LOC(M) (M).lokasiAksi

 //{ array atau stack atau list of id }
void CreateMakanan (Makanan *food, Word nama, TIME exp, TIME deliver, Word aksi) {
    // I.S food sembarang
    // F.S food terdefinisi dengan input nama, exp, deliver, aksi
    ID(*food) = 0;
    NAMA(*food) = nama;
    EXP(*food) = exp;
    DTIME(*food) = deliver;
    LOC(*food) = aksi;
}

Makanan createEmptyFood(){
    /* Membuat makanan kosong */
    Makanan food;
    ID(food) = 0;
    return food;
}

boolean isEmptyFood(Makanan food){
    /* Mengembalikan true jika ID makanan = 0 */
    return ID(food) == 0;
}

void DisplayMakanan (Makanan food) {
    // I.S food terdefinisi
    // F.S menampilkan id, nama, exp, deliver, aksi
    printf("ID makanan: \t\t%d\n", ID(food));
    printf("Nama makanan: \t\t");
    DisplayWord(NAMA(food));
    printf("Expired: \t\t");
    TulisTIME(EXP(food));
    printf("Delivery time: \t\t");
    TulisTIME(DTIME(food));
    printf("Lokasi aksi: \t\t");
    DisplayWord(LOC(food));
}

void DealocMakanan (Makanan *mkn) {
    // I.S mkn terdefinisi
    // F.S mkn terdealokasi
    free(mkn);
}

boolean isFoodEqual (Makanan food1, Makanan food2){
    /* Mengembalikan true jika kedua makanan bernilai sama */
    return  (ID(food1) == ID(food2)) &&
            (isWordEqual(NAMA(food1), NAMA(food2))) &&
            (TEQ(EXP(food1), EXP(food2))) &&
            (TEQ(DTIME(food1), DTIME(food2))) &&
            (isWordEqual(LOC(food1), LOC(food2)));
}

#endif