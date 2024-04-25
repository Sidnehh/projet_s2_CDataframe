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
    if (col->tableau_data == col->taille_physique)
    {
        if(col->taille_physique == 0)
        {

        }
        else
        {

        }
    }

    switch(col->type)
    {
        case INT:
            col.da
            break;
        case NULLVAL:
            break;
        case UINT:
            break;
        case CHAR:
            break;
        case FLOAT:
            break;
        case DOUBLE:
            break;
        case STRING:
            break;
        case STRUCTURE: //to do
            break;
    }

    return 1;

}
//3- fonction qui vide la colonne

void delete_column(COLUMN **col)
{
    if ((*col)->tableau_data != NULL) {
        free((*col)->tableau_data);
        (*col)->tableau_data = NULL;  // S'assurer de mettre le pointeur à NULL après la liberation
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
