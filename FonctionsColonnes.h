#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H

typedef struct
{
    char *titre;
    int *tableau_data;
    int taille_logique;
    int taille_physique;
} COLUMN;
//fonction qui crée une colonne vide
COLUMN *create_column(char* titre);
//fonction qui insère une valeur dans la colonne
int insert_value(COLUMN* col, int value);
//fonction qui vide la colonne
void delete_column(COLUMN **col);


//PARTIE SIDNEY

void Print_col(struct COLUMN* col);
int Frequency(struct COLUMN* col, int val);
int Val_From_Id(struct COLUMN* col, int id);
int Nb_Superior(struct COLUMN* col, int val);
int Nb_Inferior(struct COLUMN* col, int val);

#endif //PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
