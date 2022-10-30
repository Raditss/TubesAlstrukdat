#ifndef MAKANAN_H
#define MAKANAN_H

#include "wordmachine.h"
#include "time.h"
#include "queueFood.h"
#include <stdlib.h>

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

void DisplayMakanan (Makanan food) {
    // I.S food terdefinisi
    // F.S menampilkan id, nama, exp, deliver, aksi
    printf("ID makanan: %d\n", ID(food));
    printf("Nama makanan: %s\n", NAMA(food).TabWord);
    printf("Expired: ");
    TulisTIME(EXP(food));
    printf("Delivery time: ");
    TulisTIME(DTIME(food));
    printf("Lokasi aksi: %s\n", LOC(food).TabWord);
}

void DealocMakanan (Makanan *mkn) {
    // I.S mkn terdefinisi
    // F.S mkn terdealokasi
    free(mkn);
}
void IsValidFood (PrioQueueTime *P) {
    // I.S P terdefinisi
    // F.S makanan yang expired dihapus dari P lalu di-print.
    FoodType val;
    PrioQueueTime temp = *P;
    if (!IsEmptyFood(*P)){
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            if (TIME_LEFT(val) <= 0) {
                printf("Makanan %s telah basi.\n", NAMA(Info(val)).TabWord);
                DeAlokasiFood(&val);
            } else {
                EnqueueFood(P, val);
            }
        }
    }
}

void MinusTime(PrioQueueTime *P, int selama_apa) {
    // I.S P terdefinisi
    // F.S semua time_left makanan di P dikurangi selama_apa
    FoodType val;
    PrioQueueTime temp = *P;
    if (!IsEmptyFood(*P)){
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            TIME_LEFT(val) -= selama_apa;
            if (TIME_LEFT(val) <= 0) {
                DeAlokasiFood(&val);
            } else {
                EnqueueFood(P, val);
            }
        }
    }
}

#endif