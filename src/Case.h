//énumération de tous les différents type de case
enum Case {
	SAFE = -1, //case vide protégée (déplacement possible)
	AIR = 0, //case vide (déplacement possible) 
	ENTRY, //entrée du labyrinthe
	START, //point d'apparition
	SOLID, //mur
	CHEST, //coffre
	RARE_CHEST, //coffre rare
	BED, //lit
	FORGE, //forge
	SCRATCHER_SPAWN, //griffeur
	PARCHMENT, //parchemin contenant un morceau du mdp
	TRAP, //piège
	SECRET_PASSAGE, //passage secret
	LEVER, //levier d'activation
	MAP_ENTRY //passage vers une autre carte
};