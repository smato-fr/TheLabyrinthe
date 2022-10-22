//énumérations de toutes les commandes utilisateurs
enum Command {
	STOP=-1,
	UP=0,
	DOWN,
	RIGHT,
	LEFT,
	

}

int stop();
int run();
int up();
int down();
int left();

const int* Commands[]={&up, &down, &right, &left};