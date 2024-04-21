#include "FonctionsCDataFrame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        scanf("%d", &n);
        for(j=0;j<n;j++)
        {
            printf("Entrez valeur %d à insérer de la colonne %s : \n", j+1, cdf[i]->titre);
            scanf(" %d", &temp);
            insert_value(cdf[i], temp);
        }
    }
}
int maxcol_cdataframe(COLUMN** cdf, int TL)
{
    int i, nmax=0;
    for(i=0; i<TL; i++)
    {
        if(cdf[i]->taille_logique>nmax)
            nmax=cdf[i]->taille_logique;
    }
    return nmax;
}

void print_cdataframe(COLUMN** cdf, int TL)
{
    int i,j, nmax = maxcol_cdataframe(cdf, TL);
    char gap = 32;
    for(i=0;i<TL;i++)
    {
        printf("| %s | \t",cdf[i]->titre);
    }
    printf("\n");
    for(i=0; i<nmax; i++)
    {
        for(j=0; j<TL; j++)
        {
            if((cdf[j]->taille_logique)>i)
                printf("| %*d%*c |\t", strlen(cdf[j]->titre)/2, cdf[j]->tableau_data[i], strlen(cdf[j]->titre)/2, gap);
            else
                printf("|  %*c  |\t", strlen(cdf[j]->titre)-2, gap);
        }
        printf("\n");
    }
}

void print_lines_cdataframe(COLUMN** cdf, int TL, int nlines)
{
    int i,j;
    char gap = 32;
    for(i=0;i<TL;i++)
    {
        printf("| %s | \t",cdf[i]->titre);
    }
    printf("\n");
    for(i=0; i<nlines; i++)
    {
        for(j=0; j<TL; j++)
        {
            if((cdf[j]->taille_logique)>i)
                printf("| %*d%*c |\t", strlen(cdf[j]->titre)/2, cdf[j]->tableau_data[i], strlen(cdf[j]->titre)/2, gap);
            else
                printf("|  %*c  |\t", strlen(cdf[j]->titre)-2, gap);
        }
        printf("\n");
    }
}

void print_columns_cdataframe(COLUMN** cdf, int TL, int ncol)
{
    int i,j, nmax = maxcol_cdataframe(cdf, ncol);
    char gap = 32;
    for(i=0;i<ncol;i++)
    {
        printf("| %s | \t",cdf[i]->titre);
    }
    printf("\n");
    for(i=0; i<nmax; i++)
    {
        for(j=0; j<ncol; j++)
        {
            if((cdf[j]->taille_logique)>i)
                printf("| %*d%*c |\t", strlen(cdf[j]->titre)/2, cdf[j]->tableau_data[i], strlen(cdf[j]->titre)/2, gap);
            else
                printf("|  %*c  |\t", strlen(cdf[j]->titre)-2, gap);
        }
        printf("\n");
    }
}

void add_col_cdataframe(COLUMN** cdf, int TL, COLUMN* col)
{
    cdf = realloc(cdf, TL++);
    if(cdf == NULL)
    {
        free(cdf);
    }
    cdf[TL] = col;
}

void add_line_cdataframe(COLUMN** cdf, int TL)
{
    int i;
    for(i=0;i<TL;i++)
    {
        cdf[i]->taille_physique++;
    }
}


void delete_column_cdf(COLUMN*** cdataframe, int* TL, int index) {
    if (cdataframe == NULL || *cdataframe == NULL || index < 0 || index >= *TL) {
        printf("Erreur: index invalide ou CDataframe non initialisé.\n");
        exit(EXIT_FAILURE);
    }
    // Libére la mémoire de la colonne à l'index spécifié
    delete_column(&((*cdataframe)[index]));
    // Décale les colonnes restantes vers la gauche pour remplir l'espace laissé par la suppression
    for (int i = index; i < (*TL) - 1; i++) {
        (*cdataframe)[i] = (*cdataframe)[i + 1];
    }
    // Réduit le nombre de colonnes
    (*TL)--;
    (*cdataframe)[*TL] = NULL;
}


