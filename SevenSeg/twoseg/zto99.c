#include<LPC21xx.h>
#include "delay_ms.h"

typedef unsigned char usc;
typedef unsigned int usi;
#define sevpin 0xFF
#define seg1 1<<8
#define seg2 1<<9
usc lut[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void sevseg(usc, usi);

int main(){
	usc d=0;
	usc one=0;
	usc two=0;
	usc i;

	IODIR0=sevpin|seg1|seg2;  //p0.0 to p0.9

	while(d<97){
		for(i=0;i<100;i++) {
			sevseg(two,seg1);
			sevseg(one,seg2);
		}
		one++;
		d++;
		if(!(d%10)){
			one=0;
			two++;
		}
	}

	while(1)
	{	
		sevseg(two,seg1);
		sevseg(one-1,seg2);
	}
}
void sevseg(usc digit, usi segm){
	IOCLR0=sevpin;
	IOSET0=lut[digit];
	IOCLR0=segm;
	delay_ms(5);
	IOSET0=segm;
}
