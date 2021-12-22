/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include <stdint.h>
#include<timer.h>
#include<stdio.h>
#include<exti.h>
#include<stdio.h>
#include<uart.h>


int timestamp = 0;
void EXTI15_10_IRQHandler();
static void exti_callback();

//set up: Connect a jumper wire from PA5 to PA6
int main(void)
{
	RCC->AHB1ENR |= (1U<<0);

	GPIOA->MODER |= (1U<<10);
	GPIOA->MODER &= ~(1<11);

	pc13_exti_init();
	usart2_txRx_init();

	while(1)
	{

	}


}

static void exti_callback()
{
	printf("Button is pressed\n");

	GPIOA->ODR ^= (1U<<5);
}

void EXTI15_10_IRQHandler()
{
	if((EXTI->PR & LINE13)!=0)
	{
		//clear the PR flag
		EXTI->PR |= LINE13;

		//do the interrupt
		exti_callback();

	}

}
