#include <stdio.h>
#include "../header/wait.h"

int main(){
    TIME T1;
    printf("BACA TIME\n");
    BacaTIME(&T1);
    
    printf("TULIS TIME\n");
    printf("T1 = ");
    TulisTIME(T1);

    WAIT(&T1, 60, 30);
    TulisTIME(T1);

    return 0;
}