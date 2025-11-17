#include<LPC21xx.h>
#include"lcd.h"

void UART0_CONFIG(void);
unsigned char UART0_RX(void);
unsigned char UART0_RX(void){
	while(!(U0LSR&0x01));
	return U0RBR;	                             
}
void UART0_CONFIG(void){
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
int main(){
	LCD_INIT();
	LCD_DATA('A');
	UART0_CONFIG();
	while(1) LCD_DATA(UART0_RX());
}
