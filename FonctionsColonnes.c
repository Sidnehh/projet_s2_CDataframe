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

    // copie du titre dans l'espace alloué y compris '\0'
    strcpy(column->titre, titre);

    // initialisation des autres attributs de column
    column->tableau_data = NULL;
    column->taille_logique = 0;
    column->taille_physique = 0;
    // Initialisation des nouveaux attributs pour le tri
    column->index = NULL;
    column->valid_index = 0;
    column->sort_dir = 0;

    return column;
}

// 2- fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, int value)
{
    if (col==NULL)
    {
        return 0; // arrêt si col vaut NULL
    }
    // augmentation de la mémoire du tableau et donc de la taille physique du tableau si la taille logique et physique sont égales
    if (col->taille_physique == col->taille_logique)
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
    {
        col->tableau_data[col->taille_logique++] = value; // ajout de la valeur dans le tableau si pas de problème de place
    }

    return 1;

}
//3- fonction qui vide la colonne

void delete_column(COLUMN** col_ptr) {
    if (col_ptr && *col_ptr) {
        // Libérer la mémoire allouée
        free((*col_ptr)->titre);
        free((*col_ptr)->tableau_data);
        free(*col_ptr);
        *col_ptr = NULL;
    }
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

void fill_column(COLUMN* col)
{
    int i, n, temp;
    printf("Entrez le nombre de valeurs a insérer : \n");
    scanf("%d", &n);
    for(i=0; i<n;i++)
    {
        printf("Entrez la valeur %d :\n", i+1);
        scanf("%d", &temp);
        insert_value(col, temp);
    }
}



//PARTIE 5.1

//PARTIE 6
