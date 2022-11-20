
#ifndef __MESIN_KALIMAT_H__
#define __MESIN_KALIMAT_H_

#include "../WordMachine/wordmachine.h"
#define maxKalimat 1000

typedef struct
{
    char TabKalimat[maxKalimat];
    int LengthKalimat;
} Kalimat;

static boolean endKalimat;
static Kalimat currentKalimat;

void CopyKalimat();
void STARTKALIMAT(){
    /* Menginput kalimat dari keyboard */
    STARTINPUT();
    IgnoreBlanks();
    if (currentChar == ENTER){
        endKalimat = true;
    } else {
        endKalimat = false;
        CopyKalimat();
    }
}

void CopyKalimat(){
    /* Akuisisi kalimat */
    int i = 0;
    while ((currentChar != ENTER) && (i < maxKalimat) && (currentChar != MARK))
    {
        currentKalimat.TabKalimat[i] = currentChar;
        ADV();
        i++;
    }
    currentKalimat.LengthKalimat = i;
    
}

void DisplayKalimat(Kalimat currentKalimats){
    /* Display kalimat ke layar */
    // printf("%s\n",currentKalimats.TabKalimat);
    for (int i = 0; i < currentKalimats.LengthKalimat; i++){
        printf("%c",currentKalimats.TabKalimat[i]);
    }
    printf("\n");   
}

boolean isKalimatEqual(Kalimat k1, Kalimat k2){
    /* Mengembalikan true jika k1 dan k2 sama */
    if (k1.LengthKalimat != k2.LengthKalimat){
        return false;
    }
    for (int i = 0; i < k1.LengthKalimat; i++){
        if (k1.TabKalimat[i] != k2.TabKalimat[i]){
            return false;
        }
    }
    return true;
}

Word kalimatToWord(Kalimat k){
    /* Mengubak bentukan kalimat menjadi word */
    Word hasil;
    hasil.Length = k.LengthKalimat;
    for (int i = 0; i < k.LengthKalimat; i++){
        hasil.TabWord[i] = k.TabKalimat[i];
    }
    return hasil;
}

Kalimat wordToKalimat(Word w){
    /* Mengubah bentukan word menjadi kalimat */
    Kalimat hasil;
    hasil.LengthKalimat = w.Length;
    for (int i = 0; i < w.Length; i++){
        hasil.TabKalimat[i] = w.TabWord[i];
    }
    return hasil;
}

#endif