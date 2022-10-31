/*chargement des fichers
trouver le sous dossier L dans res/levels/levels.opt
trouver le nombre de map dans res/levels/L/labyrinthe_0.opt
charger chaque map x en trouvant sa taille dans res/levels/L/labyrinthe_x.opt
puis son contenu dans res/levels/L/labyrinthe_x.lvl 

*/
int loadingFiles(int* nb_maps, Map** maps);