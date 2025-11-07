#include<LPC21xx.h>
void eint_nv(void) __irq{
	if((VICIRQStatus>>14)&1){
		EXTINT=0x01;
		IOSET0=1<<8;
		IOCLR0=1<<8;
	}
	if((VICIRQStatus>>15)&1){
		EXTINT=0x02;
		IOSET0=1<<9;
		IOCLR0=1<<9;
	}
	if((VICIRQStatus>>16)&1){
		EXTINT=0x04;
		IOSET0=1<<10;
		IOCLR0=1<<10;
	}
	VICVectAddr=0;
}
int main(){
	int a=0;
	PINSEL0=0xC0CC;            //p0.1,p0.3,p0.7    all mode 4 (11)
	IODIR0=7<<8;			   //p0.8 p0.9 p0.10  output pins

	VICIntSelect=0;
	VICDefVectAddr=(unsigned long)eint_nv;
	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=7<<14;		   //EINT0,EINT1,EINT2  14,15,16

	while(1){
		a++;
	}
}
