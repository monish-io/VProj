#include<LPC21xx.h>
#include"spi.h"
#include"adc.h"
#include"lcd.h"
//#include"delay.h"

int main(){
	float f;
	SPI_INIT();
	LCD_INIT();

	LCD_STR("Voltage:");
	IOPIN0=1<<7;

	while(1){
		f=ADC_READ(0);	//channel 0
		LCD_CMD(0xC0);
		LCD_FL(f);
		delay_ms(500);
		LCD_CMD(0xC0);
		LCD_STR("                ");
	}
}
