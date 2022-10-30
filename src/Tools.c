#include <stdlib.h>
#include "Case.h"

#include <stdio.h>
#include <assert.h>


//structure liste dynamique chainée 
typedef struct List {
    int x;
    int y;
    struct List* next;
}List; 


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


//ensemble des directions possibles (gauche, droite, haut, bas)
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


//copie chemin
int* copy_path(int* path, int length) {
    int* path2 = (int*) malloc(sizeof(int)*length);
    for (int i = 0; i < length; i++) path2[i] = path[i];
    return path2;
}


//parcours de graphe itératif en largeur
int* graph(int* map, const int size, int x, int y, int* path, const int dMax, const int xTarget, const int yTarget) {
    if (x == xTarget && y == yTarget) return NULL; //arrivée et départ identiques 
    //printf("1\n");
    List* arrivee = (List*) malloc(sizeof(List));
    arrivee->x = xTarget;
    arrivee->y = yTarget;
    arrivee->next = NULL;

    map[yTarget*size+xTarget] = SOLID;
    //printf("2\n");
    map[y*size + x] = AIR;
    //printf("3\n");
    List* dynamic_list = arrivee;

    int* back_x = (int*) malloc(sizeof(int)*size*size); //permet de retracer le chemin à l'envers si trouvé (pos en x)
    int* back_y = (int*) malloc(sizeof(int)*size*size); //permet de retracer le chemin à l'envers si trouvé (pos en y)
    
    if (back_x == NULL || back_y == NULL) return NULL;

    int found = 0;
    int dist = 0;

    while (dynamic_list != NULL && dist < dMax) { //tant que la liste n'est pas vide
         //printf("searching... !\n");
        dist++;
        List* liste = dynamic_list; //on copie la liste principale
        dynamic_list = NULL; //on vide la liste principale
        while (liste != NULL) //pour chaque elt de l'ancienne liste
        {          
           
            //on va ajouter tous les cases adjacentes accessibles et non marquées
            List* pos = liste;
            
            //printf("for: %d/%d\n",pos->x, pos->y);
        
            for (int i = 0; i < 4; i++) {
                //printf("dir:%d\n",i);
                int x2 = pos->x + dir[i][0];
                int y2 = pos->y + dir[i][1];

                if (x2 < 0 && x2 >= size && y2 < 0 && y2 >= size) continue; //si position en dehors de la map

                if (map[y2*size + x2] == AIR) { //si la case est accessible et non marqué
                    //printf("canGoTO! %d/%d\n", x2, y2);
                    List* element= (List*) malloc(sizeof(List));
                    element->x = x2;
                    element->y = y2;
                    element->next = dynamic_list;
                    
                    dynamic_list = element;

                    map[y2*size + x2] = SOLID;  //on marque la case pour ne plus y repasser
                    //on pointe sur l'element precedent en inversant la direction
                    back_x[y2*size+x2] = -dir[i][0];
                    back_y[y2*size+x2] = -dir[i][1];
                    //printf("set to %d/%d\n", -dir[i][0], -dir[i][1]);

                    if (x2 == x && y2 == y) {
                        //printf("found.........!\n");
                        found = 1;
                        while (liste != NULL)//s'il reste des elts dans la liste on libère la mémoire
                        { 
                            List* l2 = liste;
                            liste=liste->next;
                            free(l2);
                        }
                        while (dynamic_list != NULL) {//s'il reste des elts dans la liste on libère la mémoire
                            List* l2 = dynamic_list;
                            dynamic_list=dynamic_list->next;
                            free(l2);
                        }
                        break;
                    }
                }
            }
            if (!found) {
                liste=pos->next; //passage à l'elt suivant
                free(pos);
            }
        }

        
    
    }

   
    
    
    if (found) {
        //printf("found!");
        int pos_x = x;
        int pos_y = y;
        int dist = 0;
        while (!(pos_x == xTarget && pos_y == yTarget))
        {
            if (dist > dMax) {
                //printf("ERROOOOOR\n");
                exit(EXIT_FAILURE);
            }
            //printf("for %d/%d\n", pos_x, pos_y);
            int dir_x = back_x[pos_y*size + pos_x];
            int dir_y = back_y[pos_y*size + pos_x];
           // printf("dir: %d/%d\n",dir_x, dir_y);
            path[dist*2] = dir_x;
            path[dist*2 + 1] = dir_y;
            pos_x+=dir_x;
            pos_y+=dir_y;
            dist++;
        }
        free(back_x);
        free(back_y);
        return path;
    }
    
    free(back_x);
    free(back_y);
    return NULL;
}

//recherche d'un chemin d'un point A à un point B dans le labyrinthe, avec une distance max dMax
int* pathFinding(const int* map, const int size, int x_A, int y_A, int x_B, int y_B, int dMax) {
    //printf("2\n");
    int* empty_path = (int*) malloc(sizeof(int)*2*(dMax+1));
    //printf("test...\n");
    int* map_copy = (int*) malloc(sizeof(int)*size*size);
    for (int i = 0; i < size; i++) 
        for (int j = 0; j < size; j++)
            map_copy[i*size+j]=map[i*size+j];

    if (empty_path != NULL && map_copy != NULL) {
        for (int i = 0; i < (dMax+1)*2; i++) empty_path[i] = 0;
        //printf("starting graph...\n");
        
        int* path = graph(map_copy, size, x_A, y_A, empty_path, dMax, x_B, y_B);
        if (path == NULL) free(empty_path);
        free(map_copy);
       // printf("graph ended !...\n");
        return path;
    } else {
        return NULL;
    }
}