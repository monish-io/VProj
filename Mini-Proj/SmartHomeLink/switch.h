#include<LPC21xx.h>

void light_sw(void) __irq;
void fan_sw(void) __irq;
void EXT_INIT(void);

void EXT_INIT(){
	PINSEL0|=0xC0C0;			//p0.3, p0.7  eint1,2 

	VICIntSelect=0;
	VICVectCntl1=(0x20)|15;
	VICVectAddr1=(unsigned long)light_sw;
	VICVectCntl2=(0x20)|16;
	VICVectAddr2=(unsigned long)fan_sw;
	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=3<<15;
}
void fan_sw(void) __irq{
	EXTINT=0x04;
	//delay_ms(50);
	if(fn==0) fn=1;
	else fn=0;
	VICVectAddr=0;	
}
void light_sw(void) __irq{
	EXTINT=0x02;
	//delay_ms(50);
	if(lt==0) lt=1;
	else lt=0;
	VICVectAddr=0;
}
