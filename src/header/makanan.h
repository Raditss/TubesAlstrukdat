/* File : makanan.h */

#ifndef makanan_H
#define makanan_H

#include "waktu.h"
#include "wordmachine.h"

/* Definisi makanan: */
typedef struct {
    int id;
    Word nama;
    Waktu expired;
    Waktu deliveryTime;
    Word lokasiAksi; // lokasi dilakukannya aksi untuk mendapat makanan tsb.
} Makanan;

#define ID(M) (M).id
#define NAMA(M) (M).nama
#define EXP(M) (M).expired
#define DTIME(M) (M).deliveryTime
#define LOC(M) (M).lokasiAksi




#endif