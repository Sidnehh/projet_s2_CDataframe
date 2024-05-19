#include <stdio.h>
#include <stdlib.h>
#include "FonctionsCDataFrame.h"
#include "FonctionsColonnes.h"

int main()
{
    int TL=0;
    COLUMN** cdf = create_empty_cdataframe(TL);
    COLUMN* c1 = create_column(INT, "entiers");
    COLUMN* c2 = create_column(CHAR, "phrases");
    fill_column(c2);
    Print_col(c2);
    return 0;
}