#include<LPC21XX.H>
void delay(int ms){
	int i;
	for(;ms>0;ms--) for(i=12000;i>0;i--);
}
int main(){
	int i,j,a;
	unsigned int arr[4]={0x0,0x1,0x2,0x3};
	PINSEL0=0X00000000;
	IODIR0=0X3;
	IOSET0=0X3;
	for(a=0;a<5;a++){
		for(i=0,j=3;i<4;i++,j--){
			IOCLR0=arr[i];
			delay(500);
			IOSET0=arr[j];
			delay(500);
		}
	}
}
