#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H

union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;

enum enum_type
{
    NULLVAL = 1 , UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;

typedef struct
{
    char *titre;
    int taille_logique;
    int taille_physique;
    unsigned long long int* index;
    COL_TYPE **tableau_data;
    ENUM_TYPE type;
} COLUMN;


//fonction qui crée une colonne vide
COLUMN *create_column(ENUM_TYPE , char* titre);
//fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, void* value);
//fonction qui vide la colonne
void delete_column(COLUMN **col);
//fonction qui affiche une colonne
void Print_col(COLUMN* col);
//fonction qui retourne la fréquence d'une valeur val dans une colonne
int Frequency(COLUMN* col, int val);
//fonction qui retourne une valeur val depuis un id
int Val_From_Id(COLUMN* col, int id);
//fonction qui retourne le nombre de valeurs supérieures à val dans une colonne
int Nb_Superior(COLUMN* col, int val);
//fonction qui retourne le nombre de valeurs inférieures à val dans une colonne
int Nb_Inferior(COLUMN* col, int val);

//Partie 5.1

//Partie 6

#endif //PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
