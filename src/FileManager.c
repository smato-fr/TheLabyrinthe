#include <stdlib.h>
#include <stdio.h>
//énumération des types de case
#include "Case.h"


//chemin vers le fichier où se trouve tous les niveaux
#define LEVELS_PATH "./res/levels/"

/*

const char* path -> chemin vers le fichier où se trouve les infos de la map
const int size -> taille d'un coté du tableau 2D
int* map -> pointeur vers un tableau 2D

charger le fichier se trouvant au path, et stocker toutes les infos dans le tableau map
accès à la position x, y de map -> map[y*size+x]

*/

int loadMap(const char* path, const int size, int* map) {
	FILE* flux_entree = fopen(path, "r");
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	char buffer[size];
	for (int i = 0; i < size; i++){
		fscanf(flux_entree, "%s", buffer);
		for (int j=0; j < size; j++){
			if (buffer[j] == 'S'){ // recherche safe zone
				map[i*size + j] = SAFE;
			}
			else if (buffer[j] == '0'){ // recherche air
				map[i*size + j] = AIR;
			}
			else if (buffer[j] == 's'){ // spawn
				map[i*size + j] = START;
			}
			else if (buffer[j] == 'x'){ // mur
				map[i*size + j] = SOLID;
			}
			else if (buffer[j] == 'c'){ //coffre
				map[i*size + j] = CHEST;
			}
			else if (buffer[j] == 'r'){ //coffre rare
				map[i*size + j] = RARE_CHEST;
			}
			else if (buffer[j] == 'l'){ //lit
				map[i*size + j] = BED;
			}
			else if (buffer[j] == 'f'){ //forge
				map[i*size + j] = FORGE;
			}
			else if (buffer[j] == 'g'){ //spawn griffeur !!
				map[i*size + j] = SCRATCHER_SPAWN;
			}
			else if (buffer[j] == 'k'){ //parchemin
				map[i*size + j] = PARCHMENT;
			}
			else if (buffer[j] == 'T'){ //piège !!
				map[i*size + j] = TRAP;
			}
			else if (buffer[j] == 'P'){ // passage secret !
				map[i*size + j] = SECRET_PASSAGE;
			}
			else if (buffer[j] == 'L'){ //levier d'activation
				map[i*size + j] = LEVER;
			}
			else if (buffer[j] == '1'){ //chemin vers bloc 1
				map[i*size + j] = ENTRY1;
			}
			else if (buffer[j] == '2'){ //chemin vers bloc 2 
				map[i*size + j] = ENTRY2;
			}
			else if (buffer[j] == '3'){ //chemin vers bloc 3
				map[i*size + j] = ENTRY3;
			}
			else if (buffer[j] == '4'){ //chemin vers bloc 4
				map[i*size + j] = ENTRY4;
			}
		}
	}
	return 0;
}

/*

const int level -> indice du niveau à charger (dans: ./res/levels/level_'level'/)
int* nb_maps -> entier à modifier, nombre de total de maps
int** size_maps -> pointeur à modifier, pointe sur un tableau d'entier ()
int*** maps -> pointeur à modifier, pointe sur nb_map pointeurs pointant eux memes chacun sur un tableau 2D (carte du jeu) 

1) charger le fichier level_0.opt
- définir nb_maps
- créer un tableau de taille nb_maps dans size_maps
- définir size_maps[0] avec "size"
2) charger les nb_maps-1 fichiers restants (de level_1 à level_'nb_maps-1')
- définir size_maps[i]
3) charger chacune des maps dans maps
- créer un tableau de pointeur de taille nb_maps, il s'agit de int *** maps
- le remplir avec des pointeurs sur des tableaux 2D
- remplir les tableaux 2D avec la fonction loadMap
*/



/* On définit quelques fonctions auxiliaires qui nous serons utiles*/
int concat(char s1[], char s2[]){ //concaténer deux strings
  int taille = 0; 
  int j = 0;
	
  // déterminer la taille de s1
  while (s1[taille] != '\0') {
    ++taille;
  }

  // concaténer s2 dans s1
  while (s2[j] != '\0') {
    s1[taille] = s2[j]; //ici, on étend s1 à taille + j, càd on associé s1[taille] à s2[0], s1[taille + 1] à s2[1] etc...
	j++;
	taille++;
  }

  // Il faut bien sûr terminer le string s1 !
  s1[taille] = '\0';
  return 0;
}



void duplicate(char dest[], char source[]){ //dupliquer un string source vers un string dest
	int taille=0;
	while (source[taille] != '\0') {
    	++taille;
  	}
	for (int i = 0; i<taille; i++){
		dest[i] = source[i];
	}
}



int prendre_int(char str[], int n){ //renvoie le premier int contenu dans un string, en cherchant à partir de la nieme position, jusqu'à rencontrer un caractère qui ne soit pas un chiffre.
    int taille=0;
	while (str[taille] != '\0') {
    	++taille;
  	}
    char tempo[taille];
    for (int i = 0; i<=(taille-n); i++){
        tempo[i] = str[i+n];
    }
    int val =atoi(tempo);
    return val;
}




//Programme principal loadingFiles
int loadingFiles(const int level, int* nb_maps, int** size_maps, int*** maps) {
	
	//définition d'un string chemin de base to_path, on devra s'en servir par la suite
	char niveau[256];
	sprintf(niveau, "%d", level); // définit un string qui contient la valeur de level, un int.
	char to_path[256] = "level./res/levels/level_";
	concat(niveau,"/");
	concat(to_path, niveau); // to_path = ./res/levels/level_'level'/
	
	
	// Recherche du nombre de maps dans le jeu
	char lab0opt[256]; 
	duplicate(lab0opt, to_path); 
	concat(lab0opt,"labyrinthe_0.opt"); // lab0opt = ./res/levels/level_'level'/labyrinthe_0.opt
	FILE* flux_entree = fopen(lab0opt, "r"); // labyrinthe_0.opt contient la taille de la carte centrale et le nombre total de maps
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	char buffer[256];
	fscanf(flux_entree, "nb_maps: %s", buffer); //on trouve le premier motif 'nb_maps: %s', où %s représente le string contenant le nombre de cartes (la reconnaissance avec %s s'arrête au premier espace au sens large).
	*nb_maps = prendre_int(buffer, 9); //nb_maps pointe donc vers le nombre de maps


	
	//Définition du tableau size_maps et de maps
	for(int i = 0; i < *nb_maps; i++) { 

		//définition de path
		char num[256]; 
		sprintf(num, "%d", i);
		char path[256];
		duplicate(path, to_path); // On définit path, et on va le concaténer avec tempo pour obtenir le chemin final
		char tempo[256] = "labyrinthe_"; // On va maintenant s'occuper de tempo, pour obtenir un string de la forme
		concat(tempo,num); // tempo = labyrinthe_X
		concat(tempo,".lvl"); // tempo = labyrinthe_X.lvl
		concat(path, tempo); // path = ./res/levels/level_'level'/labyrinthe_X.lvl
		
		//accès au document
		FILE* flux_entree = fopen(path, "r"); // accède au document
		if (flux_entree == NULL) {
			printf("erreur chargement");
			return (-1);
		}
		
		// défiition de size_maps
		char taille[256];
		fscanf(flux_entree, "size: %s", taille); 
		*size_maps[i] = prendre_int(taille, 6); 
	
		// définition de maps
		*maps[i] = (int*)malloc(sizeof(int)*(*size_maps[i])*(*size_maps[i])); //définition de maps
		loadMap(path,*size_maps[i],*maps[i]);
	}
	return 0; 
}
	
	
	
