#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FonctionsColonnes.h"
#define REALOC_SIZE 256


// Fonction qui crée une colonne
COLUMN *create_column(ENUM_TYPE type, char* titre)
{
    int longueur_titre = strlen(titre); // Calcul de la longueur du titre

    COLUMN *column = (COLUMN *) malloc(sizeof(COLUMN)); // Allocation dynamique de mémoire pour une structure COLUMN
    column->titre = (char *) malloc(longueur_titre + 1); // Allocation de mémoire pour le titre de la colonne
    if (column->titre == NULL)
    {
        free(column); // Libération de la mémoire de la colonne en cas d'échec
        printf("Erreur d'allocation"); // Message d'erreur en cas d'échec de l'allocation
        return NULL;
    }

    strcpy(column->titre, titre); // Copie du titre dans la mémoire allouée

    column->index = NULL; // Initialisation de l'index à NULL
    column->data = NULL; // Initialisation des données à NULL
    column->taille_logique = 0; // Initialisation de la taille logique à 0
    column->taille_physique = 0; // Initialisation de la taille physique à 0
    column->type = type; // Affectation du type de la colonne

    return column; // Retourne le pointeur vers la colonne créée
}

// Fonction qui supprime une colonne
void delete_column(COLUMN **col)
{
    if ((*col)->data != NULL)
    {
        free((*col)->data); // Libération de la mémoire des données si elles existent
        (*col)->data = NULL; // Mise à NULL du pointeur data
    }
    if((*col)->index != NULL)
    {
        free((*col)->index); // Libération de la mémoire de l'index si il existe
        (*col)->index = NULL; // Mise à NULL du pointeur index
    }

    free(*col); // Libération de la mémoire de la colonne
    *col = NULL; // Mise à NULL du pointeur de la colonne
}

// Fonction qui convertit une valeur en chaîne de caractères
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size)
{
    switch(col->type)
    {
        case INT:
            snprintf(str, size, "%d", *((int*)col->data[i]));
            break;
        case UINT:
            snprintf(str, size, "%u", *((unsigned int*)col->data[i]));
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
            snprintf(str, size, "%s", (char*)col->data[i]);
            break;
    }
}

// Fonction qui affiche le contenu d'une colonne
void print_col(COLUMN* col)
{
    int n = col->taille_logique; // Récupération de la taille logique
    int i;
    printf("%s :\n", col->titre); // Affichage du titre de la colonne
    if(col->type != STRING)
    {
        for(i = 0; i < n; i++)
        {
            char str[50]; // Tampon pour la conversion
            convert_value(col, i, str, 50); // Conversion de la valeur en chaîne
            printf("[%d] %s \n", i, str); // Affichage de la valeur convertie
        }
    }
    else
    {
        for(i = 0; i < n; i++)
        {
            printf("[%d] %s\n", i, (char*)col->data[i]); // Affichage des chaînes de caractères
        }
    }
}

