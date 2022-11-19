
#include "../Makanan/makanan.h"

#ifndef _QUEUE_FOOD_
#define _QUEUE_FOOD_

#define NilFood -1
#define CAPACITY 100

typedef struct
{
    int time_left;
    Makanan food;
} FoodType;

typedef int address;

typedef struct {
    FoodType * T;   /* tabel penyimpan elemen */
    address HEAD;  /* alamat penghapusan */
    address TAIL;  /* alamat penambahan */
    int MaxElmtFood;     /* Max elemen queue */
} PrioQueueTime;

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah FoodType dan Q adalah PrioQueueTime, maka akses elemen : */

#define TIME_LEFT(e)    (e).time_left
#define Info(e)         (e).food
#define Head(Q)         (Q).HEAD
#define Tail(Q)         (Q).TAIL
#define InfoHead(Q)     (Q).T[(Q).HEAD]
#define InfoTail(Q)     (Q).T[(Q).TAIL]
#define MaxElmtFood(Q)  (Q).MaxElmtFood
#define Elmt(Q,i)       (Q).T[(i)]

/* ********* Prototype ********* */
void makeFoodType (FoodType *tipe, int time, Makanan food){
    /* Membuat foodtype dari time dan food */
    tipe->time_left = time;
    tipe->food = food;
}


boolean IsEmptyFood (PrioQueueTime Q){
/* Mengirim true jika Q kosong: lihat definisi di atas */
    return (Head(Q) == NilFood) && (Tail(Q) == NilFood);
}

int NBElmtFood (PrioQueueTime Q){
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
    if (IsEmptyFood(Q)){
        return 0;
    } else {
        if ((Tail(Q) - Head(Q)) >= 0){
            return Tail(Q) - Head(Q) + 1;
        } else {
            return MaxElmtFood(Q) - (Head(Q) - (Tail(Q) + 1));
        }
    }
}

boolean IsFullFood (PrioQueueTime Q){
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxElmtFood */
    return MaxElmtFood(Q) == NBElmtFood(Q);
}

/* *** Kreator *** */
void MakeEmptyFood (PrioQueueTime * Q, int Max){
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxElmtFood=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
    (*Q).T = (FoodType *)malloc((Max) * sizeof(FoodType));
    if ((*Q).T == NULL){
        MaxElmtFood(*Q) = 0;
    } else{
        Head(*Q) = NilFood;
        Tail(*Q) = NilFood;
        MaxElmtFood(*Q) = Max;
    }
}

/* *** Destruktor *** */
void DeAlokasiFood(PrioQueueTime * Q){
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxElmtFood(Q) diset 0 */
    Head(*Q) = NilFood;
    Tail(*Q) = NilFood;
    MaxElmtFood(*Q) = 0;
    free((*Q).T);
}

/* *** Primitif Add/Delete *** */
void EnqueueFood (PrioQueueTime * Q, FoodType X){
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut membesar berdasarkan time */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
    int i, j;
    FoodType temp;
    if (IsEmptyFood(*Q)){
        Head(*Q) = 0;
        Tail(*Q) = 0;
        InfoTail(*Q) = X;
    }else{
        Tail(*Q) = Tail(*Q) == MaxElmtFood(*Q) - 1 ? 0 : Tail(*Q) + 1;
        InfoTail(*Q) = X;
        i = Tail(*Q);
        j = (i == 0) ? MaxElmtFood(*Q) - 1 : i - 1;
        while (i != Head(*Q) && TIME_LEFT(Elmt(*Q, i)) < (TIME_LEFT(Elmt(*Q, j)))){
            temp = Elmt(*Q, i);
            Elmt(*Q, i) = Elmt(*Q, j);
            Elmt(*Q, j) = temp;
            i = j;
            j = (i == 0) ? MaxElmtFood(*Q) - 1 : i - 1;
        }
    }
}

void DequeueFood (PrioQueueTime * Q, FoodType * X){
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
    if (NBElmtFood(*Q) == 1){
        *X = InfoHead(*Q);
        Head(*Q) = NilFood;
        Tail(*Q) = NilFood;
    }else{
        *X = InfoHead(*Q);
        Head(*Q) = (Head(*Q) == MaxElmtFood(*Q) - 1) ? 0 : Head(*Q) + 1;
    }
}

