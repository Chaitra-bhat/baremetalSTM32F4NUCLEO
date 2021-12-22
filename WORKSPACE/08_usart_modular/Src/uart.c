/*
 * uart.c
 *
 *  Created on: Dec 19, 2021
 *      Author: Navjeevan
 */

#include <uart.h>


//function prototypes
void usart2_tx_init(void);
static void setBaudrate(USART_TypeDef *USARTx, uint32_t PeriphClock, uint32_t Baudrate);
static uint16_t compute_uart_baudrate(uint32_t PeriphClock, uint32_t Baudrate);
void uart2_write(int ch);

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


void usart2_tx_init(void)
{

	// enable clock for GPIO and USART
	RCC->AHB1ENR |= GPIOA_ENA;
	RCC->APB1ENR |= USART2ENA;

	//set alternate function
	GPIOA->MODER |= (2U<<4);

	//set alternate function type
	GPIOA->AFR[0] |= (7U<<8);

	//Configure Baud rate
	setBaudrate(USART2, SYS_FREQ, USARt_BAUDRATE);

	//set the transfer direction
	USART2->CR1 = (1U<<3);

	//enable module from control register
	USART2->CR1 |= (1U<<13);


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

