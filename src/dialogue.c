#include <timer.h>
#include <gray.h>
#include <display.h>
#include <keyboard.h>
#include <string.h>

#include "maps.h"
#include "ressources.h"

#include "dialogue.h"

void talk(perso_t p, char *str) {
	char output[40];
	int offset_x = 0, offset_y = 0, i;
	
	text_configure(&pol_police, color_black);
	
	while(*str) {
		gclear();
		if(*str != '\n') {
			str++; //pour eviter %
			switch(*str) { //detection du perso qui parle
				case 'j':
					offset_x = 0;
					offset_y = 35;
					break;
				case 'p':
					offset_x = 35;
					offset_y = 0;
					break;
				default:
					gtext(0, 0, "Erreur");
					gupdate();
					getkey();
					return;
			}
		}
		
		str++;
		i = 0;
		do output[i++] = *(str++);
		while(*str != '%' && *str != '\n' && *str != '\0');
		output[i] = '\0';
		gimage_part(DWIDTH-TAILLE_AVA, DHEIGHT-TAILLE_AVA, &img_ava, 0, 0, TAILLE_AVA, TAILLE_AVA); //affichage jint
		gimage_part(0, 0, &img_ava, 0, p*TAILLE_AVA, TAILLE_AVA, TAILLE_AVA); //affichage pnj
		gtext(offset_x, offset_y, output);
		gupdate();
		getkey();
	}
	
	gclear();
}