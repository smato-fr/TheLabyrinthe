//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS
#include <assert.h>

//Constante
#include "Constants.h"

//Structure partie
#include "Game.h"

//énumération des types de commande utilisateur (en console)
#include "Command.h"
const FunctionCommand Commands[]={&debug_CMD, &unknownCommand, &up, &down, &right, &left};

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
	print(PRINT_LOADING_START);
	game.level = GAME_LEVEL;
	game.renderDistance = GAME_RENDER_DISTANCE;

  	if (loadingFiles(game.level, &game.nb_map, &game.size_maps, &game.maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//recherche du point de spawn du joueur
  	
	int found = 0;	
	for (int m = 0; m < game.nb_map; m++) {

  		game.current_map = game.maps[m];
  		game.current_size = game.size_maps[m];
		
	  	for (int y = 0; y < game.current_size; y++) {

	  		for (int x = 0; x < game.current_size; x++) {
				
	  			if (game.current_map[y*game.current_size+x] == START) {
	  				game.x_spawn=x;
	  				game.y_spawn=y;
	  				game.x_player=game.x_spawn;
	  				game.y_player=game.y_spawn;
					found=1;
	  				break;
	  			}

	  		}

			if (found) break;
	  	}

		if (found) break;
  	}


	print(PRINT_LOADING_COMPLETE);

	//printf("loaded ! size_map: %d map: %d\n", game.current_size, game.current_map[0]);
	//display(game.current_map, game.current_size, 0, 0, game.current_size-1, game.current_size-1);
  	enum Command cmd = UP;
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

			display(game.current_map, game.current_size, xMin, yMin, xMax, yMax, game.x_player, game.y_player);
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

int debug_CMD() {
	return 1;
}

int unknownCommand() {
	print(USER_ERROR_UNKNOWN);
	return 0;
}

int up() {

	if (game.y_player > 0 && canGoToCaseAt(game.x_player, game.y_player-1)) {
		game.y_player--;
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int down() {

	if (game.y_player+1 < game.current_size && canGoToCaseAt(game.x_player, game.y_player+1)) {
		game.y_player++;
		return 1;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;

}

int right() {

	if (game.x_player+1 < game.current_size && canGoToCaseAt(game.x_player+1, game.y_player)) {
		game.x_player++;
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
