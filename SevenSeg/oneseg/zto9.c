#include<lpc21xx.h>
#define seg 0xFF
#define seg1 1<<8
#include "delay_ms.h"
char lut[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
int main(){
	char d=0;
	IODIR0=0x1FF;  //p0.0 to p0.8
	while(d<10){
		IOCLR0=seg;
		IOSET0=lut[d++];
		IOCLR0=seg1;
		delay_ms(1000);
		IOSET0=seg1;
		if(d==10) d=0;
	}
}
