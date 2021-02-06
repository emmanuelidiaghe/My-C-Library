

#ifndef AFROUNO_H
#define AFROUNO_H 1

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#define delay_ms(m) _delay_ms(m)
#define delay_us(m) _delay_us(m)
#define Delay_ms(m) _delay_ms(m)
#define Delay_us(m) _delay_us(m)

#define DEC 0
#define HEX 1


uint8_t Hi(uint16_t _m){  return ( _m/256);}
uint8_t Lo(uint16_t _m){  return ( _m%256);}

#define TRUE     1
#define FALSE    0

#define OUTPUT   1
#define INPUT    0

#define HIGH     1
#define LOW      0

#define endOfString  '\0'

#define enableGlobalInterrupt  SREG=SREG|0b10000000       //enable global intterupt
#define disableGlobalInterrupt SREG=SREG&0b01111111




void Byte2String(uint8_t hyve_byte, char* hyve_my_string){

	*(hyve_my_string+0) = (hyve_byte / 100) + 48;
	*(hyve_my_string+1) = ((hyve_byte % 100) / 10)+ 48;
	*(hyve_my_string+2) = ((hyve_byte % 100) % 10)+ 48;


	if (  ( *(hyve_my_string+0) == 48) && ( *(hyve_my_string+1) == 48)  )  {

		*(hyve_my_string+0) = *(hyve_my_string+2);
		*(hyve_my_string+1) = ' ';
		*(hyve_my_string+2) = ' ';
	}
	else{

		if ( *(hyve_my_string+0) == 48){

			*(hyve_my_string+0) = *(hyve_my_string+1);
			*(hyve_my_string+1) = *(hyve_my_string+1);
			*(hyve_my_string+2) = ' ';
		}


	}

}


void Word2String(uint16_t hyve_word, char* hyve_my_string){  //65535

	*(hyve_my_string+0) = (hyve_word / 10000) + 48;
	*(hyve_my_string+1) = ((hyve_word % 10000) / 1000)+ 48;
	*(hyve_my_string+2) = (((hyve_word % 10000) % 1000)/100)+ 48;
	*(hyve_my_string+3) = ((((hyve_word % 10000) % 1000)%100) / 10)+ 48;
	*(hyve_my_string+4) = ((((hyve_word % 10000) % 1000)%100) % 10)+ 48;

	if (  (*(hyve_my_string+0) == 48) && ( *(hyve_my_string+1) == 48) && ( *(hyve_my_string+2) == 48)&& ( *(hyve_my_string+3) == 48)      ){

		*(hyve_my_string+0) = *(hyve_my_string+4);
		*(hyve_my_string+1) = ' ';
		*(hyve_my_string+2) = ' ';
		*(hyve_my_string+3) = ' ';
		*(hyve_my_string+4) = ' ';
	}
	else{

		if (  (*(hyve_my_string+0) == 48) && ( *(hyve_my_string+1) == 48) && ( *(hyve_my_string+2) == 48)      ){

			*(hyve_my_string+0) = *(hyve_my_string+3);
			*(hyve_my_string+1) = *(hyve_my_string+4);
			*(hyve_my_string+2) = ' ';
			*(hyve_my_string+3) = ' ';
			*(hyve_my_string+4) = ' ';
		}
		else{
			if ( (*(hyve_my_string+0) == 48) && ( *(hyve_my_string+1) == 48)      ){

				*(hyve_my_string+0) = *(hyve_my_string+2);
				*(hyve_my_string+1) = *(hyve_my_string+3);
				*(hyve_my_string+2) = *(hyve_my_string+4);
				*(hyve_my_string+3) = ' ';
				*(hyve_my_string+4) = ' ';
			}
			else{

				if ( *(hyve_my_string+0) == 48) {

					*(hyve_my_string+0) = *(hyve_my_string+1);
					*(hyve_my_string+1) = *(hyve_my_string+2);
					*(hyve_my_string+2) = *(hyve_my_string+3);
					*(hyve_my_string+3) = *(hyve_my_string+4);
					*(hyve_my_string+4) = ' ';
				}


			}





		}

	}

}
void Bin2Hex(uint8_t byte, char* hyve_my_string){
	char hyve_hex[] = "0123456789ABCDEF";

	*(hyve_my_string+0) = hyve_hex[(byte / 16)];
	*(hyve_my_string+1) = hyve_hex[(byte % 16)];

}

void Byte2Hex(uint8_t byte, char* hyve_my_string){
	char hyve_hex[] = "0123456789ABCDEF";

	*(hyve_my_string+0) = hyve_hex[(byte / 16)];
	*(hyve_my_string+1) = hyve_hex[(byte % 16)];

}


#include "hal.h"
#include "sal.h"

 #endif //AFROUNO_H
