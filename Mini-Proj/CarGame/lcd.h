#include<LPC21xx.h>

#define RS 1<<8
#define E  1<<9

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_INIT(void);
void LCD_STR(unsigned char*);
void LCD_INT(int);
void CG_CAR(void);

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
void LCD_INIT(){
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void CG_CAR(){
	unsigned char car[]  ={0x00, 0x00, 0x0c, 0x0a, 0x1b, 0x1f, 0x0a, 0x00};
	unsigned char bullet[] ={0x00, 0x00, 0x0f, 0x11, 0x11, 0x0f, 0x00, 0x00};
	int a;
	LCD_CMD(0x40);
	for(a=0;a<8;a++) LCD_DATA(car[a]);
	LCD_CMD(0x48);
	for(a=0;a<8;a++) LCD_DATA(bullet[a]);	
}
void LCD_STR(unsigned char *s){
	while(*s) LCD_DATA(*s++);
}
void LCD_INT(int n){
	unsigned char arr[5];
	signed int i=0;
	if(n==0) LCD_DATA('0');
	if(n<0) n=-n;
	while(n){
		arr[i]=n%10;
		n=n/10;
		i++;
	}
	for(i=i-1;i>=0;i--) LCD_DATA(arr[i]+48);
}
