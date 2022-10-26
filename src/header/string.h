#ifndef STRING_H
#define STRING_H

#include "wordmachine.h"
#include "matrix.h"
#include "stackint.h"

boolean cekSama (Word masukan, char pembanding[]){
    /* mengembalikan true jika masukan sama dengan string pembanding */
    for (int i = 0; i < masukan.Length; i++){
        if (masukan.TabWord[i] != pembanding[i]){
            return false;
        }
    }
    return true;
}

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

Matrix getPeta (char namaFile[]){
    /* Membaca file peta.txt untuk mendapatkan peta */
    Matrix peta;
    Stack Sm, Sn;
    int m;
    int n;
    
    STARTWORD(namaFile);

    m = strToInt(currentWord);

    ADVWORD();

    n = strToInt(currentWord);

    ADVWORD();
    // Saat ini telah didapat dimensi matrix yaitu m x n
    createMatrix(m,n,&peta);
    int i = 0;
    while (!endWord){
        for (int j = 0; j < n; j++){
            ELMT(peta,i,j) = currentWord.TabWord[j];
        }
        ADVWORD();
        i++;
    }

    return peta;
}


#endif