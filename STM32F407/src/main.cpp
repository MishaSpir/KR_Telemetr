
// тебе надо насроить таймеры при переходе на Discovery
#include "../inc/setup.hpp"
#include "../inc/Pars.hpp"
#include "../inc/time_setup.hpp"

uint8_t pkg_is_begin = 0;
uint8_t pkg_is_received = 0;

uint8_t data_buffer;	
Circular_buffer b;
uint8_t ch;

enum State{
    idle,
    data,
    fin,
    err
};
State state = idle;

//БУФФЕР ПАРСИНГА
//строка 0 --- первое рапарсированное число
//строка 1 ---второе распарсированное число
const uint8_t COL_SIZE =4;
const uint8_t ROW_SIZE =5;
char buf[ROW_SIZE][COL_SIZE];int m = 0;int k =0;


uint32_t last_time_1 = 0;
void pars_buffer_uart_print(void);






char test_str[] = "$123,456,789*]";









void usart2_isr(void)
{
    if (((USART_CR1(USART2) & USART_CR1_RXNEIE) != 0) &&
	    ((USART_SR(USART2) & USART_SR_RXNE) != 0)) {
           
     

         if(usart_recv(USART2) =='$' ){pkg_is_begin=1;
		}
		if(pkg_is_begin ){
			b.put( static_cast<uint8_t>(usart_recv(USART2)));

				if(!b.empty()){
					ch = b.get();
					usart_send_blocking(USART3,ch);

					
					//КОНЕЧНЫЙ АВТОМАТ
					switch(state){
						case idle:
							if(ch == '$'){state = data;
							}// Принят маркер, переходим к приёму данных
							else {}
						break;
						case data:

							if(ch == '*'){state = fin;pkg_is_begin=0;pkg_is_received = 1;}//Принят терминатор, заканчиваем приём данных
							else if (ch == '$'){state = err;m = 0;
							k = 0;

							}
							else if(ch!=',') {
                                buf[k+1][m] = ch;m++; m %= COL_SIZE;
								// usart_send_blocking(USART3,ch);
							}
							else {k+=1; 
								if(k>=ROW_SIZE){k=0;}
								m = 0;
								
						}//Принят разделитель, принимаем новой число int 
						break;
						case fin:
							m = 0;
							k = 0;
							if (ch == '$'){state = data;} 
						else {state = err;} 
						break;
						case err:
								
						k=0;m=0;
						break;
						// default:
					}
				}	
				
			}     
	}

}



void config_radiomodule(void){
    gpio_set(GPIOB, GPIO0);
	gpio_set(GPIOB, GPIO1);
    
    
    delay_ms(200);
	uint8_t str_tx[]={0xC0,0x00,0x00,0x1A,0x06,0x44}; // Настройка для радиомодуля
    uart2_write(str_tx,6); // Записываем конфигурацию в радиомодуль
    delay_ms(200);
    

    gpio_clear(GPIOB, GPIO0);
	gpio_clear(GPIOB, GPIO1);
    delay_ms(200);
    

}

int main(void)
{   
    clock_setup();
    gpio_setup();
    usart2_setup();
    usart3_setup();
    timer3_setup();
    timer2_setup();
  



    config_radiomodule();
	
    
    
    while (1) {
        if(get_ms() - last_time_1 >= 1000){
            last_time_1 = get_ms();
            gpio_toggle(GPIOA,GPIO0);
            pars_buffer_uart_print();
            // usart_send_blocking(USART3,buf[1][1]);
        }

    }
    
    return 0;
}

void pars_buffer_uart_print(void){//функция вывода ВСЕГО содержимого буфера на UART
	usart_send_blocking(USART3,'\t');	
			for(int i = 1; i<ROW_SIZE; i++){
				for(int j =0; j< COL_SIZE; j++){
					usart_send_blocking(USART3,buf[i][j]);
				}
				usart_send_blocking(USART3,'\t');
			}usart_send_blocking(USART3,'\n');
}

