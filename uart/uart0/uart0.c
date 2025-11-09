#include<LPC21xx.h>
void UART0_TX(unsigned char);
void UART0_CONFIG(void);
void UART0_CONFIG(){
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
void UART0_TX(unsigned char txByte){
	while(!((U0LSR>>5)&1));
	U0THR=txByte;
}
int main(){
	UART0_CONFIG();
	while(1) UART0_TX('A');
}
