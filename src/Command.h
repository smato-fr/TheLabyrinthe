#if !defined(_COMMAND_H_) //test si pas déjà importé 
  
  #define _COMMAND_H_

  //énumérations de toutes les commandes utilisateurs
  enum Command {
	  STOP=-1,
	  UP=0,
	  DOWN,
	  RIGHT,
	  LEFT,
	  

  };

  int stop();
  int run();
  int up();
  int down();
  int left();
  int right();

  const int* Commands[]={&up, &down, &right, &left};


#endif
