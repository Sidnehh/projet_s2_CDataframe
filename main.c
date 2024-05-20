#include <stdio.h>
#include <malloc.h>
#include "FonctionsColonnes.h"
#include "FonctionsCDataFrame.h"

void menu()
{
    CDATAFRAME *cdf = NULL;
    char ver[50];
    int size;
    int choice;
    int type;
    char *titre = (char *) malloc(100 * sizeof(char));
    char *col_title = (char *) malloc(100 * sizeof(char));
    unsigned int index;
    ENUM_TYPE *cdftype = NULL;

    do {
        printf("-----------------------------------------------\n");
        printf("Menu:\n");
        printf("1. Creer un dataframe\n");
        printf("2. Afficher le dataframe\n");
        printf("3. Ajouter une colonne\n");
        printf("4. Supprimer une colonne\n");
        printf("5. Obtenir le nombre de colonnes\n");
        printf("6. Supprimer le dataframe\n");
        printf("0. Quitter\n");
        printf("-----------------------------------------------\n");
        printf("Entrez votre choix: \n");
        scanf(" %d", &choice);

        switch (choice)
        {
            case 1 :
            {
                printf("Entrez le nombre de colonnes:\n ");
                scanf(" %s", ver);
                while(is_digit(ver) != 1)
                {
                    printf("Saisie invalide, veuillez entrer un nombre\n");
                    scanf(" %s", ver);
                }
                size = convert_to_int(ver);
                cdf = create_cdataframe(cdftype, size);
                if (cdf != NULL)
                    printf("Le cdataframe a bien ete cree \n");
                break;
            }

            case 2:
                print_cdf(cdf);
                break;

            case 3:
            {
                printf("Entrez le titre de la nouvelle colonne: \n");
                scanf("%s", titre);
                printf("1 : entier naturel\n2 : entier\n3 : caractere\n4 : decimal\n5 : chaine de caracteres\n");
                scanf(" %d", &type);
                COLUMN *new_col = create_column(type, col_title);
                fill_column(new_col);
                printf("la colonne a bien ete creee, indiquez l'indice ou inserer la colonne: ");
                scanf(" %d", &index);
                ajouter_column(cdf, new_col, index);
                break;
            }

            case 4:
                printf("Saisir le titre de la colonne a supprimer: ");
                scanf("%s", titre);
                delete_c(cdf, titre);
                break;

            case 5:
                printf("Il y a %d colonnes dans le Cdataframe actuellement\n", get_cdataframe_cols_size(cdf));
                break;

            case 6:
                delete_cdataframe(&cdf);
                printf("Dataframe supprime\n");
                break;

            case 0 :
                printf("Merci de votre visite ! ");
                delete_cdataframe(&cdf);
                free(col_title);
                free(titre);
                break;

            default:
                printf("Choix invalide, reessayez \n");
                break;

        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0;
}