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


void tim2_output_compare(void)
{

	// enable clock access for GPIOA
	RCC->AHB1ENR |= (1U<<0);

	//set PA5 to alternate function mode
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//set alternate function type to TIM2 CH1
	GPIOA->AFR[0] |= (1U<<20);

	// enable TIMER2 clock
	RCC->APB1ENR |= (1U<<0);

	// set pre-scaler value
	TIM2->PSC = 1600 - 1;	//16MHz

	//set auto- reload value
	TIM2->ARR = 10000 - 1;

	// output compare toggle mode
	TIM2->CCMR1 = ((1U<<4) | (1U<<5));

	//enable TIM2 ch1 in compare mode
	TIM2->CCER |= (1U<<0);

	//Clear the counter
	TIM2->CNT = 0;

	//Enable the timer
	TIM2->CR1 = (1U<<0);

}


void tim3_pa6_input_capture(void)
{
	//enable clock for pa6
	RCC->AHB1ENR |= (1U<<0);

	//set alternate function mode
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	//set alternate function type to TIM2 CH1
	GPIOA->AFR[0] |= (1U<<25);

	//enable clock access to tim3
	RCC->APB1ENR |= (1U<<1);

	//set the prescaler
	TIM3->PSC |= 16000 -1;

	//set the CH1 to capture at every edge
	TIM3->CCMR1 |= (1U<<0);

	//set CH1 to capture at rising edge
	TIM3->CCER = (1U<<0);

	//ENABLE TIM3
	TIM3->CR1 |= (1U<<0);
}
