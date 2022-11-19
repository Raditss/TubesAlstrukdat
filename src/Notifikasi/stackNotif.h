/* File : stackInt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef STACK_NOTIFIKASI_H
#define STACK_NOTIFIKASI_H

#define MaxNotif 100

#include "../WordMachine/wordmachine.h"


typedef Word notifType;
typedef int notifAddress;

typedef struct {
    notifType T[MaxNotif];
    notifAddress TOP_NOTIF;
} NOTIF_STACK;


#define NOTIF_TOP(S)    (S).TOP_NOTIF
#define INFO_NOTIF(S)   (S).T[(S).TOP_NOTIF]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyNotif(NOTIF_STACK *S){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
    NOTIF_TOP(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyNotif(NOTIF_STACK S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    return NOTIF_TOP(S) == Nil;
}

boolean IsFullNotif(NOTIF_STACK S){
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
    return NOTIF_TOP(S) == MaxEl - 1;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushNotif(NOTIF_STACK * S, notifType X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    NOTIF_TOP(*S) += 1; //kalau kosong dari -1 jadi 1 (sama aja)
    INFO_NOTIF(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopNotif(NOTIF_STACK * S, notifType* X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = INFO_NOTIF(*S);
    NOTIF_TOP(*S)--;
}

void displayNotif(NOTIF_STACK *S){
/* Menampilkan daftar notifikasi saat ini */
/* I.S. Sembarang */
/* F.S. Menampilkan notifikasi sekaligus menghapusnya */
    int i = 0;
    notifType val;
    if (IsEmptyNotif(*S)){
        printf("Notifikasi: - \n");
    } else {
        printf("Notifikasi: \n");
        while (!IsEmptyNotif(*S)){
            i++;
            PopNotif(S, &val);
            printf("%d. ", i);
            DisplayWord(val);
        }
    }
}

void clearNotif(NOTIF_STACK *S){
/* Mengosongkan stack notifikasi */
    notifType val;
    while (!IsEmptyNotif(*S)){
        PopNotif(S,&val);
    }
    
}

#endif