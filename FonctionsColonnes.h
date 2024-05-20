#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H

typedef enum {
    INT,
    CHAR,
    FLOAT,
}ENUM_TYPE;
typedef struct
{
    char *titre;
    int *tableau_data;
    int taille_logique;
    int taille_physique;
    ENUM_TYPE type;
    // partie 2 Un Cdataframe presque-parfait
    unsigned long long *index; // Ajouté pour le tri
    int valid_index;           // Ajouté pour gérer l'état de tri
    int sort_dir;              // Ajouté pour la direction du tri

} COLUMN;
//fonction qui crée une colonne vide
COLUMN *create_column(char* titre);
//fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, int value);
//fonction qui vide la colonne
void delete_column(COLUMN** col_ptr);
void Print_col(COLUMN* col);
int Frequency(COLUMN* col, int val);
int Val_From_Id(COLUMN* col, int id);
int Nb_Superior(COLUMN* col, int val);
int Nb_Inferior(COLUMN* col, int val);

//Partie 5.1

//Partie 6


#endif //PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
