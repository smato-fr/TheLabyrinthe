//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS
#include <assert.h>


//Structure partie
#include "Game.h"

//enumération des erreurs
#include "Error.h"

//énumération des types de commande utilisateur (en console)
#include "Command.h"
const FunctionCommand Commands[]={&unknownCommand, &up, &down, &right, &left};

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
	game.renderDistance = 10;

  	if (loadingFiles(game.level, &game.nb_map, &game.size_maps, &game.maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//recherche du point de spawn du joueur
  	
	int searching = 1;	
	for (int m = 0; m < game.nb_map && searching; m++) {
  		game.current_map = game.maps[m];
  		game.current_size = game.size_maps[m];
		
	  	for (int i = 0; i < game.current_size && searching; i++) {

	  		for (int j = 0; j < game.current_size; j++) {

	  			if (game.current_map[i*game.current_size+j] == START) {
	  				game.x_spawn=i;
	  				game.y_spawn=j;
	  				game.x_player=game.x_spawn;
	  				game.y_player=game.y_player;
					searching=0;
	  				break;
	  			}

	  		}

	  	}
  	}



	printf("loaded ! size_map: %d map: %d\n", game.current_size, game.current_map[0]);
	display(game.current_map, game.current_size, 0, 0, game.current_size-1, game.current_size-1);
  	enum Command cmd = read_console();
  	while(cmd != STOP) {
  		
  		if (Commands[cmd]()) {
			int xMin = game.x_player-game.renderDistance;
			int yMin = game.y_player-game.renderDistance;

			int xMax = game.x_player+game.renderDistance;
			int yMax = game.y_player+game.renderDistance;

			if (xMin<0)xMin=0;
			if (yMin<0)yMin=0;
			if (xMax>=game.current_size)xMax=game.current_size-1;
			if (yMax>=game.current_size)yMax=game.current_size-1;

			display(game.current_map, game.current_size, xMin, yMin, xMax, yMax);
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

int unknownCommand() {
	print(USER_ERROR_UNKNOWN);
	return 0;
}

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
