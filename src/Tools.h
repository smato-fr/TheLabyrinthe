//Toutes fonctions utilitaires

//recherche le nombre d'apparatition d'un type de case dans la carte
int numberOf(const int* map, const int size, const int type);


//recherche des nb premières positions d'un type de case dans la carte
int lookingFor(int* pos_x, int* pos_y, const int* map, const int size, const int type, int nb);

//recherche d'un chemin d'un point A à un point B dans le labyrinthe, avec une distance max dMax
int* pathFinding(const int* map, const int size, int x_A, int y_A, int x_B, int y_B, int dMax);