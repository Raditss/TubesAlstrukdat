#include "COOKBOOK.h"
#include "queueFood.h"
#include "simulator.h"

boolean isResepInInventory(PrioQueueTime *Inv, Akar Resep) {
    /* Mengembalikan true jika resep terdapat pada inventory */
    /* I.S. Inventory sembarang */
    /* F.S. Inventory tetap */
    /*      Mengembalikan true jika resep terdapat pada inventory */
    /*      Mengembalikan false jika resep tidak terdapat pada inventory */
    /* Kamus Lokal */
    PrioQueueTime Inv2;
    FoodType val;
    boolean foundChild, foundSibling = false;
    int idInventory, idChildResep, idSiblingResep;
    /* Algoritma */
    idSiblingResep = INFO_TREE(SIBLING(Resep));
    idChildResep = INFO_TREE(CHILD(Resep));

    MakeEmptyFood(&Inv2, CAPACITY);
    if (idSiblingResep == NULL) {
        // Resep tidak memiliki sibling, mencari child saja
        foundSibling = true;
        while (!foundChild && !IsEmptyFood(*Inv)) {
            DequeueFood(Inv, &val);
            EnqueueFood(&Inv2, val);
            idInventory = ID(Info(val));
            if ( idInventory == idChildResep ) {
                foundChild = true;
            }
        }        
    } else {
        // mencari child dan sibling
        while (!foundChild && !foundSibling && !IsEmptyFood(*Inv)) {
            DequeueFood(Inv, &val);
            EnqueueFood(&Inv2, val);
            idInventory = ID(Info(val));
            if ( idInventory == idChildResep ) {
                foundChild = true;
            } else if ( idInventory == idSiblingResep ) {
                foundSibling = true;
            }
        }
    }

    // mengembalikan inventory ke semula
    while (!IsEmptyFood(Inv2)) {
        DequeueFood(&Inv2, &val);
        EnqueueFood(Inv, val);
    }

    return foundChild && foundSibling;
}

void getMakananFromList(int ID, ListStatik daftarInformasi, Makanan *mkn) {
    /* Mengembalikan makanan dengan ID tertentu */
    /* I.S. daftarInformasi sembarang */
    /* F.S. daftarInformasi tetap */
    /*      mkn berisi makanan dengan ID tertentu */
    /*      mkn kosong jika tidak ditemukan */
    /* Kamus Lokal */
    int idxMkn;
    /* Algoritma */
    idxMkn = searchID(daftarInformasi, ID);
    if (idxMkn != -1) {
        *mkn = ELMT_LIST_STATIK(daftarInformasi, idxMkn);
    }
}

void MIX(Simulator *sim, PrioQueueTime *Inv, int ID, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Mix resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'M')) {
        Akar resep = getTree(ID, daftarResep);
        if (isResepInInventory(Inv, resep)) {
            Makanan hasil;
            getMakananFromList(ID, daftarInformasi, &hasil);
            if (LOC(hasil).TabWord == "Mix") {
                int idSiblingResep, idChildResep;
                Makanan child, sibling;
                idSiblingResep = INFO_TREE(SIBLING(resep));
                idChildResep = INFO_TREE(CHILD(resep));
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (idSiblingResep != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(*realTime);
            } else {
                printf("Makanan bukan diperoleh dengan cara Mix.\n");
            }
        } else {
            printf("Resep tidak ada di inventory.\n");
        }
    } else {
        printf("Anda tidak berada di dekat MIXER.\n");
    }
}

void CHOP(Simulator *sim, PrioQueueTime *Inv, int ID, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Chop resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'C')) {
        Akar resep = getTree(ID, daftarResep);
        if (isResepInInventory(Inv, resep)) {
            Makanan hasil;
            getMakananFromList(ID, daftarInformasi, &hasil);
            if (LOC(hasil).TabWord == "Chop") {
                int idSiblingResep, idChildResep;
                Makanan child, sibling;
                idSiblingResep = INFO_TREE(SIBLING(resep));
                idChildResep = INFO_TREE(CHILD(resep));
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (idSiblingResep != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(NextMinute(*realTime));
            } else {
                printf("Makanan bukan diperoleh dengan cara Chop.\n");
            }
        } else {
            printf("Resep tidak ada di inventory.\n");
        }
    } else {
        printf("Anda tidak berada di dekat CHOPPER.\n");
    }
}

void FRY(Simulator *sim, PrioQueueTime *Inv, int ID, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Fry resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'F')) {
        Akar resep = getTree(ID, daftarResep);
        if (isResepInInventory(Inv, resep)) {
            Makanan hasil;
            getMakananFromList(ID, daftarInformasi, &hasil);
            if (LOC(hasil).TabWord == "Fry") {
                int idSiblingResep, idChildResep;
                Makanan child, sibling;
                idSiblingResep = INFO_TREE(SIBLING(resep));
                idChildResep = INFO_TREE(CHILD(resep));
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (idSiblingResep != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(NextMinute(NextMinute(*realTime)));
            } else {
                printf("Makanan bukan diperoleh dengan cara Fry.\n");
            }
        } else {
            printf("Resep tidak ada di inventory.\n");
        }
    } else {
        printf("Anda tidak berada di dekat FRYER.\n");
    }
}

void BOIL(Simulator *sim, PrioQueueTime *Inv, int ID, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Boil resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'B')) {
        Akar resep = getTree(ID, daftarResep);
        if (isResepInInventory(Inv, resep)) {
            Makanan hasil;
            getMakananFromList(ID, daftarInformasi, &hasil);
            if (LOC(hasil).TabWord == "Boil") {
                int idSiblingResep, idChildResep;
                Makanan child, sibling;
                idSiblingResep = INFO_TREE(SIBLING(resep));
                idChildResep = INFO_TREE(CHILD(resep));
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (idSiblingResep != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(NextMinute(NextMinute(NextMinute(*realTime))));
            } else {
                printf("Makanan bukan diperoleh dengan cara Boil.\n");
            }
        } else {
            printf("Resep tidak ada di inventory.\n");
        }
    } else {
        printf("Anda tidak berada di dekat BOILER.\n");
    }
}