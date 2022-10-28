#if !defined(_GAME_H_) //test si pas déjà importé 
  
  #define _GAME_H_
  
  typedef struct Game {
    //constantes
    int level; //id du level à charger
    int nightDuration;
    int dayDuration;

    //à charger dans les fichiers
    int nb_map; //nombre de carte
    int* size_maps; //tableau des tailles des cartes
    int** maps; //tous les tableaux 2D


    //variables du jeu
    
    //position du point d'apparition
    int x_spawn;
    int y_spawn;
    
    int current_size; //taille de la carte actuelle
    int* current_map;//carte actuelle où se trouve le joueur
    
    int time; //cycle jour nuit
    int night; //0-> oui, 1-> nuit

    //position du joueur
    int x_player;
    int y_player; 

    //capacités
    int speed; //durée pour effectuer une action
    int force; //utile pour ouvrir les coffres
    int perception; //distance de vue
    int xp; //xp du joueur
    int accessLevel; //niveau d'accès dans le labyrinthe
    
  }Game;

  void onDie();
  void onDay();
  void onNight();

#endif
