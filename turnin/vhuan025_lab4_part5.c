/*	Author: vhuan025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #5
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <stdbool.h>
#endif


enum SM_STATES { SM_Start, SM_Wait, SM_WRelease, SM_RRelease } SM_STATE;

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; //configure portA as inputs
        DDRB = 0xFF; PORTB = 0x00; //configure portC as outputs
        unsigned char tmpA = 0x00; //temp var to hold value of A
	unsigned char tmpA2 = 0x00;
	bool locked = true;
	int sequence[] = {4,1,2,1};
	int count = 0;
	SM_STATE = SM_Start;
        while (1) {		
		tmpA = PINA & 0x07; //get PA0 & PA1 & PA2
		tmpA2 = PINA & 0x80; //get PA7
		if(tmpA2 == 0x80) {
			PORTB = 0x00;
			locked = true;
		}
		switch(SM_STATE) {
			case SM_Start:
				SM_STATE = SM_Wait;
				PORTB = 0x00;
				break;
			case SM_Wait:
				if(tmpA == sequence[count]) {
					SM_STATE = SM_RRelease;
					count += 1;
					if(count == 4) {
                                        	if(locked) {
							PORTB = 0x01;
							locked = false;
						}
						else {
							PORTB = 0x00;
							locked = true;
						}
						SM_STATE = SM_WRelease;
                                	}
				}
				else if(tmpA == 0x00)
					SM_STATE = SM_Wait;
				else
					SM_STATE = SM_WRelease;
				break;
			case SM_WRelease:
				count = 0;
				if(tmpA == 0x00)
					SM_STATE = SM_Wait;
				else
					SM_STATE = SM_WRelease;
				break;
			case SM_RRelease:
				if(tmpA == 0x00)
                                        SM_STATE = SM_Wait;
                                else if(tmpA == sequence[count - 1]) 
                                        SM_STATE = SM_RRelease;
				else
					SM_STATE = SM_WRelease;
                                break;
			default:
				SM_STATE = SM_Wait;
				break;
		}
        }
        return 1;
}
