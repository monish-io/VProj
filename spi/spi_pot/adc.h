#include<LPC21xx.h>

float ADC_READ(unsigned char);
float ADC_READ(unsigned char ch){		 // channel num
	unsigned char hByte,lByte;
	unsigned int adcVal=0;
	IOCLR0=1<<7;						//CS as bit low - select it

	SPI(0x06);							//D2 , SGL/DIFF , Start - 0 , 1 , 2 bits   setting 1 and 2 bits high
	hByte=SPI(ch<<6);	//read value from device	        //6 and 7 bits are D1 and D0 bits for selecting channel
	lByte=SPI(0x00);	//read remaining value				//Dont care bits 

	IOSET0=1<<7;

	adcVal=((hByte&0x0f)<<8)|lByte;		//merging two data
	return ((adcVal*3.3)/4096);			//calc for binary lvl to voltage
}
