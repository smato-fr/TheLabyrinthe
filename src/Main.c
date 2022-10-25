//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS
#include <assert.h>
#include <stdlib.h>


//Constante
#include "Constants.h"

//Structure partie
#include "Game.h"

//énumération des types de commande utilisateur (en console)
#include "Command.h"
const FunctionCommand Commands[]={&debug_CMD, &unknownCommand, &help, &up, &down, &right, &left};

//énumération des types de case
#include "Case.h"

//gestion affichage en console
#include "Interface.h"

//gestion de la lecture des ressources
#include "FileManager.h"

//fonctions utiles
#include "Tools.h"


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

	for (int m = 0; m < game.nb_map; m++) {

  		game.current_map = game.maps[m];
  		game.current_size = game.size_maps[m];
		
		int x;
		int y;

	  	if (lookingFor(&x, &y, game.current_map, game.current_size, START)) {
			game.x_spawn=x;
			game.y_spawn=y;
			game.x_player=x;
			game.y_player=y;
			break;
		}
  	}


	print(PRINT_LOADING_COMPLETE);

	//printf("loaded ! size_map: %d map: %d\n", game.current_size, game.current_map[0]);
	//display(game.current_map, game.current_size, 0, 0, game.current_size-1, game.current_size-1);
  	enum Command cmd = UP;
  	while(cmd != STOP) {
  		
  		if (Commands[cmd]()>0) {
			int xMin = game.x_player-game.renderDistance;
			int yMin = game.y_player-game.renderDistance;

			int xMax = game.x_player+game.renderDistance;
			int yMax = game.y_player+game.renderDistance;

			if (xMin<0)xMin=0;
			if (yMin<0)yMin=0;
			if (xMax>=game.current_size)xMax=game.current_size-1;
			if (yMax>=game.current_size)yMax=game.current_size-1;

			clearConsole();
			display(game.current_map, game.current_size, xMin, yMin, xMax, yMax, game.x_player, game.y_player);
  		}


  		//attente d'une instruction donnée par le joueur
  		cmd = read_console();
  	}
  	


	//désallocation mémoire
	for (int m = 0; m < game.nb_map; m++) {
		free(game.maps[m]);
	}
	free(game.maps);
	free(game.size_maps);
}


//déplacement possible sur cette case ?
int goToCaseAt(int x, int y) {
	int c = game.current_map[y*game.current_size+x];
	if (c == AIR || c == SAFE || c == START) {
		return 1;
	}

	if (c == ENTRY1) {
		if (game.current_map == game.maps[0]) {
			game.current_map = game.maps[1];
			game.current_size = game.size_maps[1];
		} else {
			game.current_map = game.maps[0];
			game.current_size = game.size_maps[0];
		}
		
		
		lookingFor(&game.x_spawn, &game.y_spawn, game.current_map, game.current_size, ENTRY1);
		game.x_player=game.x_spawn;
		game.y_player=game.y_spawn;
		return 2;
	}

	if (c == ENTRY2) {
		if (game.current_map == game.maps[0]) {
			game.current_map = game.maps[2];
			game.current_size = game.size_maps[2];
		} else {
			game.current_map = game.maps[0];
			game.current_size = game.size_maps[0];
		}

		lookingFor(&game.x_spawn, &game.y_spawn, game.current_map, game.current_size, ENTRY2);
		game.x_player=game.x_spawn;
		game.y_player=game.y_spawn;
		return 2;
	}

	if (c == ENTRY3) {
		if (game.current_map == game.maps[0]) {
			game.current_map = game.maps[3];
			game.current_size = game.size_maps[3];
		} else {
			game.current_map = game.maps[0];
			game.current_size = game.size_maps[0];
		}

		lookingFor(&game.x_spawn, &game.y_spawn, game.current_map, game.current_size, ENTRY3);
		game.x_player=game.x_spawn;
		game.y_player=game.y_spawn;
		return 2;
	}

	if (c == ENTRY4) {
		if (game.current_map == game.maps[0]) {
			game.current_map = game.maps[4];
			game.current_size = game.size_maps[4];
		} else {
			game.current_map = game.maps[0];
			game.current_size = game.size_maps[0];
		}

		lookingFor(&game.x_spawn, &game.y_spawn, game.current_map, game.current_size, ENTRY4);
		game.x_player=game.x_spawn;
		game.y_player=game.y_spawn;
		return 2;
	}

	print(USER_ERROR_UNMOVABLE);
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

int help() {
	print("\n");
	print("déplacement: up/down/left/right \n");
	print("\n");
	return 0;
}

int up() {

	if (game.y_player > 0) {

		int answer = goToCaseAt(game.x_player, game.y_player-1);
		if (answer == 1) game.y_player--;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int down() {

	if (game.y_player+1 < game.current_size) {

		int answer = goToCaseAt(game.x_player, game.y_player+1);
		if (answer == 1) game.y_player++;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;

}

int right() {

	if (game.x_player+1 < game.current_size) {

		int answer = goToCaseAt(game.x_player+1, game.y_player);
		if (answer == 1) game.x_player++;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

int left() {

	if (game.x_player > 0) {

		int answer = goToCaseAt(game.x_player-1, game.y_player);
		if (answer == 1) game.x_player--;

		return answer;
	}
	print(USER_ERROR_UNMOVABLE);
	return 0;
}
