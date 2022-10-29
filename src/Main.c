//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS
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


//INITIALISATION
int init() {


	print(PRINT_LOADING_START);
	
	//chargement des valeurs initiales (voir Constants.h)
	game.level = GAME_LEVEL;
	game.dayDuration = GAME_DAY_DURATION;
	game.nightDuration = GAME_NIGHT_DURATION;
	
	game.accessLevel = 1;
	game.force = GAME_STAT_STRENGHT;
	game.speed = GAME_STAT_SPEED;
	game.perception = GAME_STAT_PERCEPTION;
	game.xp = 0;
	game.lever= GAME_LEVER_DOWN;
	onDay();

  	if (loadingFiles(game.level, &game.nb_map, &game.maps)) {//chargement des fichier 
  		print("erreur lors du chargement des fichiers");
		return -1; //erreur détéctée
	}

	for (int m = 0; m < game.nb_map; m++) { //pour chaque map
		//recherche du nombre de griffeur dans la map
		game.maps[m].scratcherNumber = numberOf(game.maps[m].labyrinthe, game.maps[m].size, SCRATCHER_SPAWN);
		//allocation d'un tableau à 2D (nombre de griffeurs * 2) 
		//(2 entiers, un pour la pos x et l'autre pour y)
		game.maps[m].scratcherPositon = (int*) malloc(sizeof(int)*game.maps[m].scratcherNumber*2);
	
		if (game.maps[m].scratcherPositon == NULL) return -1; //si erreur
	}

	return 0;
}


//ARRET DU PROGRAMME
void shutdown() {
	//désallocation mémoire
	//attention si erreurs lors du chargement, les pointeurs peuvent être nuls
	if (game.maps != NULL) {
		for (int m = 0; m < game.nb_map; m++) {
			if (game.maps[m].labyrinthe != NULL)
				free(game.maps[m].labyrinthe);

			if (game.maps[m].scratcherPositon != NULL)
				free(game.maps[m].scratcherPositon);
		}
		
		free(game.maps);
	}
}


//FONCTION PRINCIPALE
int main() {

	//INITIALISATION
  	if (init()) {

		//en cas d'erreur
		shutdown();
		return -1;
	}

	//DEMARRAGE DU JEU

  	//recherche du point de spawn du joueur

	for (int m = 0; m < game.nb_map; m++)  { //pour chaque map

  		game.current_map = (game.maps[m]);
		
		int x;
		int y;

	  	if (lookingFor(&x, &y, game.current_map.labyrinthe, game.current_map.size, START, 1)) { //recherche le point START dans la map
			//si point trouvé, copie de ses positions
			game.x_spawn=x;
			game.y_spawn=y;

			//place le joueur sur le point de spawn
			game.x_player=x;
			game.y_player=y;
			break;
		}
  	}


	print(PRINT_LOADING_COMPLETE); //chargement terminé !


  	enum Command cmd = UP;

	//MAINLOOP (boucle principale du jeu)
  	while(cmd != STOP) { //arrêt du jeu si commande stop détéctée
		
		//déplacement des griffeurs
		if (game.night) {
			for (int i = 0; i < game.current_map.scratcherNumber; i++) {
				//debug("pathfinding start");
				int scratcher_x = game.current_map.scratcherPositon[2*i];
				int scratcher_y = game.current_map.scratcherPositon[2*i+1];
				int* path = pathFinding(game.current_map.labyrinthe, game.current_map.size, scratcher_x, scratcher_y, game.x_player, game.y_player, GAME_SCRATCHER_PERCEPTION);
				if (path != NULL) {
					//debug("path found");
					//printf("scratcher: %d/%d\n", game.current_map.scratcherPositon[i*2], game.current_map.scratcherPositon[i]);
					int x_goto = game.current_map.scratcherPositon[i*2] + path[0];
					int y_goto = game.current_map.scratcherPositon[i*2+1] + path[1];
					//printf("path: %d/%d\n", path[0], path[1]);
					game.current_map.scratcherPositon[2*i]=x_goto;
					game.current_map.scratcherPositon[2*i+1]=y_goto;
					//printf("scratcher: %d/%d\n", game.current_map.scratcherPositon[i], game.current_map.scratcherPositon[i]);
					free(path);
				}
				//debug("pathfinding end");
			}
		}
		
		//execution de la fonction associée à la cmd
  		if (CommandsFct[cmd]()>0) { //puis si retour stt positif affichage du labyrinthe
			//détermination des coordonnées des extrémités d'un cube en fct de la distance de vue, et en placant le joueur au centre 

			//position minimale d'affichage
			int xMin = game.x_player-game.perception;
			int yMin = game.y_player-game.perception;

			//position maximale d'affichage
			int xMax = game.x_player+game.perception;
			int yMax = game.y_player+game.perception;

			//si le joueur est trop proche du bord, il ne sera pas placé au centre 
			//on ne peut pas afficher ce qui est hors du tableau
			if (xMin<0)xMin=0;
			if (yMin<0)yMin=0;
			if (xMax>=game.current_map.size)xMax=game.current_map.size-1;
			if (yMax>=game.current_map.size)yMax=game.current_map.size-1;

			clearConsole(); //fait de la place dans la console
			//affichage du labyrinthe
			display_labyrinthe(game.current_map.labyrinthe, game.current_map.size, xMin, yMin, xMax, yMax, game.x_player, game.y_player, game.current_map.scratcherPositon, game.current_map.scratcherNumber); 
			//affichage du temps
			display_time(game.night, game.time);
  		}


  		//attente d'une instruction donnée par le joueur
  		cmd = read_console();
  	}
  	
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
		game.time--; //le temps avance


	int c = game.current_map.labyrinthe[y*game.current_map.size+x]; //type de la case
	return CasesFct[c](); //appel de la fonction correspondante au type
}




