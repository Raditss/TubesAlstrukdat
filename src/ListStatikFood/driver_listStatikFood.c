#include "listStatikFood.h"

/* Driver untuk listStatikFood.h */

int main(){
    ListStatik DaftarMenu = readFileMakananListStatik("../../bin/menumakanan.txt");
    CATALOG(DaftarMenu);
    return 0;
}