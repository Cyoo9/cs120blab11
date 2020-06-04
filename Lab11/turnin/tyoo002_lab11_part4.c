/*      Author: Taeho Yoo
 *  Partner(s) Name: 
 *      Lab Section: 23
*      Assignment: Lab #11  Exercise #4
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

unsigned char output[] = "Congratulations!";
unsigned char index;
enum keypadButtonSM_States { Start, keypad_wait, keypad_press, keypad_release};

int keypadButtonSMTick(int state) {
	unsigned char key = GetKeypadKey();
	
	switch(state) {
		case Start:
			index = 0;
			LCD_DisplayString(1, output);
			state = keypad_wait;
			break;
		case keypad_wait:
			if(key != '\0') {
				state = keypad_press;
			}
			else {
				state = keypad_wait;
			}
			break;
		case keypad_press:
			index++;
			if(index > 16) {
				index = 0;
			}
			else {
				LCD_Cursor(index);
				LCD_WriteData(key);
				state = keypad_release;
			}
			break;
		case keypad_release:
			if(key == '\0') {
				state = keypad_wait;
			}
			else {
				state = keypad_release;
			}
			break;
		default:
			break;
	}
	
       return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	DDRC = 0xFF; PORTC = 0x00;

	LCD_init();
        task task1;
	task *tasks[] = { &task1};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);


	task1.state = Start;
	task1.period = 50;
	task1.elapsedTime = task1.period;
	task1.TickFct = &keypadButtonSMTick;

	TimerSet(50);
	TimerOn();

	unsigned short i;

	while(1) {
		for(i = 0; i < numTasks; i++) {
			if(tasks[i]->elapsedTime >= tasks[i]->period) {
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += 50;
		}
		
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 0;
}
