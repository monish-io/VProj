#include<LPC21xx.h>
void UART0_INIT(void);
void UART0_INTR(void);
void UART0_ISR(void) __irq{
	int temp=0;
	temp=U0IIR;
	if(temp==0x04) U0THR=(U0RBR^32);
	VICVectAddr=0;
}
int main(){
	IODIR0=1<<7;
	UART0_INIT();
	UART0_INTR();
	U0THR='A';
	while(1){
		if(!((IOPIN0>>14)&1)) IOCLR0=1<<7;
		else IOSET0=1<<7;
	}
}
void UART0_INTR(){
	VICIntSelect=0;
	VICVectCntl0=(0x20)|6;
	VICVectAddr0=(unsigned long)UART0_ISR;
	U0IER=(1<<1)|(1<<0);
	VICIntEnable=1<<6;
}
void UART0_INIT(){
	PINSEL0|=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
