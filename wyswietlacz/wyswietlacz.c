/*
 * wyswietlacz.c
 *
 * Created: 2013-12-03 21:51:21
 *  Author: Marcin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "taski.h"

int tablica[10] = {0b11000000 ,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};

void wyswietlPierwszy() {
	PORTA = 0xFF;
	PORTB = ~0x01;
	PORTA = tablica[0];
}

void wyswietlDrugi() {
	PORTA = 0xFF;
	PORTB = ~0x02;
	PORTA = tablica[7];
}

int main(void)
{
	DDRA = 0xFF; // ust. port jako wyjsciowy
	DDRB = 0xFF; // ust. port jako wyjsciowy
	
	init_kernel();
	add_task(*wyswietlPierwszy, 1);
	add_task(*wyswietlDrugi, 1);
	schedule();
	
}