#include "stm32f10x.h"

static uint8_t i2cvalue ;

uint8_t I2C_Initialization(void);


int main(){



i2cvalue = I2C_Initialization();
while(1){
__NOP();
}


}



uint8_t I2C_Initialization(void){
	
	volatile uint8_t whoami;

	//ENABLING SDA AND SCL PINS PB6 AND PB7
	RCC->APB2ENR |= (1<<3);
	//ENABLING I2C1
	RCC->APB1ENR |= (1<<21);
	
	//PIN CONFIG
	GPIOB->CRL &=~ ((0xFu<<24)|(0xFu<<28));
  
  // PB6 (SCL), PB7 (SDA) ? Alternate Function Open-Drain, 50MHz
GPIOB->CRL &= ~((0xF << 24) | (0xF << 28));
GPIOB->CRL |= ((0xB << 24) | (0xB << 28));  // MODE=11 (50MHz), CNF=11 (AF Open-Drain)

//*****************************************************************
	
	//pheripheral clock frequency for i2c 
	I2C1->CR2 |= 36;//36Mhz
	
	//scl speed = (pheripheral clock frequency for i2c)/(2 x (scl clock frequency)) *we are taking 100Khz for scl clock frequency
	//then the scl speed is 180Mhz
	
	I2C1->CCR = 180;//180Khz
	
I2C1->TRISE = 37;//(pheripheral clock frequency for i2c + 1 = 36 + 1 = 37)

//*****************************************************************

// ENABLING THE I2C
I2C1->CR1 |= (1<<0);

//ENABLING THE ACK BIT
I2C1->CR1 |= (1<<10);



//*************************************************************
/*
//START BIT
I2C1->CR1 |= (1<<8);
while(!(I2C1->SR1 & (1<<0))){
__NOP();
}

//SEND SLAVE ADDRESS BIT AND READ/WRITE BIT 
I2C1->DR = ((0x68<<1)| 0);//I²C slave device address
while(!(I2C1->SR1 & (1<<1))){
__NOP();
}

(void)I2C1->SR1;
(void)I2C1->SR2;*/

//WHO IM I REGISTER IN SLAVE(MPU 6050) WHICH WILL WE USED TO READ DATA 
//I2C1->DR = 0x75;
/*while(!(I2C1->SR1 &(1<<7))){
	__NOP();
}*/
	/*(When sending the address, always assign (=) instead of OR-assign (|=), 
because DR doesn’t hold a persistent value — it’s just a transmit/receive buffer.
If you use |=, you might accidentally merge old bits with the new address.)*/

//*****************************************************************
//NOW WE ARE MAKING THE MASTER TO READ THE VALUES

/*
Why repeated START is needed:

In I²C, you can’t change the R/W direction in the middle of a transfer without sending another START condition —
otherwise the slave will treat it as another byte to write, not a read request.
The repeated START keeps the bus under your control (no STOP yet),
so the slave’s internal register pointer stays where you just set it.*/

//REPEATED START
I2C1->CR1 |= (1<<8);
while(!(I2C1->SR1 & (1<<0))){
__NOP();
}

//SEND SLAVE ADDRESS BIT AND READ/WRITE BIT
I2C1->DR = ((0x68<<1)| 1);
while(!(I2C1->SR1 & (1<<1))){
__NOP();
}

//RESET ACK BIT SO WE ARE ONLY RECEIVING ON BYTE
I2C1->CR1 &=~ (1<<10);

(void)I2C1->SR1;
(void)I2C1->SR2;


I2C1->CR1 |= (1 << 9); // STOP

while (!(I2C1->SR1 & (1 << 6))) {
    __NOP();
}

whoami = I2C1->DR;

return whoami;
	
	
	
	
	
	
	
}
