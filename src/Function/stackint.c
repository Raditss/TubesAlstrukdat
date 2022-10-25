#include "../header/stackint.h"

/* Driver untuk stackint.h */

int main(){
    
    printf("================================================\n");

    printf("Nilai Nil adalah: %d\n", Nil);
    printf("Nilai MaxEl adalah: %d\n", MaxEl);
    Stack S;
    CreateEmpty (&S);
    printf("Saat ini S memiliki index top %d\n", Top(S));
    if (IsEmpty(S)){
        printf("Saat ini S kosong\n");
    } else {
        printf("Saat ini S tidak Kosong");
    }

    printf("================================================\n");

    Push (&S, 5);
    printf("Saat ini S memiliki index top %d\n", Top(S));
    printf("Saat ini S memiliki nilai top %d\n", InfoTop(S));
    if (IsEmpty(S)){
        printf("Saat ini S kosong\n");
    } else {
        printf("Saat ini S tidak Kosong\n");
    }

    printf("================================================\n");

    infotype val;
    Pop (&S, &val);
    printf("Saat ini S memiliki index top %d\n", Top(S));
    printf("Nilai val yang di pop adalah %d\n", val);
    if (IsEmpty(S)){
        printf("Saat ini S kosong\n");
    } else {
        printf("Saat ini S tidak Kosong\n");
    }

    printf("================================================\n");
    
    for (int i = 0; i < MaxEl; i++){
        Push(&S,1);
    }
    printf("Saat ini S memiliki index top %d\n", Top(S));
    printf("Saat ini S memiliki nilai top %d\n", InfoTop(S));
    if (IsFull(S)){
        printf("Saat ini S full\n");
    } else {
        printf("Saat ini S tidak full\n");
    }

    printf("================================================\n");

    return 0;
}