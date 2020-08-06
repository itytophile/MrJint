#ifndef _KEYREAD_H
#define _KEYREAD_H

typedef struct { uint8_t k[10];} keyboard_t;

void keyboardRead(keyboard_t *kb);
int inputReader(keyboard_t *kb, key_t k1, key_t k2);

#endif
