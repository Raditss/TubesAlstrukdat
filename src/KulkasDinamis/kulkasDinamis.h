#ifndef KULKAS_DINAMIS_H
#define KULKAS_DINAMIS_H

#include "../QueueFood/queueFood.h"
#include "../SentenceMachine/sentencemachine.h"

typedef struct  
{
    FoodType *T;
    int nEff;
    int capacity;
}kulkasDinamis;

#define BUFFER_KULKAS_DINAMIS(l)    (l).T
#define ELMT_KULKAS_DINAMIS(l,i)    (l).T[i]
#define CAPACITY_KULKAS_DINAMIS(l)  (l).capacity
#define NEFF_KULKAS_DINAMIS(l)      (l).nEff


void CreateKulkasDinamis(kulkasDinamis *K, int Capacity){
/* I.S. Sembarang */
/* F.S. Terbentuk kulkas dinamis kosong dengan ukutan CAPACITY*/
    BUFFER_KULKAS_DINAMIS(*K) = (FoodType*) malloc (Capacity * sizeof (FoodType));
    NEFF_KULKAS_DINAMIS(*K) = 0;
    CAPACITY_KULKAS_DINAMIS(*K) = Capacity;
    for (int i = 0; i < Capacity; i++){
        TIME_LEFT(ELMT_KULKAS_DINAMIS(*K,i)) = -1;
    }
}

void insertLastKulkasDinamis(kulkasDinamis *K, FoodType val){
/* Proses: Menambahkan val sebagai elemen terakhir list */
/* I.S. List l boleh kosong, tetapi tidak penuh */
/* F.S. val adalah elemen terakhir l yang baru */
    int i = 0;
    while (TIME_LEFT(ELMT_KULKAS_DINAMIS(*K,i)) != -1){
        i++;
    }
    ELMT_KULKAS_DINAMIS(*K,i) = val;
}

int findKulkasDinamisByID(kulkasDinamis K, int idx){
/* Mencari lokasi ID makanan idx dalam kulkas */
    int i = 0;
    while (ID(Info(ELMT_KULKAS_DINAMIS(K,i))) != idx && i < CAPACITY_KULKAS_DINAMIS(K)) {
        i++;
    }
    if (i >= CAPACITY_KULKAS_DINAMIS(K)){
        return -1;
    }
    return i;
}

void removeItemKulkasDinamis(kulkasDinamis *K, int ID, PrioQueueTime *pindah){
/* Menghapus ID tertentu dari kulkas */
    int find = findKulkasDinamisByID(*K,ID);
    if (find == -1){
        printf("ID Tidak ditemukan\n");
    } else {
        EnqueueFood(pindah, ELMT_KULKAS_DINAMIS(*K,find));
        TIME_LEFT(ELMT_KULKAS_DINAMIS(*K,find)) = -1;
    }
}

void masukKulkasDinamis(kulkasDinamis *K, int ID, PrioQueueTime *Awal, TIME realTime){
/* Memindahkan foodtype dari inventory ke kulkas dinamis */
    PrioQueueTime awal2 = *Awal;
    PrioQueueTime temp;
    FoodType val;
    MakeEmptyFood(&temp, 10000);
    while (!IsEmptyFood(awal2)){
        DequeueFood(&awal2, &val);
        if (ID == ID(Info(val))) {
            /* Pass */
            TIME_LEFT(val) = TIME_LEFT(val) - TIMEToMinute(realTime);
            insertLastKulkasDinamis(K,val);
            ID = -1;
        } else {
            EnqueueFood(&temp, val);
        }
    }
    *Awal = temp;
}

void displayKulkasDinamik(kulkasDinamis K){
/* Display kulkas */
    int i = 0;
    while (i < CAPACITY_KULKAS_DINAMIS(K))
    {
        if (TIME_LEFT(ELMT_KULKAS_DINAMIS(K,i) < 0)){
            printf("%d. ", ID(Info(ELMT_KULKAS_DINAMIS(K,i))));
            DisplayWord(NAMA(Info(ELMT_KULKAS_DINAMIS(K,i))));
        }
        i++;
    }
    
}

void KULKAS_DINAMIS(PrioQueueTime *Inventory, kulkasDinamis *K, TIME realTime){
/* Fungsi kulkas */
    printf("Selamat datang di kulkas dinamis\n");
    printf("Silahkan ketik 1 untuk memasukkan barang dan ketik 2 untuk mengambil barang\n");
    STARTKALIMAT();
    Word tes = kalimatToWord(currentKalimat);
    if (isInt(tes)){
        int tester = strToInt(tes);
        if (tester == 1){
            // masukin barang
            displayInventoryID(*Inventory, realTime);
            printf("Masukkan ID item yang ingin dimasukkan ke dalam kulkas:\n");
            STARTKALIMAT();
            tes = kalimatToWord(currentKalimat);
            if (isInt(tes)){
                tester = strToInt(tes);
                masukKulkasDinamis(K,tester,Inventory,realTime);
            } else {
                printf("Input tidak valid\n");
            }

        } else if (tester == 2){
            // mengambil barang
            displayKulkasDinamik(*K);
            printf("Masukkan ID item yang ingin dikeluarkan kulkas:\n");
            STARTKALIMAT();
            tes = kalimatToWord(currentKalimat);
            if (isInt(tes)){
                tester = strToInt(tes);
                removeItemKulkasDinamis(K,tester,Inventory);
            } else {
                printf("Input tidak valid\n");
            }
        } else {
            printf("Input tidak valid\n");
        }
    } else {
        printf("Input tidak valid\n");
    }
}




















#endif