#include "../header/boolean.h"

/* Driver untuk boolean.h */

int main() {
    
    printf("================================================\n");

    boolean uji01 = 1 == 1;
    boolean uji02 = 1 == 2;
    printf("Hasil benar untuk boolean langsung: %d\n", uji01);
    printf("Hasil salah untuk boolean langsung: %d\n", uji02);

    boolean uji03 = 0; //berarti false
    boolean uji04 = 1; //berarti true

    if (uji03){
        printf("Kalimat ini tidak akan keluar\n");
    }
    if (uji04){
        printf("Kalimat ini pasti keluar\n");
    }

    printf("================================================\n");

    return 0;
}