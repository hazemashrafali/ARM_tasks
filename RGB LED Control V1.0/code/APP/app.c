/*
 * 	File:						app.c
 *	Module:					APP
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "app.h"

/*=========MACRO DEFINITIONS=========*/
#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 762
#define MAX_PRESS 5
#define RESET 0
/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

void app_init(void)
{
	LED_init(ENU_PORT_F, ENU_PIN_1);
	LED_init(ENU_PORT_F, ENU_PIN_2);
	LED_init(ENU_PORT_F, ENU_PIN_3);
	BUTTON_init(ENU_PORT_F, ENU_PIN_0);
}

void app_start(void)
{
	uint8 button_value	= 0;
	boolean flag				= TRUE;
	uint8 press_count		= RESET;
	/* Superloop */
  while(1)
	{
		BUTTON_digitalRead(ENU_PORT_F,ENU_PIN_0,&button_value);
		if(button_value == LOGIC_HIGH)
		{
			Delay_MS(50);
			BUTTON_digitalRead(ENU_PORT_F,ENU_PIN_0,&button_value);
			if(button_value == LOGIC_HIGH)
			{
				if(flag == FALSE)
				{
					press_count++;
					switch (press_count)
					{
						case 1:
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_1,ENU_PIN_HIGH);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_2,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_3,ENU_PIN_LOW);
						break;
						case 2:
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_1,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_2,ENU_PIN_HIGH);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_3,ENU_PIN_LOW);
						break;
						case 3:
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_1,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_2,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_3,ENU_PIN_HIGH);
						break;
						case 4:
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_1,ENU_PIN_HIGH);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_2,ENU_PIN_HIGH);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_3,ENU_PIN_HIGH);
						break;
						default:
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_1,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_2,ENU_PIN_LOW);
								LED_digitalWrite(ENU_PORT_F,ENU_PIN_3,ENU_PIN_LOW);
						break;
					}
					flag = TRUE;
					if(press_count == MAX_PRESS)
						press_count = RESET;
				}
			}
		}
		else
		{
			flag = FALSE;
		}
	}
}



