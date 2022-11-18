#include <stdlib.h>
#include <stdio.h>

void quit(){
    FILE *fptr;
    fptr=fopen("../../bin/bmobye.txt", "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }
    char filename[100], c;
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    }

    fclose(fptr);
}


