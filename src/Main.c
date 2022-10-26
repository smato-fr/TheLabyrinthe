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
 //fonctions à appeler quand une commande est executée
const FunctionCommand CommandsFct[]={&debug_CMD, &unknownCommand, &help, &up, &down, &right, &left};

//énumération des types de case
#include "Case.h"
 //fonctions à appeler quand le joueur essaie d'aller sur une case
const FunctionCase CasesFct[]={&air, &air, &air, &solid, &chest, &rareChest, &bed, &forge, &air, &parchement, &trap, &secretPassage, &lever, &entry1, &entry2, &entry3, &entry4, &dayNightDoor};

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
	game.dayDuration = GAME_DAY_DURATION;
	game.nightDuration = GAME_NIGHT_DURATION;
	onDay();

  	if (loadingFiles(game.level, &game.nb_map, &game.size_maps, &game.maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//recherche du point de spawn du joueur

	for (int m = 0; m < game.nb_map; m++)  { //pour chaque map

  		game.current_map = game.maps[m];
  		game.current_size = game.size_maps[m];
		
		int x;
		int y;

	  	if (lookingFor(&x, &y, game.current_map, game.current_size, START)) { //recherche le point START dans la map
			game.x_spawn=x;
			game.y_spawn=y;
			game.x_player=x;
			game.y_player=y;
			break;
		}
  	}


	print(PRINT_LOADING_COMPLETE); //chargement terminé !


  	enum Command cmd = UP;
  	while(cmd != STOP) { //arrêt du jeu si commande stop détéctée
		
		
		//execution de la fonction associée à la cmd
  		if (CommandsFct[cmd]()>0) { //puis si retour stt positif affichage du labyrinthe
			//détermination des coordonnées des extrémités d'un cube en fct de la distance de vue, et en placant le joueur au centre 

			//position minimale d'affichage
			int xMin = game.x_player-game.renderDistance;
			int yMin = game.y_player-game.renderDistance;

			//position maximale d'affichage
			int xMax = game.x_player+game.renderDistance;
			int yMax = game.y_player+game.renderDistance;

			//si le joueur est trop proche du bord, il ne sera pas placé au centre
			if (xMin<0)xMin=0;
			if (yMin<0)yMin=0;
			if (xMax>=game.current_size)xMax=game.current_size-1;
			if (yMax>=game.current_size)yMax=game.current_size-1;

			clearConsole(); //fait de la place dans la console
			//affichage du labyrinthe
			display_labyrinthe(game.current_map, game.current_size, xMin, yMin, xMax, yMax, game.x_player, game.y_player); 
			//affichage du temps
			display_time(game.night, game.time);
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

	//avancé du temps
	if (game.time<=0) {
		
		if (game.night) { //si nuit
			//mettre jour
			onDay();
		} else { //sinon
			//mettre nuit
			onNight();
		}

	} 
	else 
		game.time--;


	int c = game.current_map[y*game.current_size+x];
	return CasesFct[c]();
}




//fonctions appelées par  les commandes utilisateurs (définies dans Command.h)

int debug_CMD() {
	return 1;
}

//quand le joueur rentre une commande inconnue
int unknownCommand() {
	print(USER_ERROR_UNKNOWN);
	return 0;
}

//quand le joueur demande de l'aide
int help() {
	print("\n");
	print("déplacement: up/down/left/right (tips: zqsd)\n");
	print("\n");
	return 0;
}

//déplacement vers le haut
int up() {

	if (game.y_player > 0) {

		int answer = goToCaseAt(game.x_player, game.y_player-1);
		if (answer == 1) game.y_player--;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

//déplacement vers le bas
int down() {

	if (game.y_player+1 < game.current_size) {

		int answer = goToCaseAt(game.x_player, game.y_player+1);
		if (answer == 1) game.y_player++;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;

}

//déplacement vers la droite
int right() {

	if (game.x_player+1 < game.current_size) {

		int answer = goToCaseAt(game.x_player+1, game.y_player);
		if (answer == 1) game.x_player++;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;
}

//déplacement vers la gauche
int left() {

	if (game.x_player > 0) {

		int answer = goToCaseAt(game.x_player-1, game.y_player);
		if (answer == 1) game.x_player--;

		return answer;
	}
	print(USER_ERROR_UNMOVABLE);
	return 0;
}





//fonctions appelées quand un joueur veut aller sur une case (définies dans Case.h)

//revoie 2 si déplacement possible mais action spéciale
//renvoie 1 si déplacement possible
//renvoie 0 si déplacement impossible

//case vide
int air() {
	return 1;
}

//case mur
int solid() {
	print(USER_ERROR_UNMOVABLE);
	return 0;
}

//vers labyrinthe1
int entry1() {
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

//vers labyrinthe2
int entry2(){
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

//vers labyrinthe3
int entry3(){
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

//vers labyrinthe4
int entry4(){
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

//interaction avec un coffre 
int chest() {
	return 0;
}

//interaction avec un coffre rare
int rareChest() {
	return 0;
}

//interaction avec un lit
int bed() {
	print(PRINT_GAME_BED);
	if (game.night) {
		print(PRINT_GAME_BED_NIGHT);
		onDay();
	} else {
		print(PRINT_GAME_BED_DAY);
	}
	return 0;
}

//interaction avec une forge
int forge() {
	return 0;
}

//interaction avec un parchemin
int parchement() {
	return 0;
}

//interaction avec un piège
int trap() {
	return 2;
}

//interaction avec un passage secret
int secretPassage() {
	return 2;
}

//interaction avec un levier
int lever() {
	return 0;
}

//passage par la porte jour/nuit (ouverte seulement le jour)
int dayNightDoor() {
	if (game.night) {
		print(PRINT_GAME_DOOR_CLOSE);
		return 0;
	} else {
		return 1;
	}
}



//évènement durant le jeu:


//mort du joueur :(
void onDie() {
	if (!GOD_MOD) {
		game.x_player = game.x_spawn;
		game.y_player = game.y_spawn;
		print(PRINT_GAME_DIE);
	}
}

//quand le jour se lève
void onDay() {
	game.night = 0;
	game.time = game.dayDuration;
	print(PRINT_GAME_DAY);
}

//quand le jour se couche
void onNight() {
	game.night = 1;
	game.time = game.nightDuration;
	print(PRINT_GAME_NIGHT);
	
	//si le joueur se trouvait malencontreusement sur la case de la porte...
	int x;
	int y;
	if (lookingFor(&x, &y, game.current_map, game.current_size, DAY_NIGHT_DOOR)) { //recherche de la case porte
		if (x == game.x_player && y == game.y_player) {
			//le joueur est écrasé :/
			onDie();
		}
	}
}