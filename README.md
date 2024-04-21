# projet_s2_CDataframe
Projet Semestre 2 : CDataframe, SANGLIER Sidney &amp; EL HASSANI Sabrina

Lien du Projet Github : https://github.com/Sidnehh/projet_s2_CDataframe/

Description du projet :
  L'idée du projet est d'implémenter une librairie de fonctions en C permettant à un utilisateur de manipuler un "DataFrame", une structure de données sous forme de tableau
  de valeurs, dont l'utilisation se rapproche d'un tableur de calcul. 
  Grâce à cette librairie que nous appellerons "CDataFrame", il sera alors possible de se servir d'un DataFrame via le langage C, à la manière dont la librairie "Panda" permet
  de faire de même en Python.
  
Etat actuel du dépôt :
  Le dépot est composé de trois fichiers permettant son utilisation :
  - main.c : Le programme principal, regroupant l'ensemble des fonctions prêtes à l'utilisation dans un "menu" que l'utilisateur peut exécuter afin de créer un DataFrame par saisie.
  - FonctionsColonnes.h/c : Les fonctions permettant la manipulation des colonnes
  - FonctionsCdataFrame.h/c : Les fonctions permettant la manipulation de DataFrame en les considérant comme tableau de colonnes.

Remarques supplémentaires :
  - Le Dataframe est interprété comme un tableau dynamique de colonnes pour l'instant, mais il est prévu qu'on l'implémente sous forme de liste doublement chaînée.
  - La branche "main" du dépôt Github est celle prête à l'utilisation, elle ne permet pas encore aux colonnes de contenir des valeurs autres que des entiers.
  - La version du dépôt permettant aux colonnes de contenir d'autres types de variables n'est pas encore prête à l'emploi, on peut la retrouver dans la branche "sidney" du dépôt.
  - Actuellement, il y a des bugs par rapport aux encodages des caractères spéciaux contenant des accents.
