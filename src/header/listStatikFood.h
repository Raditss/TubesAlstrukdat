/* MODUL LIST INTEGER MAKANAN DENGAN ELEMEN MAKANAN */
/* Berisi definisi dan semua primitif pemrosesan list integer statik dengan elemen positif */
/* Penempatan elemen selalu rapat kiri */
/* Banyaknya elemen didefinisikan secara implisit, memori list statik */

#ifndef LIST_STATIK_FOOD_H
#define LIST_STATIK_FOOD_H

#include "makanan.h"
#include "string.h"

/*  Kamus Umum */
#define CAPACITY_LIST_FOOD 100
/* Kapasitas penyimpanan */
#define IDX_MIN 0
/* Indeks minimum list */
#define IDX_UNDEF -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef Makanan ElTypeFoodList;  /* type elemen List */
typedef int IdxType;
typedef struct {
   ElTypeFoodList contents[CAPACITY_LIST_FOOD]; /* memori tempat penyimpan elemen (container) */
} ListStatik;
/* Indeks yang digunakan [0..CAPACITY_LIST_FOOD-1] */
/* Jika l adalah ListStatik, cara deklarasi dan akses: */
/* Deklarasi : l : ListStatik */
/* Maka cara akses: 
   ELMT_LIST_STATIK(l,i) untuk mengakses elemen ke-i */
/* Definisi : 
   List kosong: semua elemen bernilai MARK
   Definisi elemen pertama: ELMT_LIST_STATIK(l,i) dengan i=0 */

/* ********** SELEKTOR ********** */
#define ELMT_LIST_STATIK(l, i) (l).contents[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create List kosong  */

