#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H

typedef struct
{
    char *titre;
    int *tableau_data;
    int taille_logique;
    int taille_physique;
    // partie 2 Un Cdataframe presque-parfait
    unsigned long long *index; // Ajouté pour le tri
    int valid_index;           // Ajouté pour gérer l'état de tri
    int sort_dir;              // Ajouté pour la direction du tri

} COLUMN;

COLUMN *create_column(char* titre);
// fonction qui crée une colonne vide
int insert_value(COLUMN* col, int value);
// fonction qui insère une valeur dans la colonne 
void delete_column(COLUMN** col_ptr);
//fonction qui supprime une colonne 
void Print_col(COLUMN* col);
//fonction qui affiche une colonne
int Frequency(COLUMN* col, int val);
//fonction qui calcule la fréquence d'une valeur dans une colonne 
int Val_From_Id(COLUMN* col, int id);

int Nb_Superior(COLUMN* col, int val);
int Nb_Inferior(COLUMN* col, int val);
void fill_column(COLUMN* col);




#endif //PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
