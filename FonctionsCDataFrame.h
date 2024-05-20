#include "FonctionsColonnes.h"
#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H


COLUMN** create_empty_cdataframe(int nb);
// fonction qui crée un cdataframe vide (tableau de type COLUMN)
void fill_cdataframe(COLUMN** cdf, int TL);
// fonction qui remplit le cdataframe
int maxcol_cdataframe(COLUMN** cdf, int TL);
// fonction qui affiche la colonne avec le plus d'éléments
void print_cdataframe(COLUMN** cdf, int TL);
// fonction qui affiche le cdataframe
void print_lines_cdataframe(COLUMN** cdf, int TL, int nlines);
//fonction qui affiche des lignes données par l'utilisateur 
void print_columns_cdataframe(COLUMN** cdf, int TL, int ncol);
//fonction qui affiche des colonnes données par l'utilisateur 
void add_col_cdataframe(COLUMN** cdf, int* TL, COLUMN* col);
// fonction qui ajoute une colonne au cdataframe
void delete_column_cdf(COLUMN*** cdataframe, int* TL, int index);
//fonction qui supprime une colonne 
#endif PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
