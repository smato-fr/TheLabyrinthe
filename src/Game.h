#if !defined(_GAME_H_) //test si pas déjà importé 
  
  #define _GAME_H_
  
  //Contient toutes les informations sur une carte
  typedef struct Map {
    int size; //taille du labyrinthe
    int* labyrinthe; //tableau 2D décrivant le contenu du labyrinthe
    int scratcherNumber; //nombre de griffeur
    int* scratcherPositon; //positions des griffeurs
  }Map;

  //Contient toutes les informations de la partie
  typedef struct Game {
    //constantes
    int level; //id du level à charger
    int nightDuration;
    int dayDuration;

    //à charger dans les fichiers
    int nb_map; //nombre de carte
    Map* maps; //tous les tableaux 2D

    //variables du jeu
    
    //position du point d'apparition
    int x_spawn;
    int y_spawn;
    
    Map current_map;//carte actuelle où se trouve le joueur
    Map spawn_map;

    int scratcherPerception; //portée de détection en cases des griffeurs
    
    int time; //cycle jour nuit
    int night; //0-> jour, 1-> nuit

    int lever; //0 -> Pas activé, 1 -> Activé

    //position du joueur
    int x_player;
    int y_player; 

    //capacités
    int speed; //durée pour effectuer une action
    int force; //utile pour ouvrir les coffres
    int force_capacity; //Capacité de force max
    int perception; //distance de vue
    int xp; //xp du joueur
    int accessLevel; //niveau d'accès dans le labyrinthe

    
    
  }Game;

  void onDie();
  void onDay();
  void onNight();
  void refreshScratcherPosition();

#endif
