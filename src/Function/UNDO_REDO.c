#include "../header/UNDO_REDO.h"

/* Driver untuk UNDO_REDO.h */

int main(){
    Matrix awal = getPeta("../../bin/peta.txt");
    awal = createBorder(awal);
    Simulator sim;
    createSimulator(&sim, strToWord("Willy."), awal);
    displayMatrix(awal);

    TIME realTime; 
    CreateTime(&realTime, 0,0,0);

    PrioQueueTime delivery;
    MakeEmptyFood(&delivery, MaxUNDO);

    UndoRedoType proses;
    createUndoRedoType(&proses, sim, realTime, delivery);

    Stack_Undo_Redo stack_UTAMA;
    Stack_Undo_Redo stack_redo;
    CreateEmptyUndoRedo(&stack_UTAMA);
    CreateEmptyUndoRedo(&stack_redo);

    if (IsEmptyUndoRedo(stack_UTAMA)){
        printf("Saat ini stack undo kosong\n");
    }
    if (IsEmptyUndoRedo(stack_redo)){
        printf("Saat ini stack redo kosong\n");
    }

    printf("%d\n", UNDO_REDO_TOP(stack_UTAMA));
    PushUndoRedo(&stack_UTAMA, proses);
    printf("===============================================\n");
    if (IsEmptyUndoRedo(stack_UTAMA)){
        printf("Saat ini stack undo kosong\n");
    }
    if (IsEmptyUndoRedo(stack_redo)){
        printf("Saat ini stack redo kosong\n");
    }
    printf("saat ini isi proses utama adalah %d\n", UNDO_REDO_TOP(stack_UTAMA) + 1);
    printf("===============================================\n");
    REDO(&stack_UTAMA, &stack_redo);
    printf("===============================================\n");
    UNDO(&stack_UTAMA, &stack_redo);
    printf("===============================================\n");
    REDO(&stack_UTAMA, &stack_redo);
    printf("===============================================\n");
    UNDO(&stack_UTAMA, &stack_redo);
    printf("===============================================\n");
    UNDO(&stack_UTAMA, &stack_redo);
    return 0;
}