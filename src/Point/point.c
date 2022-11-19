#include "../Matrix/matrix.h"
#include "../Point/point.h"

/* Driver untuk point.h */

int main(){
    Posisi A,B,C,D,E,F;
    CreatePosisi(&A,5,5);
    printf("Posisi A adalah: ");
    TulisPosisi(A); printf("\n");
    printf("Masukkan sebuah B(x,y): ");
    BacaPosisi(&B);
    DisplayPosisi(B);
    printf("Masukkan sebuah titik C(x,y): ");
    BacaPosisi(&C);
    EQ (B,C) ? printf("Titik B dan C sama\n") : printf("Titik B dan C tidak Sama\n");
    NEQ (B,C) ? printf("Titik B dan C tidak sama\n") : printf("Titik B dan C Sama\n");
    IsOrigin(B) ? printf("Titik B origin\n") : printf("Titik B tidak origin\n");
    IsOnSbX(B) ? printf("Absis B bernilai nol\n") : printf("Absis B tidak bernilai nol\n");
    IsOnSbY(B) ? printf("Ordinat B bernilai nol\n") : printf("Ordinat B tidak bernilai nol\n");
    printf("Next X dari B adalah: ");
    TulisPosisi(NextX(B)); 
    printf("\n");
    printf("Next Y dari B adalah: ");
    TulisPosisi(NextY(B));
    printf("\n");
    printf("Nilai C setelah ditambah (5,5) adalah: ");
    TulisPosisi(PlusDelta(C,5,5));
    printf("\n");
    printf("Mirror true dari C adalah: ");
    TulisPosisi(MirrorOf(C, true));
    printf("\n");
    printf("Mirror false dari C adalah: ");
    TulisPosisi(MirrorOf(C, false));
    printf("\n");
    printf("Jarak B dan C adalah: %.2f\n", Panjang(B,C));
    printf("Jarak 0 ke C adalah: %.2f\n", Jarak0(C));
    Geser(&C, 8, 8);
    printf("Titik C setelah digeser (8,8) dengan pointer menjadi: ");
    TulisPosisi(C);
    printf("\n");

    return 0;
}