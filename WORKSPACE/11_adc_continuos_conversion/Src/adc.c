/*
 * adc.c
 *
 *  Created on: Dec 19, 2021
 *      Author: Navjeevan
 */

#include<adc.h>


#define GPIOAENA	(1U<<0)
#define ADC1ENA		(1U<<8)



void adc_init()
{
	//Enable clock for GPIOA
	RCC->AHB1ENR |= GPIOAENA;

	// Configure PA1 pin as analog pin
	GPIOA->MODER |= (3U<<2);

	// Enable cock access for ADC 1
	RCC->APB2ENR |= ADC1ENA;

	//Configure the ADC peripheral
	//1. Conversion sequence start
	ADC1->SQR3 = (1U<<0);
	//2. Conversion sequence length
	ADC1->SQR1 = 0;

	//3. ADC enable
	ADC1->CR2 |= (1U<<0);

}

void start_conversion()
{
	// enable continuos conversion
	ADC1->CR2 |= (1U<<1);

	//start conversion
	ADC1->CR2 |= (1U<<30);
}


int adc_read()
{
	//check the conversion complete flag
	while(!(ADC1->SR & (1U<<1)));

	return ADC1->DR;


}
