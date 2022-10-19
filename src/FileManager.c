
//chemin vers le fichier où se trouve tous les niveaux
#define LEVELS_PATH "./res/levels/"

/*

const char* path -> chemin vers le fichier où se trouve les infos de la map
const int size -> taille d'un coté du tableau 2D
int* map -> pointeur vers un tableau 2D

charger le fichier se trouvant au path, et stocké toutes les infos dans le tableau map
accès à la position x, y de map -> map[y*size+x]

*/

void loadMap(const char* path, const int size, int* map) {
	//TODO
}

/*

const int level -> indice du niveau à charger (dans: ./res/levels/level_'level'/)
int* nb_maps -> entier à modifier, nombre de total de maps
int** size_maps -> pointeur à modifier, pointe sur un tableau d'entier ()
int*** maps -> pointeur à modifier, pointe sur nb_map pointeurs pointant eux memes sur chacun sur un tableau 2D (carte du jeu) 

1) charger le fichier level_0.opt
- définir nb_maps
- créer un tableau de taille nb_maps dans size_maps
- définir size_maps[0] avec "size"
2) charger les nb_maps-1 fichiers restants (de level_1 à level_'nb_maps-1')
- définir size_maps[i]
3) charger chacune des maps dans maps
- créer un tableau de pointeur de taille nb_maps
- le remplir avec des pointeurs sur des tableaux 2D
- remplir les tableaux 2D avec la fonction loadMap
*/
int loadingFiles(const int level, int* nb_maps, int** size_maps, int*** maps) {
	//TODO

	return -1;
	//return 0; //renvoie 0 si tout se passe bien
}