#ifndef STACK_REKOMENDASI_H
#define STACK_REKOMENDASI_H

#define MaxRekomendasi 100

#include "../WordMachine/wordmachine.h"
#include "../StackInteger/stackint.h"

typedef int RekomendasiType;
typedef int RekomendasiAddress;

typedef struct {
    RekomendasiType T[MaxRekomendasi];
    RekomendasiAddress TOP_Rekomendasi;
} Rekomendasi_STACK;


#define Rekomendasi_TOP(S)    (S).TOP_Rekomendasi
#define INFO_Rekomendasi(S)   (S).T[(S).TOP_Rekomendasi]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyRekomendasi(Rekomendasi_STACK *S){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxRekomendasi */
/* jadi indeksnya antara 0.. MaxRekomendasi */
/* Ciri stack kosong : TOP bernilai Nil */
    Rekomendasi_TOP(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyRekomendasi(Rekomendasi_STACK S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    return Rekomendasi_TOP(S) == Nil;
}

boolean IsFullRekomendasi(Rekomendasi_STACK S){
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
    return Rekomendasi_TOP(S) == MaxRekomendasi - 1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushRekomendasi(Rekomendasi_STACK * S, RekomendasiType X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    Rekomendasi_TOP(*S) += 1; //kalau kosong dari -1 jadi 1 (sama aja)
    INFO_Rekomendasi(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopRekomendasi(Rekomendasi_STACK * S, RekomendasiType* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = INFO_Rekomendasi(*S);
    Rekomendasi_TOP(*S)--;
}


#endif