/* File : makanan.h */

#ifndef makanan_H
#define makanan_H

#include "time.h"
#include "string.h"
#include "stackint.h"
#include "simulator.h"

PrioQueueTime createMakanan (char namaFile[]){
    PrioQueueTime Q;
    FoodType foodElmt;
    MakeEmptyFood(&Q, CAPACITY);
    STARTWORD(namaFile);
    Makanan m;
    int n = strToInt(currentWord);
    for (int i=0;i<n;i++){
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

        TIME_LEFT(foodElmt) = TIMEToMinute( EXP(m) );
        Info(foodElmt) = m;

        EnqueueFood(&Q, foodElmt);
    }
    return Q;
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