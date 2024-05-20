#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FonctionsColonnes.h"

// Fonction qui crée une nouvelle liste et renvoie un pointeur vers celle-ci
LIST *create_list(void)
{
    LIST *list = (LIST*) malloc(sizeof(LIST)); // Allocation dynamique pour une structure 'LIST'
    if (list) {
        list->head = NULL; // Initialise l'attribut head à NULL
        list->tail = NULL; // Initialise l'attribut tail à NULL
    }
    return list; // Retourne le pointeur vers la liste créée
}

// Fonction qui crée un nouveau nœud de liste avec une colonne donnée
LNODE* creer_lnode(COLUMN *column)
{
    LNODE* lnode= (LNODE*)malloc(sizeof(LNODE)); // Allocation dynamique de mémoire pour une structure LNODE
    if (lnode == NULL)
    {
        printf("Erreur d'allocation"); // Message d'erreur en cas d'échec de l'allocation
        return NULL;
    }
    lnode->prev = NULL; // Initialise l'attribut prev à NULL
    lnode->next = NULL; // Initialise l'attribut next à NULL
    lnode->data = column; // Affecte la colonne au champs data
    return lnode; // Retourne le pointeur vers le nœud créé
}

// Fonction qui crée un dataframe contenant plusieurs colonnes
CDATAFRAME *create_cdataframe(ENUM_TYPE *cdftype, int size)
{
    LIST *cdf = create_list(); // Création d'une nouvelle liste pour le dataframe
    if (cdf == NULL)
    {
        printf("Erreur d'allocation"); // Message d'erreur en cas d'échec de l'allocation
        free(cdf); // Libération de la mémoire allouée
        return NULL;
    }
    else
    {
        for (int i = 0; i < size; i++) { // Boucle pour créer et ajouter les colonnes
            char *titre = (char *) malloc(100 * sizeof(char)); // Allocation dynamique pour le titre de la colonne
            int type;
            if (titre == NULL) {
                free(cdf); // Libération de la mémoire allouée
                printf("Erreur d'allocation"); // Message d'erreur en cas d'échec de l'allocation
                return NULL;
            }
            printf("Saisir le titre de la colonne %d\n", i + 1);
            scanf(" %s", titre); // Lecture du titre de la colonne
            printf("Saisir le type de la colonne %d\n", i + 1);
            printf("1 : entier naturel\n2 : entier\n3 : caractere\n4 : decimal\n5 : flottant\n6: chaine de caracteres\n");
            scanf(" %d", &type); // Lecture du type de la colonne
            COLUMN *column = create_column(type - 1, titre); // Création de la colonne
            fill_column(column); // Remplissage de la colonne

            LNODE *node = creer_lnode(column); // Création d'un nouveau nœud pour la colonne

            if (column == NULL || node == NULL) {
                printf("Erreur d'allocation"); // Message d'erreur en cas d'échec de l'allocation
                free(titre); // Libération de la mémoire allouée pour le titre
                free(column); // Libération de la mémoire allouée pour la colonne
                free(node); // Libération de la mémoire allouée pour le nœud
                free(cdf); // Libération de la mémoire allouée pour la liste
                return NULL;
            }
            if (cdf->head == NULL) {
                cdf->head = node; // Si la liste est vide, le nouveau nœud devient le premier
                cdf->tail = node; // et le dernier nœud de la liste
            } else {
                node->prev = cdf->tail; // Le nœud précédent du nouveau nœud est l'ancien dernier nœud
                cdf->tail->next = node; // Le nœud suivant de l'ancien dernier nœud est le nouveau nœud
                cdf->tail = node; // Le nouveau nœud devient le dernier nœud de la liste
            }
        }
    }
    return cdf; // Retourne le pointeur vers le dataframe créé
}

// Fonction qui supprime et libère la mémoire allouée pour un dataframe
void delete_cdataframe(CDATAFRAME** cdf)
{
    if (cdf == NULL || *cdf == NULL)
        return;
    LNODE* tmp = (*cdf)->head;
    LNODE *current = tmp;
    while (tmp != NULL)
    {
        current = current->next;
        delete_column(&tmp->data); // Suppression de la colonne
        tmp->prev = NULL;
        free(tmp); // Libération de la mémoire allouée pour le nœud
        tmp = current;
    }
    free(*cdf); // Libération de la mémoire allouée pour la liste
    *cdf = NULL;
}

