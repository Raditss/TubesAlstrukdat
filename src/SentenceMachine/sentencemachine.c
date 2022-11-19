#include "../SentenceMachine/sentencemachine.h"

/* Driver untuk sentencemachine.h */

int main(){
    Kalimat tester1, tester2;

    printf("Masukkan sebuah kalimat: ");
    STARTKALIMAT();
    printf("Kalimat yang kamu masukkan adalah: ");
    tester1 = currentKalimat;
    DisplayKalimat(tester1);

    printf("Masukkan sebuah kalimat: ");
    STARTKALIMAT();
    tester2 = currentKalimat;
    printf("Kalimat yang kamu masukkan adalah: ");
    DisplayKalimat(tester2);

    if (isKalimatEqual(tester1,tester2)){
        printf("Kalimatnya sama\n");
    }

    printf("Masukkan sebuah kalimat: ");
    STARTKALIMAT();
    printf("Kalimat yang kamu masukkan adalah: ");
    DisplayKalimat(currentKalimat);
    if (isKalimatEqual(tester1,currentKalimat)){
        printf("Kalimat pertama dan sekarang sama\n");
    }

    printf("Masukkan sebuah kata: ");
    STARTWORDINPUT();
    Word tesWord = currentWord;

    Kalimat tesKalimat = wordToKalimat(tesWord);
    printf("\tKata setelah diubah menjadi kalimat menjadi: ");
    DisplayKalimat(tesKalimat);


    return 0;
}