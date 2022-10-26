/* File: wordmachine.h */
/* Definisi Word Machine: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "charmachine.h"

#define NMax 50
#define BLANK ' '
#define ENTER '\n'

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

/* State Mesin Word */
static boolean endWord;
static Word currentWord;

void CopyWord();
void ADVWORD();

void IgnoreBlanks(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : currentChar sembarang
   F.S. : currentChar ≠ BLANK atau currentChar = MARK */
    while ((currentChar == BLANK) || (currentChar == ENTER)){
        ADV();
    }

}

void STARTWORD(char namaFile[]){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    START(namaFile);
    IgnoreBlanks();

    if (currentChar == MARK){ // marknya titik
        endWord = true;
    } else {
        endWord = false;
        CopyWord(); 
    }
}

void ADVWORD(){
/* I.S. : currentChar adalah karakter pertama kata yang akan diakuisisi
   F.S. : currentWord adalah kata terakhir yang sudah diakuisisi,
          currentChar adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika currentChar = MARK, endWord = true.
   Proses : Akuisisi kata menggunakan procedure SalinWord */
    IgnoreBlanks();
    if (currentChar == MARK){
        endWord = true;
    } else {
        CopyWord();
        IgnoreBlanks();
    }
}

void CopyWord(){
/* Mengakuisisi kata, menyimpan dalam currentWord
   I.S. : currentChar adalah karakter pertama dari kata
   F.S. : currentWord berisi kata yang sudah diakuisisi;
          currentChar = BLANK atau currentChar = MARK;
          currentChar adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i = 0;
    while ((currentChar != BLANK ) && (currentChar != MARK) && (i < NMax) && (currentChar != ENTER)){
        currentWord.TabWord[i] = currentChar;
        ADV();
        i++;
    }
    currentWord.Length = i;
}

void SaveWord(char *tujuan, int baris, Word asal){
    /* Menyimpan tabword asal ke tujuan */
    /* I.S. tujuan sembarang */
    /* F.S. tujuan berisi asal.tabword */
    for (int j = 0; j < asal.Length; j++){
        *((tujuan + baris*3) + j) = asal.TabWord[j];
    }
}

void DisplayWord(Word currentWord){
    /* Melakukan print terhadap current word */
    for (int i = 0; i < currentWord.Length; i++){
        printf("%c",currentWord.TabWord[i]);
    }
    printf("\n");
}

#endif