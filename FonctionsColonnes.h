

#ifndef TEST__COLONNES_H
#define TEST__COLONNES_H

#include "FonctionsCDataFrame.h"

COLUMN *create_column(ENUM_TYPE type, char *title);
// fonction qui crée une colonne de n'importe quel type

void delete_column(COLUMN**column);
// fonction qui libère une colonne

void print_col(COLUMN*column);
//fonction qui affiche une colonne

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);
// fonction qui convertit une variable de l'indice i d'une colonne en chaîne de caractères

int fill_column(COLUMN* col);
//fonction qui remplit une colonne de manière interactive

int insert_value(COLUMN* col, void* value);
//fonction qui insère une valeur de tout type dans une colomne grâce à un pointeur void, retourne 1 si l'insertion
//bien déroulée, 0 sinon

int is_digit(char*);
// fonction qui sert à verifier la saisie de l'utilisateur

int convert_to_int(char *str);
//fonctions qui servent à verifier les saisies utilisateur

#endif //TEST__COLONNES_H
