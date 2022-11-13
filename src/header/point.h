
#include "boolean.h"

#ifndef POINT_H
#define POINT_H

typedef struct
{
    int row; /* posisi baris ke- matrix */
    int col; /* posisi kolom ke- matrix */
} Posisi; 

#define ROW_POSISI(P) (P).row
#define COL_POSISI(P) (P).col

/* *** DEFINISI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk Posisi *** */
void CreatePosisi (Posisi * P, int X, int Y){
   ROW_POSISI(*P) = X;
   COL_POSISI(*P) = Y;
}
/* Membentuk sebuah Posisi dari komponen-komponennya */

/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */                                                 
void BacaPosisi (Posisi * P){
   /* Membaca nilai ROW_POSISI dan COL_POSISI dari keyboard dan membentuk 
   Posisi P berdasarkan dari nilai ROW_POSISI dan COL_POSISI tersebut */
   /* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
   /* Contoh: 1 2 
      akan membentuk Posisi <1,2> */
   /* I.S. Sembarang */
   /* F.S. P terdefinisi */
   int X, Y;
   scanf("%d %d", &X, &Y);
   ROW_POSISI(*P) = X;
   COL_POSISI(*P) = Y;
}

void TulisPosisi (Posisi P){
   /* Nilai P ditulis ke layar dengan format "(X,Y)" 
   tanpa spasi, enter, atau karakter lain di depan, belakang, 
   atau di antaranya 
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
   */
   /* I.S. P terdefinisi */
   /* F.S. P tertulis di layar dengan format "(X,Y)" */  
   printf("(%d,%d)",ROW_POSISI(P),COL_POSISI(P));
}             
/* *** Kelompok operasi relasional terhadap Posisi *** */


boolean EQ (Posisi P1, Posisi P2){
   /* Mengirimkan true jika P1 = P2 : ROW_POSISI dan COLnya sama */
   return (ROW_POSISI(P1) == ROW_POSISI(P2)) && (COL_POSISI(P1) == COL_POSISI(P2));
}


boolean NEQ (Posisi P1, Posisi P2){
   /* Mengirimkan true jika P1 tidak sama dengan P2 */
   return (!EQ(P1, P2));
}

/* *** Kelompok menentukan di mana P berada *** */

boolean IsOrigin (Posisi P){
   /* Menghasilkan true jika P adalah titik origin */
   return ((ROW_POSISI(P)== 0) && (COL_POSISI(P) == 0));
}

boolean IsOnSbX (Posisi P){
   /* Menghasilkan true jika P terletak Pada sumbu X */
   return ROW_POSISI(P) == 0;
}

boolean IsOnSbY (Posisi P){
   /* Menghasilkan true jika P terletak pada sumbu Y */
   return COL_POSISI(P) == 0;
}

/* *** KELOMPOK OPERASI LAIN TERHADAP TYPE *** */                           
Posisi NextX (Posisi P){
   /* Mengirim salinan P dengan ROW_POSISI ditambah satu */     
   ROW_POSISI(P) += 1;
   return P;
}
         
Posisi NextY (Posisi P){
   /* Mengirim salinan P dengan COL_POSISI ditambah satu */
   COL_POSISI(P) += 1;
   return P;
}

Posisi PlusDelta (Posisi P, int deltaX, int deltaY){
   /* Mengirim salinan P yang ROWnya adalah ROW_POSISI(P) + deltaX dan COLnya adalah COL_POSISI(P) + deltaY */

   ROW_POSISI(P) += deltaX;
   COL_POSISI(P) += deltaY;
   return P;
}

Posisi MirrorOf (Posisi P, boolean SbX){
   /* Menghasilkan salinan P yang dicerminkan terhadap salah satu sumbu */
   /* Jika SbX bernilai true, maka dicerminkan terhadap sumbu X */
   /* Jika SbX bernilai false, maka dicerminkan terhadap sumbu Y */
   if (SbX){
      COL_POSISI(P) *= -1;  
   } else {
      ROW_POSISI(P) *= -1;
   }
   return P;
}

float Jarak0 (Posisi P){
   /* Menghitung jarak P ke (0,0) */
   return (sqrt(pow(ROW_POSISI(P),2)+pow(COL_POSISI(P),2)));
}

float Panjang (Posisi P1, Posisi P2){
   /* Menghitung panjang garis yang dibentuk P1 dan P2 */
   /* Perhatikanlah bahwa di sini spec fungsi kurang baik sebab menyangkut ADT Garis. */
   /* Tuliskan spec fungsi yang lebih tepat. */
   return (sqrt(pow((ROW_POSISI(P1)-ROW_POSISI(P2)),2)+pow((COL_POSISI(P2)-COL_POSISI(P2)),2)));
}

void Geser (Posisi *P, int deltaX, int deltaY){
/* I.S. P terdefinisi */
/* F.S. P digeser, ROWnya sebesar deltaX dan COLnya sebesar deltaY */
   ROW_POSISI(*P) += deltaX;
   COL_POSISI(*P) += deltaY;
}

void DisplayPosisi(Posisi p){
/* print "BNMO di posisi (x-1,y-1)" */
    printf("BNMO di posisi ");
    TulisPosisi(PlusDelta(p,-1,-1));
    printf("\n");
}

void DisplayPosisiV2(Posisi p){
/* print "BNMO di posisi (x-1,y-1)" */
   TulisPosisi(PlusDelta(p,-1,-1));
   printf("\n");
}

#endif