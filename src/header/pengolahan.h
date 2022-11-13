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
    if (SIBLING(Resep) == NULL) {
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

ListStatik ListOlahAble(ListStatik daftarInformasi, char loc[]) {
    ListStatik l;
    int i = 0;
    int nInformasi = listLengthStatik(daftarInformasi);
    CreateListStatik(&l);
    while (i < nInformasi) {
            if (LOC(ELMT_LIST_STATIK(daftarInformasi, i)).TabWord == loc) {
                insertLastListStatik(&l, ELMT_LIST_STATIK(daftarInformasi, i));
            }
            i++;
    return l;    
    }
}

void printOlahAble(ListStatik l) {
    int i = 0;
    int nInformasi = listLengthStatik(l);
    while (i < nInformasi) {
        printf("    %d. %s\n", i+1, NAMA(ELMT_LIST_STATIK(l, i)).TabWord);
        i++;
    }
}

boolean isInInventory(int ID, PrioQueueTime *Inv) {
    /* Mengembalikan true jika makanan dengan ID tertentu terdapat pada inventory */
    /* I.S. Inventory sembarang */
    /* F.S. Inventory tetap */
    /*      Mengembalikan true jika makanan dengan ID tertentu terdapat pada inventory */
    /*      Mengembalikan false jika makanan dengan ID tertentu tidak terdapat pada inventory */
    /* Kamus Lokal */
    PrioQueueTime Inv2;
    FoodType val;
    boolean found = false;
    int idInventory;
    /* Algoritma */
    MakeEmptyFood(&Inv2, CAPACITY);
    while (!found && !IsEmptyFood(*Inv)) {
        DequeueFood(Inv, &val);
        EnqueueFood(&Inv2, val);
        idInventory = ID(Info(val));
        if ( idInventory == ID ) {
            found = true;
        }
    }

    // mengembalikan inventory ke semula
    while (!IsEmptyFood(Inv2)) {
        DequeueFood(&Inv2, &val);
        EnqueueFood(Inv, val);
    }

    return found;
}

void MIX(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Mix resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'M')) {
        ListStatik l = ListOlahAble(daftarInformasi, "Mix");
        int nOlahable = listLengthStatik(l);
        printf("======================\n");
        printf("=        MIX        =\n");
        printf("======================\n");
        printf("List Bahan Makanan yang Bisa Dibuat:\n");
        printOlahAble(l);
        printf("Kirim 0 untuk exit.");
        printf("Enter Command: ");
        STARTKALIMAT();
        int input = strToInt(kalimatToWord(currentKalimat));
        while(input < 1 || input > nOlahable) {
            printf("Input tidak valid. Silakan masukkan input kembali: ");
            STARTKALIMAT();
            input = strToInt(kalimatToWord(currentKalimat));
        }
        if (input > 0) {
            int ID = ID(ELMT_LIST_STATIK(l, input-1));
            Akar resep = getTree(ID, daftarResep);
            Makanan hasil;
            getMakananFromList(ID, l, &hasil);
            int idSiblingResep, idChildResep;
            Makanan child, sibling;
            idSiblingResep = INFO_TREE(SIBLING(resep));
            idChildResep = INFO_TREE(CHILD(resep));
            if (isResepInInventory(&UserInventory(*sim), resep)) {
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (SIBLING(resep) != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(*realTime);
            } else {
                ListStatik listTidakAda;
                CreateListStatik(&listTidakAda);
                if (SIBLING(resep) != NULL) {
                    if (isInInventory(idSiblingResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, sibling);
                    }
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                } else {
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                }
                printf("Gagal membuat %d karena kamu tidak memiliki bahan berikut:\n", NAMA(ELMT_LIST_STATIK(l, input-1)).TabWord);
                printOlahAble(listTidakAda);
            }
        }
        
    } else {
        printf("Anda tidak berada di dekat MIXER.\n");
    }
}

