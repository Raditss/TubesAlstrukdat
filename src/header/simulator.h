#include "time.h"
#include "wordmachine.h"
#include "queueFood.h"
#include "matrix.h"
#include "stackNotif.h"


#ifndef _SIMULATOR_H
#define _SIMULATOR_H

typedef struct
{
    Word NamaPengguna;
    Posisi LokasiPengguna;
    PrioQueueTime Inventory;
} Simulator;

#define UserName(s)         (s).NamaPengguna
#define UserLocate(s)       (s).LokasiPengguna
#define UserInventory(s)    (s).Inventory


void createSimulator(Simulator *sim, Word nama, Posisi awal){
    /* Pembuatan awal simulator */
    /* I.S. simulator sembarang */
    /* F.S. simulator berisi nama, posisi awal, dan inventory kosong */
    PrioQueueTime Q;
    MakeEmptyFood (&Q, CAPACITY);
    UserName(*sim) = nama;
    UserLocate(*sim) = awal;
    UserInventory(*sim) = Q;
}

void addInventory (Simulator *sim, Makanan food, TIME realTime, NOTIF_STACK *NS){
    /* Menambahkan makanan pada inventory */
    /* I.S. simulator sembarang */
    /*      stak notifikasi sembarang */
    /* F.S. food ditambahkan pada inventory berdasarkan waktu expired */
    /*      stak notifikasi bertambah saat makanan masuk ke inventory */
    FoodType foodType;
    Word diterima = strToWord("sudah diterima oleh BNMO.");
    notifType notifikasi;
    notifikasi = mergeWord(NAMA(food), diterima);
    PushNotif(NS,notifikasi);
    TIME_LEFT(foodType) = TIMEToMinute(EXP(food)) + TIMEToMinute(realTime);
    Info(foodType) = food;

    EnqueueFood(&UserInventory(*sim), foodType);
}

void removeInventory (Simulator *sim, Makanan food){
    /* Menghapus makanan tertentu pada inventory */

    /* MENUNGGU FUNGSI ISEQUAL MAKANAN */

}

void removeExpired (Simulator *sim, TIME realTime, NOTIF_STACK *NS){
    /* Melenyapkan semua makanan yang telah EXPIRED */
    /* I.S. simulator sembarang */
    /*      stak notifikasi sembarang */
    /* F.S. semua item dalam inventory sim valid */
    /*      stak notifikasi bertambah jika ada makanan expired */
    FoodType val;
    notifType notifikasi;
    Word namaTrashFood;
    Word kadaluarsa = strToWord("telah kadaluarsa :(.");
    while (TIME_LEFT(InfoHead(UserInventory(*sim))) <= TIMEToMinute(realTime))
    {
        DequeueFood(&UserInventory(*sim), &val);
        namaTrashFood = NAMA(Info(val));
        notifikasi = mergeWord(namaTrashFood, kadaluarsa);
        PushNotif(NS, notifikasi);
    }
}

void displaySimulator (Simulator sim){
    /* Melakukan display pada simulator saat ini */
    printf("Nama simulator: ");
    DisplayWord(UserName(sim));
    printf("Posisi simulator: ");
    DisplayPosisi(UserLocate(sim));
    PrintPrioQueueTimeFood(UserInventory(sim)); 
}

#endif