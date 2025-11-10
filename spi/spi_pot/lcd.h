#include<LPC21xx.h>
#include"delay.h"
#define LCD_D	0xFF<<10
#define RS		1<<8 
#define E		1<<9


void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char *);
void LCD_INT(int);
void LCD_FL(float);
void LCD_FL(float f){
	int n=f;
	LCD_INT(n);
	LCD_DATA('.');
	n=(f-n)*100;
	LCD_INT(n);
}
void LCD_INT(int n){
	signed int i=0;
	unsigned char arr[9];
	if(n==0) LCD_DATA('0');
	if(n<0){
		n=-n;
		LCD_DATA('-');
	}
	while(n){
		arr[i]=n%10;
		n/=10;
		i++;
	}
	for(i=i-1;i>=0;i--) LCD_DATA(arr[i]+48);
}
void LCD_STR(unsigned char *s){
	while(*s) LCD_DATA(*s++);
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=d<<10;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD_D;
	IOSET0=cmd<<10;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_INIT(void){
	IODIR0 |= LCD_D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80); 	
}