void CHOP(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS) {
    /* Chop resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    ListStatik l = ListOlahAble(daftarInformasi, "Chop");
    int nOlahable = listLengthStatik(l);
    if (isClose(UserPeta(*sim), 'C')) {
        printf("======================\n");
        printf("=        CHOP        =\n");
        printf("======================\n");
        printf("List Bahan Makanan yang Bisa Dibuat:\n");
        printOlahAble(l);
        printf("Kirim 0 untuk exit.");
        printf("Enter Command: ");
        STARTKALIMAT();
        int input = strToInt(kalimatToWord(currentKalimat));
        while(input < 1 || input > nOlahable) {
            printf("Input tidak valid. Silakan masukkan input kembali: ");
            STARTKALIMAT();
            input = strToInt(kalimatToWord(currentKalimat));
        }
        if (input > 0) {
            int ID = ID(ELMT_LIST_STATIK(l, input-1));
            Akar resep = getTree(ID, daftarResep);
            Makanan hasil;
            getMakananFromList(ID, l, &hasil);
            int idSiblingResep, idChildResep;
            Makanan child, sibling;
            idSiblingResep = INFO_TREE(SIBLING(resep));
            idChildResep = INFO_TREE(CHILD(resep));
            if (isResepInInventory(&UserInventory(*sim), resep)) {
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (SIBLING(resep) != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(*realTime);
            } else {
                ListStatik listTidakAda;
                CreateListStatik(&listTidakAda);
                if (SIBLING(resep) != NULL) {
                    if (isInInventory(idSiblingResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, sibling);
                    }
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                } else {
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                }
                printf("Gagal membuat %d karena kamu tidak memiliki bahan berikut:\n", NAMA(ELMT_LIST_STATIK(l, input-1)).TabWord);
                printOlahAble(listTidakAda);
            }
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
    ListStatik l = ListOlahAble(daftarInformasi, "Fry");
    int nOlahable = listLengthStatik(l);
    if (isClose(UserPeta(*sim), 'F')) {
        printf("======================\n");
        printf("=        FRY        =\n");
        printf("======================\n");

        printf("List Bahan Makanan yang Bisa Dibuat:\n");
        printOlahAble(l);
        printf("Kirim 0 untuk exit.");
        printf("Enter Command: ");
        STARTKALIMAT();
        int input = strToInt(kalimatToWord(currentKalimat));
        while(input < 1 || input > nOlahable) {
            printf("Input tidak valid. Silakan masukkan input kembali: ");
            STARTKALIMAT();
            input = strToInt(kalimatToWord(currentKalimat));
        }
        if (input > 0) {
            int ID = ID(ELMT_LIST_STATIK(l, input-1));
            Akar resep = getTree(ID, daftarResep);
            Makanan hasil;
            getMakananFromList(ID, l, &hasil);
            int idSiblingResep, idChildResep;
            Makanan child, sibling;
            idSiblingResep = INFO_TREE(SIBLING(resep));
            idChildResep = INFO_TREE(CHILD(resep));
            if (isResepInInventory(&UserInventory(*sim), resep)) {
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (SIBLING(resep) != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(*realTime);
            } else {
                ListStatik listTidakAda;
                CreateListStatik(&listTidakAda);
                if (SIBLING(resep) != NULL) {
                    if (isInInventory(idSiblingResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, sibling);
                    }
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                } else {
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                }
                printf("Gagal membuat %d karena kamu tidak memiliki bahan berikut:\n", NAMA(ELMT_LIST_STATIK(l, input-1)).TabWord);
                printOlahAble(listTidakAda);
            }
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
    ListStatik l = ListOlahAble(daftarInformasi, "Boil");
    int nOlahable = listLengthStatik(l);
    if (isClose(UserPeta(*sim), 'B')) {
        printf("======================\n");
        printf("=        BOIL        =\n");
        printf("======================\n");
        printf("List Bahan Makanan yang Bisa Dibuat:\n");
        printOlahAble(l);
        printf("Kirim 0 untuk exit.");
        printf("Enter Command: ");
        STARTKALIMAT();
        int input = strToInt(kalimatToWord(currentKalimat));
        while(input < 1 || input > nOlahable) {
            printf("Input tidak valid. Silakan masukkan input kembali: ");
            STARTKALIMAT();
            input = strToInt(kalimatToWord(currentKalimat));
        }
        if (input > 0) {
            int ID = ID(ELMT_LIST_STATIK(l, input-1));
            Akar resep = getTree(ID, daftarResep);
            Makanan hasil;
            getMakananFromList(ID, l, &hasil);
            int idSiblingResep, idChildResep;
            Makanan child, sibling;
            idSiblingResep = INFO_TREE(SIBLING(resep));
            idChildResep = INFO_TREE(CHILD(resep));
            if (isResepInInventory(&UserInventory(*sim), resep)) {
                // mendefinisikan tipe makanan child dan sibling, lalu mengurangi inventory
                getMakananFromList(idChildResep, daftarInformasi, &child);
                removeInventory(sim, child);
                if (SIBLING(resep) != NULL) {
                    getMakananFromList(idSiblingResep, daftarInformasi, &sibling);
                    removeInventory(sim, sibling);
                }
                // menambahkan hasil mix ke inventory
                addInventory(sim, hasil, *realTime, NS);
                // menambah waktu
                *realTime = NextMinute(*realTime);
            } else {
                ListStatik listTidakAda;
                CreateListStatik(&listTidakAda);
                if (SIBLING(resep) != NULL) {
                    if (isInInventory(idSiblingResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, sibling);
                    }
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                } else {
                    if (isInInventory(idChildResep, &UserInventory(*sim))) {
                        insertLastListStatik(&listTidakAda, child);
                    }
                }
                printf("Gagal membuat %d karena kamu tidak memiliki bahan berikut:\n", NAMA(ELMT_LIST_STATIK(l, input-1)).TabWord);
                printOlahAble(listTidakAda);
            }
        }
        
    } else {
        printf("Anda tidak berada di dekat BOILER.\n");
    }
}