// Fonction qui affiche le dataframe
void print_cdf(CDATAFRAME* cdf, int size)
{
    if (cdf== NULL)
    {
        printf("le cdata est deja vide\n");
        return;
    }
    int choice;
    printf("Voulez vous afficher le Cdataframe dans le sens de remplissage (1) / inverse (0) / tableur (2) ?\n");
    scanf(" %d", &choice);
    switch (choice) {
        case 0 :
        {
            LNODE *current = cdf-> head;
            while (current !=NULL)
            {
                print_col(current->data);
                current = current->next;
                printf("\n");
            }
            break;
        }
        case 1 :
        {
            LNODE *current = cdf-> tail;
            while (current !=NULL)
            {
                print_col(current->data);
                current = current -> prev;
                printf("\n");
            }
            break;
        }
        case 2 :
        {
            int i;
            unsigned int width;
            unsigned int gap;
            unsigned int gap_left;
            unsigned int gap_right;
            char* str = (char*) malloc(50*sizeof(char));
            LNODE *current = cdf-> head;
            while(current != NULL)
            {
                printf("| %s | ", current->data->titre);
                current = current->next;
            }
            printf("\n");
            current = cdf->head;
            for(i=0; i<size; i++)
            {
                while(current != NULL)
                {
                    width = strlen(current->data->titre);
                    if((current->data->taille_logique) < i)
                    {
                        printf("| %*s | ", width, "");
                        current = current -> next;
                        break;
                    }
                    convert_value(current->data, i, str, 50);
                    gap = strlen(str);
                    if (gap >= width)
                        printf("| %s | ", str);
                    else
                    {
                        gap_left = (width-gap)/2;
                        gap_right = width-gap-gap_left;
                        printf("| %*s%s%*s | ", gap_left, "", str, gap_right, "");
                    }
                    current = current -> next;
                }
                current = cdf->head;
                printf("\n");
            }
        }
        default:
            printf("Choix invalide\n");
            break;
    }
}
// Fonction qui supprime une colonne d'un dataframe à partir de son titre
void delete_c(CDATAFRAME *cdf, char *titre)
{
    if (cdf == NULL)
    {
        printf("la colonne n'existe pas car le cdata est vide");
        return;
    }
    LNODE* current = cdf->head;
    while (current != NULL && strcmp(current->data->titre, titre) != 0) // Parcourt le cdataframe et
        //tant que le titre n'est pas trouvé dans la colonne du noeud , on passe au noeud suivant

    {
        current = current->next;
    }

    if (current == NULL) {
        printf("La colonne %s est introuvable\n", titre);
        return;
    }
    if (current->prev != NULL)
    {
        current->prev->next = current->next;
    }
    else {
        cdf->head = current->next;
    }
    if (current->next != NULL)
    {
        current->next->prev = current->prev;
    }
    else
    {
        cdf->tail = current->prev;
    }

    delete_column(&current->data); // Suppression de la colonne
    free(current); // Libération de la mémoire allouée pour le nœud
    printf("Colonne %s supprimee avec succes\n", titre);
}

// Fonction qui ajoute une colonne à une position donnée dans un dataframe
void ajouter_column(CDATAFRAME *cdf, COLUMN* column, unsigned int index)
{
    LNODE *new_node = creer_lnode(column); // Création d'un nouveau nœud
    if (cdf == NULL)
    {
        printf("cDataframe vide");
        free(new_node); // Libération de la mémoire allouée pour le nouveau nœud
        return;
    }
    if (index == 0 || cdf->head == NULL)
    {
        new_node->next = cdf->head; // Insertion au début de la liste
        if (cdf->head != NULL)
            cdf->head->prev = new_node; // Mise à jour du nœud suivant
        cdf->head = new_node; // Mise à jour de la tête de liste
        if (cdf->tail == NULL)
            cdf->tail = new_node; // Si la liste était vide, mise à jour de la queue de liste
        return;
    }
    LNODE* current = cdf->head;
    int i = 0;
    while (current != NULL && i < index - 1) // On s'arrête un indice avant l'insertion
    {
        current = current->next;
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
            cdf->tail = new_node;  // affecte en dernière position si dépassement lors de la boucle
        }
    }
    else {
        // Insertion au milieu
        new_node->next = current->next; // Le nœud suivant du nouveau nœud est celui après current
        new_node->prev = current; // Le nœud précédent du nouveau nœud est current
        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
    }
}

// Fonction qui renvoie le nombre de colonnes dans un dataframe
int get_cdataframe_cols_size(CDATAFRAME *cdf)
{
    if (cdf == NULL)
        return 0; // Retourne 0 si le dataframe est vide
    LNODE* current = cdf->head; // Pointeur vers le premier nœud de la liste
    int count = 0; // Initialisation du compteur
    while (current != NULL)
    {
        count++; // Incrémente le compteur
        current = current->next; // Passe au nœud suivant
    }
    return count;
}


