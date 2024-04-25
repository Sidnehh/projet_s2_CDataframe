#include "FonctionsColonnes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256

// 1 - fonction qui crée une colonne vide


COLUMN *create_column(ENUM_TYPE type, char* titre)
{
    int longueur_titre = strlen(titre);

    //allocation de mémoire pour la structure COLUMN
    COLUMN *column = (COLUMN *) malloc(sizeof(COLUMN));
    column->titre = (char *) malloc(longueur_titre + 1); //alloue le titre de la structure
    if (column->titre == NULL) // si l'allocation échoue
    {
        free(column);
        return NULL;
    }

    // copie du titre dans l'espace alloué y compris '\0'
    strcpy(column->titre, titre);

    // initialisation des autres attributs de column
    column->index = NULL;
    column->tableau_data = NULL;
    column->taille_logique = 0;
    column->taille_physique = 0;

    return column;
}

// 2- fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, void* value)
{
    if (col==NULL)
    {
        return 0; // arrêt si col vaut NULL
    }
    if (col->taille_logique == col->taille_physique)
    {
        int nouvelle_taille = REALOC_SIZE+col->taille_physique;
        COL_TYPE** temp;
        if(col->taille_physique == 0)
        {
            temp = malloc(nouvelle_taille);
        }
        else
        {
            temp = realloc(col->tableau_data, nouvelle_taille);
        }

        if(temp == NULL)
        {
            free(temp);
            return 0;
        }
        col->tableau_data = temp;
    }
    switch(col->type)
    {
        case INT:
            printf("int");
            col->tableau_data[col->taille_logique] = (int *) malloc(sizeof(int));
            *((int*)col->tableau_data[col->taille_logique]) = *((int*)value);
            break;
        case NULLVAL: //to do
            break;
        case UINT:
            col->tableau_data[col->taille_logique] = (unsigned int *) malloc(sizeof(unsigned int));
            *((unsigned int*)col->tableau_data[col->taille_logique]) = *((unsigned int*)value);
            break;
        case CHAR:
            printf("char");
            col->tableau_data[col->taille_logique] = (int *) malloc(sizeof(int));
            *((int*)col->tableau_data[col->taille_logique]) = *((int*)value);
            break;
        case FLOAT:
            col->tableau_data[col->taille_logique] = (float *) malloc(sizeof(float));
            *((float*)col->tableau_data[col->taille_logique]) = *((float*)value);
            break;
        case DOUBLE:
            col->tableau_data[col->taille_logique] = (double *) malloc(sizeof(double));
            *((double*)col->tableau_data[col->taille_logique]) = *((double*)value);
            break;
        case STRING:
            col->tableau_data[col->taille_logique] = (char **) malloc(sizeof(char*));
            *((char**)col->tableau_data[col->taille_logique]) = *((char**)value);
            break;
        case STRUCTURE: //to do
            break;
    }
    col->taille_logique++;

    return 1;
}

void fill_column(COLUMN* col)
{
    int i, n, temp;
    printf("Entrez le nombre de valeurs a insérer : \n");
    scanf("%d", &n);
    for(i=0; i<n;i++)
    {
        printf("Entrez la valeur %d :\n", i+1);
        scanf("%d", &temp);
        insert_value(col, &temp);
    }
}

//3- fonction qui vide la colonne

void delete_column(COLUMN **col)
{
    if ((*col)->tableau_data != NULL)
    {
        free((*col)->tableau_data);
        (*col)->tableau_data = NULL;  // S'assurer de mettre le pointeur à NULL après la liberation
    }
    if((*col)->index != NULL)
    {
        free((*col)->index);
        (*col)->index = NULL;
    }

    // Libère la structure de la colonne elle-même.
    free(*col);
    *col = NULL;  // Mettre le pointeur sur la colonne à NULL
}

void Print_col(COLUMN* col)
{
    int i;
    for(i=0; i<col->taille_logique; i++)
    {
        printf("[%d] %d", i, col->tableau_data[i]);
    }
    printf("\n");
}

int Frequency(COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->taille_logique; i++)
    {
        sum += (col->tableau_data[i] == val);
    }
    return sum;
}

int Val_From_Id(COLUMN* col, int id)
{
    return col->tableau_data[id];
}

int Nb_Superior(COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->taille_logique; i++)
    {
        sum += (col->tableau_data[i] > val);
    }
    return sum;
}

int Nb_Inferior(COLUMN* col, int val)
{
    int i, sum=0;
    for(i=0; i<col->taille_logique; i++)
    {
        sum += (col->tableau_data[i] < val);
    }
    return sum;
}

//PARTIE 5.1

//PARTIE 6
