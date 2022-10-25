
//recherche de la position d'un élément dans la carte (renvoie le premier trouvé)
int lookingFor(int* pos_x, int* pos_y, const int* map, const int size, const int type) {
    
    for (int y = 0; y < size; y++) {

        for (int x = 0; x < size; x++) {
    
            if (map[y*size+x] == type) {	  				
                *pos_x=x;
                *pos_y=y;
                return 1;
            }

		}
	}
    
    return 0;
}