// Fonction qui insère une valeur dans une colonne
int insert_value(COLUMN* col, void* value)
{
    if (col == NULL)
    {
        return 0; // Retourne 0 si la colonne est NULL
    }
    if (col->taille_logique == col->taille_physique)
    {
        int nouvelle_taille = REALOC_SIZE + col->taille_physique; // Nouvelle taille avec augmentation
        COL_TYPE** temp;
        if(col->taille_physique == 0)
        {
            temp = malloc(nouvelle_taille * sizeof(COL_TYPE*)); // Allocation initiale
        }
        else
        {
            temp = realloc(col->data, nouvelle_taille * sizeof(COL_TYPE*)); // Réallocation
        }

        if(temp == NULL)
        {
            free(temp); // Libération de la mémoire en cas d'échec de réallocation
            return 0; // Retourne 0 en cas d'échec
        }
        col->data = temp;
        col->taille_physique = nouvelle_taille;
    }

    switch(col->type)
    {
        case INT:
            col->data[col->taille_logique] = malloc(sizeof(int)); // Allocation pour un entier
            *((int*)col->data[col->taille_logique]) = *((int*)value); // Copie de la valeur
            break;

        case UINT:
            col->data[col->taille_logique] = malloc(sizeof(unsigned int)); // Allocation pour un entier non signé
            *((unsigned int*)col->data[col->taille_logique]) = *((unsigned int*)value); // Copie de la valeur
            break;

        case CHAR:
            col->data[col->taille_logique] = malloc(sizeof(char)); // Allocation pour un caractère
            *((char*)col->data[col->taille_logique]) = *((char*)value); // Copie de la valeur
            break;

        case FLOAT:
            col->data[col->taille_logique] = malloc(sizeof(float)); // Allocation pour un flottant
            *((float*)col->data[col->taille_logique]) = *((float*)value); // Copie de la valeur
            break;

        case DOUBLE:
            col->data[col->taille_logique] = malloc(sizeof(double)); // Allocation pour un double
            *((double*)col->data[col->taille_logique]) = *((double*)value); // Copie de la valeur
            break;

        case STRING:
            col->data[col->taille_logique] = malloc(sizeof(char*)); // Allocation pour une chaîne de caractères
            col->data[col->taille_logique] = value; // Copie de la valeur
            break;

        default:
            printf("Erreur : Type inexistant \n");
            return 0; // Retourne 0 en cas d'erreur
    }
    col->taille_logique++; // Incrémente la taille logique
    return 1; // Retourne 1 en cas de succès
}

// Fonction qui remplit une colonne avec des valeurs
int fill_column(COLUMN* col)
{
    int i, n;
    char ver[50];
    void* ptr = NULL;
    printf("Entrez le nombre de valeurs à insérer : \n");
    scanf(" %s", ver); // Lecture du nombre de valeurs à insérer
    while(is_digit(ver) != 1)
    {
        printf("Saisie invalide, veuillez entrer un nombre\n");
        scanf(" %s", ver); // Lecture jusqu'à obtenir un nombre valide
    }
    n = convert_to_int(ver); // Conversion de la chaîne en entier
    for(i = 0; i < n; i++)
    {
        printf("Valeur %d :\n", i);
        switch(col->type)
        {
            case UINT:
            {
                unsigned int* temp = (unsigned int*) malloc(sizeof(unsigned int));
                scanf(" %u", temp); // Lecture d'un entier non signé
                ptr = temp;
                break;
            }
            case INT:
            {
                int* temp = (int*) malloc(sizeof(int));
                scanf(" %d", temp); // Lecture d'un entier
                ptr = temp;
                break;
            }
            case CHAR:
            {
                char* temp = (char*) malloc(sizeof(char));
                scanf(" %c", temp); // Lecture d'un caractère
                ptr = temp;
                break;
            }
            case FLOAT:
            {
                float* temp = (float*) malloc(sizeof(float));
                scanf(" %f", temp); // Lecture d'un flottant
                ptr = temp;
                break;
            }
            case DOUBLE:
            {
                double* temp = (double*) malloc(sizeof(double));
                scanf(" %lf", temp); // Lecture d'un double
                ptr = temp;
                break;
            }
            case STRING:
            {
                char* temp = (char*) malloc(100 * sizeof(char));
                scanf("%s", temp); // Lecture d'une chaîne de caractères
                ptr = temp;
                break;
            }
            default:
                printf("Erreur: Type inexistant");
                return 0; // Retourne 0 en cas d'erreur
        }
        insert_value(col, ptr); // Insertion de la valeur dans la colonne
    }
    return 1; // Retourne 1 en cas de succès
}

// Fonction qui vérifie si une chaîne est composée uniquement de chiffres


int is_digit(char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int convert_to_int(char *str)
{
    int i = 0;
    int val = 0;
    while (str[i] != '\0') {
        val = val * 10 + (*str - '0');
        i++;
    }
    return val;
}