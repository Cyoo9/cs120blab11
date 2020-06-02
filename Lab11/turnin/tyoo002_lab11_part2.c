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

enum States {Start, First} state;

unsigned char phrase[] = "CS120B is Legend... wait for it DARY!                ";
unsigned char output[17];
unsigned char index; 

void Tick() {
	switch(state) {
		case Start:
			index = 0;
			state = First;
			for(unsigned char j = 0; j < 17; ++j) {
				output[j] = ' ';
			}
			output[16] = '\0';
			break;
		case First:
			for(unsigned char i = 0; i < 15; ++i) {
				output[i] = output[i+1];
			} 
			output[15] = phrase[index];
			index++;
			if(phrase[index] == '\0') {
				state = Start;
			}
			else 
			{
				state = First;
			}

			LCD_DisplayString(0, output);
			break;
		default:
			break;
	}
}

			
int main(void) {
    /* Insert DDR and PORT initializations */
	
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	LCD_init();
	TimerSet(300);
	TimerOn();
	while(1) {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
