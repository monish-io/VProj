#include<LPC21xx.h>
#include"delay.h"
#include"lcd_header.h"

int main(){
	int i,n;
	unsigned char str[]="Embedded";       //Length is Upto 16 only
	for(n=0;str[n];n++);
	n=17-n;
	PINSEL0=0x00;
	IODIR0=0x3FF;			//P0.0-P0.9		LCD_D|RS|E
	LCD_INIT();
	while(1){
		for(i=0;i<16;i++){
			LCD_CMD(0x80+i);
			LCD_STR(str);
			if(i>=n){
				LCD_CMD(0x80);
				LCD_STR(&str[16-i]);
			}
			delay_ms(300);
			LCD_CMD(0x01);
		}
	}
}
