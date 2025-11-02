#include<LPC21xx.h>
#include"delay.h"
#include"LCD.h"

static int dice=0;
int count=0;
void eint0_isr(void) __irq
{	
	delay_ms(300);
	EXTINT=0x01;
	//
	count++;

			LCD_CMD(0x01);
		LCD_CMD(0x80);
			LCD_STR("DICE");
		LCD_CMD(0x87);
			LCD_STR("COUNT");
		LCD_CMD(0xC9);
			LCD_INTE(count);
		LCD_CMD(0xC1);
			LCD_DATA('[');
		LCD_CMD(0xC3);
			LCD_DATA(']');
	dice=T1PC;
		if(dice==0) dice=6;
		LCD_CMD(0x40);
		dice_char(dice);
		LCD_CMD(0xC2);
		LCD_DATA(0);
	
	//
	VICVectAddr=0;
}  
int main(){
	PINSEL1=1<<0;      //p0.16 EINT0 -- 2 mode(01)
	IODIR0=0xFF;	   //LCD output pins LCD_D|RS|E

	VICIntSelect=0;
	VICVectCntl0=0x20|14;	 //EINT0 is channel 14
	VICVectAddr0=(unsigned long)eint0_isr;
	EXTMODE=0x01;            //EINT0 MODE edge 
	EXTPOLAR=0x00;
	VICIntEnable=1<<14;		 //EINT0 is channel 14

	LCD_INIT();
	LCD_CMD(0x80);
	LCD_STR("ROLL DICE!");

	while(1){
		//dice++;
		//if(dice==7) dice=0;
		T1PR=6-1;
		T1TCR=0x01;
	}
}
