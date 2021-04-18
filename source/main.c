/*	Author: vhuan025
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #4 Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SM_STATES { SM_Start, SM_Wait, SM_Reset, SM_Release0, SM_Release1 } SM_STATE;

int main(void) {
        DDRA = 0x00; PORTA = 0xFF; //configure portA as inputs
        DDRC = 0xFF; PORTC = 0x00; //configure portC as outputs
        unsigned char tmpA = 0x00; //temp var to hold value of A
	unsigned char tmpC = 0; //temp var to hold value of C
	SM_STATE = SM_Start;
        while (1) {		
		tmpA = PINA & 0x03; //get PA0 & PA1
		switch(SM_STATE) {
			case SM_Start:
				SM_STATE = SM_Wait;
				tmpC = 0x07;
				break;
			case SM_Wait:
				if(tmpA == 0x03) {
					SM_STATE = SM_Reset;
					tmpC = 0;
				}
				else if(tmpA == 0x02) {
					SM_STATE = SM_Release1;
					if(tmpC > 0)	
						tmpC -= 1;
				}
				else if(tmpA == 0x01) {
					SM_STATE = SM_Release0;
					if(tmpC < 9) {
						tmpC += 1;
					}
				}
				else {
					SM_STATE = SM_Wait;
				}
				break;
			case SM_Reset:
				if(tmpA == 0x02)
					SM_STATE = SM_Release1;
				else if(tmpA == 0x01)
					SM_STATE = SM_Release0;
				else
					SM_STATE = SM_Reset;
				break;
			case SM_Release0:
				if(tmpA == 0x00)
                                        SM_STATE = SM_Wait;
                                else if(tmpA == 0x03) {
					tmpC = 0;
                                        SM_STATE = SM_Reset;
				}
				else
					SM_STATE = SM_Release0;
                                break;
			case SM_Release1:
				if(tmpA == 0x00) 
                                        SM_STATE = SM_Wait;
                                else if(tmpA == 0x03) {
                                        tmpC = 0;
                                        SM_STATE = SM_Reset;
                                }
                                else
                                        SM_STATE = SM_Release0;
                                break;
			default:
				SM_STATE = SM_Wait;
				break;
		}
		PORTC = tmpC;
        }
        return 1;
}
