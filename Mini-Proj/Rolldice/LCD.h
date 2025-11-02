#include<LPC21xx.h>

#define LCD_D 0xFF
#define RS    1<<8
#define E     1<<9

typedef unsigned int usi;
typedef unsigned char usc;

unsigned char d_one[]={0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00};
unsigned char d_two[]={0x00,0x02,0x00,0x00,0x00,0x08,0x00,0x00};
unsigned char d_thr[]={0x00,0x08,0x00,0x04,0x00,0x02,0x00,0x00};
unsigned char d_four[]={0x00,0x0a,0x00,0x00,0x00,0x0a,0x00,0x00};
unsigned char d_five[]={0x00,0x0a,0x00,0x04,0x00,0x0a,0x00,0x00};
unsigned char d_six[]={0x00,0x0a,0x00,0x0a,0x00,0x0a,0x00,0x00};

void dice_char(int);
void LCD_INIT(void);
void LCD_CMD(usc);
void LCD_DATA(usc);
void LCD_STR(unsigned char*);
void LCD_INTE(int);
void LCD_INIT(){
	IODIR0=LCD_D|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0C);
	LCD_CMD(0x38);
	LCD_CMD(0x80);
}
void LCD_CMD(usc cmd){
	IOCLR0=LCD_D;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay_ms(2);
	IOCLR0=E;
}
void LCD_DATA(usc d){
	IOCLR0=LCD_D;
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
void LCD_INTE(int n){
	usc arr[5];
	signed char i=0;
	if(n==0) LCD_DATA('0');
	while(n){
		arr[i++]=n%10;
		n=n/10;
	}
	for(i=i-1;i>=0;i--) LCD_DATA(arr[i]+48);
}
void dice_char(int no){
	int i;
	for(i=0;i<8;i++){
		switch(no){
			case 1: 
				LCD_DATA(d_one[i]);
				break;
			case 2: 
				LCD_DATA(d_two[i]);
				break;
			case 3: 
				LCD_DATA(d_thr[i]);
				break;
			case 4: 
				LCD_DATA(d_four[i]);
				break;
			case 5: 
				LCD_DATA(d_five[i]);
				break;
			case 6: 
				LCD_DATA(d_six[i]);
				break;
		}
	}
}
