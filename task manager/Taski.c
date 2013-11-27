/*
 * Taski.c
 *
 * Created: 2013-11-20 15:37:33
 *  Author: student
 */ 


#include "Taski.h"

TASK task[MAX_TASK];
unsigned char task_count = 0;

void init_kernel(void){
	unsigned char i;
	for(int i = 0; i < MAX_TASK; i++){
		task[i].tastPtr = NULL_PTR;
		task[i].ready = 0;
		task[i].toGo = 0;
		task[i].interval = 0;		
	}	
	
	TCCR0 |=(1<<WGM01); //ctc
	// konfiguracja i ustawianie licznika
	TIMSK |= (1<<OCIE0);
	TCCR0 |= (1<<CS00)| (1<<CS01); //64 prescaler

	OCR0 = 250;
	
}

void schedule(void){
	uint8_t task_num = 0;
	
	// odblokowanie przerwañ
	sei();

	while(task_count){
		if(task[task_num].ready > 0){
			// uruchamia task
			task[task_num].ready--;
			task[task_num].tastPtr();			
			task_num = 0;								
		}else{
			// przejscie do nastepnego taska
			task_num++;
			if(task_num == task_count){
				task_num = 0;
			}			
		}
	}	
}
void add_task(TASK_PTR ptr, uint16_t tval){
	if(task_count + 1 < MAX_TASK){
		task[task_count].tastPtr = ptr;
		task[task_count].interval = tval;
		task[task_count].toGo = tval;
		task_count++;
	}
}

//przerwania
ISR(TIMER0_OVF_vect){
	uint8_t i;
	TASK *tsk;
	// dla kazdego zarejestrowanego tasku	
	for(int i =0; i < task_count; i++){
		tsk = task + i;
		// jesli task periodyczny
		if(tsk->interval != NON_PERIODIC){
			// zmiejsza licznik oczekiwania			
			tsk->toGo--;
			// jesli gotowy do uruchomienia
			if(tsk->toGo == 0){
				tsk->toGo = tsk->interval;
				// zaznacza task jaklo gotowy
				tsk->ready++;
			}					
		}else if(tsk->toGo > 0){
			tsk->toGo--;
			if(tsk->toGo == 0){
				tsk->ready++;
			}
		}
	}
}

/*
void set_periodic(TASK_PTR ptr, uint16_t tval);
void set_ready(TASK_PTR ptr, uint16_t tval);
*/
