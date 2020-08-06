#include <bfile.h>

#include "maps.h"

#define STORAGE "\\\\fls0\\"
#define SDCARD "\\\\crd0\\"

void strToPath(char *str, uint16_t *fc, char *p) {
	while(*p) *fc++ = *p++;
	while((*fc = *str)) fc++, str++;
}

int getMap(struct map *m, int id) {
	uint16_t path[15];
	int f, t;
	if(id < 0) return 0;
	strToPath("maps.mj", path, STORAGE);
	f = BFile_Open(path, BFile_ReadOnly);
	if(f < 0) {
		BFile_Close(f);
		return 0;
	}
	t = BFile_GetFileSize(f);
	if(t < (id+1)*sizeof(struct map) || t%sizeof(struct map)) { //Si le fichier a certains blemes
		BFile_Close(f);
		return 0;
	}
	if(BFile_Read(f, m, sizeof(struct map), id*sizeof(struct map)) <= 0) {
		BFile_Close(f);
		return 0;
	}
	BFile_Close(f);
	return 1;
}