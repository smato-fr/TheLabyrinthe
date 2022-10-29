
//fait de la place sur la console
void clearConsole();

//affichage du temps
void display_time(int night, int time);
//affichage d'une partie du labyrinthe en console
void display_labyrinthe(int* map, int size, int xMin, int yMin, int xMax, int yMax, int xPlayer, int yPlayer, int* scratcherPos, int scratcherNumber);

//interaction du joueur avec la forge
void forgeInteract(int xp, int vitesse, int force, int perception, char buffer[256], int* nb_exp);

/*
demande à l'utilisateur d'entrer une commande sous une chaine de caractère
renvoie la commande dans le type Command
*/
enum Command read_console();

//affichage en console d'un string
void print(char* str);

//affichage en console si le debuggage est activé
void debug(char* str);