/* Operasi Tambahan */
void PrintPrioQueueTimeFood (PrioQueueTime Q){
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<time-1> <elemen-1>
...
<time-n> <elemen-n>
#
*/
    PrioQueueTime Q2;
    FoodType val;
    PrioQueueTime temp = Q;
    if (!IsEmptyFood(Q)){
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);

            printf("Waktu makanan expired: ");
            TulisTIME(MinuteToTIME(TIME_LEFT(val)));
            printf("ID = %d\n", ID(Info(val)));
            DisplayWord(NAMA(Info(val)));
            TulisTIME(EXP(Info(val)));
            TulisTIME(DTIME(Info(val)));
            DisplayWord(LOC(Info(val)));
            printf("\n");
            
        }
    }
    
    printf("#\n");

}

void displayTime (TIME t){
/* Melakukan display time dengan format dd hari hh jam mm menit */
    if (Day(t) > 0){
        printf("%d hari ", Day(t));
    }
    if (Hour(t) > 0){
        printf("%d jam ", Hour(t));
    }
    if (Minute(t) > 0){
        printf("%d menit ", Minute(t));
    }
}

void displayDelivery(PrioQueueTime Q, TIME realTime){
/* Melakukan display pada DELIVERY */
    PrioQueueTime temp = Q;
    FoodType val;
    int i = 1;
    printf("Daftar barang yang sedang diantar: \n");
    if (IsEmptyFood(temp)){
        printf("\tTidak ada barang yang sedang diantar\n");
    } else {
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            printf("\t%d. ",i);
            DisplayWordNoEnter(NAMA(Info(val)));
            printf(" - ");
            displayTime(MinuteToTIME(TIME_LEFT(val) - TIMEToMinute(realTime)));
            i++;
            printf("\n");
        }
    }
    printf("\n");
}

void displayInventory(PrioQueueTime Q, TIME realTime){
/* Melakukan display terhadap INVENTORY */
    PrioQueueTime temp = Q;
    FoodType val;
    int i = 1;
    printf("Daftar isi INVENTORY: \n");
    if (IsEmptyFood(temp)){
        printf("\tTidak ada barang dalam INVENTORY\n");
    } else {
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            printf("\t%d. ",i);
            DisplayWordNoEnter(NAMA(Info(val)));
            printf(" - ");
            displayTime(MinuteToTIME(TIME_LEFT(val) - TIMEToMinute(realTime)));
            i++;
            printf("\n");
        }
    }
    printf("\n");
}

void IsValidFood (PrioQueueTime *P) {
    // I.S P terdefinisi
    // F.S makanan yang expired dihapus dari P lalu di-print.
    FoodType val;
    PrioQueueTime temp = *P;
    if (!IsEmptyFood(*P)){
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            if (TIME_LEFT(val) <= 0) {
                printf("Makanan %s telah basi.\n", NAMA(Info(val)).TabWord);
                // DeAlokasiFood(&val);
            } else {
                EnqueueFood(P, val);
            }
        }
    }
}

void MinusTime(PrioQueueTime *P, int selama_apa) {
    // I.S P terdefinisi
    // F.S semua time_left makanan di P dikurangi selama_apa
    FoodType val;
    PrioQueueTime temp = *P;
    if (!IsEmptyFood(*P)){
        while (!IsEmptyFood(temp)){
            DequeueFood(&temp, &val);
            TIME_LEFT(val) -= selama_apa;
            if (TIME_LEFT(val) <= 0) {
                // DeAlokasiFood(&val);
            } else {
                EnqueueFood(P, val);
            }
        }
    }
}

PrioQueueTime copyPrioQueue (PrioQueueTime Q){
/* copy Q lalu dikembalikan dalam address yang berbeda */
    PrioQueueTime temp = Q;
    PrioQueueTime Q2;
    MakeEmptyFood(&Q2, CAPACITY);
    FoodType val;
    while (!IsEmptyFood(temp))
    {
        DequeueFood(&temp,&val);
        EnqueueFood(&Q2,val);
    }
    return Q2;
}

#endif

