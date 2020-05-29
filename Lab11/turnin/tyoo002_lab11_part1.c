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

enum State {Start} state;
unsigned char x;

void Tick() {
	switch(state) {
		case Start:
			x = GetKeypadKey();
			if(x == '0') 
				PORTB = 0x00;
			else if(x == '1')
				PORTB = 0x01;
			else if(x == '2')
				PORTB = 0x02;
			else if(x == '3')
				PORTB = 0x03;
			else if(x == '4') 
				PORTB = 0x04;
			else if(x == '5') 
				PORTB = 0x05;
			else if(x == '6')
				PORTB = 0x06;
			else if(x == '7')
				PORTB = 0x07;
			else if(x == '8')
				PORTB = 0x08;
			else if(x == '9')
				PORTB = 0x09;
			else if(x == 'A')
				PORTB = 0x0A;
			else if(x == 'B')
				PORTB = 0x0B;
			else if(x == 'C')
				PORTB = 0x0C;
			else if(x == 'D')
				PORTB = 0x0D;
			else if(x == '*')
				PORTB = 0x0E;
			else if(x == '#')
				PORTB = 0x0F;
			else
				PORTB = 0x00;
			break;
		default:
			PORTB = 0x00;
			state = Start;
			break;
	}
}
			

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;

	state = Start;
	while(1) {
		Tick();
	}
	return 0;
}
