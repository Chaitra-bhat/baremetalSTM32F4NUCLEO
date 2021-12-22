/*
 * uart.c
 *
 *  Created on: Dec 19, 2021
 *      Author: Navjeevan
 */

#include <uart.h>


int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


void usart2_txRx_init(void)
{

	// enable clock for GPIO and USART
	//RCC->AHB1ENR |= GPIOA_ENA;
	RCC->APB1ENR |= USART2ENA;

	//set alternate function
	GPIOA->MODER |= (2U<<4);

	//set alternate function type
	GPIOA->AFR[0] |= (7U<<8);

	//set PA3 as Rx mode
	GPIOA->MODER |= (2U<<6);

	// set alternate function type for PA3
	GPIOA->AFR[0] |= (7U<<12);

	//Configure Baud rate
	setBaudrate(USART2, SYS_FREQ, USARt_BAUDRATE);

	//set the transfer direction to both Tx and Rx
	USART2->CR1 = ((1U<<3) | (1U<<2));


	//enable module from control register
	USART2->CR1 |= (1U<<13);


}

char uart2_read()
{
	// make sure data regsiter is not empty
	while(!(USART2->SR & (1U<<5)));

	// read from data register
	return USART2->DR;
}

void uart2_write(int ch)
{
	//Transmit data register is empty
	while(!(USART2->SR & (1U<<7)));

	//Write to transmit

	USART2->DR |= (ch & 0xFF);
}

static void setBaudrate(USART_TypeDef *USARTx, uint32_t PeriphClock, uint32_t Baudrate)
{
	USARTx->BRR |= compute_uart_baudrate(PeriphClock, Baudrate);
}

static uint16_t compute_uart_baudrate(uint32_t PeriphClock, uint32_t Baudrate)
{
	return ((PeriphClock + (Baudrate/2U))/Baudrate);
}

