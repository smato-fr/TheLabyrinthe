#if !defined(_GAME_H_) //test si pas déjà importé 
  
  #define _GAME_H_
  
  typedef struct Game {
    //constantes
    int level = 1; //id du level à charger
    int nb_map; //nombre de carte
    int* size_maps; //tableau des tailles des cartes
    int** maps; //tous les tableaux 2D


    //variables du jeu
    
    //position du point d'apparition
    int x_spawn;
    int y_spawn;
    
    int current_size; //taille de la carte actuelle
    int* current_map;//carte actuelle où se trouve le joueur
    
    //position du joueur
    int x_player;
    int y_player; 
  }Game;
  
#endif
