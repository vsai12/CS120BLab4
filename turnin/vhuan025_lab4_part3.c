/*	Author: vhuan025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES { SM_Start, SM_Wait, SM_WRelease, SM_RRelease, SM_RWait } SM_STATE;

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; //configure portA as inputs
        DDRB = 0xFF; PORTB = 0x00; //configure portC as outputs
        unsigned char tmpA = 0x00; //temp var to hold value of A
	unsigned char tmpA2 = 0x00;
	SM_STATE = SM_Start;
        while (1) {		
		tmpA = PINA & 0x07; //get PA0 & PA1 & PA2
		tmpA2 = PINA & 0x80; //get PA7
		if(tmpA2 == 0x80) 
			PORTB = 0x00;
		switch(SM_STATE) {
			case SM_Start:
				SM_STATE = SM_Wait;
				PORTB = 0x00;
				break;
			case SM_Wait:
				if(tmpA == 0x01)
					SM_STATE = SM_WRelease;
				else if(tmpA == 0x02)
					SM_STATE = SM_WRelease;
				else if(tmpA == 0x04)
					SM_STATE = SM_RRelease;
				else
					SM_STATE = SM_Wait;
				break;
			case SM_WRelease:
				if(tmpA == 0x00)
					SM_STATE = SM_Wait;
				else
					SM_STATE = SM_WRelease;
				break;
			case SM_RRelease:
				if(tmpA == 0x00)
                                        SM_STATE = SM_RWait;
                                else if(tmpA == 0x04) 
                                        SM_STATE = SM_RRelease;
				else
					SM_STATE = SM_WRelease;
                                break;
			case SM_RWait:
				if(tmpA == 0x02) {
					PORTB = 0x01;
					SM_STATE = SM_WRelease;
				}
                                else if(tmpA == 0x00) 
                                        SM_STATE = SM_RWait;
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
