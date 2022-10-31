#include <stdlib.h>
#include <stdio.h>
//énumération des types de case
#include "Case.h"
//structure du jeu
#include "Game.h"


/*

const char* path -> chemin vers le fichier où se trouve les infos de la map
const int size -> taille d'un coté du tableau 2D
int* map -> pointeur vers un tableau 2D

charger le fichier se trouvant au path, et stocker toutes les infos dans le tableau map
accès à la position x, y de map -> map[y*size+x]

*/

int loadMap(char* path, const int size, int* map) {
	FILE* flux_entree = fopen(path, "r");
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	char* buffer = (char*)malloc(sizeof(char)*size);
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
			else if (buffer[j] == 'D'){ //chemin vers bloc 4
				map[i*size + j] = DAY_NIGHT_DOOR;
			}
			else if (buffer[j] == 'E'){ //sortie
				map[i*size + j] = EXIT_DOOR;
			}
			else {
				map[i*size + j] = 0;
			}
		}
	}
	free(buffer);
	fclose(flux_entree);
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
  int taille = 0; //taille de s1
  int j = 0;
	
  while (s1[taille] != '\0') {
    ++taille;
  }

  // concaténer s2 dans s1
  while (s2[j] != '\0') {
    s1[taille] = s2[j]; //ici, on étend s1 à taille + j, càd on associe s1[taille] à s2[0], s1[taille + 1] à s2[1] etc...
	j++;
	taille++;
  }
	
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
	dest[taille]='\0';
}

int egaux(char *tab1, char *tab2){
	int taille1=0;
	int taille2=0;
	while (tab1[taille1] != '\0') {
    	taille1++;
  	}
	while (tab2[taille2] != '\0') {
    	taille2++;
	}
	if (taille1 != taille2){
		return 0;
	}
	for (int i=0; i<taille1; i++){
		if (tab1[i] != tab2[i]){
			return 0;
		}
	}
	return 1;
}


//Programme principal loadingFiles
/*charge toutes les données nécessaires au jeu depuis le dossier res */
int loadingFiles(int* nb_maps, Map** maps) {
	char buffer[256]; //sera utilisé pour récupérer les données des fichiers

	//définition d'un string chemin de base to_path, on devra s'en servir par la suite
	char to_path[256] = "./res/levels/";


	//On cherche le chemin vers le dossier du niveau à charger

	char levelOPT[256]; 
	duplicate(levelOPT, to_path); //copie de to_path
	concat(levelOPT, "levels.opt"); //chemin obtenue: './res/levels/levels.opt'

	printf("Scan du fichier: %s\n", levelOPT);

	FILE* flux_entree = fopen(levelOPT, "r"); // labyrinthe_0.opt contient la taille de la carte centrale et le nombre total de maps
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	
	while(fscanf(flux_entree,"%s", buffer) != EOF){
		if (egaux(buffer, "level:")){  //on trouve le premier motif 'nb_maps: '
			fscanf(flux_entree,"%s", buffer); // on sait alors que le string suivant est la donnée de nb_maps, bingo!
			break;
		}
	}
	concat(to_path, buffer);
	concat(to_path, "/");
	printf("chargement de la map à: %s\n",to_path);
	fclose(flux_entree);

	// Recherche du nombre de maps dans le jeu
	char lab0opt[256]; 
	duplicate(lab0opt, to_path); 
	concat(lab0opt,"labyrinthe_0.opt"); // lab0opt = ./res/levels/'level'/labyrinthe_0.opt
	//printf("%s\n", lab0opt);
	flux_entree = fopen(lab0opt, "r"); // labyrinthe_0.opt contient la taille de la carte centrale et le nombre total de maps
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	//printf("2\n");
	while(fscanf(flux_entree,"%s", buffer) != EOF){
		if (egaux(buffer, "nb_maps:")){  //on trouve le premier motif 'nb_maps: '
			fscanf(flux_entree,"%s", buffer); // on sait alors que le string suivant est la donnée de nb_maps, bingo!
			break;
		}
	}
	//printf("%s\n",buffer);
	//printf("%d\n",*nb_maps);
	*nb_maps = atoi(buffer); //nb_maps pointe donc vers le nombre de maps
	printf("%d à charger...\n",*nb_maps);
	fclose(flux_entree);
	
	*maps = (Map*) malloc(sizeof(Map)*(*nb_maps)); //on alloue la bonne taille à *maps
	if (*maps == NULL) return -1;

	//Définition du tableau size_maps et de maps
	for(int i = 0; i < *nb_maps; i++) { 

		//définition de path
		char num[256]; 
		sprintf(num, "%d", i);
		char path[256];
		duplicate(path, to_path); // On définit path, et on va le concaténer avec tempo pour obtenir le chemin final
		char tempo[256] = "labyrinthe_"; // On va maintenant s'occuper de tempo, pour obtenir un string de la forme
		concat(tempo,num); // tempo = labyrinthe_X
		concat(path, tempo); // path = ./src/res/levels/level_'level'/labyrinthe_X


		char path_size[256];
		duplicate(path_size, path);
		concat(path_size,".opt"); // path = ./src/res/levels/level_'level'/labyrinthe_X.opt
		
		//accès au document
		FILE* flux_entree = fopen(path_size, "r"); // accède au document
		if (flux_entree == NULL) {
			printf("erreur chargement");
			return (-1);
		}
		
		// définition de size_maps
		char taille[256];
		while(fscanf(flux_entree,"%s", taille) != EOF){
			if (egaux(taille, "size:")){  //on trouve le premier motif 'size: '
				fscanf(flux_entree,"%s", taille); // on sait alors que le string suivant est la donnée de nb_maps, bingo!
				break; 
			}
		}
		(*maps)[i].size = atoi(taille);
		fclose(flux_entree);

		// définition de maps
		char path_maps[256];
		duplicate(path_maps, path);
		concat(path_maps, ".lvl");
		
		//allocation du tableau 2D (size*size)
		(*maps)[i].labyrinthe = (int*)malloc(sizeof(int)*((*maps)[i].size)*((*maps)[i].size)); 
		if ((*maps)[i].labyrinthe == NULL) return -1;

		//chargement des valeurs du tableau 2D
		if (loadMap(path_maps,(*maps)[i].size, (*maps)[i].labyrinthe))  {
			printf("map id: %d do not load !",i);
			return -1;
		}

		printf("map %d chargée !\n", i);
	}

	printf("Toutes les maps sont chargées !\n");
	return 0;
}
