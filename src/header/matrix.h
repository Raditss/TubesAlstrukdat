#include "sentencemachine.h"
#include "point.h"
#include "time.h"

/* ********** Definisi TYPE Matrix dengan Index dan elemen CHAR ********** */

#ifndef MATRIX_H
#define MATRIX_H

/* Ukuran maksimum baris dan kolom */
#define ROW_CAP 100
#define COL_CAP 100

typedef int IdxType; /* Index baris, kolom */
typedef char ElType; /* Tipe elemen matrix char */

typedef struct
{
   ElType mem[ROW_CAP][COL_CAP];
   int rowEff; /* banyaknya/ukuran baris yg terdefinisi */
   int colEff; /* banyaknya/ukuran kolom yg terdefinisi */
} Matrix;
/* rowEff >= 1 dan colEff >= 1 */
/* Indeks matriks yang digunakan: [0..ROW_CAP-1][0..COL_CAP-1] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
#define ROW_EFF(M) (M).rowEff
#define COL_EFF(M) (M).colEff
#define ELMT(M, i, j) (M).mem[(i)][(j)]

boolean cekSama (Word masukan, char pembanding[]);

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk Matrix *** */
void createMatrix(int nRows, int nCols, Matrix *m)
{
    /* Membentuk sebuah Matrix "kosong" yang siap diisi berukuran nRow x nCol di "ujung kiri" memori */
    /* I.S. nRow dan nCol adalah valid untuk memori matriks yang dibuat */
    /* F.S. Matriks m sesuai dengan definisi di atas terbentuk */
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void readMatrixV1(Matrix *m, int nRow, int nCol)
{
    /* I.S. isIdxValid(nRow,nCol) */
    /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
    /* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    ElType X;
    createMatrix(nRow, nCol, m);
    for (IdxType i = 0; i < nRow; i++)
    {
        for (IdxType j = 0; j < nCol; j++)
        {
            while (true){
                scanf("%c", &ELMT(*m, i, j));
                if (ELMT(*m,i,j) != 10){
                    break;
                }
            }
        }
    }
}

void readMatrixV2(Matrix *m, int nRow, int nCol)
{
    /* I.S. isIdxValid(nRow,nCol) */
    /* F.S. m terdefinisi nilai elemen efektifnya, berukuran nRow x nCol */
    /* Proses: Melakukan CreateMatrix(m,nRow,nCol) dan mengisi nilai efektifnya */
    /* Selanjutnya membaca nilai elemen per baris dan kolom */
    ElType X;
    char baris[nCol];
    createMatrix(nRow, nCol, m);
    for (IdxType i = 0; i < nRow; i++)
    {
        scanf("%s",&baris);
        for (int j = 0; j < nCol; j++){
            ELMT(*m,i,j) = baris[j];
        }
    }
}

void displayMatrix(Matrix m)
{
    /* I.S. m terdefinisi */
    /* F.S. Nilai m(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
       dipisahkan sebuah spasi. Baris terakhir tidak diakhiri dengan newline */
    /* Proses: Menulis nilai setiap elemen m ke layar dengan traversal per baris dan per kolom */
    /* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
    1 2 3
    4 5 6
    8 9 10
    */
    for (IdxType i = 0; i < ROW_EFF(m); i++)
    {
        printf("%c", ELMT(m, i, 0));
        for (IdxType j = 1; j < COL_EFF(m); j++)
        {
            printf(" %c", ELMT(m, i, j));
        }
        printf("\n"); //diakhir line tetap ada enter, kalau gaada enter malah disalahin olympia
    }
}

Posisi getPosisi (Matrix M){
    /* Mencari posisi S, Matrix M sudah di createBorder */
    Posisi P;
    for (int i = 1; i < ROW_EFF(M) - 1; i++){
        for (int j = 0; j < COL_EFF(M) - 1; j++){
            if (ELMT(M,i,j) == 'S'){
                ROW_POSISI(P) = i;
                COL_POSISI(P) = j;
            }
        }
    }
    return P;
}

Matrix createBorder (Matrix M){
    /* Matrix sembarang */
    /* Matrix diberi border * dan mengubah '#' menjadi ' ' */
    Matrix mNew;
    int row = ROW_EFF(M) + 2;
    int col = COL_EFF(M) + 2;
    createMatrix(row,col,&mNew);

    for (IdxType i = 0; i < row; i++){
        ELMT(mNew,i,0) = '*';
        ELMT(mNew,0,i) = '*';
        ELMT(mNew,row-1,i) = '*';
        ELMT(mNew,i,col-1) = '*';
    }

    for (IdxType i = 1; i < row - 1; i++){
        for (IdxType j = 1; j < col - 1; j++){
            if (ELMT(M,i-1,j-1) == '#'){
                ELMT(mNew,i,j) = ' ';
            } else {
                ELMT(mNew,i,j) = ELMT(M,i-1,j-1);
            }
        }
    }
    return mNew;
}

boolean moveCommand (Matrix *M, Word command){
    /* I.S. command terdefinisi untuk move */
    /* F.S. jika move valid maka S akan bergeser sesuai arah command */
    boolean valid;
    Posisi P = getPosisi(*M);
    if (cekSama(command,"NORTH")){
        if (ELMT(*M, ROW_POSISI(P) - 1, COL_POSISI(P)) != ' '){
            printf("Gagal berpindah\n"); 
            valid = 0;
        } else {
            ELMT(*M, ROW_POSISI(P) - 1, COL_POSISI(P)) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            ROW_POSISI(P)--;
            valid = 1;
        }
    } else if (cekSama(command, "SOUTH")){
        if (ELMT(*M, ROW_POSISI(P) + 1, COL_POSISI(P)) != ' '){
            printf("Gagal berpindah\n");
            valid = 0;
        } else {
            ELMT(*M, ROW_POSISI(P) + 1, COL_POSISI(P)) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            ROW_POSISI(P)++;
            valid = 1;
        }
    } else if (cekSama(command, "EAST")){
        if (ELMT(*M, ROW_POSISI(P), COL_POSISI(P) + 1) != ' '){
            printf("Gagal berpindah\n");
            valid = 0;
        } else {
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P) + 1) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            COL_POSISI(P)++;
            valid = 1;
        }
    } else if (cekSama(command, "WEST")){
        if (ELMT(*M, ROW_POSISI(P), COL_POSISI(P) - 1) != ' '){
            printf("Gagal berpindah\n");
            valid = 0;
        } else {
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P) - 1) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            COL_POSISI(P)--;
            valid = 1;
        }
    } else {
        printf("Masukan tidak valid!\n");
        valid = 0;
    }
    DisplayPosisi(P);
    return valid;
}


