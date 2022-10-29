#include "../header/simulator.h"
#include "../header/makananedited.h"
#include "../header/point.h"

/* Driver untuk simulator.h */

int main(){
    PrioQueueTime Daftar = createMakanan("../../bin/testfilereadfood.txt");
    TIME realTime = MakeTIME(1,1,1);
    FoodType val;
    Simulator sim;
    Word nama_sim = strToWord("Willy.");
    Posisi awal;
    NOTIF_STACK notifikasi;
    CreateEmptyNotif(&notifikasi);

    CreatePosisi(&awal, 3, 2);
    createSimulator(&sim, nama_sim, awal);

    printf("================================================\n");
    displaySimulator(sim);
    printf("================================================\n");

    DequeueFood(&Daftar,  &val);
    addInventory(&sim, Info(val), realTime, &notifikasi);

    DequeueFood(&Daftar,  &val);
    addInventory(&sim, Info(val), realTime, &notifikasi);

    printf("================================================\n");
    displaySimulator(sim);
    printf("================================================\n");
    
    realTime = NextNMinute(realTime, 15);
    removeExpired(&sim, realTime, &notifikasi);

    printf("================================================\n");
    displaySimulator(sim);
    printf("================================================\n");

    return 0;
}