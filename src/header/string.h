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

Matrix getPeta (char namaFile[]){
    /* Membaca file peta.txt untuk mendapatkan peta */
    Matrix peta;
    Stack Sm, Sn;
    int m = 0;
    int n = 0;
    int val;
    int pengali = 1;
    CreateEmpty(&Sm);
    CreateEmpty(&Sn);
    STARTWORD(namaFile);

    for (int i = 0; i < currentWord.Length; i++){
        // Untuk mendapatkan dimensi m matrix
        Push(&Sm, currentWord.TabWord[i] - 48);
    }

    while (!IsEmpty(Sm)){
        Pop(&Sm, &val);
        m += val * pengali;
        pengali *= 10;
    }

    ADVWORD();
    // Saat ini telah didapat jumlah baris matrix

    for (int i = 0; i < currentWord.Length; i++){
        // Untuk mendapatkan dimensi m matrix
        Push(&Sn, currentWord.TabWord[i] - 48);
    }

    pengali = 1;
    while (!IsEmpty(Sn)){
        Pop(&Sn, &val);
        n += val * pengali;
        pengali *= 10;
    }

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