#include <stdio.h>
#include <stdlib.h>
#include "FonctionsCDataFrame.h"
#include "FonctionsColonnes.h"

int main()
{
    int TL=0;
    COLUMN** cdf = create_empty_cdataframe(TL);
    COLUMN* c1 = create_column(INT, "entiers");
    COLUMN* c2 = create_column(CHAR, "caractères");
    fill_column(c1);
    add_col_cdataframe(cdf, &TL, c1);
    print_cdataframe(cdf, TL);
    return 0;
}