#include<LPC21xx.h>
void delay_ms(int);
unsigned char lut[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
void sevseg(unsigned char digit, unsigned int segm){
	IOCLR0=0xFF;
	IOSET0=lut[digit];
	IOCLR0=segm;
	delay_ms(5);
	IOSET0=segm;
}
void delay_ms(int ms){
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR-0x00;
}
