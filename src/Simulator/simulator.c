
#include "../MakananEdited/makananedited.h"
#include "../Point/point.h"

/* Driver untuk simulator.h */

int main(){
    PrioQueueTime Daftar = createMakanan("../../bin/testfilereadfood.txt");
    TIME realTime = MakeTIME(1,1,1);
    FoodType val;
    Simulator sim;
    Word nama_sim = strToWord("Willy.");
    Matrix awal = getPeta("../../bin/peta.txt");
    awal = createBorder(awal);
    NOTIF_STACK notifikasi;
    CreateEmptyNotif(&notifikasi);

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

    realTime = NextNMinute(realTime, 15);
    removeExpired(&sim, realTime, &notifikasi);

    printf("================================================\n");
    displaySimulator(sim);
    printf("================================================\n");

    printf("================================================\n");
    printf("================================================\n\n");

    DequeueFood(&Daftar,  &val);
    addInventory(&sim, Info(val), realTime, &notifikasi);
    DequeueFood(&Daftar,  &val);
    addInventory(&sim, Info(val), realTime, &notifikasi);
    DequeueFood(&Daftar,  &val);
    addInventory(&sim, Info(val), realTime, &notifikasi);

    displaySimulator(sim);
    Makanan Minyak_Goreng;
    ID(Minyak_Goreng) = 15;
    NAMA(Minyak_Goreng) = strToWord("Minyak Goreng.");
    EXP(Minyak_Goreng) = MakeTIME(0,1,30);
    DTIME(Minyak_Goreng) = MakeTIME(0,1,0);
    LOC(Minyak_Goreng) = strToWord("Buy.");
    removeInventory(&sim, Minyak_Goreng);

    printf("================================================\n");

    displaySimulator(sim);
    return 0;
}