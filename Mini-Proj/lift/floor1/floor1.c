#include<LPC21xx.h>
#include"can_driver.h"

#define LED 1<<1
int main(){
	CAN msg;
	IODIR0|=LED;
	CAN_INIT();
	while(1){
		CAN_RX(&msg);
		if(msg.byteA==1){
			IOCLR0=LED;
		}
		else{
			IOSET0=LED;
		}
	}
}
