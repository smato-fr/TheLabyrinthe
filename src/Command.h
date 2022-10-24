#if !defined(_COMMAND_H_) //test si pas déjà importé 
  
  #define _COMMAND_H_



  //énumérations de toutes les commandes utilisateurs
  enum Command {

	  STOP=-1,
	  UNKNOW_COMMAND=0,
    UP,
	  DOWN,
	  RIGHT,
	  LEFT,
	  

  };


  //fonctions appelées à la suite d'une commande utilisateur
  int unknowCommand();
  int up();
  int down();
  int left();
  int right();

  typedef int (*FunctionCommand)(); //crée un type qui peut contenir un pointeur vers une fonction
  //tableau qui renvoie la fonction correspond à la Command. Exemple Commands[DOWN] = down();


#endif
