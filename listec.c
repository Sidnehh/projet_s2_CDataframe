#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listec.h"

LIST *create_list(void)
{
    LIST *list = (LIST*) malloc(sizeof(LIST));
    if (list) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

LNODE* creer_lnode(COLUMN *column)
{
    LNODE* lnode= (LNODE*)malloc(sizeof(LNODE));
    if (lnode==NULL)
    {
        printf("erreur d'allocation");
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
            if (titre == NULL) {
                free(cdf);
                printf("Erreur d'allocation");
                return NULL;
            }
            printf("Saisir le titre de la colonne %d", i + 1);
            gets(titre);
            COLUMN *column = create_column(*(cdftype + i), titre);
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