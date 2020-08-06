#ifndef _MAPS_H
#define _MAPS_H

typedef enum {
	PNJ_RIEN,
	PNJ_VIEUX
} perso_t;

struct pnj {
	int x;
	perso_t nom;
};

struct map {
	struct pnj pnj[3];
};

int getMap(struct map *m, int id);

#endif
