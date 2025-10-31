#ifndef TIME_SETUP_HPP
#define TIME_SETUP_HPP
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
# include <libopencm3/cm3/nvic.h>



void timer2_setup(void);
void timer3_setup(void);
void tim2_isr(void);
void tim3_isr(void);
void delay_ms(uint32_t ms);
uint32_t get_ms();


#endif