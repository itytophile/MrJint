#include <gray.h>
#include <stdlib.h>

#include "gray.h"

void spriteRun(int x, int y, image_t *img, int tx, int ty, int nb_frame, char *frame) {
	if((*frame) >= nb_frame) (*frame) = 0;
	gimage_part(x, y, img, 0, (*frame)*ty, tx, ty);
	*frame = (*frame+1)%nb_frame;
}

void fondRun(image_t *img, int t, char *fid, int *avf, int sens) {
	int i;
	for(i = 0; i < 9; ++i) gimage_part(t*(i-sens)-*avf, 0, img, 0, t*fid[i], t, t);
	*avf += 1-2*sens;
	if(*avf*(*avf) == t*t) {
		if(sens) {
			i = 8;
			while(i > 0) {
				fid[i] = fid[i-1];
				--i;
			}
			fid[i] = rand()%8;
		} else {
			i = 0;
			while(i < 8) {
				fid[i] = fid[i+1];
				++i;
			}
			fid[i] = rand()%8;
		}
		*avf = 0;
	}
}