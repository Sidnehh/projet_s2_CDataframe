#include <stdio.h>
#include <stdlib.h>
#include "FonctionsCDataFrame.h"
#include "FonctionsColonnes.h"

int main() {
    int choice;
    int TL = 0;
    COLUMN** cdf = NULL;

    do {
        printf("\n--- Menu CDataframe ---\n");
        printf("1. Créer, remplir et afficher un CDataframe\n");
        printf("2. Ajouter une colonne au CDataframe\n");
        printf("3. Supprimer une colonne spécifique du CDataframe\n");
        printf("4. Afficher le CDataframe actuel\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                if (cdf) {
                    printf("Un CDataframe existe déjà. Voulez-vous en créer un nouveau ?  (1 pour Oui, 0 pour Non): ");
                    int confirm;
                    scanf(" %d", &confirm);
                    if (confirm == 1) {
                        for (int i = 0; i < TL; i++) {
                            delete_column(&cdf[i]);
                        }
                        free(cdf);
                        cdf = NULL;
                        TL = 0;
                    } else {
                        break;
                    }
                }

                printf("Entrez le nombre de colonnes : ");
                scanf(" %d", &TL);
                cdf = create_empty_cdataframe(TL);
                fill_cdataframe(cdf, TL);
                print_cdataframe(cdf, TL);
                break;
            case 2:
                if (cdf) {
                    COLUMN* new_col = create_column("Nouvelle Colonne");  // Nom fixe pour la simplicité
                    add_col_cdataframe(cdf, TL, new_col);
                    TL++;  // Incrémenter la taille logique après l'ajout de la colonne

                    int numValues;
                    printf("Entrez nombre de valeurs à insérer : \n");
                    scanf(" %d", &numValues);

                    for (int j = 0; j < numValues; j++) {
                        int temp;
                        printf("Entrez valeur %d à insérer : \n", j + 1);
                        scanf(" %d", &temp);

                        // Supposons que nous ajoutons simplement la valeur à la fin du tableau existant
                        // en supposant que le tableau est suffisamment grand
                        new_col->tableau_data[new_col->taille_logique] = temp;
                        new_col->taille_logique++;
                    }
                } else {
                    printf("Veuillez d'abord créer un CDataframe.\n");
                }
                break;


            case 3:
                if (cdf && TL > 0) {
                    int colIndex;
                    printf("Entrez l'indice de la colonne à supprimer (0 à %d) : ", TL - 1);
                    scanf(" %d", &colIndex);
                    if (colIndex >= 0 && colIndex < TL) {
                        delete_column_cdf(&cdf, &TL, colIndex);
                    } else {
                        printf("Index invalide.\n");
                    }
                } else {
                    printf("Le CDataframe est vide ou aucune colonne à supprimer.\n");
                }
                break;
            case 4:
                if (cdf && TL > 0) {
                    print_cdataframe(cdf, TL);
                } else {
                    printf("Aucun CDataframe à afficher ou le CDataframe est vide.\n");
                }
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide, réessayez.\n");
        }
    } while(choice != 0);

    // Libere la mémoire avant de quitter
    if (cdf) {
        for (int i = 0; i < TL; i++) {
            delete_column(&cdf[i]);
        }
        free(cdf);
    }

    return 0;
}
