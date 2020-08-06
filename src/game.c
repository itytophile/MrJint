#include <gray.h>
#include <timer.h>
#include <keyboard.h>
#include <stdio.h>
#include <display.h>

#include "keyRead.h"
#include "animation.h"
#include "ressources.h"
#include "maps.h"
#include "dialogue.h"

#include "game.h"

void title() {
	gclear();
	gimage(0, 0, &img_title);
	gupdate();
	getkey();
}

struct paquet_jeu {
	int x;
	char frame;
	enum {RIEN, GAUCHE, DROITE, KICK, ACT} choix;
	enum {FREE, HIT, DIA} etat;
	struct map map;
};

void affiche_pnj(struct map *m);

keyboard_t clavier;

void callback_jeu(struct paquet_jeu *pak) {
	gclear();
	if(pak->etat == FREE) {
		//input
		keyboardRead(&clavier);
		//mouvements
		if(inputReader(&clavier, KEY_LEFT, 0) || inputReader(&clavier, KEY_4, 0)) pak->choix = GAUCHE;
		else if(inputReader(&clavier, KEY_RIGHT, 0) || inputReader(&clavier, KEY_6, 0)) pak->choix = DROITE;
		else pak->choix = RIEN;
		//actions
		if(inputReader(&clavier, KEY_SHIFT, 0)) pak->choix = KICK;
		else if(inputReader(&clavier, KEY_EXE, 0)) pak->choix = ACT;
		//traitement
		switch(pak->choix) {
			case GAUCHE:
				if(pak->x > 0) pak->x--;
				goto dessin;
			case DROITE:
				if(pak->x < 128) pak->x++;
				dessin: spriteRun(pak->x-XJINT/2, 30, &img_jintrun, XJINT, YJINT, JRUNF, &(pak->frame));
				break;
			case KICK:
				pak->etat = HIT;
				pak->frame = 0;
				break;
			case ACT:
				pak->etat = DIA;
				break;
			default:
				spriteRun(pak->x-XJINT/2, 30, &img_jint, XJINT, YJINT, JIDLEF, &(pak->frame));
		}
	}
	if(pak->etat == HIT) {
		spriteRun(pak->x-XJINT/2, 30, &img_jintkick, XJINT, YJINT, JKICKF, &(pak->frame));
		if(!pak->frame) pak->etat = FREE;
	}
	
	//gestion de la carte
	affiche_pnj(&pak->map);
	gline(0, 61, 127, 61, color_black);
	gupdate();
}

void jeu() {
	struct paquet_jeu pak;
	pak.x = 110;
	pak.frame = 0;
	pak.choix = RIEN;
	pak.etat = FREE;
	if(!getMap(&pak.map, 0)) return;
	
	key_t out = 0;
	
	timer_t *chrono = timer_create(1000/FRAMERATE, 0);
	timer_attach(chrono, callback_jeu, &pak);
	timer_start(chrono);
	
	while(out != KEY_EXIT) {
		out = getkey();
		if(pak.etat == DIA) {
			timer_stop(chrono);
			talk(PNJ_VIEUX, "%jSalut vieux.\nIl se passe quoi ici ?%ptg fils de pute");
			pak.etat = FREE;
			timer_start(chrono);
		}
	}
	
	timer_destroy(chrono);
}

void affiche_pnj(struct map *m) {
	image_t *img;
	int i = 0;
	while(i < 3 && m->pnj[i].nom != PNJ_RIEN) {
		switch(m->pnj[i].nom) {
			case PNJ_VIEUX:
				img = &img_vieux;
			default:
				img = &img_vieux;
		}
		gimage(m->pnj[i].x-XJINT/2, 30, img);
		++i;
	}
}