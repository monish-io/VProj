#include<LPC21xx.h>
#include"delay.h"
#include"lcd.h"

void carup(void) __irq;
void cardown(void) __irq;
void end_game(void);

char i=0x8F,j=0xCC,k=0x89,l=0xC6;
unsigned char car_pos=0xC0;
char score=0;

int main(){
	char hit;

	PINSEL0=5<<29;		 //EINT1 mode:(10) bit:28-31  pin 14,15
	IODIR0=0x3FF;

	VICIntSelect=0;
	VICVectCntl0=0x20|15;
	VICVectAddr0=(unsigned long)carup;
	VICVectCntl1=0x20|16;
	VICVectAddr1=(unsigned long)cardown;
	EXTMODE=0x00;
	EXTPOLAR=0x00;
	VICIntEnable=3<<15;
													
	LCD_INIT();
	CG_CAR();
	while(1){
			LCD_CMD(0x01);
			LCD_CMD(i);
			LCD_DATA(1);
			LCD_CMD(j);
			LCD_DATA(1);
			LCD_CMD(k);
			LCD_DATA(1);
			LCD_CMD(l);
			LCD_DATA(1);

			hit=(car_pos==i)||(car_pos==j)||(car_pos==k)||(car_pos==l);
			if((car_pos==0x80 && j==0xC0)||(car_pos==0xC0 && i==0x80)) score++;
			if((car_pos==0x80 && l==0xC0)||(car_pos==0xC0 && k==0x80)) score++;
			if(hit) end_game();
			
			LCD_CMD(car_pos);
			LCD_DATA(0);
			delay_ms(500);
			
			if(i==0x80) i=0x8F;
			else i--;
			if(j==0xC0) j=0xCF;
			else j--;
			if(k==0x80) k=0x8F;
			else k--;
			if(l==0xC0) l=0xCF;
			else l--;
	}
}
void carup(void) __irq
{
	EXTINT=0x02;
	car_pos=0x80;
	VICVectAddr=0;
}
void cardown(void) __irq
{
	EXTINT=0x04;
	car_pos=0xC0;
	VICVectAddr=0;
}
void end_game(){	
	LCD_CMD(0x01);
	LCD_CMD(0x84);
	LCD_STR("GAME OVER!");
	LCD_CMD(0xC8);
	LCD_INT(score);
	score=0;
	car_pos=0xC0;
	i=0x8F,j=0xCC,k=0x89,l=0xC6;
	while(1){
		if(!(IOPIN0&1<<14)) break;
	}
}
