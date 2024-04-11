#include "FonctionsCDataFrame.h"
#include <stdio.h>
#include <stdlib.h>

COLUMN** create_empty_cdataframe(int TL)
{
    int i;
    char temp[50];
    COLUMN**cdf = malloc(TL*sizeof(COLUMN*));
    for(i=0;i<TL;i++)
    {
        printf("Entrez titre de la colonne %d : \n", i+1);
        scanf("%s", temp);
        cdf[i] = create_column(temp);
    }
    if(cdf==NULL) // Si l'allocation échoue
    {
        free(cdf);
        return NULL;
    }
    return cdf;
}

void fill_cdataframe(COLUMN** cdf, int TL)
{
    int i, j, n, temp;
    for(i=0;i<TL;i++)
    {
        printf("Colonne : %s \n", cdf[i]->titre);
        printf("Entrez nombre de valeurs à insérer : \n");
        scanf("%d", &cdf[i]->taille_logique);
        for(j=0;j<n;j++)
        {
            printf("Entrez valeur %d à insérer de la colonne %s : \n", j+1, cdf[i]->titre);
            scanf(" %d", &temp);
            insert_value(cdf[i], temp);
        }
    }
}