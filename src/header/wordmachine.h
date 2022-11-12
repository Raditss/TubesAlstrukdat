/* File: wordmachine.h */
/* Definisi Word Machine: Model Akuisisi Versi I */

#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "charmachine.h"
#include "stackint.h"

#define NMax 50
#define BLANK ' '
#define ENTER '\n'

typedef struct
{
   char TabWord[NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
   int Length;
} Word;

#define Len(w) (w).Length
#define HurufKe(w,i) (w).TabWord[i]

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

void STARTWORDINPUT(){
/* I.S. : currentChar sembarang
   F.S. : endWord = true, dan currentChar = MARK;
          atau endWord = false, currentWord adalah kata yang sudah diakuisisi,
          currentChar karakter pertama sesudah karakter terakhir kata */
    STARTINPUT();
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

void DisplayWordNoEnter(Word currentWord){
    /* Melakukan print terhadap current word */
    for (int i = 0; i < currentWord.Length; i++){
        printf("%c",currentWord.TabWord[i]);
    }
}

void createEmptyWord(Word *kata){
    /* I.S. currentWord sembarang */
    /* F.S. currentWord memiliki length 0 */
    Len(*kata) = 0;
}

Word strToWord (char s[]){
    /* Mengubah string s menjadi word */
    /* string harus diakhiri dengan MARK */
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

char * wordToStr(Word kata){
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