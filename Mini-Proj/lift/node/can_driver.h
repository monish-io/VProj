#include<LPC21xx.h>

typedef struct can{
	unsigned int id;	//2047 - MAX ID	RANGE
	unsigned int rtr;	//ONLY ONE BIT
	unsigned int dlc;  //ONLY FOUR BITS
	unsigned int byteA;
	unsigned int byteB;
}CAN;

void CAN_INIT(void){
	PINSEL1|=0x14000;	//P0.23 -> RD2 [01] P0.24 -> TD2 [01]  CAN2 port only available
	VPBDIV=1;			//By default 4 for 15MHz Pclk, CAN operates on 60MHz so 1.

	C2MOD=0x01;			//reset mode in 0 bit, 1 for register mode
	AFMR=0x02;			//allow all rx messages
	C2BTR=0x1C001D;		//speed 125kbps, pclk 60MHz==1D  for 1C refer notes.
	C2MOD=0x00;			//can i/o operations mode
}
void CAN_TX(CAN msg){
	C2TID1=msg.id;
	C2TFI1=(msg.dlc<<16);
	if(msg.rtr==0){				//Data frame check 
		C2TFI1&=~(1<<30);		//RTR=0
		C2TDA1=msg.byteA;
		C2TDB1=msg.byteB;
	}
	else{						//Remote frame
		C2TFI1|=1<<30;			//RTR=1
	}
	C2CMR=(1<<0)|(1<<5);		//bit :0-> start transmit, 5-> select TX buffer 1
	while( (C2GSR&(1<<3))==0);	//wait all data transmit (all buff) bit [3]
}
void CAN_RX(CAN *msg){
	while(((C2GSR>>0)&1)==0);	//wait until recieve data bit [0]
	msg->id=C2RID;				
	msg->dlc=(C2RFS>>16)&0xF;   //dlc in 16 to 19 bits
	msg->rtr=(C2RFS>>30)&0x1;	//rtr in 30 
	if(msg->rtr==0){				//data frame
		msg->byteA=C2RDA;
		msg->byteB=C2RDB;
	}
	C2CMR=1<<2;					//release recieve buffer
}

