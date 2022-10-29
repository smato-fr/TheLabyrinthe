#include <stdlib.h>
#include "Case.h"

#include <stdio.h>

//recherche le nombre d'apparatition d'un type de case dans la carte
int numberOf(const int* map, const int size, const int type) {
    int nb = 0;

    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            if (map[y*size+x] == type)	  				
                nb++;
    
    return nb;
}

//recherche des nb premières positions d'un type de case dans la carte
int lookingFor(int* pos_x, int* pos_y, const int* map, const int size, const int type, int nb) {
    
    int i = 0; //nombre d'elements actuellement trouvés

    for (int y = 0; y < size; y++) {

        for (int x = 0; x < size; x++) {
    
            if (map[y*size+x] == type) {	  				
                pos_x[i]=x;
                pos_y[i]=y;
                i++;
                if (i==nb) return i;
            }

		}
	}
    
    return i;
}


//ensemble des directions possibles (haut, bas, gauche, droite)
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


//copie chemin
int* copy_path(int* path, int length) {
    int* path2 = (int*) malloc(sizeof(int)*length);
    for (int i = 0; i < length; i++) path2[i] = path[i];
    return path2;
}

//parcours de graphe récursif en profondeur
int* graph(int* map, const int size, int x, int y, int* path, int* distance, const int dMax, const int xTarget, const int yTarget) {
    //printf("newRec\n");
    if (x == xTarget && y == yTarget) return path; //chemin trouvé !
    //printf("d:%d\n", *distance);
    if (*distance > dMax) return NULL; //chemin non trouvé
    //printf("graph: %d/%d\n", x, y, *distance);
    map[y*size+x] = SOLID; //marque la case pour ne plus y repasser
    

    int* path2 = NULL;
    int distMin;
    for (int i = 0; i < 4; i++) {
        //printf("dir:%d\n",i);
        int x2 = x + dir[i][0];
        int y2 = y + dir[i][1];

        if (map[y2*size+x2] == AIR) { //si déplacement possible vers cette case
            //printf("can go !\n");
            path[(*distance)*2] = dir[i][0];
            path[(*distance)*2+1] = dir[i][1];

            int nDistance = (*distance)+1;
            int* nPath = graph(map, size, x2, y2, path, &nDistance, dMax, xTarget, yTarget); //continue la rechercher
            if (nPath != NULL) {
                //printf("DISTANCES: %dvs%d\n", nDistance, path2 == NULL ? -1 : distMin);
                //on garde le chemin le plus court

                if (path2 == NULL || nDistance < distMin) {
                  //  printf("good !!!\n");
                    if (path2 != NULL) free(path2);
                    path2 = copy_path(nPath, nDistance*2);
                    distMin = nDistance;
                } else {
                    //printf("free nPath\n");
                    free(nPath);
                }
            }
        }
    }
    
    if (path2 != NULL) *distance = distMin;
   // printf("graph next...");
    return path2;
}

//recherche d'un chemin d'un point A à un point B dans le labyrinthe, avec une distance max dMax
int* pathFinding(const int* map, const int size, int x_A, int y_A, int x_B, int y_B, int dMax) {
   // printf("2\n");
    int* empty_path = (int*) malloc(sizeof(int)*2*(dMax+1));
    //printf("test...\n");
    int* map_copy = (int*) malloc(sizeof(int)*size*size);
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++)
            map_copy[i*size+j]=map[i*size+j];

    if (empty_path != NULL && map_copy != NULL) {
        for (int i = 0; i < (dMax+1)*2; i++) empty_path[i] = -1;
        //printf("starting graph...\n");
        int dist = 0;
        int* path = graph(map_copy, size, x_A, y_A, empty_path, &dist, dMax, x_B, y_B);
        free(empty_path);
        free(map_copy);
        //printf("graph ended !...\n");
        return path;
    } else {
        return NULL;
    }
}