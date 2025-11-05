#include<LPC21xx.h>
#include "sev_delay.h"

#define sevpin 0xFF
#define seg1 1<<8
#define seg2 1<<9
#define seg3 1<<10
#define seg4 1<<11
typedef unsigned char usc;
typedef unsigned int usi;

int main(){
	int i;
	usi one=0,two=0,thr=0,fou=0;
	IODIR0=0xFFF; //p0.0 to p0.11
	while(1){
		for(i=0;i<50;i++){		  // four segment so 50*4*5 = 1000ms
			sevseg(fou,seg1);
			sevseg(thr,seg2);
			sevseg(two,seg3);
			sevseg(one,seg4);
		}
		one++;
		if(one>=10){
			one=0;
			two++;
		}
		if(two>=10){
			two=0;
			thr++;
		}
		if(thr>=10){
			thr=0;
			fou++;
		}
	}
}
