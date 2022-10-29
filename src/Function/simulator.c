#include "../header/simulator.h"
#include "../header/makananedited.h"
#include "../header/point.h"

/* Driver untuk simulator.h */

int main(){
    PrioQueueTime Daftar = createMakanan("../../bin/testfilereadfood.txt");
    TIME realTime = MakeTIME(0,0,0);
    FoodType val;
    Simulator sim;
    Word nama_sim = strToWord("Willy.");
    Posisi awal;
    NOTIF_STACK notifikasi;

    CreatePosisi(&awal, 3, 2);
    createSimulator(&sim, nama_sim, awal);

    DequeueFood(&Daftar,  &val);
    Makanan food = Info(val);

    addInventory(&sim, food, realTime, &notifikasi);
    realTime = NextNMinute(realTime, 15);
    removeExpired(&sim, realTime, &notifikasi);
    displaySimulator(sim);

    return 0;
}