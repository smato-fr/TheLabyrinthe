
//recherche de la position d'un élément dans la carte (renvoie les nb premier-s- trouvé-s-)
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