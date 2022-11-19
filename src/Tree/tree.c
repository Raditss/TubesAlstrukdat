#include "tree.h"

int main(){
    KumpulanTree KT;
    createKumpulanTree(&KT);
    printf("1. TULISAN INI HARUS TERLIHAT\n");

    resepReader(&KT, "../../bin/resepmakanan.txt"); /* Baca file */
    printf("\t--- %d ---\n", INFO_TREE(SIBLING(CHILD(ELMT_TREE(KT,29)))));

    KumpulanTree AdvancedTree;
    createKumpulanTree(&AdvancedTree);
    AdvancedTree = mergeAdvancedTree(KT);

    printf("2. TULISAN INI HARUS TERLIHAT\n");

    printf("\tID pertama makanan yang menjadi parental:\n");
    printf("\t--- %d ---\n", INFO_TREE(ELMT_TREE(AdvancedTree,0)));

    printf("3. TULISAN INI HARUS TERLIHAT\n");

    printf("\tID kedua makanan yang menjadi parental:\n");
    printf("\t--- %d ---\n", INFO_TREE(ELMT_TREE(AdvancedTree,1)));

    printf("4. TULISAN INI HARUS TERLIHAT\n");

    printf("\tID ketiga makanan yang menjadi parental:\n");
    printf("\t--- %d ---\n", INFO_TREE(ELMT_TREE(AdvancedTree,2)));

    printf("5. TULISAN INI HARUS TERLIHAT\n");

    printf("\tAnakan parental ketiga: \n");
    printf("\t--- %d ---\n", INFO_TREE(CHILD(CHILD(ELMT_TREE(AdvancedTree,2)))));

    printf("6. TULISAN INI HARUS TERLIHAT\n");

    printf("\tJumlah resep adalah = %d\n", lengthKumpulanTree(KT));
    printf("\tJumlah resep utama adalah = %d\n", lengthKumpulanTree(AdvancedTree));

    printf("7. TULISAN INI HARUS TERLIHAT\n");

    for (int i = 0; i < 11; i++){
        printf("\tTree ke %d adalah %d\n", i+1,INFO_TREE(ELMT_TREE(AdvancedTree,i)));
    }

    printf("8. TULISAN INI HARUS TERLIHAT\n");

    printf("\t5 tingkat di bawah id 43 adalah %d\n", INFO_TREE(
                                                        CHILD( // anaknya dari
                                                        CHILD( // anaknya dari
                                                        CHILD( // anaknya dari
                                                        SIBLING(CHILD( // saudara dari anaknya dari
                                                        CHILD( // anaknya bapak
                                                            ELMT_TREE(AdvancedTree,6)))))))));

    printf("9. TULISAN INI HARUS TERLIHAT\n");

    Address p = getTree(18, KT);
    printf("\tinfonya adalah: %d\n\tanaknya adalah: %d\n", INFO_TREE(p), INFO_TREE(CHILD(p)));
    
    printf("10. TULISAN INI HARUS TERLIHAT\n");
    return 0;
}