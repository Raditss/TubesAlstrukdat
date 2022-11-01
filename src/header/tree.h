#ifndef _LINKED_TREE_H_
#define _LINKED_TREE_H_


#include "string.h"

/* Definisi Node : */
typedef int ElTypeTree;
typedef struct node* Address;
typedef struct node {
    ElTypeTree info;
    Address child;
    Address sibling;
} Node;

#define INFO_TREE(p)    (p)->info
#define CHILD(p)        (p)->child
#define SIBLING(p)      (p)->sibling

#define CAPACITY_TREE   50   /* kapasitas penyimpanan */

typedef Address Akar;
typedef struct
{
    Akar contents[CAPACITY_TREE];
}KumpulanTree;

#define ELMT_TREE(l,i)      (l).contents[(i)]


Address newNodeTree(ElTypeTree val){
    /* Definisi TREE : */
    /* TREE kosong : CHILD(p)   = NULL */
    /*               SIBLING(p) = NULL */
    /*               INFO_TREE  = val  */
    /* Setiap elemen dengan Address p dapat diacu CHILD(p), SIBLING(p) */
    /* Elemen terakhir anakan : jika addressnya Last, maka CHILD(Last) = NULL */
    /* Elemen terakhir sibs   : jika addressnya Last, maka SIBLING(Last) = NULL */
    Address p = (Address) malloc (sizeof(Node));
    if (p != NULL){
        INFO_TREE(p) = val;
        CHILD(p) = NULL;
        SIBLING(p) = NULL;
    }
    return p;
}

void createRoot(Akar *A){
    /* Membuat akar */
    /* I.S. Sembarang */
    /* F.S. Terbentuk tree kosong */
    *A = NULL;
}

boolean isEmptyTree(Akar A){
    /* Mengembalikan true jika tree kosong */
    return A == NULL;
}

void addChild(Akar *A, ElTypeTree val){
    /* Tambahin anak */
    /* A tidak mungkin kosong karena mau punya anak */
    Address pencariAnak = *A;
    Address pembuatAnak = newNodeTree(val);
    if (CHILD(pencariAnak) == NULL){
        CHILD(pencariAnak) = pembuatAnak;
    } else {
        pencariAnak = CHILD(pencariAnak);
        while (SIBLING(pencariAnak) != NULL){
            pencariAnak = SIBLING(pencariAnak);
        }
        SIBLING(pencariAnak) = pembuatAnak;
    }
}

void readerTreeV1(Akar *A, int cabang){
    /* TESTER READ */
    /* I.S. Membaca n buah cabang untuk diterima sebagai anakan A */
    /* F.S. A memiliki anakan berjumlah cabang */
    int isiValue;
    for (int i = 0; i < cabang; i++){
        scanf("%d", &isiValue);
        addChild(A,isiValue);
    }
}

Address findValTree(Akar A, ElTypeTree X){
    /* Mengembalikan address tempat X berada */
    /* Mencari X dalam tree dengan rekursif */
    boolean found = false;
    if (isEmptyTree(A)){
        return NULL;
    }

    if (INFO_TREE(A) == X){
        found = true;
        return A;
    }

    Address result = findValTree(SIBLING(A), X);
    if (result) return result;

    Address result2 = findValTree(CHILD(A), X);
    return result2;
}

void mergeTree(Akar *A, Akar child){
    /* Menggabungkan akar utama dengan akar anakan */
    /* I.S. child merupakan salah satu akar dari A */
    /* F.S. child menjadi bagian dari A setelah di merge */
    Address cabang = findValTree(*A, INFO_TREE(child));
    CHILD(cabang) = CHILD(child);
    free(child);
}

void createKumpulanTree(KumpulanTree *KT){
    /* I.S. Sembarang */
    /* F.S. Terbentuk kumpulan tree kosong */
    /* Proses: Inisialisasi semua elemen kumpulan tree dengan NULL */
    for (int i = 0; i < CAPACITY_TREE; i++){
        ELMT_TREE(*KT, i) = NULL;
    }
}

void resepReader(KumpulanTree *simpenan, char namaFile[]){
    /* Membaca resep dari file  */
    /* Menyimpan resep dalam bentukan tree */
    STARTWORD(namaFile);
    int N = strToInt(currentWord);
    Akar A;
    int loopers;
    for (int i = 0; i < N; i++){
        ADVWORD();
        A = newNodeTree(strToInt(currentWord)); /* ID sebagai parrental */
        ADVWORD();
        loopers = strToInt(currentWord); /* loopers untuk berapa anakan dari parental */
        for (int j = 0; j < loopers; j++){
            ADVWORD();
            addChild(&A,strToInt(currentWord));
        }
        ELMT_TREE(*simpenan, i) = A;
    }
}

int lengthKumpulanTree (KumpulanTree KT){
    /* Mengembalikan panjang KT efektif */
    int i = 0;
    while (ELMT_TREE(KT, i) != NULL && i < 50){
        i++;
    }
    return i;
}

KumpulanTree mergeAdvancedTree(KumpulanTree simpenan){
    /* Menggabungkan semua yang mungkin di dalam array of akar */
    /* Untuk memusatkan resep */
    KumpulanTree Hasil;
    createKumpulanTree(&Hasil);
    int i,j,k;
    int walkers = 0;
    Akar checker;
    Akar mergeable;
    Akar walkyChecker;
    boolean found;
    while (ELMT_TREE(simpenan, walkers) != NULL){
        checker = ELMT_TREE(simpenan, walkers);
        /* Checker selalu berubah seiring perkembangan walkers */
        i = walkers + 1;
        found = false;

        while (ELMT_TREE(simpenan, i) != NULL){
            /* Mengecek apakah resep bisa digabungkan ke yang lain */
            walkyChecker = ELMT_TREE(simpenan, i);
            mergeable = findValTree(walkyChecker, INFO_TREE(checker));
            
            if (mergeable) {
                mergeTree(&walkyChecker, checker);
                found = true;
            }

            ELMT_TREE(simpenan, i) = walkyChecker;

            i++; /* Ngecek semuanya dengan pivot walkers */
        }
        if (found) ELMT_TREE(simpenan, walkers) = NULL; 
        /* Kalau udah pernah merge, lenyapkan dirinya sendiri */
        walkers++;
    }
    /* Saat ini SEHARUSNYA sudah tidak ada tree yang bisa di merge */
    j = 0;
    k = 0;
    while (j < CAPACITY_TREE){
        if (ELMT_TREE(simpenan, j) != NULL){
            ELMT_TREE(Hasil, k) = ELMT_TREE(simpenan, j);
            k++;
        }
        j++;
    }

    return Hasil;
}

#endif