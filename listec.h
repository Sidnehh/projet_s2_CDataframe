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

typedef struct {
    char *titre;
    unsigned int taille_logique;
    ENUM_TYPE column_type;
    void *data; // array of pointers to stored data
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
void print_col(COLUMN*column);
//fonction qui affiche une colonne
void delete_cdataframe(CDATAFRAME** cdf);
// fonction qui libère un cdataframe
void delete_c (CDATAFRAME *cdf, char *titre);
// fonction qui supprime une colonne d'un cdataframe à partir de son titre
void ajouter_column( CDATAFRAME*cdf, COLUMN*column, unsigned int index);
// fonction qui permet d'ajouter un noeud/ colonne dans le cdataframe (specifier l'indice)
void print_cdf(CDATAFRAME* cdf);
//fonction qui affiche un cdataframe
int get_cdataframe_cols_size(CDATAFRAME *cdf);
//fonction qui renvoie le nombre de colonnes d'un cdataframe
#endif //TEST__LISTE_CHAÎNÉ_H
