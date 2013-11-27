#define F_CPU  16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>


void SETUP_PWM() {

        TCCR0 |= (1<<WGM01)|(1<<WGM00); // Fast PWM
        TCCR0 |= (1<<CS00); //presc1x
        TCCR0 |= (1<<COM01); //set on bottom (1<<COM00)

        DDRB |= (1<<PB3); //COC to out

}

void SETUP_TIMEOUT( unsigned char uss ) {        
        TCCR0|=(1<<WGM01); //CTC
        TCCR0|=(1<<CS01); //presc x8
	TCCR0|=(1<<COM00); // ustawienie zachowania pinu OC
        TIMSK|=(1<<OCIE0); //send interrput on compare
        
        OCR0 = uss<<1; //x2 (x16 with prescaler)

        sei();
}

void SET_PWM(unsigned char uss) {
        OCR0 = uss % 256;
}

ISR(TIMER0_COMP_vect) {
        
}

ISR(TIMER0_OVF_vect) {

}


int main() {
        //SETUP_TIMEOUT(20);
        DDRB = 0x08;
        SETUP_PWM();
	unsigned char i = 0;
        while(1) {
	  i++;
	  i = i % 256;
	  SET_PWM(i);
	  _delay_ms(10);
        }
}
