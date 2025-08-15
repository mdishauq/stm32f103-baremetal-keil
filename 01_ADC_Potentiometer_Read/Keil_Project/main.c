#include "stm32f10x.h"
#include<stdint.h>

static volatile uint16_t ADCvalue =0;
static volatile float voltage=0;

int main(){


//gpioa clock enale
RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

//adc1_in0 enable
RCC->APB2ENR  |= RCC_APB2ENR_ADC1EN;
//GPIOA0 AS ANOLOG PIN
//reset(mode-00,config-00)
GPIOA->CRL &=~ ((uint32_t)(0xF << 0));


  //ADC PRESCALAR
//72Mhz/6 = 12Mhz
RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;

//sampling time for channel 0
ADC1->SMPR2 |= ADC_SMPR2_SMP0;

//selecting channel 1 for PA0_IN0
ADC1->SQR3 =0;

//ADON ADC ON/OFF
ADC1->CR2 |= ADC_CR2_ADON;//ON
//SMALL DELAY
for (int i =0;i<1000;i++);

//RESET CALIBRATION
ADC1->CR2 |= ADC_CR2_RSTCAL;
while(ADC1->CR2 & ADC_CR2_RSTCAL)
	__NOP();

//SET CALIBRATION
ADC1->CR2 |= ADC_CR2_CAL;
while(ADC1->CR2 & ADC_CR2_CAL)
	__NOP();

//continuos conversion
ADC1->CR2 |= ADC_CR2_CONT;

// Right align (default)
    ADC1->CR2 &= ~ADC_CR2_ALIGN;

//STARTING THE CONVERSION
 ADC1->CR2 |= ADC_CR2_ADON;//START CONVERSION


while(1){

//WAIT TILL THE END OF CONVERSION
 while(!(ADC1->SR & ADC_SR_EOC))
	__NOP();

//READ THE RESULT
 ADCvalue = (uint16_t)(ADC1->DR);
 voltage = (3.3f * ADCvalue) / 4095.0f;
}

}
