#include "FonctionsColonnes.h"
#include <stdio.h>
#include <stdlib.h>
#define REALOC_SIZE 256

//PARTIE SABRINA

//PARTIE SIDNEY

void Print_col(struct COLUMN* col)
{
    int i;
    for(i=0; i<col->TL; i++)
    {
        printf("[%d] %d", i, col->T[i]);
    }
    printf("\n");
}

int Frequency(struct COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->TL; i++)
    {
        sum += (col->T[i] == val);
    }
    return sum;
}

int Val_From_Id(struct COLUMN* col, int id)
{
    return col->T[id];
}

int Nb_Superior(struct COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->TL; i++)
    {
        sum += (col->T[i] > val);
    }
    return sum;
}

int Nb_Inferior(struct COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->TL; i++)
    {
        sum += (col->T[i] < val);
    }
    return sum;
}