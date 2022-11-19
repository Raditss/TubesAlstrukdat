#include "simulator.h"

/* Driver untuk MOVE COMMAND */

int main(){
    Matrix peta = getPeta("../../bin/peta.txt");
    peta = createBorder(peta);

    Simulator sim;
    createSimulator(&sim, strToWord("Willy."), peta);

    TIME realTime;
    CreateTime(&realTime,0,0,0);

    while (true)
    {
        printf(">> ");
        STARTKALIMAT();
        moveCommandV2(&UserPeta(sim), &realTime, currentKalimat);
        TulisTIME(realTime);
        displayMatrix(UserPeta(sim));
    }
    

    return 0;
}