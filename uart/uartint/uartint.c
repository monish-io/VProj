#include<LPC21xx.h>

void UART0_CONFIG(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_INT(int);
void UART0_FLOAT(float);

void UART0_FLOAT(float f){
	int i=f;
	int j;
	UART0_INT(i);
	UART0_TX('.');
	j=(f-i)*100;
	UART0_INT(j);
}
void UART0_INT(int n){
	unsigned char arr[9];
	signed i=0;
	if(n==0) UART0_TX('0');
	if(n<0){
		UART0_TX('-');
		n=-n;
	}
	while(n){
		arr[i++]=n%10;
		n=n/10;
	}
	for(i=i-1;i>=0;i--) UART0_TX(arr[i]+48);
}
unsigned char UART0_RX(){
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
	UART0_INT(223);
	UART0_TX(' ');
	UART0_FLOAT(334.9090);
}
