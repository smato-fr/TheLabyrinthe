//affichage d'une partie du labyrinthe en console
void display(int* map, int size, int xMin, int yMin, int xMax, int yMax);

/*
demande à l'utilisateur d'entrer une commande sous une chaine de caractère
renvoie la commande dans le type Command
*/
enum Command read_console();

//affichage en console d'un string
void print(char* str);

//affichage en console si le debuggin mode est activé
void debug(char* str);
