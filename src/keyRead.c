#include <keyboard.h>

#include "keyRead.h"

void keyboardRead(keyboard_t *kb) {
	volatile uint8_t *p = keyboard_stateBuffer();
	for(int i = 0; i < 10; ++i) kb->k[i] = p[i];
}

int inputReader(keyboard_t *kb, key_t k1, key_t k2) {
	if(!k1) k1 = k2;
	if(!k1) {
		for(int i = 0; i < 10; ++i) if(kb->k[i]) return 0;
		return 1;
	}
	if(k1 == k2) k2 = 0;
	//the first digit of k1 is the position in the kb array. We must get it with k1&0x0f.
	//the second digit of k1 is the bit position in kb[x] where we can see if the key is down.
	//we get this second digit with k1>>4. To check if the bit = 1, we shift the whole number by the second digit then we compare it with &1.
	if(
		(( kb->k[k1&0x0f] >> (k1>>4) ) & 1)
		&&
		(!k2 || (( kb->k[k2&0x0f] >> (k2>>4) ) & 1))
	) return 1;
	return 0;
}