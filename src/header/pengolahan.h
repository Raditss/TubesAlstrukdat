
ListStatik ListOlahAble(ListStatik daftarMakanan, char loc[5]){
    /* Menerima daftar makanan */
    /* Mengeluarkan makanan yang tipe BUY */
    ListStatik olahAble;
    CreateListStatik(&olahAble);
    int i = 0;
    for (int j = 0; j < listLengthStatik(daftarMakanan); j++){
        if (isWordEqual(LOC(ELMT_LIST_STATIK(daftarMakanan,j)), strToWord(loc))){
            ELMT_LIST_STATIK(olahAble,i) = ELMT_LIST_STATIK(daftarMakanan,j);
            i++;
        }
    }
    return olahAble;
}

void printOlahAble(ListStatik l) {
    int i = 0;
    int nInformasi = listLengthStatik(l);
    while (i < nInformasi) {
        printf("    %d. %s\n", i+1, NAMA(ELMT_LIST_STATIK(l, i)).TabWord);
        i++;
    }
}

boolean isInInventory(PrioQueueTime *Inv, int ID) {
    boolean found = false;
    FoodType val;
    PrioQueueTime Inv2;
    MakeEmptyFood(&Inv2, 100);

    while(!found && !IsEmptyFood(*Inv)) {
        DequeueFood(Inv, &val);
        if (ID(Info(val)) == ID) {
            found = true;
        }
        EnqueueFood(&Inv2, val);
    }

    while(!IsEmptyFood(Inv2)) {
        DequeueFood(&Inv2, &val);
        EnqueueFood(Inv, val);
    }
    return found;
}

ListStatik ListTidakAda(PrioQueueTime *Inv, Akar resep, ListStatik daftarMakanan) {
    ListStatik l;
    Makanan val;
    CreateListStatik(&l);
    Address P = CHILD(resep);
    while (P != NULL) {
        if (!isInInventory(Inv, INFO_TREE(P))) {
            val = ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(P)));
            insertLastListStatik(&l, val);
        }
        P = SIBLING(P);
    }
    return l;
}

void olahInventory(Simulator *sim, Akar resep, ListStatik daftarMakanan, TIME *realTime, NOTIF_STACK *NS) {
    // Mengolah inventori (menambahkan makanan yang bisa dibuat dan menghapus bahan di inventory)
    // I.S. : Inventori terdefinisi dan resep terdefinisi, resep  berada di inventory
    // F.S. : Inventori terolah
    Makanan hasil, bahan;
    PrioQueueTime Inv2, Inv;
    boolean found;
    MakeEmptyFood(&Inv2, 100);
    Inv = UserInventory(*sim);
    Address P = CHILD(resep);
    while (P != NULL) {
        bahan = ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(P)));
        removeInventory(sim, bahan);
        P = SIBLING(P);
    }
    ID(hasil) = ID(ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(resep))));
    NAMA(hasil) = NAMA(ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(resep))));
    EXP(hasil) = EXP(ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(resep))));
    DTIME(hasil) = DTIME(ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(resep))));
    LOC(hasil) = LOC(ELMT_LIST_STATIK(daftarMakanan, searchID(daftarMakanan, INFO_TREE(resep))));
    addInventory(sim, hasil, *realTime, NS);
}


void Olah(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS, char loc[5], boolean *isValid) {
    /* Mix resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    ListStatik l = ListOlahAble(daftarInformasi, loc);
    printf("List Bahan Makanan yang Bisa Dibuat:\n");
    printOlahAble(l);
    printf("\n");
    printf("Kirim 0 untuk exit.\n");
    printf("Enter Command: ");
    int nOlahable = listLengthStatik(l);
    STARTKALIMAT();
    int input = strToIntV2(kalimatToWord(currentKalimat));
    while(input < 0 || input > nOlahable) {
        printf("Input tidak valid. Silakan masukkan input kembali: ");
        STARTKALIMAT();
        input = strToIntV2(kalimatToWord(currentKalimat));
    }
    if (input > 0) {
        Makanan hasil = ELMT_LIST_STATIK(l, input-1);
        int ID = ID(hasil);
        Akar resep = getTree(ID, daftarResep);
        
        ListStatik tidakAda = ListTidakAda(&(UserInventory(*sim)), resep, daftarInformasi);

        if (isEmptyListStatik(tidakAda)) {
            olahInventory(sim, resep, daftarInformasi, realTime, NS);
            printf("%s selesai dibuat dan sudah masuk ke inventory!\n", NAMA(hasil).TabWord);
            *isValid = true;

        } else {
            printf("Gagal membuat %s karena kamu tidak memiliki bahan berikut:\n", NAMA(ELMT_LIST_STATIK(l, input-1)).TabWord);
            printOlahAble(tidakAda);
        }
    }
}

void MIX(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS, boolean *isValid) {
    if (isClose(UserPeta(*sim), 'M')) {
        printf("======================\n");
        printf("=        MIX         =\n");
        printf("======================\n");
        Olah(sim, daftarResep, daftarInformasi, realTime, NS, "Mix.", isValid);
        *realTime = NextMinute(*realTime);
    } else {
        printf("Anda tidak berada di dekat MIXER.\n");
    }
    
}



void CHOP(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS, boolean *isValid) {
    /* Chop resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'C')) {
        printf("======================\n");
        printf("=        CHOP        =\n");
        printf("======================\n");
        Olah(sim, daftarResep, daftarInformasi, realTime, NS, "Chop.",isValid);
        *realTime = NextMinute(*realTime);
    } else {
        printf("Anda tidak berada di dekat CHOPPER.\n");
    }
}

void FRY(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS, boolean *isValid) {
    /* Fry resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'F')) {
        printf("======================\n");
        printf("=        FRY         =\n");
        printf("======================\n");
        Olah(sim, daftarResep, daftarInformasi, realTime, NS, "Fry.", isValid);
        *realTime = NextMinute(*realTime);
    } else {
        printf("Anda tidak berada di dekat FRYER.\n");
    }
}

void BOIL(Simulator *sim, KumpulanTree daftarResep, ListStatik daftarInformasi, TIME *realTime, NOTIF_STACK *NS, boolean *isValid) {
    /* Boil resep menjadi makanan */
    /* I.S. Resep terdefinisi */
    /* F.S. Resep menjadi makanan */
    /*      Resep dihapus dari inventory */
    /*      Makanan ditambahkan ke inventory */
    if (isClose(UserPeta(*sim), 'B')) {
        printf("======================\n");
        printf("=        BOIL        =\n");
        printf("======================\n");
        Olah(sim, daftarResep, daftarInformasi, realTime, NS, "Boil.", isValid);
        *realTime = NextMinute(*realTime);
    } else {
        printf("Anda tidak berada di dekat BOILER.\n");
    }
}