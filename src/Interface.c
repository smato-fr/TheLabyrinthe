/*
Partie affichage et lecture en console 

 - Fichier à compléter par Louis-Eliott -

*/

#include <stdio.h>
#include <string.h>
//énumération des types de commande utilisateur (en console)
#include "Command.h"

//énumération des types de case dans le labyrinthe
#include "Case.h" 
//associe à chaque case un caractère à afficher
char characteres[]={' ', ' ', ' ', 'X', '?', '+', 'L', 'F', ' ', '?', '?', '^', '?','A', 'B', 'C', 'D', '^', 'x'};

//activation du mode de debuggage 
#define DEBUG_MOD 1



//fait de la place dans la console
void clearConsole() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
}



//affichage du temps
void display_time(int night, int time) {
	if (night) {
		printf("Il fait nuit, %d heure(s) avant le jour...\n", time);
	} else {
		printf("Il fait jour, %d heure(s) avant la nuit...\n", time);
	}
}


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
(min et max inclus)
*/
void display_labyrinthe(int* map, int size, int xMin, int yMin, int xMax, int yMax, int xPlayer, int yPlayer, int* scratcherPos, int scratcherNumber) 
{
	
	/*parcours des lignes du tableau */
	for (int y = yMin; y <= yMax; y++)
	{
		/* parcours des colonnes du tableau */
		for (int x = xMin; x <= xMax; x++)
		{
			/*printf("pos: %d/%d\n", x, y);
			printf("map: %d\n",map[y*size+x]);
			printf("char: %c\n", characteres[map[y*size+x]]);*/
			
			//test si griffeur
			int notPrinted = 1;
			for (int i = 0; i < scratcherNumber; i++) {
				if (scratcherPos[2*i] == x && scratcherPos[2*i+1] == y) {
					notPrinted=0;
					printf("! ");
					break;
				}
			}

			if (notPrinted) {
				//test si joueur
				if (x == xPlayer && y == yPlayer)
				{
					printf("o "); //affiche le joueur
				}
				else 
				{
					printf("%c ",characteres[map[y*size+x]]); /*affiche le caractere associe a sa case */
				}
			}
		}
	printf("\n");
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

	
	/* test si le mot entre par l utilisateur correspond au mot associe a l action de debuggage */
	if (strcmp(mot, "debug") == 0)
	{
		/* fonction de debuggade */
		return (DEBUG);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui demande de l'aide*/
	if (strcmp(mot, "help") == 0)
	{
		/* affichage des aides pour le joueur*/
		return (HELP);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui arrête le jeu */
	if (strcmp(mot, "stop") == 0)
	{
		/* arrêt du jeu*/
		return (STOP);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en haut */
	if (strcmp(mot, "up") == 0 || strcmp(mot, "z") == 0)
	{
		/* si c est le cas alors le personnage va en haut*/
		return (UP);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller a gauche */
	if (strcmp(mot, "left") == 0 || strcmp(mot, "q") == 0)
	{
		/* si c est le cas alors le personnage va a gauche */
		return (LEFT);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en droite */
	if (strcmp(mot, "right") == 0 || strcmp(mot, "d") == 0)
	{
		/* si c est le cas alors le personnage va a droite */
		return (RIGHT);
	}
	/* test si le mot entre par l utilisateur correspond au mot associe a l action qui le fera aller en bas */
	if (strcmp(mot, "down") == 0 || strcmp(mot, "s") == 0)
	{
		/* si c est le cas alors le personnage va en bas*/
		return (DOWN);
	}

	return UNKNOWN_COMMAND;
}

//affichage en console d'un string
void print(char* str) 
{
	printf("%s\n", str);
}

void forgeInteract(int xp, int vitesse, int force, int perception, char buffer[256], int* nb_exp){
	printf("vous voici dans la forge. vous avez %d niveaux d'expérience à utiliser. Voici vos niveaux de compétence : \n Vitesse : %d/7 \t Force : %d/7 \t Perception : %d/7 \t. \n Choisissez une compétence à améliorer :", xp, vitesse, force, perception);
	scanf("%s", buffer);
	printf("\n Nombre de niveaux :");
	scanf("%d", nb_exp); 
}

//affichage en console si le debuggin mode est activé
void debug(char* str) 
{
	if (DEBUG_MOD) 
	{
		print(str);
	}
} 
