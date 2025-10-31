#ifndef SETUP_HPP
#define SETUP_HPP

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>

#define BAUD_RATE (9600)
#define M0	GPIO0//портВ  
#define M1	GPIO1

void clock_setup(void);
void gpio_setup(void);
void usart2_setup(void);//для общения с модулем
void usart3_setup(void);//для общения с ПК






#endif