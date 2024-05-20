#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FonctionsColonnes.h"
#define REALOC_SIZE 256

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)
{
    switch(col->type)
    {

        case INT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        case UINT:
            snprintf(str, size, "%d", *((unsigned int*)col->data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)col->data[i]));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float*)col->data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double*)col->data[i]));
            break;
        case STRING:
            break;
    }
}

void print_col(COLUMN* col)
{
    int n = col->taille_logique;
    int i;
    printf("%s :\n", col->titre);
    if(col->type != STRING)
    {
        for(i=0;i<n;i++)
        {
            char str[10];
            convert_value(col, i, str, 50);
            printf("[%d] %s \n", i, str);
        }
    }
    else
    {
        for(i=0;i<n;i++)
        {
            printf("%s\n", col->data[i]);
        }
    }
}

int insert_value(COLUMN* col, void* value)
{
    if (col==NULL)
    {
        return 0;
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
            temp = realloc(col->data, nouvelle_taille);
        }

        if(temp == NULL)
        {
            free(temp);
            return 0;
        }
        col->data = temp;
    }

    switch(col->type)
    {
        case INT:
            col->data[col->taille_logique] = (int *) malloc(sizeof(int));
            *((int*)col->data[col->taille_logique]) = *((int*)value);
            break;

        case UINT:
            col->data[col->taille_logique] = (unsigned int *) malloc(sizeof(unsigned int));
            *((unsigned int*)col->data[col->taille_logique]) = *((unsigned int*)value);
            break;

        case CHAR:
            col->data[col->taille_logique] = (char *) malloc(sizeof(char));
            *((char*)col->data[col->taille_logique]) = *((char*)value);
            break;

        case FLOAT:
            col->data[col->taille_logique] = (float *) malloc(sizeof(float));
            *((float*)col->data[col->taille_logique]) = *((float*)value);
            break;

        case DOUBLE:
            col->data[col->taille_logique] = (double *) malloc(sizeof(double));
            *((double*)col->data[col->taille_logique]) = *((double*)value);
            break;
        case STRING:
            col->data[col->taille_logique] = (char **) malloc(sizeof(char*));
            *((char**)col->data[col->taille_logique]) = *((char**)value);
            break;

        default:
            printf("Error : la valeur n'a pas pu être inseree, saisie invalide \n");
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
        printf("%d", col->type);
        switch(col->type)
        {
            case UINT:
            {
                unsigned int* temp = (unsigned int*) malloc(sizeof(unsigned int));
                scanf(" %d", temp);
                ptr = temp;
                break;
            }
            case INT:
            {
                int* temp = (int*) malloc(sizeof(int));
                scanf(" %d", temp);
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
                printf("STRING\n");
                char** temp = (char**) malloc(sizeof(char**));
                scanf(" %s", *temp);
                ptr = &temp;
                break;
            }
            default:
                printf("Error: Conversion Failed");
                break;
        }
        insert_value(col, ptr);
    }
}
