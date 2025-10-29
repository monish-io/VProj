#include<lpc21xx.h>
void delay(int ms){
	int i;
	for(;ms>0;ms--) for(i=12000;i>0;i--);}
int main(){
	int i,j;
	PINSEL0=0X0;
	IODIR0=0XFF;
	IOSET0=0xFF;
	for(i=0,j=7;i<8;i++,j--){
		IOCLR0=1<<i | 1<<j;
		delay(300);
		IOSET0=0xFF;
		delay(300);
	} 	
}
