#include<LPC21xx.h>
#include<string.h>
#include"lcd.h"
#include"blueto.h"
#include"switch.h"

int main(){
	IODIR0|=1<<5|1<<6|1<<2;
	EXT_INIT();
	UART0_INIT();
	UART0_INTR();
	LCD_INIT();
	U0THR='A';
	while(1){
		LCD_CMD(0x01);

		if(fn==0){
			LCD_CMD(0xC0);
			LCD_STR("Fan off");
			IOCLR0=1<<2;
		}
		if(fn==1){
			LCD_CMD(0xC0);
			LCD_STR("Fan on");
			IOSET0=1<<2;
		}
		if(lt==0){
			LCD_CMD(0x80);
			LCD_STR("Light off");
			IOSET0=1<<5;
		}
		else{
			LCD_CMD(0x80);
			LCD_STR("Light on");
			IOCLR0=1<<5;
		}

		if((IOPIN0&1<<4)){
			IOCLR0=1<<6;
		}
		else{
			IOSET0=1<<6;
		}
		delay_ms(2000);
	}
}