void moveCommandV2 (Matrix *M, TIME *realTime, Kalimat perintah){
    /* I.S. Matrix sembarang */
    /* F.S. Jika move valid, S akan bergeser sesuai perintah */
    /*      Mirip seperti movecommand hanya saja perintah dalam bentuk kalimat */
    Kalimat north, south, east, west;
    Word tempNorth, tempSouth, tempEast, tempWest;
    tempNorth = strToWord("MOVE NORTH.");
    tempEast = strToWord("MOVE EAST.");
    tempSouth = strToWord("MOVE SOUTH.");
    tempWest = strToWord("MOVE WEST.");
    north = wordToKalimat(tempNorth);
    south = wordToKalimat(tempSouth);
    east = wordToKalimat(tempEast);
    west = wordToKalimat(tempWest);
    
    Posisi P = getPosisi(*M);
    if (isKalimatEqual(perintah,north)){
        if (ELMT(*M, ROW_POSISI(P) - 1, COL_POSISI(P)) != ' '){
            printf("Gagal berpindah\n");
        } else {
            ELMT(*M, ROW_POSISI(P) - 1, COL_POSISI(P)) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            ROW_POSISI(P)--;
            *realTime = NextMinute(*realTime);
        }
    } else if (isKalimatEqual(perintah,south)){
        if (ELMT(*M, ROW_POSISI(P) + 1, COL_POSISI(P)) != ' '){
            printf("Gagal berpindah\n");
        } else {
            ELMT(*M, ROW_POSISI(P) + 1, COL_POSISI(P)) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            ROW_POSISI(P)++;
            *realTime = NextMinute(*realTime);
        }
    } else if (isKalimatEqual(perintah,east)){
        if (ELMT(*M, ROW_POSISI(P), COL_POSISI(P) + 1) != ' '){
            printf("Gagal berpindah\n");
        } else {
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P) + 1) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            COL_POSISI(P)++;
            *realTime = NextMinute(*realTime);
        }
    } else if (isKalimatEqual(perintah,west)){
        if (ELMT(*M, ROW_POSISI(P), COL_POSISI(P) - 1) != ' '){
            printf("Gagal berpindah\n");
        } else {
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P) - 1) = 'S';
            ELMT(*M, ROW_POSISI(P), COL_POSISI(P)) = ' ';
            COL_POSISI(P)--;
            *realTime = NextMinute(*realTime);
        }
    } else {
        printf("Masukan tidak valid!\n");
    }
    DisplayPosisi(P);
}

boolean isClose (Matrix M, char c){
    /* Menerima matrix lalu mengecek apakah S dekat dengan c */
    /* Mengembalikan true jika S tepat di kanan/kiri/atas/bawah c */
    /* Dapat digunakan saat ingin melakukan sesuatu di tempat tertentu */
    Posisi pos = getPosisi(M);
    int x = ROW_POSISI(pos);
    int y = COL_POSISI(pos);
    return (ELMT(M,x,y+1) == c) ||
           (ELMT(M,x+1,y) == c) ||
           (ELMT(M,x,y-1) == c) ||
           (ELMT(M,x-1,y) == c);
}

Matrix getPeta (char namaFile[]){
    /* Membaca file peta.txt untuk mendapatkan peta */
    Matrix peta;
    Stack Sm, Sn;
    int m;
    int n;

    STARTWORD(namaFile);

    m = strToInt(currentWord);

    ADVWORD();

    n = strToInt(currentWord);

    ADVWORD();
    // Saat ini telah didapat dimensi matrix yaitu m x n
    createMatrix(m,n,&peta);
    int i = 0;
    while (!endWord){
        for (int j = 0; j < n; j++){
            ELMT(peta,i,j) = currentWord.TabWord[j];
        }
        ADVWORD();
        i++;
    }

    return peta;
}

#endif