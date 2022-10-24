/*
Partie affichage et lecture en console 

 - Fichier à compléter par Louis-Eliott -

*/

#include <stdio.h>
#include <string.h>
//énumération des types de commande utilisateur (en console)
#include "Command.h"
#include "Case.h"
char characteres[]={' ', ' ', 'S', 'X', '?', '+', 'Z', 'F', '!', '$', 'T', 'P', '/','E', 'E', 'E', 'E'};

//activation du mode de debuggage 
#define DEBUG_MOD 1

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
void display(int* map, int size, int xMin, int yMin, int xMax, int yMax) 
{
	/* parcours des colonnes du tableau */
	for (int i = xMin; i < xMax; i++)
	{
		/*parcours des lignes du tableau */
		for (int j = yMin; j < yMax; j++)
		{
			/*affiche le caractere associe a sa commande */
			printf("%c ",characteres[map[j*size+i]]); 
		}
	printf('\n');
	}
}

/*
demande à l'utilisateur d'entrer une commande sous une chaine de caractère
renvoie la commande dans le type Command
*/
enum Command read_console() 
{
	
	char mot[10];
	/* demande a l'utilisateur d entrer un mot */
	scanf("%s", mot);
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en haut */
	if (strcmp(mot, "up") == 0)
	{
		/* si c est le cas alors le personnage va en haut sinon il ne se passe rien*/
		return (UP);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller a gauche */
	if (strcmp(mot, "left") == 0)
	{
		/* si c est le cas alors le personnage va a gauche sinon il ne se passe rien*/
		return (LEFT);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en droite */
	if (strcmp(mot, "right") == 0)
	{
		/* si c est le cas alors le personnage va a droite sinon il ne se passe rien*/
		return (RIGHT);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en bas */
	if (strcmp(mot, "down") == 0)
	{
		/* si c est le cas alors le personnage va en bas sinon il ne se passe rien*/
		return (DOWN);
	}

	return UNKNOWN_COMMAND;
}

//affichage en console d'un string
void print(char* str) 
{
	printf("(%s)\n", str);
}

//affichage en console si le debuggin mode est activé
void debug(char* str) 
{
	if (DEBUG_MOD) 
	{
		print(str);
	}
} 
