/*      Author: Taeho Yoo
 *  Partner(s) Name: 
 *      Lab Section: 23
*      Assignment: Lab #11  Exercise #1
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "keypad.h"
#include "scheduler.h"
#include "io.h"
#include "timer.h"

#endif

/*unsigned char GetKeypadKey() {
	PORTA = 0xEF;
	asm("nop");
	if(GetBit(PINA, 0) == 0) { return('1'); }
	if(GetBit(PINA, 1) == 0) { return('4'); }
	if(GetBit(PINA, 2) == 0) { return('7'); }
	if(GetBit(PINA, 3) == 0) { return('*'); }

	PORTA = 0xDF;
	asm("nop");
	if(GetBit(PINA,0) == 0) { return('2'); }
	PORTA = 0xBF;
	asm("nop");
	return('\0');
}*/
int main(void) {
    /* Insert DDR and PORT initializations */
	unsigned char x;
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	while(1) {
		x = GetKeypadKey();
		switch(x) {
			case '\0': PORTB = 0x00; break;
			case '1': PORTB = 0x01; break;
			case '2': PORTB = 0x02; break;
			case '3': PORTB = 0x03; break;
			case '4': PORTB = 0x04; break;
			case '5': PORTB = 0x05; break;
			case '6': PORTB = 0x06; break;
			case '7': PORTB = 0x07; break;
			case '8': PORTB = 0x08; break;
			case '9': PORTB = 0x09; break;
			case 'A': PORTB = 0x0A; break;
			case 'B': PORTB = 0x0B; break;
			case 'C': PORTB = 0x0C; break;
			case 'D': PORTB = 0x0D; break;
			case '*': PORTB = 0x0E; break;
			case '0': PORTB = 0x00; break;
			case '#': PORTB = 0x0F; break;

			default: PORTB = 0x00; break;
		}
	}
	return 0;
}
