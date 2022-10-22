//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS

//Structure partie
struct Game
{
	//constantes
	int level = 1; //id du level à charger
  	int nb_map; //nombre de carte
  	int* size_maps; //tableau des tailles des cartes
  	int** maps; //tous les tableaux 2D


	//variables du jeu
  	int x_spawn, y_spawn;
  	int current_size; //taille de la carte actuelle
  	int* current_map;//carte actuelle où se trouve le joueur
  	int x_player, y_player; //position du joueur
};

//enumération des erreurs
#include<Error.h>

//énumération des types de commande utilisateur (en console)
#include<Command.h>

//énumération des types de case
#include<Case.h>

//gestion affichage en console
#include<Renderer.c>

//gestion de la lecture des ressources
#include<FileManger.c>



//instance de game
const Game game;

//FONCTION PRINCIPALE
int main() {
  	//INITIALISATION
	

  	if (loadingFiles(level, &nb_map, &size_maps, &maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//recherche du point de spawn du joueur
  	for (int m = 0; m < nb_map; m++) {
  		game.current_map = maps[m];
  		game.current_size = size_maps[m];
	  	for (int i = 0; i < current_size; i++) {

	  		for (int j = 0; j < current_size; j++) {

	  			if (current_map[i*current_size+j] == START) {
	  				game.x_spawn=i;
	  				game.y_spawn=j;
	  				game.x_player=game.x_spawn;
	  				game.y_player=game.y_player;
	  				break;
	  			}

	  		}

	  	}
  	}


  	enum Command cmd = read_console();
  	while(cmd != STOP) {
  		
  		(*Commands[cmd])();


  		//attente d'une instruction donnée par le joueur
  		cmd = read_console();
  	}
  	

}


//déplacement possible sur cette case ?
int canGoToCaseAt(int x, int y) {
	int c = game.current_map[y*game.current_size+x];
	if (c == AIR || c == SAFE) {
		return 1;
	}
	return 0;
}


//fonctions appelées par  les commandes utilisateurs (définies dans Command.h)
int up() {

	if (game.y_player+1 < game.current_size && canGoToCaseAt(game.x_player, game.y_player+1)) {
		game.y_player++;
		return 0;
	}

	print(USER_ERROR_UNMOVABLE);
	return 1;
}

int down() {

	if (game.y_player > 0 && canGoToCaseAt(game.x_player, game.y_player-1)) {
		game.y_player--;
		return 0;
	}

	print(USER_ERROR_UNMOVABLE);
	return 1;
}

int right() {

	if (game.x_player+1 < game.current_size && canGoToCaseAt(game.x_player+1, game.y_player)) {
		game.x_player--;
		return 0;
	}

	print(USER_ERROR_UNMOVABLE);
	return 1;
}

int left() {

	if (game.x_player > 0 && canGoToCaseAt(game.x_player-1, game.y_player)) {
		game.x_player--;
		return 0;
	}

	print(USER_ERROR_UNMOVABLE);
	return 1;
}