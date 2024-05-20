#include <stdio.h>
#include <malloc.h>
#include "listec.h"

void menu()
{
    CDATAFRAME *cdf = NULL;
    int size;
    int choice;
    char *titre = (char *) malloc(100 * sizeof(char));
    char *col_title = (char *) malloc(100 * sizeof(char));
    COLUMN *column;
    unsigned int index;
    ENUM_TYPE *cdftype = NULL;

    do {
        printf("\n Menu:\n");
        printf("1. Créer un dataframe\n");
        printf("2. Afficher le dataframe\n");
        printf("3. Ajouter une colonne\n");
        printf("4. Supprimer une colonne\n");
        printf("5. Obtenir le nombre de colonnes\n");
        printf("6. Supprimer le dataframe\n");
        printf("0. Quitter\n");
        printf("Entrez votre choix: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1 :
                printf("Entrez le nombre de colonnes: ");
                scanf(" %d", &size);
                cdftype = (ENUM_TYPE *) malloc(size * sizeof(ENUM_TYPE));
                if (cdftype == NULL) {
                    printf("ERREUR d'allocation");
                    break;
                }
                for (int i = 0; i < size; i++) {
                    int type;
                    printf("Saisir le type de la colonne %d, (1: UINT, 2: INT, 3: CHAR, 4: FLOAT, 5: DOUBLE, 6: STRING): ",
                           i + 1);
                    scanf(" %d", &type);
                    switch (type) {
                        case 1:
                            cdftype[i] = UINT;
                            break;
                        case 2:
                            cdftype[i] = INT;
                            break;
                        case 3:
                            cdftype[i] = CHAR;
                            break;
                        case 4:
                            cdftype[i] = FLOAT;
                            break;
                        case 5:
                            cdftype[i] = DOUBLE;
                            break;
                        case 6:
                            cdftype[i] = STRING;
                            break;
                        default:
                            printf("type invalide, le type a été remplacé par int pour la colonne %d ", i + 1);
                            cdftype[i] = INT;
                            break;
                    }

                }
                cdf = create_cdataframe(cdftype, size);
                if (cdf != NULL)
                    printf("Le cdataframe a bien été créé \n");
                free(cdftype);
                break;

            case 2:
                print_cdf(cdf);
                break;

            case 3:
                printf("Entrez le titre de la nouvelle colonne: ");
                gets(col_title);
                printf("Saisir le type de la nouvelle colonne (1: UINT, 2: INT, 3: CHAR, 4: FLOAT, 5: DOUBLE, 6: STRING):  ");
                int type;
                scanf(" %d", &type);
                ENUM_TYPE type_col;
                switch (type) {
                    case 1:
                        type_col = UINT;
                        break;
                    case 2:
                        type_col = INT;
                        break;
                    case 3:
                        type_col = CHAR;
                        break;
                    case 4:
                        type_col = FLOAT;
                        break;
                    case 5:
                        type_col = DOUBLE;
                        break;
                    case 6:
                        type_col = STRING;
                        break;
                    default:
                        printf("Type invalide, colonne définie à INT par défaut\n");
                        type_col = INT;
                        break;
                }
                COLUMN *new_col = create_column(type_col, col_title);
                printf("la colonne a bien été créée indiquez l'indice où insérer la colonne: ");
                scanf(" %d", &index);
                ajouter_column(cdf, new_col, index);
                break;

            case 4:
                printf("Saisir le titre de la colonne à supprimer: ");
                gets(titre);
                delete_c(cdf, titre);
                break;

            case 5:
                printf("Il y a %d colonnes dans le Cdataframe actuellement\n", get_cdataframe_cols_size(cdf));
                break;
            case 6:
                delete_cdataframe(&cdf);
                printf("Dataframe supprimé\n");
                break;
            case 0 :
                printf("Merci de votre visite ! ");
                delete_cdataframe(&cdf);
                free(col_title);
                free(titre);
                break;
            default:
                printf("Choix invalide, réessayez \n");
                break;

        }
    } while (choice != 0);

}

int main() {
    menu();
    return 0;
}