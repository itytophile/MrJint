#include <stdio.h>
#include <assert.h>
#include <endian.h>

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

int main() {
	struct map map1, cache;
	FILE *f;
	int choix, i, nb;
	
	printf("1: Ecriture Fichier\n0: Lecture fichier\n> ");
	scanf("%d", &choix);
	
	if(choix) {
		f = fopen("maps.mj", "wb");
		puts("Ecriture...");
		map1.pnj[0].x = htobe32(64);
		map1.pnj[0].nom = htobe32(PNJ_VIEUX);
		map1.pnj[1].nom = htobe32(PNJ_RIEN);
		fwrite(&map1, sizeof(struct map), 1, f);
		fclose(f);
	} else {
		f = fopen("maps.mj", "rb"); assert(f);
		i = 0;
		while(fread(&cache, sizeof(struct map), 1, f)) {
			puts("==========");
			printf("map %d:\n", ++i);
			puts("pnj :");
			nb = 0;
			while(nb < 3 && be32toh(cache.pnj[nb].nom) != PNJ_RIEN) {
				switch(be32toh(cache.pnj[nb].nom)) {
					case PNJ_VIEUX:
						printf("vieux | ");
				}
				printf("%d\n", be32toh(cache.pnj[nb].x));
				++nb;
			}
			puts("FIN");
		}
		fclose(f);
	}
	puts("Sans encombre");
	return 0;
}