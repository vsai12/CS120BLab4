/*	Author: vhuan025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES { SM_Start, SM_Wait0, SM_Wait1, SM_Release0, SM_Release1 } SM_STATE;

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; //configure portA as inputs
        DDRB = 0xFF; PORTB = 0x00; //configure portB as outputs
        unsigned char tmpA = 0x00; //temp var to hold value of A
	SM_STATE = SM_Start;
        while (1) {		
		tmpA = PINA & 0x01; //get PA0
		switch(SM_STATE) {
			case SM_Start:
				SM_STATE = SM_Wait0;
				PORTB = 0x01;
				break;
			case SM_Wait0:
				if(tmpA == 0x01) 
					SM_STATE = SM_Release0;
				else
					SM_STATE = SM_Wait0;
				break;
			case SM_Release0:
				if(tmpA == 0x00)
                                        SM_STATE = SM_Wait1;
                                else
                                        SM_STATE = SM_Release0;
                                break;
			case SM_Wait1:
                                if(tmpA == 0x01)
                                        SM_STATE = SM_Release1;
                                else
                                        SM_STATE = SM_Wait1;
                                break;
			case SM_Release1:
                                if(tmpA == 0x00)
                                        SM_STATE = SM_Wait0;
                                else
                                        SM_STATE = SM_Release1;
				break;
			default:
				SM_STATE = SM_Wait0;
				break;
		}
		//actions
		switch(SM_STATE) {
			case SM_Start:
				break;
			case SM_Wait0:
				break;
			case SM_Release0:
				PORTB = 0x02;
				break;
			case SM_Wait1:
				break;
			case SM_Release1:
                                PORTB = 0x01;
                                break;
		}
        }
        return 1;
}
