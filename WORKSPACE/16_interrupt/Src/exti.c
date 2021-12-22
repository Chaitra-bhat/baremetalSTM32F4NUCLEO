/*
 * exti.c
 *
 *  Created on: Dec 22, 2021
 *      Author: Navjeevan
 */
#include<exti.h>

void pc13_exti_init(void){

	//disable global interrupt
	__disable_irq();

	// enable GPIOC
	RCC->AHB1ENR |= (1U<<2);

	// set the port c pc 13 as input
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	//Enable clock access to SYSCFG
	RCC->APB2ENR |= (1U<<14);

	//Select Port c to be connected to exti 13
	SYSCFG->EXTICR[3] |= (2U<<5);

	//Un mask EXTI 13
	EXTI->IMR |= (1U<<13);

	//Select falling edge trigger
	EXTI->FTSR |= (1U<<13);

	//enable the exti13 line in nvic
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	//enable global interrupt
	__enable_irq();
}

