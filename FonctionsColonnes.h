#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H

struct COLUMN
{
    char titre[50];
    int* T;
    int TL;
    int TP;
};

//PARTIE SABRINA

//PARTIE SIDNEY

void Print_col(struct COLUMN* col);
int Frequency(struct COLUMN* col, int val);
int Val_From_Id(struct COLUMN* col, int id);
int Nb_Superior(struct COLUMN* col, int val);
int Nb_Inferior(struct COLUMN* col, int val);

#endif //PROJET_S2_CDATAFRAME_FONCTIONSCOLONNES_H
