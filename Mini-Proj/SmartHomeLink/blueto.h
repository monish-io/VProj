#include<LPC21xx.h>

unsigned char blue_msg[10];
unsigned char msg;
int fn=0,i=0,lt=0;

void UART0_INIT(void);
void UART0_TX(unsigned char);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char*);
void UART0_INTR(void);
void BLUETTH(void) __irq;

void BLUETTH(void) __irq{
	int temp=0;
	temp=U0IIR;
	if(temp==0x04){
		msg=U0RBR;
		if(msg=='\r'||msg=='\n'){
			blue_msg[i]='\0';
			i=0;
		}
		else{
			if(i<(sizeof(blue_msg)-1))
			blue_msg[i++]=msg;
		}
	}
	if((strcmp(blue_msg,"fanon"))==0) fn=1;
	else if((strcmp(blue_msg,"fanoff"))==0) fn=0;
	else if((strcmp(blue_msg,"lightoff"))==0) lt=0;
	else if((strcmp(blue_msg,"lighton"))==0) lt=1;	

	VICVectAddr=0;
}
void UART0_INTR(void){
	VICIntSelect=0;
	VICVectCntl0=(0x20)|6;
	VICVectAddr0=(unsigned long)BLUETTH;
	U0IER=3;	//1<<0|1<<1;
	VICIntEnable=1<<6;
}
void UART0_STR(unsigned char *s){
	while(*s) UART0_TX(*s++);
}
unsigned char UART0_RX(){
	while(!(U0LSR&0x1));
	return U0RBR;
}
void UART0_TX(unsigned char txByte){
	while(!((U0LSR>>5)&1));
	U0THR=txByte;
}
void UART0_INIT(){
	PINSEL0|=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
