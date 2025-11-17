#include<LPC21xx.h>
#include"delay.h"

#define LCD 0xFF<<10
#define RS  1<<8
#define E   1<<9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);

void LCD_STR(unsigned char *s){
	while(*s) LCD_DATA(*s++);
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_INIT(){
	IODIR0=LCD|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
