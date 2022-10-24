/*
Partie affichage et lecture en console 

 - Fichier à compléter par Louis-Eliott -

*/

#include <stdio.h>
#include <string.h>
//énumération des types de commande utilisateur (en console)
#include "Command.h"
#include "Case.h"
char Characteres[]={' ', ' ', 'S', 'X', '?', '+', 'Z', 'F', '!', '$', 'T', 'P', '/','E'};

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
void display(int* map, int xMin, int yMin, int xMax, int yMax, int size) 
{
	/* parcours des lignes du tableau */
	for (int i = xMin; i < xMax; i++)
	{
		/*parcours des colonnes du tableau */
		for (int j = yMin; j < yMax; j++)
		{
			/* les printf correspondent a l affichage des differents caracteres associe aux commandes */
			/* test si la case est vide ou si c est la safe zone */
			if (map[i*size + j] == SAFE or map[i*size + j] == AIR)
			{
				printf('%c ', ' ');
			}
			/* test si la case est le point de depart */
			if (map[i*size + j] == START)
			{
				printf('%c ', 'S');
			}
			/* test si la case est un mur */
			if (map[i*size + j] == SOLID)
			{
				printf('%c ', 'X');
			}
			/* test si la case est un coffre */
			if (map[i*size + j] == CHEST)
			{
				printf('%c ', '?');
			}
			/* test si la case est un coffre rare */
			if (map[i*size + j] == RARE_CHEST)
			{
				printf('%c ', '+');
			}
			/* test si la case est un lit */
			if (map[i*size + j] == BED)
			{
				printf('%c ', 'Z');
			}
			/* test si la case est une forge */
			if (map[i*size + j] == FORGE)
			{
				printf('%c ', 'F');
			}
			/* test si la case est un point d apparition du griffeur */
			if (map[i*size + j] == SCRATCHER_SPAWN)
			{
				printf('%c ', '!');
			}
			/* test si la case est un parchemin contenant un bout du mot de passe*/
			if (map[i*size + j] == PARCHMENT)
			{
				printf('%c ', '$');
			}
			/* test si la case est un piege */
			if (map[i*size + j] == TRAP)
			{
				printf('%c ', 'T');
			}
			/* test si la case est un passage secret */
			if (map[i*size + j] == SECRET_PASSAGE)
			{
				printf('%c ', 'P');
			}
			/* test si la case est un levier */
			if (map[i*size + j] == LEVER)
			{
				printf('%c ', '/');
			}
			/* test si la case est une des 4 entrees pour acceder aux 4 autres labyrinthes */
			if (map[i*size + j] == ENTRY1 or map[i*size + j] == ENTRY2 or map[i*size + j] == ENTRY3 or map[i*size + j] == ENTRY4)
			{
				printf('%c ', 'E');
			}
		}
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
