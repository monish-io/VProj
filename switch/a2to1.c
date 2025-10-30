#include<LPC21XX.h>
#define ALLED 0x00000001
int main(){
	int ALS1,ALS2;
	PINSEL0=0x00000000;
	IODIR0=ALLED;
	IOSET0=ALLED;
	//IOCLR0=ALLED;
	while(1){
		ALS1=(!(IOPIN0&1<<1));
		ALS2=(!(IOPIN0&1<<2));
		if(ALS1^ALS2) IOCLR0=ALLED;
		else IOSET0=ALLED;
	}
}
