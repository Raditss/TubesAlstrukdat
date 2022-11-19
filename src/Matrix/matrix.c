#include "matrix.h"

/* Driver untuk matrix.h */

int main(){
    
    printf("================================================\n");

    printf("Nilai ROW_CAP adalah: %d\n", ROW_CAP);
    printf("Nilai COL_CAP adalah: %d\n", COL_CAP);
    Matrix m;
    createMatrix(3,3,&m);
    printf("Baris matrix m ada %d\n", ROW_EFF(m));
    printf("Kolom matrix m ada %d\n", COL_EFF(m));

    printf("================================================\n");

    printf("Silahkan coba input matrix dengan elemen char\n");
    readMatrixV1(&m,3,3);
    printf("Bentuk matrix sebelum diberi border adalah:\n");
    displayMatrix(m);
    printf("Bentuk matrix setelah diberi border adalah:\n");
    Matrix mNew = createBorder(m);
    displayMatrix(mNew);

    printf("================================================\n");

    Posisi p = getPosisi(mNew);
    printf("Posisi S dalam matrix adalah pada (%d,%d)\n", ROW_POSISI(p)-1,COL_POSISI(p)-1);
    isClose(m,'D') ? printf("S dekat dengan D\n") : printf("S tidak dekat dengan D\n");
    Word command;
    command.Length = 4;
    command.TabWord[0] = 'E';
    command.TabWord[1] = 'A';
    command.TabWord[2] = 'S';
    command.TabWord[3] = 'T';
    printf("Akan dilakukan MOVE EAST\n");
    moveCommand(&mNew,command);
    displayMatrix(mNew);

    printf("================================================\n");

    return 0;
}