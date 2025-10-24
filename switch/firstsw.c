#include<LPC21xx.h>
void delay(int ms){
	int i;
	for(;ms>0;ms--) for(i=12000;i>0;i--);
}
int main(){
	PINSEL0=0x00000000;
	IODIR0=0x00000001;
	while(1){
		if(!(IOPIN0 & 0x2)) IOCLR0=0x1;
		else IOSET0=0x1; 
	}
}
