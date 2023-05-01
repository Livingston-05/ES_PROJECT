#include <LPC17xx.h>

unsigned long int var1;
unsigned int r=0;

void on()
{
	var1=0xF;
	//configure it to port P1.4 to P1.7
	LPC_GPIO1->FIOPIN=var1 << 8;
	//for(r=0;r<3000;r++);
}

void off()
{
	var1=0x0;
	LPC_GPIO0->FIOPIN=var1 <<8;
	//for(r=0;r<3000;r++);
}


void controlLed(int stat){
	if(stat){
		on();
	}
	else{
		off();
	}
}