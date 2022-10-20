//FICHIER PRINCIPAL DEMARRE A L'EXECUTION


//IMPORTATIONS

//énumération des types de commande utilisateur (en console)
#include<Command.h>

//énumération des types de case
#include<Case.h>

//gestion affichage en console
#include<Renderer.c>

//gestion de la lecture des ressources
#include<FileManger.c>



//FONCTION PRINCIPALE
int main() {
  	//INITIALISATION
	int level = 1; //id du level à charger


  	//chargement des fichiers
  	int nb_map; //nombre de carte
  	int* size_maps; //tableau des tailles des cartes
  	int** maps; //tous les tableaux 2D

  	if (loadingFiles(level, &nb_map, &size_maps, &maps)) //chargement des fichier 
  		assert("erreur lors du chargement des fichiers"); //lance une exception


  	//variables du jeu
  	int x_spawn, y_spawn;
  	int current_size; //taille de la carte actuelle
  	int* current_map;//carte actuelle où se trouve le joueur
  	int x_player, y_player; //position du joueur

  	//recherche du point de spawn du joueur
  	for (int m = 0; m < nb_map; m++) {
  		current_map = maps[m];
  		current_size = size_maps[m];
	  	for (int i = 0; i < current_size; i++) {

	  		for (int j = 0; j < current_size; j++) {

	  			if (current_map[i*current_size+j] == START) {
	  				x_spawn=i;
	  				y_spawn=j;
	  				x_player=x_spawn;
	  				y_player=y_player;
	  				break;
	  			}

	  		}

	  	}
  	}


  	
}
