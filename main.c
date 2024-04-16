#include <stdio.h>
#include <stdlib.h>
#include "FonctionsCDataFrame.h"
#include "FonctionsColonnes.h"

int main()
{
    COLUMN** cdf = create_empty_cdataframe(4);
    printf("TL : %d, TP : %d \n", cdf[0]->taille_logique, cdf[0]->taille_physique);
    fill_cdataframe(cdf, 4);
    print_cdataframe(cdf, 4);
    printf("\n");
    print_columns_cdataframe(cdf, 4, 2);
    printf("\n");
    print_lines_cdataframe(cdf, 4, 2);
    return 0;
}