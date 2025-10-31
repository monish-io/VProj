#include<LPC21xx.h>
#include"delay.h"
#include"lcd.h"
int main(){
	int j;
	IODIR0=0x3FF;
	LCD_INIT();
	LCD_CMD(0x40);
	LCD_CGRAM();
	while(1){
	j=0;
	while(j<16){
		LCD_CMD(0x01);
		LCD_CMD(0x80+j);
		LCD_DATA(0);
		delay_ms(100);
		LCD_CMD(0x01);
		LCD_CMD(0xC0+j);
		LCD_DATA(0);
		delay_ms(100);
		LCD_CMD(0x01);
		LCD_CMD(0x80+j);
		LCD_DATA(0);
		delay_ms(100);
		j++;	
	}
	}
}
