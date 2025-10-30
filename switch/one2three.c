#include<LPC21XX.h>
void delay(int ms){
	int i;
	for(;ms>0;ms--) for(i=12000;i>0;i--);
}
int main(){
	int i=0;
	PINSEL0=0x00000000;
	IODIR0=0xE;
	IOSET0=0xE;
	while(1){
		if(!(IOPIN0&0x1)) i++;
		if(i==1){ 
			IOCLR0=0x2;
			IOSET0=0xC;
		}
		else if(i==2){
			IOCLR0=0x4;
			IOSET0=0xA;
		}
		else if(i==3){
			IOCLR0=0x8;
			IOSET0=0x6;
		}
		delay(200); 
	}
}