//fonctions appelées par  les commandes utilisateurs (définies dans Command.h)

//fct utilisée pour le debuggage
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

	if (game.y_player+1 < game.current_map.size) {

		int answer = goToCaseAt(game.x_player, game.y_player+1);
		if (answer == 1) game.y_player++;

		return answer;
	}

	print(USER_ERROR_UNMOVABLE);
	return 0;

}

//déplacement vers la droite
int right() {

	if (game.x_player+1 < game.current_map.size) {

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
	//si le pointeur labyrinthe de la map où se trouve le joueur est le même que celui de la map 0
	//alors le joueur se trouve dans la map 0
	//sinon le joueur se trouve dans la map 1
	if (game.current_map.labyrinthe == game.maps[0].labyrinthe) {
		game.current_map = game.maps[1]; //déplacement vers la map 1
	} else {
		game.current_map = game.maps[0]; //déplacement vers la map2
	}
	
	//met le joueur à l'entrée correspondante
	lookingFor(&game.x_spawn, &game.y_spawn, game.current_map.labyrinthe, game.current_map.size, ENTRY1, 1);
	game.x_player=game.x_spawn;
	game.y_player=game.y_spawn;
	return 2;
}

//vers labyrinthe2
int entry2(){
	if (game.current_map.labyrinthe == game.maps[0].labyrinthe) {
		game.current_map = game.maps[2];
	} else {
		game.current_map = game.maps[0];
	}

	lookingFor(&game.x_spawn, &game.y_spawn, game.current_map.labyrinthe, game.current_map.size, ENTRY2, 1);
	game.x_player=game.x_spawn;
	game.y_player=game.y_spawn;
	return 2;
}

//vers labyrinthe3
int entry3(){
	if (game.current_map.labyrinthe == game.maps[0].labyrinthe) {
		game.current_map = game.maps[3];
	} else {
		game.current_map = game.maps[0];
	}

	lookingFor(&game.x_spawn, &game.y_spawn, game.current_map.labyrinthe, game.current_map.size, ENTRY3, 1);
	game.x_player=game.x_spawn;
	game.y_player=game.y_spawn;
	return 2;
}

//vers labyrinthe4
int entry4(){
	if (game.current_map.labyrinthe == game.maps[0].labyrinthe) {
		game.current_map = game.maps[4];
	} else {
		game.current_map = game.maps[0];
	}

	lookingFor(&game.x_spawn, &game.y_spawn, game.current_map.labyrinthe, game.current_map.size, ENTRY4, 1);
	game.x_player=game.x_spawn;
	game.y_player=game.y_spawn;
	return 2;
}


//interaction avec un coffre 
int chest() {
	if(game.force >= GAME_CHEST_FORCE){
		game.xp +=  GAME_CHEST_XP;
		game.force -= GAME_CHEST_FORCE;
		print(PRINT_GAME_COFFRE_SUCCES);
	}
	else {
		print(PRINT_GAME_COFFRE_ECHEC);
	}
	return 0;
}

//interaction avec un coffre rare
int rareChest() {
	if(game.force >= GAME_RARE_CHEST_FORCE){
		game.xp += GAME_RARE_CHEST_XP;
		game.force -= GAME_RARE_CHEST_FORCE;
		print(PRINT_GAME_COFFRE_SUCCES);
	}
	else {
		print(PRINT_GAME_COFFRE_ECHEC);
	}
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
	char buffer[256];
	int niveau;
	forgeInteract(game.xp, game.speed, game.force, (game.perception-1), buffer, &niveau);
	if (game.xp < niveau){
		print(USER_ERROR_DATA);
	} else {
		 if ((buffer[0] == 'v')){
			if ((game.speed + niveau <= GAME_STAT_SPEED_MAX)) {
				game.speed += niveau;
				game.xp -= niveau;
				print(PRINT_GAME_FORGE);
			} else {
				print(PRINT_GAME_FORGE_LEVEL_MAX);
			}
		} 
		else if ((buffer[0] == 'f')){
			if ((game.force + niveau <= GAME_STAT_STRENGHT_MAX)) {
				game.force += niveau;
				game.xp -= niveau;
				print(PRINT_GAME_FORGE);
			} else {
				print(PRINT_GAME_FORGE_LEVEL_MAX);
			}
		} 
		else if ((buffer[0] == 'p')){
			if ((game.perception + niveau <= GAME_STAT_PERCEPTION_MAX)) {
				game.perception += niveau;
				game.xp -= niveau;
				print(PRINT_GAME_FORGE);
			} else {
				print(PRINT_GAME_FORGE_LEVEL_MAX);
			}
		} 
		else{
			print("Erreur, cette compétence n'existe pas. (Ecrivez bien en minuscules)");
		}
	}
	return 0;
}

//interaction avec un parchemin
int parchement() {
	return 0;
}

//interaction avec un piège
int trap() {
	print(PRINT_GAME_TRAP);
	return 2;
}

//interaction avec un passage secret
int secretPassage() {
	if (game.lever == 0){
		return 1;
	}
	else {
		return 0;
	}
}
//interaction avec un levier
int lever() {
	game.lever = 1;
	print(PRINT_GAME_LEVER);
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
	if (lookingFor(&x, &y, game.current_map.labyrinthe, game.current_map.size, DAY_NIGHT_DOOR, 1)) { //recherche de la case porte
		if (x == game.x_player && y == game.y_player) {
			//le joueur est écrasé :/
			onDie();
		}
	}


	//apparition des griffeurs
	int* pos_x = (int*) malloc(sizeof(int)*game.current_map.scratcherNumber);
	int* pos_y = (int*) malloc(sizeof(int)*game.current_map.scratcherNumber);
	if (pos_x != NULL && pos_y != NULL) {
		lookingFor(pos_x, pos_y, game.current_map.labyrinthe, game.current_map.size, SCRATCHER_SPAWN, game.current_map.scratcherNumber);
		for (int i = 0; i < game.current_map.scratcherNumber; i++) {
			//printf("scratcher: %d/%d", pos_x[i], pos_y[i]);
			game.current_map.scratcherPositon[2*i]=pos_x[i];
			game.current_map.scratcherPositon[2*i+1]=pos_y[i];
		}
		
		free(pos_x);
		free(pos_y);
	} else {
		debug("malloc error");
	}
}