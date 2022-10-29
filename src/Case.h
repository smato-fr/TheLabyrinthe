#if !defined(_CASE_H_) //test si pas déjà importé 
  
  #define _CASE_H_
  
  //énumération de tous les différents type de case
  enum Case {
	  SAFE, //case vide protégée (déplacement possible)
	  AIR, //case vide (déplacement possible)
	  START, //point d'apparition
	  SOLID, //mur
	  CHEST, //coffre
	  RARE_CHEST, //coffre rare
	  BED, //lit
	  FORGE, //forge
	  SCRATCHER_SPAWN, //griffeur
	  PARCHMENT, //parchemin contenant un morceau du mdp
	  TRAP, //piège
	  SECRET_PASSAGE, //passage secret
	  LEVER, //levier d'activation
	  ENTRY1, // Passage bloc 1
	  ENTRY2, // Passage bloc 2
	  ENTRY3, // Passage bloc 3
	  ENTRY4, // Passage bloc 4	
	  DAY_NIGHT_DOOR, // Porte qui se ferme la nuit pour que la zone safe soit bien sécurisée !
	  EXIT;
  };

  	//fonction appelées quand on va vers la case
	int air();
	int solid();
	int chest();
	int rareChest();
	int bed();
	int forge();
	int parchement();
	int trap();
	int secretPassage();
	int lever();
	int entry1();
	int entry2();
	int entry3();
	int entry4();
	int dayNightDoor();
	int exit();

   	typedef int (*FunctionCase)(); //crée un type qui peut contenir un pointeur vers une fonction

  	//à utiliser pour créer un tableau qui renvoie la fonction correspondante à la Case. Exemple Cases[SOLID] = solid();

  
#endif 
