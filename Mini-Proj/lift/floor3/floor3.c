#include<LPC21xx.h>
#include"can_driver.h"

#define MOTA 1<<1
#define MOTC 1<<2
#define LED 1<<0
void delay_ms(int ms){
	T0PR=60000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0x00;
}
int main(){
	int mot=0,mot2;
	CAN msg;
	CAN_INIT();
	IODIR0|=MOTA|MOTC|LED;
	while(1){
		CAN_RX(&msg);
		mot2=msg.byteA;
		if((mot-mot2)>0){
			IOSET0=MOTA;
			IOCLR0=MOTC;
			delay_ms(300);
			IOCLR0=MOTA|MOTC;
		}
		else if((mot-mot2)<0){
			IOSET0=MOTC;
			IOCLR0=MOTA;
			delay_ms(300);
			IOCLR0=MOTA|MOTC;
		}
		mot=mot2;
		if(msg.byteA==3) IOCLR0=LED;
		else IOSET0=LED;
	}
}
