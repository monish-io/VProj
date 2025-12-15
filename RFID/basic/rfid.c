#include<LPC21xx.h>
#include"uart.h"
int main(){
	unsigned char tx[13];
	int i;
	UART0_CONFIG();
	while(1){
		for(i=0;i<12;i++) tx[i]=UART0_RX();
		tx[12]='\0';
		UART0_STR(tx);	
		UART0_STR("\r\n");
		UART0_STR("THANK You\r\n");
	}
}
