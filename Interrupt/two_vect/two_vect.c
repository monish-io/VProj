#include<LPC21xx.h>
#include "delay.h"

void eint0_isr(void) __irq
{
	delay_ms(500);
	EXTINT=0x01;
	IOCLR0=0x01;
	delay_ms(500);
	IOSET0=0x01;
	delay_ms(500);
	VICVectAddr=0;
}
void eint1_isr(void) __irq
{
	
	delay_ms(500);
	EXTINT=0x02;
	IOCLR0=0x04;
	delay_ms(500);
	IOSET0=0x04;
	delay_ms(500);
	VICVectAddr=0;
}
int main(){
	unsigned char count=0;
	PINSEL0=0xCC;
	IODIR0=0x05;
	IOSET0=0x05;
	VICIntSelect=0;
	VICVectCntl0=0x20|14;
	VICVectCntl1=0x20|15;
	VICVectAddr0=(unsigned long)eint0_isr;
	VICVectAddr1=(unsigned long)eint1_isr;
	VICIntEnable=0xC000;
	
	while(1){
		count++;
		if(count==100) count=0;
	}	
} 	
