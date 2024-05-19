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
    column->type = type;

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
            col->tableau_data[col->taille_logique] = (int *) malloc(sizeof(int));
            *((int*)col->tableau_data[col->taille_logique]) = *((int*)value);
            break;

        case UINT:
            col->tableau_data[col->taille_logique] = (unsigned int *) malloc(sizeof(unsigned int));
            *((unsigned int*)col->tableau_data[col->taille_logique]) = *((unsigned int*)value);
            break;

        case CHAR:
            col->tableau_data[col->taille_logique] = (char *) malloc(sizeof(char));
            *((char*)col->tableau_data[col->taille_logique]) = *((char*)value);
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

        case NULLVAL: //to do
            break;

        default:
            printf("ça va pas \n");
            break;
    }
    col->taille_logique++;
    return 1;
}

void fill_column(COLUMN* col)
{
    int i, n;
    void* ptr = NULL;
    printf("Entrez le nombre de valeurs a inserer : \n");
    scanf(" %d", &n);
    for(i=0; i<n;i++)
    {
        printf("Valeur %d :\n", i);
        switch(col->type)
        {
            case UINT: //to do
                break;

            case INT:
            {
                int* temp = (int*) malloc(sizeof(int));
                scanf("  %d", temp);
                ptr = temp;
                break;
            }
            case CHAR:
            {
                char* temp = (char*) malloc(sizeof(char));
                scanf(" %c", temp);
                ptr = temp;
                break;
            }
            case FLOAT:
            {
                float* temp = (float*) malloc(sizeof(float));
                scanf(" %f", temp);
                ptr = temp;
                break;
            }
            case DOUBLE:
            {
                double* temp = (double*) malloc(sizeof(double));
                scanf(" %lf", temp);
                ptr = temp;
                break;
            }
            case STRING:
            {
                char** temp = (char**) malloc(sizeof(char**));
                scanf(" %s", *temp);
                ptr = &temp;
                break;
            }
            case STRUCTURE://to do
                break;

            case NULLVAL://to do
                break;
            default:
                printf("Error: Conversion Failed");
                break;
        }
        insert_value(col, ptr);
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

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)
{
    switch(col->type)
    {

        case INT:
            snprintf(str, size, "%d", *((int*)col->tableau_data[i]));
            break;
        case UINT:
            snprintf(str, size, "%d", *((unsigned int*)col->tableau_data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)col->tableau_data[i]));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)col->tableau_data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->tableau_data[i]));
            break;
        case STRING:
            break;
    }
}

void Print_col(COLUMN* col)
{
    int n = col->taille_logique;
    int i;
    printf("%s :\n", col->titre);
    for(i=0;i<n;i++)
    {
        char str[10];
        convert_value(col, i, str, col->taille_logique);
        printf("[%d] %s \n", i, str);
    }
}
//PARTIE 5.1

//PARTIE 6
