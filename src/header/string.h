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

boolean isInt (Word currentWord){
    /* Mengembalikan true jika kata berupa integer */
    for (int i = 0; i < currentWord.Length; i++){
        if (currentWord.TabWord[i] < 48 || currentWord.TabWord[i] > 57){
            return 0;
        }
    }
    return 1;
}

Word mergeWord (Word kata1, Word kata2){
    /* Menggabungkan kata1 dan kata2 yang dipisahkan oleh spasi menjadi kata3 */
    /* Mengembalikan kata3 */
    Word kata3 = kata1;

    Len(kata3)++;
    HurufKe(kata3,Len(kata3)-1) = BLANK;
    for (int j = 0; j < kata2.Length; j++){
        Len(kata3)++;
        HurufKe(kata3,Len(kata3)-1) = kata2.TabWord[j];
    }
    return kata3;
}

void pMergeWord (Word *kata1, Word kata2){
    /* I.S. kata1 sembarang */
    /* F.S. kata1 dimerge dengan kata2 dan dipisahkan oleh spasi */
    Len(*kata1)++;
    HurufKe(*kata1 , Len(*kata1) - 1) = BLANK;

    for (int i = 0; i < Len(kata2); i++){
        Len(*kata1)++;
        HurufKe(*kata1 , Len(*kata1) - 1) = HurufKe(kata2,i);
    }
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

Word strToWord (char s[]){
    /* Mengubah string s menjadi word */
    Word kata;
    createEmptyWord(&kata);
    int i = 0;
    while (s[i] != MARK)
    {
        Len(kata)++;
        HurufKe(kata, i) = s[i];
        i++;
    }
    return kata;
}

const char * wordToStr(Word kata){
    /* Mengubah Word menjadi string */
    // char str[Len(kata)];
    // for (int i = 0; i < Len(kata); i++){
    //     str[i] = HurufKe(kata, i);
    // }
    char * str = kata.TabWord;
    return str;
}

boolean isWordEqual(Word kata1, Word kata2){
    /* Mengembalikan true jika kedua kata sama */
    if (Len(kata1) != Len(kata2)){
        return false;
    }
    for (int i = 0; i < Len(kata1); i++){
        if (HurufKe(kata1,i) != HurufKe(kata2,i)){
            return false;
        }
    }
    return true;
}

#endif