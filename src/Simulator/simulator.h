
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
    foodType.time_left = 0;
    // printf("%d\n", foodType.time_left);
    TIME temp = food.expired;
    foodType.time_left += TIMEToMinute(temp);
    // printf("%d\n", foodType.time_left);
    foodType.time_left += TIMEToMinute(realTime);
    Info(foodType) = food;
    notifType notifikasi;
    Word tempWord = food.nama;
    notifikasi = mergeWord(tempWord, diterima); // Lewat sini menghilangkan food
    PushNotif(NS,notifikasi);


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

void removeDelivery (Simulator *sim, PrioQueueTime *del, TIME realTime, NOTIF_STACK *NS){
/* Menghapus makanan dari delivery (jika sudah sampai) */
/* I.S. Sembarang */
/* F.S. Jika makanan sudah sampai maka akan dipindahkan ke inventory */
    FoodType val;
    notifType notifikasi; // brb
    Word sampai = strToWord("telah diterima.");
    int newKadal;
    if (!IsEmptyFood(*del)){
        while (!IsEmptyFood(*del) && (TIME_LEFT(InfoHead(*del)) <= TIMEToMinute(realTime))){
            DequeueFood(del,&val);
            newKadal = TIME_LEFT(val) + TIMEToMinute(EXP(Info(val)));
            TIME_LEFT(val) = newKadal;
            EnqueueFood(&UserInventory(*sim), val);
            
            notifikasi = mergeWord(NAMA(Info(val)), sampai);
            PushNotif(NS, notifikasi);
        }
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
    if (!IsEmptyFood(UserInventory(*sim))){
        while (!IsEmptyFood(UserInventory(*sim)) && (TIME_LEFT(InfoHead(UserInventory(*sim))) <= TIMEToMinute(realTime))){
            DequeueFood(&UserInventory(*sim),&val);
            
            notifikasi = mergeWord(NAMA(Info(val)), kadaluarsa);
            PushNotif(NS, notifikasi);
        }
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

void displayBasic (Simulator sim, TIME realTime, NOTIF_STACK *notif, boolean frontNotif){
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
    if (frontNotif){
        displayNotif(notif);
    } else {
        clearNotif(notif);
    }
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

void WAITV2 (TIME *realTime, int hh, int mm){
    /* Versi kedua dari WAIT */
    *realTime = NextNMinute(*realTime, hh*60+mm);
}

void getWaitHour (Kalimat k, int *hh, int *mm){
    /* Membelah kalimat menjadi 3 */
    int i = 0;
    *hh = 0;
    *mm = 0;


    while (k.TabKalimat[i] != ' '){
        i++;
    }

    i++;

    int j = i;
    while ((k.TabKalimat[j] != ' ') && (k.TabKalimat[j] != '\n')){
        j++;
    }

    j++;

    int l = j;
    while (l < k.LengthKalimat){
        l++;
    }

    l--;

    int pengali =  1;
    for (int m = j-2; m >= 5; m--){
        *hh += pengali * (k.TabKalimat[m] - 48);
        pengali *= 10;
    }

    pengali = 1;
    for (int n = l; n >= j; n--){
        *mm += pengali * (k.TabKalimat[n] - 48);
        pengali *= 10;
    }
    
}


boolean isWaitValid (Kalimat k){
    /* True jika command wait valid */
    if (k.TabKalimat[0] == 'W' &&
        k.TabKalimat[1] == 'A' &&
        k.TabKalimat[2] == 'I' &&
        k.TabKalimat[3] == 'T' &&
        k.TabKalimat[4] == ' '){
            int i = 5;
            boolean valid = false;
            while (k.TabKalimat[i] != ' ' && i < k.LengthKalimat){
                valid = true;
                i++;
            }
            
            i++;
            if (i >= k.LengthKalimat){
                return false;
            }

            for (i; i < k.LengthKalimat; i++){
                if ((currentKalimat.TabKalimat[i] < 48) || (currentKalimat.TabKalimat[i] > 57)){
                    return false;
                }
            }
        return valid;

    }
    return false;


}

#endif