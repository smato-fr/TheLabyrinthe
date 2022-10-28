
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