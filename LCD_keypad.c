#include <LPC17xx.h>
#include "lcd.c"
#include "fan_control.c"
#include "led_control.c"
#include<string.h>

void scan();
unsigned char Msg[20] = {"KEY PRESSED= "};
unsigned char row, flag, key;
unsigned long int i, var1, temp, temp1, temp2, temp3;
unsigned char SCANCODE[16] = {0x11, 0x21, 0x41, 0x81,
                              0x12, 0x22, 0x42, 0x82,
                              0x14, 0x24, 0x44, 0x84,
                              0x18, 0x28, 0x48, 0x88};
unsigned char ASCIICODE[16] = {'F', 'A', 'N', 'O',
                               'L', 'E', 'D', 'F',
                               'C', 'E', '3', '4', // c for clear and e for enter
                               '5', '6', '7', '8'};
 char input_str[6] = {' ',' ',' ',' ', ' ', '\0'};
int set_fan_on = 0;
int set_led_on =0;
int main(void)
{
    LPC_GPIO2->FIODIR |= 0xF << 10;
    LPC_GPIO1->FIODIR &= 0xF87FFFFF;
    LPC_GPIO0->FIODIR |= 0xF << 23 | 1 << 27 | 1 << 28;
		LPC_GPIO0->FIODIR|=0xF<<4;
		LPC_GPIO0->FIODIR|=0xF<<8;
    clear_ports();
    delay_lcd(3200);
    lcd_init();
    lcd_comdata(0x80, 0);
    delay_lcd(3200);
    lcd_puts(Msg);
    //unsigned char input_str[3] = {' ', ' ', '\0'};  // Initialize input string
                                     // Initialize set_fan_on variable to 0
    while (1)
    {
			controlFan(set_fan_on);
			controlLed(set_led_on);
			
        while (1)
        {
            for (row = 1; row < 5; row++)
            {
                if (row == 1)
                {
                    var1 = 0x00000400;
                }
                else if (row == 2)
                {
                    var1 = 0x00000800;
                }
                else if (row == 3)
                {
                    var1 = 0x00001000;
                }
                else if (row == 4)
                {
                    var1 = 0x00002000;
                }
                temp = var1;
                LPC_GPIO2->FIOCLR = 0x00003C00;
                LPC_GPIO2->FIOSET = var1;
                flag = 0;
                scan();
                if (flag)
                {
                    break;
                }
            }
            if (flag)
            {
                break;
            }
        }
        for (i = 0; i < 16; i++)
        {
            if (key == SCANCODE[i])
            {
                key = ASCIICODE[i];
                break;
            }
        }
        lcd_comdata(0xC0, 0);
        delay_lcd(800);
        lcd_puts(&key);
        // Check for input string "on"
        input_str[0] = input_str[1];
				input_str[1] = input_str[2];
				input_str[2] = input_str[3];
				input_str[3] = input_str[4];
				input_str[4] = key;
				if (strcmp(input_str, "fanon") == 0) {
						set_fan_on = 1;
						key ='C';
						break;
				}
				if (strcmp(input_str, "fanoff") == 0) {
						set_fan_on = 0;
						key ='C';
						break;
				}
				if (strcmp(input_str, "ledoff") == 0) {
						set_led_on = 0;
						key ='C';
						break;
				}
				if (strcmp(input_str, "ledon") == 0) {
						set_led_on = 1;
						key ='C';
						break;
				}
				// Check for input string "clear"
				if (key == 'C') {
						input_str[0] = ' ';
						input_str[1] = ' ';
						input_str[2] = ' ';
						input_str[3] = ' ';
						input_str[4] = ' ';
						lcd_clear();
				}
					
    }
    return 0;
}


void scan()
{
	temp3=LPC_GPIO1->FIOPIN;
	temp3&=0x07800000;
	if(temp3!=0x00000000)
	{
		flag=1;
		temp3>>=19;
		var1>>=10;
		key=temp3|var1;
	}
}
