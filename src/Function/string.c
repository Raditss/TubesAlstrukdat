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

    return 0;
}