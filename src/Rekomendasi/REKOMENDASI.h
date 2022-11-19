#include "../Simulator/simulator.h"
#include "../Tree/tree.h"
#include "../StackRekomendasi/stackRekomendasi.h"
#include "../ListStatikFood/listStatikFood.h"

#ifndef REKOMENDASI_H
#define REKOMENDASI_H

#define CAPACITY_REKOMENDASI 200

typedef int ElType_Rekomendasi;
typedef struct {
    ElType_Rekomendasi contents[CAPACITY_REKOMENDASI];
}ListHash;

#define ELMT_REKOMENDASI(l,i)   (l).contents[(i)]
#define MARK_REKOMENDASI        (-1)

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */

void CreateListHash(ListHash *l){
    /* I.S. l sembarang */
    /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY_REKOMENDASI */
    /* Proses: Inisialisasi semua elemen List l dengan MARK */
    int i;
    for (i=0;i<CAPACITY_REKOMENDASI;i++){
        ELMT_REKOMENDASI(*l, i) = MARK_REKOMENDASI;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthRekomendasi(ListHash l){
    /* Mengirimkan banyaknya elemen efektif List */
    /* Mengirimkan nol jika List kosong */  
    int i = 0;
    while ((ELMT_REKOMENDASI(l,i)) != MARK_REKOMENDASI){
        i++;
    }
    return i;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListHash(ListHash l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return 0;
}

IdxType getLastIdxListHash(ListHash l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    return listLengthRekomendasi(l) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListHash(ListHash l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return ((0 <= i) && (i < CAPACITY_REKOMENDASI));
}

boolean isIdxEffListHash(ListHash l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
    /* yaitu antara 0..length(l)-1 */
    return  (isIdxValidListHash(l,i)) ?
            (ELMT_REKOMENDASI(l,i) != MARK_REKOMENDASI) :
            false;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListHash(ListHash l){
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    /* *** Test List penuh *** */
    return (ELMT_REKOMENDASI(l,0) = MARK_REKOMENDASI); //karena rata kiri
}

boolean isFullListHash(ListHash l){
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return (ELMT_REKOMENDASI(l,CAPACITY_REKOMENDASI-1) != -1); //kapasitasnya 100
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListHashEqual(ListHash l1, ListHash l2){
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
    elemennya sama */
    if (listLengthRekomendasi(l1)==listLengthRekomendasi(l2)){
        for (int i = 0; i < listLengthRekomendasi(l1) - 1 ; i++){
            if (ELMT_REKOMENDASI(l1,i) != ELMT_REKOMENDASI(l2,i)){
                return false;
            }
        }
        return true;
    }
    return false;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListHashFood(ListHash l, ElType_Rekomendasi val){
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT_REKOMENDASI(l,i) = val */
    /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
    /* Skema Searching yang digunakan bebas */
    for (int i = 0; i < listLengthRekomendasi(l); i++){
        if (ELMT_REKOMENDASI(l,i) == val){
            return i;
        } 
    } 
    return MARK_REKOMENDASI;
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirstListHash(ListHash *l, ElType_Rekomendasi val){
    /* Proses: Menambahkan val sebagai elemen pertama List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen pertama l yang baru */
    /* *** Menambahkan elemen pada index tertentu *** */
    for (int i = listLengthRekomendasi(*l); i >= 1; i--){
        ELMT_REKOMENDASI(*l,i) = ELMT_REKOMENDASI(*l,i-1);
    }
    ELMT_REKOMENDASI(*l,0) = val;
}

void insertAtListHash(ListHash *l, ElType_Rekomendasi val, IdxType idx){
    /* Proses: Menambahkan val sebagai elemen pada index idx List */
    /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
    /* F.S. val adalah elemen yang disisipkan pada index idx l */
    /* *** Menambahkan elemen terakhir *** */
    for (int i = listLengthRekomendasi(*l); i >= idx; i--){
        ELMT_REKOMENDASI(*l,i) = ELMT_REKOMENDASI(*l,i-1);
    }
    ELMT_REKOMENDASI(*l,idx) = val;
}

void insertLastListHash(ListHash *l, ElType_Rekomendasi val){
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    ELMT_REKOMENDASI(*l,listLengthRekomendasi(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListHash(ListHash *l, ElType_Rekomendasi *val){
    /* Proses : Menghapus elemen pertama List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    /* *** Menghapus elemen pada index tertentu *** */
    *val = ELMT_REKOMENDASI(*l,0);
    for (int i = 0; i<listLengthRekomendasi(*l); i++){
        ELMT_REKOMENDASI(*l,i) = ELMT_REKOMENDASI(*l,i+1);
    }
    ELMT_REKOMENDASI(*l, listLengthRekomendasi(*l)-1) = MARK_REKOMENDASI;
}

void deleteAtListHash(ListHash *l, ElType_Rekomendasi *val, IdxType idx){
    /* Proses : Menghapus elemen pada index idx List */
    /* I.S. List tidak kosong, idx adalah index yang valid di l */
    /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    /* *** Menghapus elemen terakhir *** */
    *val = ELMT_REKOMENDASI(*l,idx);
    for (IdxType i = idx; i < listLengthRekomendasi(*l); i++){
        ELMT_REKOMENDASI(*l,i) = ELMT_REKOMENDASI(*l,i+1);
    }
    ELMT_REKOMENDASI(*l,listLengthRekomendasi(*l)-1) = MARK_REKOMENDASI;
}

void deleteLastListHash(ListHash *l, ElType_Rekomendasi *val){
    /* Proses : Menghapus elemen terakhir List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT_REKOMENDASI(*l,listLengthRekomendasi(*l)-1);
    ELMT_REKOMENDASI(*l,listLengthRekomendasi(*l)-1) = MARK_REKOMENDASI;
}

/* ********** SORTING ********** */
void sortListHashFood(ListHash *l, boolean asc){
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    int i,j,swap_idx,len;
    ElType_Rekomendasi temp;
    len = listLengthRekomendasi(*l);
    if (asc) {
        for (i=0;i<len;i++) {
            swap_idx = i; 
            for (j=i+1;j<len;j++) {
                if (ELMT_REKOMENDASI(*l,j) < ELMT_REKOMENDASI(*l,swap_idx))
                    swap_idx = j; //menukar nilai
            }
            temp = ELMT_REKOMENDASI(*l,swap_idx);
            ELMT_REKOMENDASI(*l,swap_idx) = ELMT_REKOMENDASI(*l,i);
            ELMT_REKOMENDASI(*l,i) = temp;
            } 
        } else {
            for (i=0;i<len;i++) {
            swap_idx = i; 
                for (j=i+1;j<len;j++) {
                    if (ELMT_REKOMENDASI(*l,j) > ELMT_REKOMENDASI(*l,swap_idx))
                        swap_idx = j; //menukar nilai
                }
                temp = ELMT_REKOMENDASI(*l,swap_idx);
                ELMT_REKOMENDASI(*l,swap_idx) = ELMT_REKOMENDASI(*l,i);
                ELMT_REKOMENDASI(*l,i) = temp;
            }
        }
}

boolean subset_Rekomendasi(ListHash l1, ListHash l2){
    /* mengembalikan true jika l1 merupakan subset dari l2 */
    /* l2 lebih banyak elemennya dibanding l1 jika tidak sama */
    for (int i = 0; i < CAPACITY_REKOMENDASI; i++){
        if ((ELMT_REKOMENDASI(l1,i) == 1) && (ELMT_REKOMENDASI(l2,i) != 1)){
            return false;
        }
    }
    return true;
}

ListHash getHash(Akar Menu){
    /* index ListHash menandakan ID dari makanan pembuatan */
    /* index ke 0 merupakan nilai ID dari makanan utama */
    Address walkers = Menu;
    ListHash LH;
    CreateListHash(&LH);
    if (CHILD(walkers) != NULL){
        ELMT_REKOMENDASI(LH,0) = INFO_TREE(walkers);
        walkers = CHILD(walkers);
        ELMT_REKOMENDASI(LH, INFO_TREE(walkers)) = 1;
        while (SIBLING(walkers) != NULL){
            walkers = SIBLING(walkers);
            ELMT_REKOMENDASI(LH, INFO_TREE(walkers)) = 1;
        }
    }
    return LH;
}

ListHash getInventoryHash(Simulator sim){
    /* Menerima simulator */
    /* Mengecek inventory dari simulator */
    /* Mengubah inventory simulator menjadi bentuh hash of ID */
    ListHash hashVentory;
    CreateListHash(&hashVentory);
    ELMT_REKOMENDASI(hashVentory,0) = 0; /* Menandakan hash milik inventory */
    PrioQueueTime Invent;
    Invent = UserInventory(sim);
    IdxType temp;
    FoodType val;
    while (!IsEmptyFood(Invent)){
        DequeueFood(&Invent, &val);
        temp = ID(Info(val));
        ELMT_REKOMENDASI(hashVentory, temp) = 1;
    }
    return hashVentory;
}

Rekomendasi_STACK getRekomendasi(KumpulanTree DaftarResep, Simulator sim){
    /* Rekomendasi stack merupakan stack yang berisi daftar rekomendasi (word) */
    ListHash hashVentory = getInventoryHash(sim);
    Rekomendasi_STACK daftar_Rekomendasi;
    CreateEmptyRekomendasi(&daftar_Rekomendasi);
    int i = 0;
    ListHash calonSubset;
    while (ELMT_TREE(DaftarResep, i) != NULL){
        calonSubset = getHash(ELMT_TREE(DaftarResep, i));
        if (subset_Rekomendasi(calonSubset, hashVentory)){
            PushRekomendasi(&daftar_Rekomendasi, ELMT_REKOMENDASI(calonSubset, 0));
        }
        i++;
    }
    return daftar_Rekomendasi;
}

void displayRekomendasi(Rekomendasi_STACK daftar_Rekomendasi, ListStatik daftar_Makanan){
    /* Menampilkan rekomendasi makanan */
    int val;
    Word kalimat;
    int i = 0;
    printf("=== Berikut daftar makanan yang direkomendasikan untuk dibuat ===\n");
    if (IsEmptyRekomendasi(daftar_Rekomendasi)){
        printf("Tidak ada makanan yang bisa direkomendasikan!\n");
    } else {
        while (!IsEmptyRekomendasi(daftar_Rekomendasi)){
            i++;
            PopRekomendasi(&daftar_Rekomendasi, &val);
            kalimat = findFoodByID(daftar_Makanan, val);
            printf("%d. ", i);
            DisplayWord(kalimat);
        }
    }
}

#endif