/*
 * timer.c
 *
 *  Created on: Dec 22, 2021
 *      Author: Navjeevan
 */

#include<timer.h>

void tim2_1hz_init(void)
{
	// enable TIMER2 clock
	RCC->APB1ENR |= (1U<<0);

	// set prescaler value
	TIM2->PSC = 1600 - 1;	//16MHz

	//set auto- reloead value
	TIM2->ARR = 10000 - 1;

	//Clear the counter
	TIM2->CNT = 0;

	//Enable the timer
	TIM2->CR1 = (1U<<0);

}
