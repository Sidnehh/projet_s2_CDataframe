#include "FonctionsColonnes.h"
#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H


COLUMN** create_empty_cdataframe(int nb);
// fonction qui crée un cdataframe vide (tableau de type COLUMN)
void fill_cdataframe(COLUMN** cdf, int TL);
// fonction qui remplit le cdataframe
int maxcol_cdataframe(COLUMN** cdf, int TL);
//
void print_cdataframe(COLUMN** cdf, int TL);
// fonction qui affiche le cdataframe
void print_lines_cdataframe(COLUMN** cdf, int TL, int nlines);

void print_columns_cdataframe(COLUMN** cdf, int TL, int ncol);

void add_col_cdataframe(COLUMN** cdf, int* TL, COLUMN* col);
void delete_column_cdf(COLUMN*** cdataframe, int* TL, int index);
#endif PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
