#include<LPC21xx.h>
void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
unsigned char UART0_RX(void){
	while(!(U0LSR&0x1));
	return U0RBR;
}
void UART0_TX(unsigned char txByte){
	while(!((U0LSR>>5)&1));
	U0THR=txByte;
}
void UART0_CONFIG(){
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
int main(){
	UART0_CONFIG();
	while(1){
		UART0_TX((UART0_RX()^32));
	}
}
