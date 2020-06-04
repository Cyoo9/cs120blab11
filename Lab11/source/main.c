/*      Author: Taeho Yoo
 *  Partner(s) Name: 
 *      Lab Section: 23
*      Assignment: Lab #11  Exercise #5
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

unsigned char obstacle = '#';   
unsigned char gameOver[] = "GAME OVER";
unsigned char index1;
unsigned char index2;
unsigned char gameIndex = 1;

unsigned char game;

enum displaySM_States {Start, First, Clear, Hold};

int displaySMTick(int state) {

	switch(state) {
		case Start:
			game = 0;
			index1 = 9;
			index2 = 29;
			LCD_Cursor(index1);
			LCD_WriteData(obstacle);
			LCD_Cursor(index2);
			LCD_WriteData(obstacle);
			LCD_Cursor(gameIndex);
			state = First;
			break;
		case First:
			if(game == 1) {
				LCD_ClearScreen();
				index1--;
				index2--;
				if(index1 < 1) {
					index1 = 16;			
				}
				else {
					LCD_Cursor(index1);
					LCD_WriteData(obstacle);
				}
	
				if(index2 < 17) {
					index2 = 32;
				}
				else {
					LCD_Cursor(index2);
					LCD_WriteData(obstacle);
				}
				
				LCD_Cursor(gameIndex);

				if(gameIndex == index1 || gameIndex == index2) {
					LCD_DisplayString(1, gameOver);
					index1 = 9;
					index2 = 29;
					gameIndex = 1;
					game = 0;
					break;
				}
					
			}
			state = First;
			break;
	}
	return state;
}

enum pressButtonSM_States { button_Init, button_press, button_release };

int pressButtonSMTick(int state) {
	unsigned char press2 = ~PINA & 0x07;

	switch(state) {
		case button_Init:
			if(press2) {
				state = button_press;
			}
			else {
				state = button_Init;
			}
			break;
		case button_press:
			state = button_release;
			break;
		case button_release:
			if(press2) {
				state = button_release;
			}
			else {
				state = button_Init;
			}
			break;
		default:
			break;
	}
	switch(state) {
		case button_press:
			if(press2 == 0x02) {
				gameIndex = 1;
			}
			else if(press2 == 0x04) {
				gameIndex = 17;
			}
			else {
				if(game == 0) 
					game = 1;
				else 
					game  = 0;
			}
			break;
	}
	return state;
}




//int pressButtonSMTick

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0xF0; PORTA = 0x0F;
	DDRC = 0xFF; PORTC = 0x00;

	LCD_init();
        task task1, task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);


	task1.state = Start;
	task1.period = 200;
	task1.elapsedTime = task1.period;
	task1.TickFct = &displaySMTick;

	task2.state = button_Init;
	task2.period = 50;
	task2.elapsedTime = task2.period;
	task2.TickFct = &pressButtonSMTick;

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
