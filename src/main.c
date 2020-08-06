#include <keyboard.h>
#include <gray.h>
#include <stdlib.h>
#include <modules/rtc.h>

#include "animation.h"
#include "game.h"
#include "ressources.h"

void testage();

int main(void) {
	srand(RTC.time->R64CNT);
	gray_start();
	title();
	testage();
	jeu();
	
	gray_stop();
	return 0;
}

void testage() {
	int input = 0;
	char frames[NB_IMG] = {0};
	char fondid[9] = {0, 1, 2, 3, 4, 5, 6, 7, 0};
	int avFond = 0;
	int sens = 1;
	while(input != KEY_EXIT) {
		gclear();
		spriteRun(0, 30, &img_jintrun, XJINT, YJINT, JRUNF, frames);
		spriteRun(20, 30, &img_jint, XJINT, YJINT, JIDLEF, frames+1);
		spriteRun(40, 30, &img_jintkick, XJINT, YJINT, JKICKF, frames+2);
		fondRun(&img_fond, TAILLE_FOND, fondid, &avFond, sens);
		gupdate();
		input = getkey_opt(getkey_none, 1000/FRAMERATE);
		switch(input) {
			case KEY_SHIFT:
				sens = !sens;
		}
	}
}
