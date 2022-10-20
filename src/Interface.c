/*
Partie affichage et lecture en console 

 - Fichier à compléter par Louis-Eliott -

*/

#include <stdio.h>


/*

int* map -> pointeur vers un tableau 2D caractérisant la carte
int xMin, yMin -> coordonnées x, y de la case la plus en haut à gauche du tableau à afficher
int xMax, yMax -> coordonnées x, y de la case la plus basse à droite du tableau à afficher


|y/x|  0 | 1 | 2 | 3 |
______________________
| 0 |    |   |   |   |
______________________
| 1 |    | min | x | x |
______________________
| 2 |    | x | x | x |
______________________
| 3 |    | x | x | max |
______________________
x-> case à afficher

*/
void display(int* map, int xMin, int yMin, int xMax, int yMax) {

}


/*
demande à l'utilisateur d'entrer une commande sous une chaine de caractère
renvoie la commande dans le type Command
*/
enum Command read_console() {

}