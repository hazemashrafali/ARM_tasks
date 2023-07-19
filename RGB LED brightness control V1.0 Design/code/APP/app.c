/*
 * 	File:					app.c
 *	Module:					APP
 *	Description: 		source file 
 * 	Author: 			HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "app.h"

/*=========MACRO DEFINITIONS=========*/
#define MAX_PRESS 		4
#define RESET 			0 
#define PERODIC_TIME 	500
#define _90_PERCENT		90
#define _60_PERCENT		60
#define _30_PERCENT		30
#define STOP			0
#define DEBOUNCE_TIME 	50
#define BUTTON_PIN		ENU_PIN_0
#define GREEN_LED_PIN	ENU_PIN_3
#define FIRST_PRESS		1
#define SECOND_PRESS	2
#define THIRD_PRESS		3

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DEFINITIONS=========*/
void app_init(void)
{
	LED_init(ENU_PORT_F, GREEN_LED_PIN);
	BUTTON_init(ENU_PORT_F, BUTTON_PIN);
	PWM_Init(ENU_PORT_F,GREEN_LED_PIN,TIMER0_ID);
}

void app_start(void)
{
	boolean state_flag 	= FALSE;
	uint8 button_value	= 0;
	boolean flag		= TRUE;
	uint8 press_count	= RESET;
	uint8 u8_duty_cycle	= 0;

  while(1)
	{
		
		BUTTON_digitalRead(ENU_PORT_F,BUTTON_PIN,&button_value);
		if(button_value == LOGIC_HIGH)
		{
			delay_ms(TIMER1_ID,DEBOUNCE_TIME);
			BUTTON_digitalRead(ENU_PORT_F,BUTTON_PIN,&button_value);
			if(button_value == LOGIC_HIGH)
			{
				if(flag == FALSE)
				{
					state_flag =TRUE;
					press_count++;
					if(press_count == FIRST_PRESS)
					{
						u8_duty_cycle = _30_PERCENT;
					}
					else if(press_count == SECOND_PRESS)
					{		
						u8_duty_cycle = _60_PERCENT;		
					}
					else if(press_count == THIRD_PRESS)
					{
						u8_duty_cycle = _90_PERCENT;	
					}
					else
					{
						u8_duty_cycle = STOP;
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
			state_flag = FALSE;
		}
		if(state_flag == TRUE)
		{
			PWM_start(TIMER0_ID,PERODIC_TIME,MSEC,u8_duty_cycle);
			state_flag = FALSE;
		}
	}
	
}
