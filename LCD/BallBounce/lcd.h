#include<LPC21xx.h>

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_CGRAM(void);

#define RS 1<<8
#define E  1<<9
unsigned char balllut[]={0x04, 0x0E, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00};

void LCD_INIT(void){
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_CMD(unsigned char cmd){
	IOCLR0=0xFF;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOCLR0=0xFF;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_CGRAM(){
	int i;
	for(i=0;i<8;i++) LCD_DATA(balllut[i]);
}
