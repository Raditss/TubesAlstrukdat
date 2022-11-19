#include<stdio.h>
#include<stdlib.h>
#ifndef SPLASH_H
#define SPLASH_H

void splash()
{
    FILE *fptr;
    fptr=fopen("../../bin/bmo.txt", "r");
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

#endif