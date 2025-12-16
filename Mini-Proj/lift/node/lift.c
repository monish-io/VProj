#include<LPC21xx.h>
#include"can_driver.h"
#include"lcd.h"

#define UP 1<<10
#define DN 1<<11
#define ST 1<<12

#define BUZ 1<<14
#define LED1 1<<15
#define LED2 1<<16
#define LED3 1<<17
int main(){
	int flr=1,st=0;
	CAN msg;
	CAN_INIT();
	LCD_INIT();
	IODIR0|=LED1|LED2|LED3;
	LCD_CMD(0x80);
	//LCD_ROT("CAN based Elevator Control system");
	LCD_STR("CAN based");
	LCD_CMD(0xC0);
	LCD_STR("Elevator System");
	delay_ms(500);
	
	msg.id=1;
	msg.dlc=4;
	msg.rtr=0;
	
	while(1){
		CAN_TX(msg);
		delay_ms(200);
		if(!(IOPIN0&UP)){
			if(flr<3) flr++;
		}
		if(!(IOPIN0&DN)){
			if(flr>1) flr--;
		}
		if(!(IOPIN0&ST)) {
			flr=1;
			st=1;
		}
		msg.byteA=flr;
		if(flr==1){	
			IOCLR0=LED1;
			IOSET0=LED2|LED3;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			LCD_STR("FLOOR");
			LCD_CMD(0x87);
			LCD_INT(1);
		}
		if(flr==2){
			IOCLR0=LED2;
			IOSET0=LED1|LED3;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			LCD_STR("FLOOR");
			LCD_CMD(0x87);
			LCD_INT(2);
		}
		if(flr==3){
			IOCLR0=LED3;
			IOSET0=LED1|LED2;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			LCD_STR("FLOOR");
			LCD_CMD(0x87);
			LCD_INT(3);
		}
		if(st==1){
			IOSET0=BUZ;
			LCD_CMD(0x01);
			LCD_CMD(0x80);
			LCD_STR("EMERGENCY STOP");
			delay_ms(1000);
			IOCLR0=BUZ;
			st=0;
		}
		delay_ms(200);
	}
}
