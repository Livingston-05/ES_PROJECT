#include <LPC17xx.h>

unsigned long int var1;
unsigned int q=0,w=0,k=0;

void rotate()
{
	var1=0x100;
	for(q=0;q<=3;q++)
	{
		var1 >>=1;
		LPC_GPIO0->FIOPIN=var1;
		//for(k=0;k<3000;k++);
	}
}

void stop()
{
	var1=0x000;
	for(q=0;q<=3;q++)
	{
		var1 >>=0;
		LPC_GPIO0->FIOPIN=var1;
		//for(k=0;k<3000;k++);
	}
}

void controlFan(int stat){
	if(stat){
		rotate();
	}
	else{
		stop();
	}
}