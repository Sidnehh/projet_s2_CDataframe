#ifndef TEST__CDATAFRAME_H
#define TEST__CDATAFRAME_H
#include "FonctionsColonnes.h"

typedef enum {
    UINT,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,
} ENUM_TYPE;

typedef union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
}COL_TYPE ;

typedef struct
{
    char *titre;
    int taille_logique;
    int taille_physique;
    unsigned long long int* index;
    COL_TYPE **data;
    ENUM_TYPE type;
} COLUMN; // structure d'une colonne

typedef struct lnode {
    COLUMN *data; // Pointer to a column
    struct lnode *prev;
    struct lnode *next;
}LNODE; // structure d'un noeud

typedef struct {
    LNODE *head;
    LNODE *tail;
} LIST ; // structure d'une liste
typedef LIST CDATAFRAME;

LIST *create_list(void);
//fonction crée un pointeur de type liste

LNODE* creer_lnode(COLUMN *column);
// fonction qui crée un noeud

CDATAFRAME *create_cdataframe( ENUM_TYPE *cdftype, int size);
// fonction qui crée un cdataframe

void delete_cdataframe(CDATAFRAME** cdf);
// fonction qui libère un cdataframe

void ajouter_column( CDATAFRAME*cdf, COLUMN*column, unsigned int index);
// fonction qui permet d'ajouter un noeud/ colonne dans le cdataframe (specifier l'indice)

void print_cdf(CDATAFRAME* cdf);
//fonction qui affiche un cdataframe

int get_cdataframe_cols_size(CDATAFRAME *cdf);
//fonction qui renvoie le nombre de colonnes d'un cdataframe

void delete_c (CDATAFRAME *cdf, char *titre);
// fonction qui supprime une colonne d'un cdataframe à partir de son titre

void delete_cdataframe(CDATAFRAME** cdf);
// fonction qui libère un cdataframe

void ajouter_column( CDATAFRAME*cdf, COLUMN*column, unsigned int index);
// fonction qui permet d'ajouter un noeud/ colonne dans le cdataframe (specifier l'indice)

void print_cdf(CDATAFRAME* cdf);
//fonction qui affiche un cdataframe

int get_cdataframe_cols_size(CDATAFRAME *cdf);
//fonction qui renvoie le nombre de colonnes d'un cdataframe

#endif //TEST__CDATAFRAME_H