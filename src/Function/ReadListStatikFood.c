#include "../header/listStatikFood.h"

/* Driver untuk listStatikFood.h untuk pembacaan dan penyimpanan file*/

int main(){
    ListStatik DaftarMenu = readFileMakananListStatik("../../bin/menumakanan.txt");
    printListStatikFood(DaftarMenu);
    return 0;
}