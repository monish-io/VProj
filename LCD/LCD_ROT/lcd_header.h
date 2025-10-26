#include<LPC21xx.h>

#define LCD_D 0xFF    		//p0.0 to p0.7
#define RS 		1<<8				//p0.8
#define E  		1<<9				//p0.9

void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(unsigned char*);
void LCD_INT(int);

void LCD_INIT(){
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD_D|RS|E;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char d){
	IOCLR0=LCD_D|RS|E;
	IOSET0=d;
	IOSET0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_STR(unsigned char *s){
	while(*s){
		LCD_DATA(*s++);
	}
}
void LCD_INT(int n){
	unsigned char arr[10];
	signed int i=0;
	if(n==0) LCD_DATA('0');
	if(n<0){
		LCD_DATA('-');
		n=-n;
	}
	while(n){
		arr[i++]=n%10;
		n/=10;
	}
	for(i=i-1;i>=0;i--) LCD_DATA(arr[i]+48);
}
