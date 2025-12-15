void UART0_TX(unsigned char);
void UART0_CONFIG(void);
unsigned char UART0_RX(void);
void UART0_STR(unsigned char*);

void UART0_STR(unsigned char *s){
	while(*s){
		UART0_TX(*s++);
	}
}
unsigned char UART0_RX(){
	while(!(U0LSR&0x1));
	return U0RBR;
}
void UART0_CONFIG(){
	PINSEL0=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
void UART0_TX(unsigned char txByte){
	while(!((U0LSR>>5)&1));
	U0THR=txByte;
}

