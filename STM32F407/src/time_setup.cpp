#include "../inc/time_setup.hpp"


 uint32_t tiks_ms = 0;
 uint32_t tiks_us = 0;

void timer3_setup(void) {
    rcc_periph_clock_enable(RCC_TIM3);
	// 2. Настраиваем таймер:
	//Настройка PSC. Частота таймера = 72 МГц / ((36-1) + 1) = 2 MГц = 0.5 us
	//Максимальное число, кот можно записать в prescaler = 65535
	timer_set_prescaler(TIM3,16-1);
	//настройка ARR Период = ((8-1) + 1) * 0.5 us = 4.0 us
	timer_set_period(TIM3,1007-1);
	// 3. Настраиваем прерывание по обновлению
	timer_enable_irq(TIM3, TIM_DIER_UIE);
	// 4. Включаем таймер
	timer_enable_counter(TIM3);
	nvic_enable_irq(NVIC_TIM3_IRQ);

}

void timer2_setup(void) {
    rcc_periph_clock_enable(RCC_TIM2);
	// 2. Настраиваем таймер:
	//Настройка PSC. Частота таймера = 72 МГц / ((36-1) + 1) = 2 MГц = 0.5 us
	//Максимальное число, кот можно записать в prescaler = 65535
	timer_set_prescaler(TIM2,16-1);
	//настройка ARR Период = ((8-1) + 1) * 0.5 us = 4.0 us
	timer_set_period(TIM2,20);
	// 3. Настраиваем прерывание по обновлению
	timer_enable_irq(TIM2, TIM_DIER_UIE);
	// 4. Включаем таймер
	timer_enable_counter(TIM2);
	nvic_enable_irq(NVIC_TIM2_IRQ);

}

void tim3_isr(void) {//обработчик прерывания
	// Проверяем флаг прерывания
	if (timer_get_flag(TIM3, TIM_SR_UIF)) {
		// Сбрасываем флаг
		timer_clear_flag(TIM3, TIM_SR_UIF);
		// Переключаем светодиод
		// gpio_toggle(GPIOB, GPIO15);
		// tiks_us++;
        // gpio_toggle(GPIOA,GPIO1);
        // gpio_set(GPIOA,GPIO1);
        tiks_ms++;

	}

}

void tim2_isr(void) {//обработчик прерывания
	// Проверяем флаг прерывания
	if (timer_get_flag(TIM2, TIM_SR_UIF)) {
		// Сбрасываем флаг
		timer_clear_flag(TIM2, TIM_SR_UIF);
		// Переключаем светодиод
		// gpio_toggle(GPIOB, GPIO15);
		// tiks_us++;
        // gpio_toggle(GPIOA,GPIO1);
        // gpio_set(GPIOA,GPIO1);
        tiks_us++;

	}

}

void delay_ms(uint32_t ms) {
    uint32_t start = tiks_ms ;
	while (tiks_ms - start < ms) {
		
	}
}

uint32_t get_ms(){
    return tiks_ms;
} 