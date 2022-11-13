
#include "queueFood.h"
#include "matrix.h"
#include "stackNotif.h"


#ifndef _SIMULATOR_H
#define _SIMULATOR_H

typedef struct
{
    Word NamaPengguna;
    Matrix LokasiPengguna;
    PrioQueueTime Inventory;
} Simulator;

#define UserName(s)         (s).NamaPengguna
#define UserPeta(s)         (s).LokasiPengguna
#define UserInventory(s)    (s).Inventory


void createSimulator(Simulator *sim, Word nama, Matrix awal){
    /* Pembuatan awal simulator */
    /* I.S. simulator sembarang */
    /* F.S. simulator berisi nama, posisi awal, dan inventory kosong */
    PrioQueueTime Q;
    MakeEmptyFood (&Q, CAPACITY);
    UserName(*sim) = nama;
    UserPeta(*sim) = awal;
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
    FoodType val;
    PrioQueueTime sim2;
    MakeEmptyFood(&sim2, CAPACITY);
    while (!isFoodEqual(Info(InfoHead(UserInventory(*sim))),food) && !IsEmptyFood(UserInventory(*sim))){
        DequeueFood(&UserInventory(*sim),&val);
        EnqueueFood(&sim2, val);
    }
    if (isFoodEqual(Info(InfoHead(UserInventory(*sim))),food)){
        DequeueFood(&UserInventory(*sim),&val);
    }
    while (!IsEmptyFood(sim2)){
        DequeueFood(&sim2, &val);
        EnqueueFood(&UserInventory(*sim), val);
    }
    

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
    while (TIME_LEFT(InfoHead(UserInventory(*sim))) <= TIMEToMinute(realTime) && !IsEmptyFood(UserInventory(*sim)))
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
    printf("Posisi simulator: \n");
    displayMatrix(UserPeta(sim));
    PrintPrioQueueTimeFood(UserInventory(sim)); 
}

void displayBasic (Simulator sim, TIME realTime, NOTIF_STACK *notif){
    /* Menampilkan bentuk simulator saat ini */
    /* Menampilkan waktu saat ini */
    /* Menampilkan notifikasi saat ini */
    /* I.S. Sembarang */
    /* F.S. Notif ditampilkan lalu dihapuskan */
    DisplayWordNoEnter(UserName(sim));
    printf(" di posisi: ");
    DisplayPosisiV2(getPosisi(UserPeta(sim)));
    printf("Waktu saat ini: ");
    TulisTIME(realTime);
    displayNotif(notif);
    displayMatrix(UserPeta(sim));
}

void WAIT(TIME *realTime, int h, int m){
    int DD, HH, MM;
    DD = Day(*realTime);
    HH = Hour(*realTime) + h;
    MM = Minute(*realTime) + m;

    if (MM > 60) {
        if (HH > 24) {
            Minute(*realTime) = (MM % 60);
            Hour(*realTime) = ((MM / 60) + HH) % 24;
            Day(*realTime) = ((MM / 60) + HH) / 24 + DD;
        }
        else {
            Minute(*realTime) = (MM % 60);
            Hour(*realTime) = (MM / 60) + HH;
            if (((MM / 60) + HH) > 60) {
                Day(*realTime) = ((MM / 60) + HH) / 24 + DD;
            } else {
                Day(*realTime) = DD;
            }
        }
    } 
    else {
        if (HH > 24) {
            Minute(*realTime) = MM;
            Hour(*realTime) = HH % 24;
            Day(*realTime) = (HH / 24) + DD;
        }
        else {
            Minute(*realTime) = Minute(*realTime) + m;
            Hour(*realTime) = Hour(*realTime) + h;
            Day(*realTime) = DD; 
        }
    }
    *realTime = MakeTIME(Day(*realTime), Hour(*realTime), Minute(*realTime));
}

boolean isWaitCommand (Kalimat currentKalimat){
    /* True jika kata dimulai dengan WAIT */
    return (currentKalimat.TabKalimat[0] == 'W' &&
            currentKalimat.TabKalimat[1] == 'A' &&
            currentKalimat.TabKalimat[2] == 'I' &&
            currentKalimat.TabKalimat[3] == 'T' &&
            currentKalimat.TabKalimat[4] == ' ');
}

boolean isWaitCommandValid (Kalimat currentKalimat){
    /* Mengembalikan true jika X dan Y valid */
    for (int i = 5; i < currentKalimat.LengthKalimat; i++){
        if ((currentKalimat.TabKalimat[i] < 48) || (currentKalimat.TabKalimat[i] > 57) || (currentKalimat.TabKalimat[i] != 32)){
            return false;
        }
    }
    return true;
}

void getWaitHour (Kalimat currentKalimat, int *hour, int *minute){
    /* Prekondisi: Wait valid */
    int i = 5;
    *hour = 0;
    *minute = 0;
    int lenHour;
    int lenMinute = 0;
    while (currentKalimat.TabKalimat[i] != ' ')
    {
        i++;
    }
    lenHour = i;

    for (int j = i+1; j < currentKalimat.LengthKalimat; j++){
        lenMinute++;
    }
    
    int pengali = 1;
    for (int k = 5 + lenHour - 1; k > 5 ; k--){
        *hour += (currentKalimat.TabKalimat[k] - 48) * pengali;
        pengali *= 10;
    }
    pengali = 1;

    for (int l = currentKalimat.LengthKalimat - 1; l > lenHour+2; l--){
        *minute += (currentKalimat.TabKalimat[l] - 48) * pengali;
    }
}

#endif