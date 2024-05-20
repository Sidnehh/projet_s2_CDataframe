#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FonctionsColonnes.h"
#define REALOC_SIZE 256

LIST *create_list(void)
{
    LIST *list = (LIST*) malloc(sizeof(LIST));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

COLUMN *create_column(ENUM_TYPE type, char* titre)
{
    int longueur_titre = strlen(titre);

    COLUMN *column = (COLUMN *) malloc(sizeof(COLUMN));
    column->titre = (char *) malloc(longueur_titre + 1);
    if (column->titre == NULL)
    {
        free(column);
        printf("Erreur d'allocation");
        return NULL;
    }

    strcpy(column->titre, titre);

    column->index = NULL;
    column->data = NULL;
    column->taille_logique = 0;
    column->taille_physique = 0;
    column->type = type;

    return column;
}

LNODE* creer_lnode(COLUMN *column)
{
    LNODE* lnode= (LNODE*)malloc(sizeof(LNODE));
    if (lnode==NULL)
    {
        printf("Erreur d'allocation");
        return NULL;
    }
    lnode->prev=NULL;
    lnode->next=NULL;
    lnode->data= column;
    return lnode;
}

CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size)
{
    LIST *cdf = create_list();
    if (cdf == NULL)
    {
        printf("Erreur d'allocation");
        free(cdf);
        return NULL;
    }
    else
    {
        for (int i = 0; i < size; i++) {
            char *titre = (char *) malloc(100 * sizeof(char));
            int type;
            if (titre == NULL) {
                free(cdf);
                printf("Erreur d'allocation");
                return NULL;
            }
            printf("Saisir le titre de la colonne %d", i + 1);
            gets(titre);
            printf("Saisir le type de la colonne %d", i + 1);
            scanf(" %d", &type);
            printf("1 : entier naturel\n2 : entier\n3 : caractere\n4 : decimal\n5 : chaine de caracteres\n");
            COLUMN *column = create_column(type, titre);
            LNODE *node = creer_lnode(column);

            if (column == NULL || node == NULL) {
                printf("Erreur d'allocation");
                free(titre);
                free(column);
                free(node);
                free(cdf);
                return NULL;
            }
            if (cdf->head == NULL) {
                cdf->head = node;
                cdf->tail = node;
            } else
            {
                node->prev = cdf -> tail;
                cdf->tail->next = node;
                cdf-> tail = node ;
            }
        }
    }

    return cdf;
}

void delete_column(COLUMN**column)
{

}

void delete_cdataframe(CDATAFRAME** cdf)
{
    if (cdf==NULL || *cdf == NULL)
        return ;
    LNODE* tmp = (*cdf) -> head;
    LNODE * current = tmp;
    while(tmp != NULL)
    {
        current = current -> next;
        delete_column(&tmp->data);
        tmp->prev = NULL;
        free(tmp);
        tmp=current;
    }
    free(*cdf);
    *cdf= NULL;
}

void print_cdf(CDATAFRAME* cdf)
{
    if (cdf== NULL)
    {
        printf("le cdata est déjà vide\n");
        return;
    }
    int choice;
    printf("Voulez vous afficher le Cdataframe dans le sens de remplissage (1) ou inverse (0) ?");
    scanf(&choice);
    switch (choice) {
        case 0 :
        {
            LNODE *current = cdf-> head;
            while (current !=NULL)
            {
                print_col(current->data);
                current = current->next;
            }
            break;
        }
        case 1 :
        {
            LNODE *current = cdf-> tail;
            while (current !=NULL)
            {
                print_col(current->data);
                current = current -> next;
            }
            break;
        }
        default:
            printf("Choix invalide\n");
            break;
    }
}

void delete_c (CDATAFRAME *cdf, char *titre)
{
    if (cdf==NULL)
    {
        printf("la colonne n'existe pas car le cdata est vide");
        return ;
    }
    LNODE* current = cdf-> head;
    while (current!=NULL && strcmp(current->data->titre, titre)!=0 )
    {
        current= current->next;
    }

    if (current == NULL) {
        printf("La colonne %s est introuvable\n", titre);
        return;
    }
    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else{
        cdf->head= current->next;
    }
    if(current->next !=NULL)
    {
        current->prev->next= current->next;
    }
    else
    {
        cdf->tail=current->prev;
    }

    delete_column(&current->data);
    free(current);
    printf("Colonne %s supprimée avec succès\n", titre);

}

void ajouter_column(CDATAFRAME *cdf, COLUMN*column, unsigned int index)
{
    LNODE *new_node = creer_lnode(column);
    if (cdf==NULL)
    {
        printf("cDataframe vide");
        free(new_node);
        return;
    }
    if (index==0 || cdf->head ==NULL)
    {
        new_node->next = cdf->head;
        if (cdf->head != NULL)
            cdf->head->prev = new_node;
        cdf->head= new_node;
        if (cdf->tail==NULL)
            cdf->tail=new_node;
        return;
    }
    LNODE* current = cdf->head;
    int i = 0;
    while( current!=NULL && i<index-1)
    {
        current = current -> next;
        i++;
    }
    if (current == NULL || current->next == NULL) {
        if (current != NULL) {
            current->next = new_node;
            new_node->prev = current;
        }
        else {
            if (cdf->tail != NULL) {
                cdf->tail->next = new_node;
                new_node->prev = cdf->tail;
            }
            cdf->tail = new_node;
        }
    }
    else {
        // Insertion au milieu
        new_node->next = current->next;
        new_node->prev = current;
        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
    }
}


int get_cdataframe_cols_size(CDATAFRAME *cdf)
{
    if (cdf==NULL)
        return 0;
    LNODE* current= cdf-> head;
    int count=0;
    while(current!=NULL)
    {
        count++;
        current=current->next;

    }
    return count;
}

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
    for(i=0;i<n;i++)
    {
        char str[10];
        convert_value(col, i, str, col->taille_logique);
        printf("[%d] %s \n", i, str);
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
            printf("Error : la valeur n'a pas pu être insérée, saisie invalide \n");
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

            default:
                printf("Error: Conversion Failed");
                break;
        }
        insert_value(col, ptr);
    }
}