void CreateListStatik(ListStatik *l){
    /* I.S. l sembarang */
    /* F.S. Terbentuk List l kosong dengan kapasitas CAPACITY_LIST_FOOD */
    /* Proses: Inisialisasi semua elemen List l dengan MARK */
    int i;
    for (i=IDX_MIN;i<CAPACITY_LIST_FOOD;i++){
        ELMT_LIST_STATIK(*l, i) = createEmptyFood();
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int listLengthStatik(ListStatik l){
    /* Mengirimkan banyaknya elemen efektif List */
    /* Mengirimkan nol jika List kosong */  
    int i = 0;
    while (!isEmptyFood(ELMT_LIST_STATIK(l,i)) && (i < 100)){
        i++;
    }
    return i;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdxListStatik(ListStatik l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l pertama */
    return 0;
}

IdxType getLastIdxListStatik(ListStatik l){
    /* Prekondisi : List l tidak kosong */
    /* Mengirimkan indeks elemen l terakhir */
    IdxType i, count = 0;
    for (i = 0; i < CAPACITY_LIST_FOOD; i++){
        if (!isEmptyFood(ELMT_LIST_STATIK(l,i))){
            count++;
        }
    }
    return count - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean isIdxValidListStatik(ListStatik l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */
    /* yaitu antara indeks yang terdefinisi utk container*/
    return ((IDX_MIN <= i) && (i < CAPACITY_LIST_FOOD));
}

boolean isIdxEffListStatik(ListStatik l, IdxType i){
    /* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */
    /* yaitu antara 0..length(l)-1 */
    return (isIdxValidListStatik(l,i)) ?
        ((!isEmptyFood(ELMT_LIST_STATIK(l,i)))) :
        false;
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test List kosong *** */
boolean isEmptyListStatik(ListStatik l){
    /* Mengirimkan true jika List l kosong, mengirimkan false jika tidak */
    /* *** Test List penuh *** */
    return (isEmptyFood(ELMT_LIST_STATIK(l,0))); //karena rata kiri
}

boolean isFullListStatik(ListStatik l){
    /* Mengirimkan true jika List l penuh, mengirimkan false jika tidak */
    return (!isEmptyFood(ELMT_LIST_STATIK(l,CAPACITY_LIST_FOOD-1))); //kapasitasnya 100
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan List: *** */
boolean isListEqual(ListStatik l1, ListStatik l2){
    /* Mengirimkan true jika l1 sama dengan l2 yaitu jika ukuran l1 = l2 dan semua 
    elemennya sama */
    if (listLengthStatik(l1)==listLengthStatik(l2)){
        for (int i = 0; i < listLengthStatik(l1) - 1 ; i++){
            if (!isFoodEqual (ELMT_LIST_STATIK(l1,i), ELMT_LIST_STATIK(l2,i))){
                return false;
            }
        }
        return true;
    }
    return false;
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : List boleh kosong!! *** */
int indexOfListStatikFood(ListStatik l, ElTypeFoodList val){
    /* Search apakah ada elemen List l yang bernilai val */
    /* Jika ada, menghasilkan indeks i terkecil, dengan ELMT_LIST_STATIK(l,i) = val */
    /* Jika tidak ada atau jika l kosong, mengirimkan IDX_UNDEF */
    /* Skema Searching yang digunakan bebas */
    for (int i = 0; i < listLengthStatik(l); i++){
        if (isFoodEqual(ELMT_LIST_STATIK(l,i),val)){
            return i;
        } if (isEmptyFood){
            return IDX_UNDEF;
        }
    } return IDX_UNDEF;
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void insertFirstListStatik(ListStatik *l, ElTypeFoodList val){
    /* Proses: Menambahkan val sebagai elemen pertama List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen pertama l yang baru */
    /* *** Menambahkan elemen pada index tertentu *** */
    for (int i = listLengthStatik(*l); i >= 1;i--){
        ELMT_LIST_STATIK(*l,i) = ELMT_LIST_STATIK(*l,i-1);
    }
    ELMT_LIST_STATIK(*l,0) = val;
}

void insertAtListStatik(ListStatik *l, ElTypeFoodList val, IdxType idx){
    /* Proses: Menambahkan val sebagai elemen pada index idx List */
    /* I.S. List l tidak kosong dan tidak penuh, idx merupakan index yang valid di l */
    /* F.S. val adalah elemen yang disisipkan pada index idx l */
    /* *** Menambahkan elemen terakhir *** */
    for (int i = listLengthStatik(*l); i >= idx; i--){
        ELMT_LIST_STATIK(*l,i) = ELMT_LIST_STATIK(*l,i-1);
    }
    ELMT_LIST_STATIK(*l,idx) = val;
}

void insertLastListStatik(ListStatik *l, ElTypeFoodList val){
    /* Proses: Menambahkan val sebagai elemen terakhir List */
    /* I.S. List l boleh kosong, tetapi tidak penuh */
    /* F.S. val adalah elemen terakhir l yang baru */
    ELMT_LIST_STATIK(*l,listLengthStatik(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
/* *** Menghapus elemen pertama *** */
void deleteFirstListStatik(ListStatik *l, ElTypeFoodList *val){
    /* Proses : Menghapus elemen pertama List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen pertama l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    /* *** Menghapus elemen pada index tertentu *** */
    *val = ELMT_LIST_STATIK(*l,0);
    for (int i = 0; i<listLengthStatik(*l); i++){
        ELMT_LIST_STATIK(*l,i) = ELMT_LIST_STATIK(*l,i+1);
    }
    ELMT_LIST_STATIK(*l, listLengthStatik(*l)-1) = createEmptyFood();
}

void deleteAtListStatik(ListStatik *l, ElTypeFoodList *val, IdxType idx){
    /* Proses : Menghapus elemen pada index idx List */
    /* I.S. List tidak kosong, idx adalah index yang valid di l */
    /* F.S. val adalah nilai elemen pada index idx l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    /* *** Menghapus elemen terakhir *** */
    *val = ELMT_LIST_STATIK(*l,idx);
    for (IdxType i = idx; i < listLengthStatik(*l); i++){
        ELMT_LIST_STATIK(*l,i) = ELMT_LIST_STATIK(*l,i+1);
    }
    ELMT_LIST_STATIK(*l,listLengthStatik(*l)-1) = createEmptyFood();
}

void deleteLastListStatik(ListStatik *l, ElTypeFoodList *val){
    /* Proses : Menghapus elemen terakhir List */
    /* I.S. List tidak kosong */
    /* F.S. val adalah nilai elemen terakhir l sebelum penghapusan, */
    /*      Banyaknya elemen List berkurang satu */
    /*      List l mungkin menjadi kosong */
    *val = ELMT_LIST_STATIK(*l,listLengthStatik(*l)-1);
    ELMT_LIST_STATIK(*l,listLengthStatik(*l)-1) = createEmptyFood();
}

Word findFoodByID(ListStatik l, int ID){
    /* Mengembalikan word yang merupakan nama dari ID makanan */
    boolean found = false;
    int i = 0;
    while ((!found) && (!(isFoodEqual(ELMT_LIST_STATIK(l,i), createEmptyFood()))))
    {
        if (ID(ELMT_LIST_STATIK(l,i)) == ID){
            found = true;
        }
        i++;
    }
    if (found){
        return (NAMA(ELMT_LIST_STATIK(l,i-1)));
    } else {
        return (strToWord("Makanan tidak ditemukan."));
    }
}

/* ********** SORTING ********** */
void sortListStatikFood(ListStatik *l, boolean asc){
    /* I.S. l boleh kosong */
    /* F.S. Jika asc = true, l terurut membesar */
    /*      Jika asc = false, l terurut mengecil */
    /* Proses : Mengurutkan l dengan salah satu algoritma sorting,
    algoritma bebas */
    int i,j,swap_idx,len;
    ElTypeFoodList temp;
    len = listLengthStatik(*l);
    if (asc) {
        for (i=0;i<len;i++) {
            swap_idx = i; 
            for (j=i+1;j<len;j++) {
                if (ID(ELMT_LIST_STATIK(*l,j)) < ID(ELMT_LIST_STATIK(*l,swap_idx)))
                swap_idx = j; //menukar nilai
            }
            temp = ELMT_LIST_STATIK(*l,swap_idx);
            ELMT_LIST_STATIK(*l,swap_idx) = ELMT_LIST_STATIK(*l,i);
            ELMT_LIST_STATIK(*l,i) = temp;
            } 
        } else {
            for (i=0;i<len;i++) {
            swap_idx = i; 
                for (j=i+1;j<len;j++) {
                    if (ID(ELMT_LIST_STATIK(*l,j)) > ID(ELMT_LIST_STATIK(*l,swap_idx)))
                    swap_idx = j; //menukar nilai
                }
                temp = ELMT_LIST_STATIK(*l,swap_idx);
                ELMT_LIST_STATIK(*l,swap_idx) = ELMT_LIST_STATIK(*l,i);
                ELMT_LIST_STATIK(*l,i) = temp;
            }
        }
}

ListStatik readFileMakananListStatik (char namaFile[]){
    ListStatik Q;
    STARTWORD(namaFile);
    Makanan m;
    int n = strToInt(currentWord);
    for (int i=0; i < n; i++){
        ADVWORD();
        ID(m) = strToInt(currentWord);
        ADVWORD();
        Word name = currentWord;
        ADVWORD();
        while (!(isInt(currentWord))){
            name = mergeWord(name,currentWord);
            ADVWORD();
        }
        NAMA(m) = name;
        
        // Untuk yang expired
        
        TIME expired;
        int hari,jam,mnt;
        // Algoritma
        hari=strToInt(currentWord); /*simpan nilai hari*/
        ADVWORD();
        jam=strToInt(currentWord); /*simpan nilai jam*/
        ADVWORD();
        mnt=strToInt(currentWord); /*simpan nilai menit*/
        ADVWORD();
        // Sudah dapat nilai hari jam dan menit dalam integer*/
        CreateTime(&expired,hari,jam,mnt);
        EXP(m) = expired;
        
        // Untuk yang delivery time
        
        TIME deliveryTime;
        // Algoritma
        hari=strToInt(currentWord); /*simpan nilai hari*/
        ADVWORD();
        jam=strToInt(currentWord); /*simpan nilai jam*/
        ADVWORD();
        mnt=strToInt(currentWord); /*simpan nilai menit*/
        ADVWORD();
        // Sudah dapat nilai hari jam dan menit*/
        CreateTime(&deliveryTime,hari,jam,mnt);
        DTIME(m) = deliveryTime;
        
        // Untuk lokasi aksi
        LOC(m) = currentWord;

        insertLastListStatik(&Q, m);
    }
    sortListStatikFood(&Q, true);
    return Q;
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi List dari pembacaan *** */

void printListStatikFood(ListStatik l){
    /* Melakukan display makanan setiap elemen list */
    if (isEmptyListStatik(l)){
        printf("Tidak ada daftar makanan dalam list ini\n");
    } else {
        printf ("===================DAFTAR MAKANAN===================\n");
        for (int i = 0; i < listLengthStatik(l); i++){
            printf("=====================================================================\n");
            DisplayMakanan(ELMT_LIST_STATIK(l,i));
        }
    }
}

void CATALOG (ListStatik l){
    /* Menampilkan daftar makanan */
    /* (nama - durasi kedaluwarsa - aksi yang diperlukan - delivery time) */
    for (int i = 0; i < listLengthStatik(l); i++){
        if (i < 9){
            printf("0%d. ", i+1);
        } else {
            printf("%d. ", i+1);
        }
        DisplayWordNoEnter(NAMA(ELMT_LIST_STATIK(l,i)));
        printf(" ----------- ");
        TulisTIMEnoEnter(EXP(ELMT_LIST_STATIK(l,i)));
        printf(" ----------- ");
        DisplayWordNoEnter(LOC(ELMT_LIST_STATIK(l,i)));
        printf(" ----------- ");
        TulisTIMEnoEnter(DTIME(ELMT_LIST_STATIK(l,i)));
        printf("\n");
    }
}

#endif