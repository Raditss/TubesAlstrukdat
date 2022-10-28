#ifndef MAKANAN_H
#define MAKANAN_H
#include "wordmachine.h"
#include "time.h"
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

#endif