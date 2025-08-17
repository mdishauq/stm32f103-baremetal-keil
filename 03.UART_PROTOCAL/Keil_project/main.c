#include "stm32f10x.h"

void uart_init(void);
void uart_start(uint8_t);


int main(){

uint8_t data = 50;
uart_init();
USART2->CR1 |= (1<<13); // UE first
uart_start(data);







}


void uart_init(void){
	
	//GPIO A Configure TX as Alternate Function Push-Pull. Configure RX as Input Floating / Pull-up.
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRL &=~(uint32_t) ((1<<8)|(1<<9)|(1<<10)|(1<<11));
	GPIOA->CRL |= ((1<<8)|(0<<9)|(0<<10)|(1<<11));
	GPIOA->CRL &=~(uint32_t) ((1<<12)|(1<<13)|(1<<14)|(1<<15));
  GPIOA->CRL |= ((0<<12)|(0<<13)|(0<<14)|(1<<15));
	

	//UART ENABLE
	RCC->APB1ENR |= (1<<17);
	//BAUD RATE
	USART2->BRR = (234 << 4) | 6;
	//TX AND RX ENABLE
	USART2->CR1 |=(1<<2);//RE
	USART2->CR1 |= (1<<3);//TE
	//DATA LENGTH,STOP BIT,PARITY BIT
	USART2->CR1 |= (0<<12);// 0: 1 Start bit, 8 Data bits, n Stop bit
	USART2->CR2 |= ((0<<12)|(0<<13));// 00: 1 Stop bit
	//USART2->CR1 |= (1<<9);//1: Odd parity
	
	/*CLOCK ENABLE FOR SYNCRONOUS 
	USART2->CR2 |=(1<<11);// CLKEN:
	USART2->CR2 |= (1<<10);//CPOL
	USART2->CR2 |= (0<<9);//CPHA*/
	
	

}

void uart_start(uint8_t x){

while(1){
// TX 
while(!(USART2->SR & USART_SR_TXE)); // wait TXE
USART2->DR = x; // send
x=x+1;
while(!(USART2->SR & USART_SR_TC)); // wait until fully sent
for(int i =0;i<500000;i++);
}

}
