#include<lpc21xx.h>
void delay(int);
int main(){
	PINSEL0=0x00000000;
	IODIR0=0x00000001;
	while(1){
		IOCLR0=0x00000001;
		delay(200);
		IOSET0=0x00000001;
		delay(1000);
	}
}
void delay(int ms){
	int i;
	for(;ms>0;ms--) for(i=12000;i>0;i--);
	}
