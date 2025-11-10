#include<LPC21xx.h>

unsigned char SPI(unsigned char);
void SPI_INIT(void);

void SPI_INIT(){
	PINSEL0|=0x1500;	//P0.4 SCLK [2] P0.5 MISO [2] P0.6 MOSI [2]
	S0SPCCR=150;		//(Pclk/SPI rate)	Pclk=15000000	SPI rate=100 kHz kbps
	S0SPCR=1<<5|3<<3;	//SPCR MSTR bit[5] and CPOL, CPHA [4,3]
						//CPOL and CPHA are selected based on the datasheet
	IODIR0=1<<7;		//_CS (low) is available in pin 7 - P0.7 So making as noraml IO pin and make output pin
}
unsigned char SPI(unsigned char data){
					//reading S0SPSR value first time will clear the SPIF bit [7]
	S0SPDR=data;				//data register
	while(!((S0SPSR>>7)&1));	//waiting until it becomes high [if high transfer data is complete] so exits the loop
	return S0SPDR;				//returns the data from the pin out
}
