/*      Author: Taeho Yoo
 *  Partner(s) Name: 
 *      Lab Section: 23
*      Assignment: Lab #11  Exercise #2
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

enum States {Start, First, Second, Third} state;
unsigned char i; //36 characters total in the string
void Tick() {
	switch(state) {
		case Start:
			i = 16;
			state = First;
			break;
		case First:
			if(i > 0) {
				LCD_DisplayString(i, "CS120B is Legend... wait for it DARY!");
				i--;
				state = First;
			}
			else {	
				LCD_DisplayString(1, "S120B is Legend.");
				i = 16;
				state = Second;
			}	
			break;
		case Second:
			if(i > 0) {
				LCD_DisplayString(i, "
		case Third:
		default:
			break;
	}


			
int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRC = 0xFF; PORTC = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	LCD_init();
	TimerSet(100);
	TimerOn();
	while(1) {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
