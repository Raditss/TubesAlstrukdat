#include "../header/listStatikFood.h"

/* Driver untuk listStatikFood.h untuk pembacaan dan penyimpanan file*/

int main(){
    ListStatik DaftarMenu = readFileMakananListStatik("../../bin/menumakanan.txt");
    // printListStatikFood(DaftarMenu);
    ListStatik buyAbleFood = isBuyAble(DaftarMenu);
    printListStatikFood(buyAbleFood);
    return 0;
}