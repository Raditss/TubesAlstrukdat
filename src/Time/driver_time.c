#include <stdio.h>
#include "../header/time.h"

int main(){
    TIME T1, T2;
    printf("BACA TIME\n");
    BacaTIME(&T1);
    BacaTIME(&T2);

    // TULIS TIME
    printf("TULIS TIME\n");
    printf("T1 = ");
    TulisTIME(T1);
    printf("\nT2 = ");
    TulisTIME(T2);
    printf("\n");

    // TIME TO Menit
    printf("TIME TO MENIT\n");
    printf("T1 = %ld menit\n",TIMEToMinute(T1));
    printf("T2 = %ld menit\n",TIMEToMinute(T2));

    // MENIT TO TIME
    printf("MENIT TO TIME\n");
    printf("T1 = ");
    TulisTIME(MinuteToTIME(TIMEToMinute(T1)));
    printf("\nT2 = ");
    TulisTIME(MinuteToTIME(TIMEToMinute(T2)));
    printf("\n");

    // TEQ
    printf("TEQ\n");
    if(TEQ(T1,T2)){
        printf("T1 = T2\n");
    }else{
        printf("T1 != T2\n");
    }

    // TNEQ
    printf("TNEQ\n");
    if(TNEQ(T1,T2)){
        printf("T1 != T2\n");
    }else{
        printf("T1 = T2\n");
    }

    // TLT
    printf("TLT\n");
    if(TLT(T1,T2)){
        printf("T1 < T2\n");
    }else{
        printf("T1 >= T2\n");
    }

    // TGT
    printf("TGT\n");
    if(TGT(T1,T2)){
        printf("T1 > T2\n");
    }else{
        printf("T1 <= T2\n");
    }


    // NextMinute
    printf("NextMinute\n");
    printf("T1 = ");
    TulisTIME(NextMinute(T1));
    printf("\nT2 = ");
    TulisTIME(NextMinute(T2));
    printf("\n");

    // NextNMinute
    printf("NextNMinute\n");
    printf("T1 = ");
    TulisTIME(NextNMinute(T1,10));
    printf("\nT2 = ");
    TulisTIME(NextNMinute(T2,10));
    printf("\n");

    // PrevMinute
    printf("PrevMinute\n");
    printf("T1 = ");
    TulisTIME(PrevMinute(T1));
    printf("\nT2 = ");
    TulisTIME(PrevMinute(T2));
    printf("\n");

    // PrevNMinute
    printf("PrevNMinute\n");
    printf("T1 = ");
    TulisTIME(PrevNMinute(T1,10));
    printf("\nT2 = ");
    TulisTIME(PrevNMinute(T2,10));
    printf("\n");

    // Durasi
    printf("Durasi\n");
    printf("T1-T2 = %ld menit\n",Durasi(T1,T2));
    printf("T2-T1 = %ld menit\n",Durasi(T2,T1));

    return 0;

}
