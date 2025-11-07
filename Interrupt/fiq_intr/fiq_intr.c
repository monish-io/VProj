#include<LPC21xx.h>
void eint0_fiq(void) __irq
{
	EXTINT=0x01;
	IOSET0=0x01;
	IOCLR0=0x01;
}
int main(){
	int a=0;
	PINSEL1=0x01;
	IODIR0=0x01;
	VICIntSelect=1<<14;


	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=1<<14;
	while(1){
		a++;
	}
}
