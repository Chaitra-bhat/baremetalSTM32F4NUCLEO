/*
 * timer.h
 *
 *  Created on: Dec 22, 2021
 *      Author: Navjeevan
 */

#ifndef TIMER_H_
#define TIMER_H_
#include<stm32f4xx.h>


#define SR_UIF	(1U<<0)

void tim2_1hz_init(void);
void tim2_output_compare(void);

#endif /* TIMER_H_ */
