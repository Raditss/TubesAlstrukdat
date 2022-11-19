#include "../Rekomendasi/REKOMENDASI.h"

#ifndef _UNDO_REDO_H
#define _UNDO_REDO_H

#define MaxUNDO 200

typedef struct
{
    Simulator Sim;
    TIME RealTime;
    PrioQueueTime Delivery;
    Kulkas KULKAS;
} UndoRedoType;

typedef int UndoRedoAddress;
typedef int uji;

typedef struct
{
    UndoRedoType *T;
    UndoRedoAddress TOP_UNDO_REDO;
} Stack_Undo_Redo;

#define SIMULASI_PROSES(u) (u).Sim
#define TIME_PROSES(u) (u).RealTime
#define DELIVERY_PROSES(u) (u).Delivery
#define KULKAS_PROSES(u) (u).KULKAS
#define UNDO_REDO_TOP(s) (s).TOP_UNDO_REDO
#define INFO_UNDO_REDO(s) (s).T[(s).TOP_UNDO_REDO]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyUndoRedo(Stack_Undo_Redo *S)
{
    /* I.S. sembarang; */
    /* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
    /* jadi indeksnya antara 0.. MaxEl */
    /* Ciri stack kosong : TOP bernilai Nil */
    (*S).T = (UndoRedoType *)malloc((MaxUNDO) * sizeof(UndoRedoType));
    UNDO_REDO_TOP(*S) = -1;
}

void createUndoRedoType(UndoRedoType *proses_saat_ini, Simulator sim, TIME realTime, PrioQueueTime delivery, Kulkas kulkas)
{
    /* TAMBAH KULKAS NANTI */
    /* I.S. proses saat ini sembarang */
    /* F.S. proses saat ini terbentuk dari simulator, realtime, delivery */
    SIMULASI_PROSES(*proses_saat_ini) = sim;
    TIME_PROSES(*proses_saat_ini) = realTime;
    DELIVERY_PROSES(*proses_saat_ini) = delivery;
    KULKAS_PROSES(*proses_saat_ini) = kulkas;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyUndoRedo(Stack_Undo_Redo S)
{
    /* Mengirim true jika Stack kosong: lihat definisi di atas */
    return UNDO_REDO_TOP(S) == Nil;
}

boolean IsFullUndoRedo(Stack_Undo_Redo S)
{
    /* Mengirim true jika tabel penampung nilai elemen stack penuh */
    return UNDO_REDO_TOP(S) == MaxUNDO - 1;
}

UndoRedoType copyStackElmt(UndoRedoType s)
{
    /* Mengembalikan copy dari s */
    PrioQueueTime del = copyPrioQueue(DELIVERY_PROSES(s));
    Simulator sim = SIMULASI_PROSES(s);
    TIME realTime = TIME_PROSES(s);
    Kulkas kulkas = KULKAS_PROSES(s);
    UndoRedoType top;
    createUndoRedoType(&top, sim, realTime, del, kulkas);
    return top;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushUndoRedo(Stack_Undo_Redo *S, UndoRedoType X)
{
    /* Menambahkan X sebagai elemen Stack S. */
    /* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
    /* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
    UNDO_REDO_TOP(*S)
    ++; // kalau kosong dari -1 jadi 1 (sama aja)
    INFO_UNDO_REDO(*S) = copyStackElmt(X);
    Head(DELIVERY_PROSES(INFO_UNDO_REDO(*S))) = Head(DELIVERY_PROSES(X));
    Tail(DELIVERY_PROSES(INFO_UNDO_REDO(*S))) = Tail(DELIVERY_PROSES(X));
    // DELIVERY_PROSES(INFO_UNDO_REDO(*S)) = DELIVERY_PROSES(X);
    // TIME_PROSES(INFO_UNDO_REDO(*S)) = TIME_PROSES(X);
    // SIMULASI_PROSES(INFO_UNDO_REDO(*S)) = SIMULASI_PROSES(X);
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopUndoRedo(Stack_Undo_Redo *S, UndoRedoType *X)
{
    /* Menghapus X dari Stack S. */
    /* I.S. S  tidak mungkin kosong */
    /* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    *X = INFO_UNDO_REDO(*S);
    UNDO_REDO_TOP(*S)
    --;
}

void UNDO(Stack_Undo_Redo *utama, Stack_Undo_Redo *buangan)
{
    /* Melakukan UNDO dengan melakukan pop utama dan push ke buangan */
    UndoRedoType val;
    if (IsEmptyUndoRedo(*utama) || UNDO_REDO_TOP(*utama) == 0)
    {
        printf("Tidak ada proses yang bisa di-UNDO\n");
    }
    else
    {
        PopUndoRedo(utama, &val);
        PushUndoRedo(buangan, val);
        printf("Proses berhasil di-UNDO\n");
    }
}

void REDO(Stack_Undo_Redo *utama, Stack_Undo_Redo *buangan)
{
    /* Melakukan REDO dengan melakukan pop buangan dan push ke utama */
    UndoRedoType val;
    if (IsEmptyUndoRedo(*buangan))
    {
        printf("Tidak ada proses yang bisa di-REDO\n");
    }
    else
    {
        PopUndoRedo(buangan, &val);
        PushUndoRedo(utama, val);
        printf("Proses berhasil di-REDO\n");
    }
}

void getProses(Stack_Undo_Redo utama, TIME *realTime, Simulator *sim, PrioQueueTime *delivery, Kulkas *kulkas)
{
    /* Mengembalikan isi stack ke proses saat ini */
    /* I.S. Sembarang, stack tidak mungkin kosong */
    /* F.S. realTime dan sim serta delivery diubah menjadi sama seperti top dari stack */
    *realTime = TIME_PROSES(INFO_UNDO_REDO(utama));
    *sim = SIMULASI_PROSES(INFO_UNDO_REDO(utama));
    *delivery = DELIVERY_PROSES(INFO_UNDO_REDO(utama));
    *kulkas = KULKAS_PROSES(INFO_UNDO_REDO(utama));
}

void clearProses(Stack_Undo_Redo *redo)
{
    /* Menghapus semua elemen undo redo */
    /* I.S. Sembarang */
    /* F.S. Redo di set kosong */
    UndoRedoType val;
    while (!IsEmptyUndoRedo(*redo))
    {
        PopUndoRedo(redo, &val);
    }
}

#endif