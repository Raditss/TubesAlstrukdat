/* File : makanan.h */

#ifndef makanan_H
#define makanan_H

#include "time.h"
#include "wordmachine.h"
#include "stackint.h"

/* Definisi makanan: */
typedef struct {
    int id;
    Word nama;
    TIME expired;
    TIME deliveryTime;
    Word lokasiAksi; // lokasi dilakukannya aksi untuk mendapat makanan tsb.
} Makanan;

#define ID(M) (M).id
#define NAMA(M) (M).nama
#define EXP(M) (M).expired
#define DTIME(M) (M).deliveryTime
#define LOC(M) (M).lokasiAksi

int strToInt (Word kata){
    /* Mengembalikan bentuk integer dari kata */
    /* Prekondisi: kata merupakan string positif misal "16" */
    int hasil = 0;
    int val;
    int pengali = 1;
    Stack S;
    CreateEmpty(&S);
    for (int i = 0; i < kata.Length; i++){
        Push(&S, currentWord.TabWord[i] - 48);
    }
    while (!IsEmpty(S))
    {
        Pop(&S,&val);
        hasil += val * pengali;
        pengali *= 10;
    }
    return hasil;
}

Makanan createMakanan (char namaFile[]){
    STARTWORD(namaFile);
    Makanan m;
    int n = strToInt(currentWord);
    for (int i=0;i<n;i++){
        ADVWORD();
        ID(m) = strToInt(currentWord);
        ADVWORD();
        Word name = currentWord;
        while (!(isInt(currentWord))){
            pmergeword(&name,currentWord);
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
    }
    return m;
}

int getId (char namaFile[]){
    // Kamus
    int id;
    // Algoritma
    STARTWORD(namaFile);
    id=strToInt(currentWord);
    ADVWORD();
    while(!endWord){
        for(int i=0; i<currentWord.Length;i++){
            id = currentWord.TabWord[i];
        }
    ADVWORD();
    }
    return id;
}

Word getNama (char namaFile[]){
    // Kamus
    Word nama;
    // Algoritma
    STARTWORD(namaFile);
    while(!endWord){
        ADVWORD();
    }
    return nama;
}

TIME getExpired (char namaFile[]){
    // Kamus
    TIME expired;
    int h,j,m;
    // Algoritma
    STARTWORD(namaFile);
    h=strToInt(currentWord); /*simpan nilai hari*/
    ADVWORD();
    j=strToInt(currentWord); /*simpan nilai jam*/
    ADVWORD();
    m=strToInt(currentWord); /*simpan nilai menit*/
    ADVWORD();
    // Sudah dapat nilai hari jam dan menit dalam integer*/
    CreateTime(&expired,h,j,m);
    while (!endWord){
        Day(expired)=currentWord.TabWord[h];
        ADVWORD();
    }
    return expired;
}

TIME getDeliveryTime (char namaFile[]){
    // Kamus
    TIME deliveryTime;
    int h,j,m;
    // Algoritma
    STARTWORD(namaFile);
    h=strToInt(currentWord); /*simpan nilai hari*/
    ADVWORD();
    j=strToInt(currentWord); /*simpan nilai jam*/
    ADVWORD();
    m=strToInt(currentWord); /*simpan nilai menit*/
    ADVWORD();
    // Sudah dapat nilai hari jam dan menit*/
    CreateTime(&deliveryTime,h,j,m);
    while (!endWord){
        for(int i=0; i<currentWord.Length;i++){
            Day(deliveryTime)=currentWord.TabWord[h];
        }
    ADVWORD();
    }
    return deliveryTime;
} 

Word getLokasiAksi (char namaFile[]){
    // Kamus
    Word lokasiAksi;
    // Algoritma
    STARTWORD(namaFile);
    while(!endWord){
        ADVWORD();
    }
    return lokasiAksi;
}

#endif