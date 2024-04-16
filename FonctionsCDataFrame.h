#include "FonctionsColonnes.h"
#ifndef PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
#define PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H

COLUMN** create_empty_cdataframe(int nb);
void fill_cdataframe(COLUMN** cdf, int TL);
int maxcol_cdataframe(COLUMN** cdf, int TL);
void print_cdataframe(COLUMN** cdf, int TL);
void print_lines_cdataframe(COLUMN** cdf, int TL, int nlines);
void print_columns_cdataframe(COLUMN** cdf, int TL, int ncol);
void add_col_cdataframe(COLUMN** cdf, int TL, COLUMN* col);
void del_col_cdataframe(COLUMN** cdf, int TL);
#endif //PROJET_S2_CDATAFRAME_FONCTIONSCDATAFRAME_H
