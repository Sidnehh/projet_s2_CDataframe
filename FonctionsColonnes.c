#include "FonctionsColonnes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REALOC_SIZE 256

// 1 - fonction qui crée une colonne vide

COLUMN *create_column(char* titre)
{
    int longueur_titre = strlen(titre);

    //allocation de mémoire pour la structure COLUMN
    COLUMN *column = (COLUMN *) malloc(sizeof(COLUMN));
    if (column == NULL) //si l'allocation échoue
    {
        free(column);
        return NULL;
    }

    column->titre = (char *) malloc(longueur_titre + 1); //alloue le titre de la structure
    if (column->titre == NULL) // si l'allocation échoue
    {
        free(column);
        return NULL;
    }

    // copie du titre dans l'espaace alloué y compris '\0'
    strcpy(column->titre, titre);

    // initialisation des autres attributs de column
    column->tableau_data = NULL;
    column->taille_logique = 0;
    column->taille_physique = 0;

    return column;
}

// 2- fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, int value)
{
    if (col==NULL)
        return 0; // arrêt si col vaut NULL
    // augmentation de la mémoire du tableau et donc de la taille physique du tableau si la taille logique et physique sont égales
    if (col->taille_physique== col->taille_logique)
    {
        int nouvelle_taille_physique = col->taille_physique + REALOC_SIZE;
        int * temp = (int *) realloc(col->tableau_data, nouvelle_taille_physique); // variable temporaire pour éviter de perdre les données en cas de problème avec realloc
        if (temp==NULL)
            return 0;

        col->tableau_data = temp;
        col->taille_physique = nouvelle_taille_physique; // changement de taille physique
        col->tableau_data[col->taille_logique++] = value; // ajout de la valeur dans le tableau
    }
    else
        col->tableau_data[col->taille_logique++] = value; // ajout de la valeur dans le tableau si pas de problème de place

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