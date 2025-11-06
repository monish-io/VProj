#include<LPC21xx.h>
void eint0_isr(void) __irq
{
	EXTINT=0x01;
	IOCLR0=0x01;
	//delay_ms(500);
	IOSET0=0x01;
	VICVectAddr=0;
}
int main(){
	unsigned char ch=1;
	 
	PINSEL0=0x0C;
	IODIR0=0x01;

	VICIntSelect=0;
	
	VICVectCntl0=0x20|14;
	VICVectAddr0=(unsigned long)eint0_isr;

	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=1<<14;
	while(1){
	ch++;
	if(ch==80) ch=0;
	}
}
