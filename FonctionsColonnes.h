#ifndef TEST__LISTE_CHAÎNÉ_H
#define TEST__LISTE_CHAÎNÉ_H

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
} COLUMN;

typedef struct lnode {
    COLUMN *data; // Pointer to a column
    struct lnode *prev;
    struct lnode *next;
}LNODE;

typedef struct {
    LNODE *head;
    LNODE *tail;
} LIST ;
typedef LIST CDATAFRAME;


LIST *create_list(void);
//fonction crée un pointeur de type liste

LNODE* creer_lnode(COLUMN *column);
// fonction qui crée un noeud

COLUMN *create_column(ENUM_TYPE type, char *title);
// fonction qui créer une colonne de n'importe quel type

CDATAFRAME *create_cdataframe( ENUM_TYPE *cdftype, int size);
// fonction qui crée un cdataframe

void delete_column(COLUMN**column);
// fonction qui libère une colonne

void delete_c (CDATAFRAME *cdf, char *titre);
// fonction qui supprime une colonne d'un cdataframe à partir de son titre

void print_col(COLUMN*column);
//fonction qui affiche une colonne

void delete_cdataframe(CDATAFRAME** cdf);
// fonction qui libère un cdataframe

void ajouter_column( CDATAFRAME*cdf, COLUMN*column, unsigned int index);
// fonction qui permet d'ajouter un noeud/ colonne dans le cdataframe (specifier l'indice)

void print_cdf(CDATAFRAME* cdf);
//fonction qui affiche un cdataframe

int get_cdataframe_cols_size(CDATAFRAME *cdf);
//fonction qui renvoie le nombre de colonnes d'un cdataframe

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
// fonction qui convertit une variable de l'indice i d'une colonne en chaîne de caractères

void print_col(COLUMN* col);
//fonction qui affiche une colonne

int fill_column(COLUMN* col);
//fonction qui remplit une colonne de manière interactive

int insert_value(COLUMN* col, void* value);
//fonction qui insère une valeur de tout type dans une colomne grâce à un pointeur void, retourne 1 si l'insertion
//bien déroulée, 0 sinon

int is_digit(char*);
int convert_to_int(char *str);
//fonctions qui servent à vérifier les saisies utilisateur

#endif //TEST__LISTE_CHAÎNÉ_H
