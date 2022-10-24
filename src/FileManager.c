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
  int taille = 0; 
  int j = 0;
	
  // déterminer la taille de s1
  while (s1[taille] != '\0') {
    ++taille;
  }

  // concaténer s2 dans s1
  while (s2[j] != '\0') {
    s1[taille] = s2[j]; //ici, on étend s1 à taille + j, càd on associe s1[taille] à s2[0], s1[taille + 1] à s2[1] etc...
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
int loadingFiles(const int level, int* nb_maps, int** size_maps, int*** maps) {
	
	//définition d'un string chemin de base to_path, on devra s'en servir par la suite
	char niveau[256];
	sprintf(niveau, "%d", level); // définit un string qui contient la valeur de level, un int.
	char to_path[256] = "./src/res/levels/level_";
	concat(niveau,"/");
	concat(to_path, niveau); // to_path = ./src/res/levels/level_'level'/
	printf("%s\n",to_path);
	
	// Recherche du nombre de maps dans le jeu
	char lab0opt[256]; 
	duplicate(lab0opt, to_path); 
	concat(lab0opt,"labyrinthe_0.opt"); // lab0opt = ./src/res/levels/level_'level'/labyrinthe_0.opt
	printf("%s\n", lab0opt);
	FILE* flux_entree = fopen(lab0opt, "r"); // labyrinthe_0.opt contient la taille de la carte centrale et le nombre total de maps
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	char buffer[256];
	while(fscanf(flux_entree,"%s", buffer) != EOF){
		if (egaux(buffer, "nb_maps:")){  //on trouve le premier motif 'nb_maps: '
			fscanf(flux_entree,"%s", buffer); // on sait alors que le string suivant est la donnée de nb_maps, bingo!
			break;
		}
	}
	*nb_maps = atoi(buffer); //nb_maps pointe donc vers le nombre de maps
	printf("nb _maps = %d\n",*nb_maps);
	fclose(flux_entree);
	*size_maps = (int*)malloc(sizeof(int)*(*nb_maps));
	*maps = (int**)malloc(sizeof(int*)*(*nb_maps)); //on alloue la bonne taille à *maps

	//Définition du tableau size_maps et de maps
	for(int i = 0; i < *nb_maps; i++) { 

		//définition de path
		char num[256]; 
		sprintf(num, "%d", i);
		char path[256];
		duplicate(path, to_path); // On définit path, et on va le concaténer avec tempo pour obtenir le chemin final
		char tempo[256] = "labyrinthe_"; // On va maintenant s'occuper de tempo, pour obtenir un string de la forme
		concat(tempo,num); // tempo = labyrinthe_X
		printf("%s\n", tempo);
		printf("%s\n", path);
		concat(path, tempo); // path = ./src/res/levels/level_'level'/labyrinthe_X
		printf("%s\n", path);


		char path_size[256];
		duplicate(path_size, path);
		concat(path_size,".opt"); // path = ./src/res/levels/level_'level'/labyrinthe_X.opt
		printf("%s\n", path_size);
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
		(*size_maps)[i] = atoi(taille);
		printf("%s, %d\n", taille, (*size_maps)[i]);
		fclose(flux_entree);

		// définition de maps
		char path_maps[256];
		duplicate(path_maps, path);
		concat(path_maps, ".lvl");
		printf("%s\n",path_maps);
		(*maps)[i] = (int*)malloc(sizeof(int)*((*size_maps)[i])*((*size_maps)[i])); //définition de maps
		printf("verif1\n");
		loadMap(path_maps,(*size_maps)[i], (*maps)[i]);
		printf("verif2\n");
	}
	return 0;
}


	
void print(int* tab, int taille){
	for (int i = 0; i<taille; i++){
		for (int j = 0; j<taille; j++){
		printf("%d", tab[i*taille + j]);
		}
		printf("\n");
	}
}

void main(){
	int nb_maps;
	int* size_maps;
	int** map; 
	loadingFiles(1, &nb_maps, &size_maps, &map);
	print(map[0], size_maps[0]);
	//loadingFiles(1, nb_maps, size_maps, maps);
}
