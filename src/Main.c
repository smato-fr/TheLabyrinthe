//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS
#include <assert.h>


//Structure partie
#include "Game.h"

//enumération des erreurs
#include "Error.h"

//énumération des types de commande utilisateur (en console)
#include "Command.h"
const FunctionCommand Commands[]={&unknowCommand, &up, &down, &right, &left};

//énumération des types de case
#include "Case.h"

//gestion affichage en console
#include "Interface.h"

//gestion de la lecture des ressources
#include "FileManager.h"



//instance de game
Game game;

//FONCTION PRINCIPALE
int main() {
  	//INITIALISATION
	game.level = 1;

  	if (loadingFiles(game.level, &game.nb_map, &game.size_maps, &game.maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//recherche du point de spawn du joueur
  	for (int m = 0; m < game.nb_map; m++) {
  		game.current_map = game.maps[m];
  		game.current_size = game.size_maps[m];
	  	for (int i = 0; i < game.current_size; i++) {

	  		for (int j = 0; j < game.current_size; j++) {

	  			if (game.current_map[i*game.current_size+j] == START) {
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
  		
  		if (Commands[cmd]()) {
  			//display(); //TODO
  		}


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
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int down() {

	if (game.y_player > 0 && canGoToCaseAt(game.x_player, game.y_player-1)) {
		game.y_player--;
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int right() {

	if (game.x_player+1 < game.current_size && canGoToCaseAt(game.x_player+1, game.y_player)) {
		game.x_player--;
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int left() {

	if (game.x_player > 0 && canGoToCaseAt(game.x_player-1, game.y_player)) {
		game.x_player--;
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}
