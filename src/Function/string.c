#include "../header/string.h"

/* Driver untuk string.h */

int main(){

    printf("================================================\n");
    
    STARTWORD("../../bin/ujiCharMachine.txt");
    boolean sama = cekSama(currentWord, "halo");
    sama ? printf("Maka isi file adalah -halo-\n") : printf("Maka isi file bukan -halo-");
    Matrix peta = getPeta("../../bin/peta.txt");
    Matrix newPeta = createBorder(peta);
    printf("Peta yang didapatkan adalah sebagai berikut: \n");
    displayMatrix(peta);

    printf("================================================\n");
    printf("Peta yang terbentuk adalah sebagai berikut: \n");
    displayMatrix(newPeta);

    printf("================================================\n");

    printf("Masukkan SATU kata untuk pengecekan strToInt: ");
    STARTWORDINPUT();

    isInt(currentWord) ?
        printf("Kata merupakan angka bernilai %d\n", strToInt(currentWord)) :
        printf("Kata bukanlah sebuah angka\n");


    printf("Masukkan 2 kata untuk digabung: ");
    ADVWORD();

    Word gabungan;
    createEmptyWord(&gabungan);

    pMergeWord(&gabungan, currentWord); //dengan pointer

    ADVWORD();

    gabungan = mergeWord(gabungan, currentWord); // tanpa pointer

    printf("Gabungan katanya adalah:");
    DisplayWord(gabungan);
    printf("================================================\n");
    return 0;
}