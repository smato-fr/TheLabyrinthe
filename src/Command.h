//énumérations de toutes les commandes utilisateurs
enum Command {
	STOP=-1,
	UP=0,
	DOWN,
	RIGHT,
	LEFT,
	

}

void stop();
void run();
void up();
void down();
void left();

const void* Commands[]={&up, &down, &right, &left};