/*

Fichier à compléter par Elie

*/


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
	char* buffer[size];
	for (int i = 0; i < size; i++){
		fscanf(flux_entree, "%c", buffer);
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
int loadingFiles(const int level, int* nb_maps, int** size_maps, int*** maps) {
	char niveau[1];
	sprintf(niveau, "%d", level); // définit un string qui contient la valeur de level
	char to_path[256] = strcat((strcat("/",niveau)),"level./res/levels/level_"); // concatène les strings, + écriture du path jusqu'au niveau de difficulté désiré
	
	
	char tempo[256] = strcat("labyrinthe_0.opt",to_path); // on définit le chemin vers labyrinthe_0.opt
	FILE* flux_entree = fopen(tempo, "r"); // on importe les caractéristiques de labyrinthe_0, qui contiennent sa taille et le nombre total de maps
	if (flux_entree == NULL) {
		printf("erreur chargement");
		return (-1);
	}
	char* buffer[256];
	fscanf(flux_entree, "nb_maps: %d", buffer); // On donne à buffer la première valeur du style "nb_maps: %d", qui est présent dans labyrinthe_0.opt.
	*nb_maps = atoi(buffer[9]); //on définit nb_maps en premier le chiffre du buffer et en le convertissant en int avec atoi, ce qui est bien, c'est que atoi convertira tous les éléments du buffer en int à partir du 9e, jusqu'à trouver une lettre ou que le stirng finisse.

	
	
	for (int i = 0; i < *nb_maps, i++) { //définition du tableau size
		char num[1]; // string qui devra contenir le numéro du labyrinthe désiré
		sprintf(num, "%d", i); // définit le string num comme contenant l'unique caractère i
		char terminaison[16] = strcat(".lvl", (strcat(num,"labyrinthe_"))); //définit le string de terminaison (pour accéder à la bonne carte de labyrinthe)
		char path[256] = strcat(terminaison, to_path); //définit le path final, ./res/levels/level_'level'/labyrinthe_X.lvl
		FILE* flux_entree = fopen(path, "r"); // accède au document
		if (flux_entree == NULL) {
			printf("erreur chargement");
			return (-1);
		}
		char taille[256];
		fscanf(flux_entree, "size: %d", taille); //on trouve le premier motif tq size : %d où %d représente 2 entiers consécutifs (ce n'est pas un problème, la reconnaissance avec %d s'arrête au premier espace au sens large.
		size_maps[i] = atoi(taille[6]); //Même si la taille fait 2 chiffres, atoi va convertir ce string à partir du 6e élément et continuer pour obtenir un unique int, jusqu'à trouver une lettre ou finir le string !
	}
	
	
	for (int i=0; i<*nb_maps; i++) { // définition de maps
		*maps[i] = (int*)malloc(sizeof(int)*size[i]*size[i]);
		loadMap(path,size[i],*maps[i]);
	}
	return 0; 
}

	
	
	
