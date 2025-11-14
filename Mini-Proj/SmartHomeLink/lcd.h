#include<LPC21xx.h>
#include"delay.h"
#define LCD_D 0xFF<<10
#define RS 1<<8
#define E  1<<9

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INIT(void);
void LCD_STR(unsigned char*);
void LCD_INT(int);
void LCD_FL(float);

void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD_D;
	IOSET0=(cmd)<<10;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
	
	/*IOCLR0=LCD_D;
	IOSET0=(cmd&0xf)<<10;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E; */
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D;
	IOSET0=(d)<<10;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;

	/*IOCLR0=LCD_D;
	IOSET0=(d&0xf)<<10;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;	 */
}
void LCD_INIT(){
	IODIR0|=LCD_D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_STR(unsigned char *s){
	while(*s) LCD_DATA(*s++);
}
void LCD_INT(int n){
	unsigned char arr[5];
	signed int i=0;
	if(n==0) LCD_DATA('0');
	if(n<0){
		LCD_DATA('-');
		n=-n;
	}
	while(n){
		arr[i]=n%10;
		n=n/10;
		i++;
	}
	for(i=i-1;i>=0;i--) LCD_DATA(arr[i]+48);
}
void LCD_FL(float f){
	int n=f;
	LCD_INT(n);
	LCD_DATA('.');
	n=(f-n)*100;
	LCD_INT(n);
}
