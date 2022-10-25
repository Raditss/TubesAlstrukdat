#include "../header/wordmachine.h"

/* Driver untuk wordmachine.h */

int main(){
    
    printf("================================================\n");

    printf("Nilai ASCII blank adalah: %d\n", BLANK);
    STARTWORD("../../bin/ujiWordMachine.txt");
    int i = 1;
    while (!endWord){
        printf("Kata ke %d: ",i);
        for (int i = 0; i < currentWord.Length; i++){
            printf("%c", currentWord.TabWord[i]);
        }
        printf("\n");
        i++;
        ADVWORD();
    }
    printf("================================================\n");

    printf("Untuk SaveWord kata akan disimpan dalam matrix baris tertentu\n");
    STARTWORD("../../bin/ujiCharMachine.txt");
    char tujuan[1][4];
    SaveWord(*tujuan, 0, currentWord);
    for (int j = 0; j < 4; j++){
        printf(" %c",tujuan[0][j]);
    }
    printf("\n");

    printf("================================================\n");

    return 0;
}