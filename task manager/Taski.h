/*
 * Taski.h
 *
 * Created: 2013-11-20 15:38:30
 *  Author: student
 */ 


#ifndef TASKI_H_
#define TASKI_H_
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#define MAX_TASK 10
#define NULL_PTR 0
#define  NON_PERIODIC 0

typedef void(*TASK_PTR)(void);

typedef struct{
	TASK_PTR tastPtr;
	uint8_t ready;
	uint16_t toGo;
	uint16_t interval;
	} TASK;
	
	void schedule(void);
	void int_kernel(void);
	void add_task(TASK_PTR ptr, uint16_t tval);
	void set_periodic(TASK_PTR ptr, uint16_t tval);	
	void set_ready(TASK_PTR ptr, uint16_t tval);
	
#endif /* TASKI_H_ */
