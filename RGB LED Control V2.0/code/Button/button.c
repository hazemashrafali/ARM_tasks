/*
 * 	File:						button.c
 *	Module:					Button
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "button.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS=========*/
enu_button_error_t BUTTON_init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_button_error_t enu_error_state = ENU_BUTTON_VALID;
	str_gpio_config_t str_gpio_config ;
	if((enu_gpio_port_id >= ENU_PORT_A) && (enu_gpio_port_id < ENU_MAX_PORT))
	{
		if((enu_gpio_pin_id >= ENU_PIN_0) && (enu_gpio_pin_id < ENU_MAX_PIN))
		{
				str_gpio_config.enu_gpio_current_level 		= ENU_PIN_CUR_8MA;
				str_gpio_config.enu_gpio_internal_attach 	= ENU_PIN_PUR;
				str_gpio_config.enu_gpio_pin_direction 		= ENU_PIN_INPUT;
				str_gpio_config.enu_gpio_pin_id 					= enu_gpio_pin_id;
				str_gpio_config.enu_gpio_pin_level 				= ENU_PIN_LOW;
				str_gpio_config.enu_gpio_pin_mode 				= ENU_DIGITAL_MODE;
				str_gpio_config.enu_gpio_port_id 					= enu_gpio_port_id;
				GPIO_init(&str_gpio_config);
		}
		else
		{
			enu_error_state = ENU_BUTTON_INVALID;
		}
	}
	else
	{
		enu_error_state = ENU_BUTTON_INVALID;
	}
	return enu_error_state;
}



enu_button_error_t BUTTON_digitalRead(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,uint8* p_value)
{
	enu_button_error_t enu_error_state = ENU_BUTTON_VALID;
	uint8 u8_value = 0;
	if((enu_gpio_port_id >= ENU_PORT_A) && (enu_gpio_port_id < ENU_MAX_PORT))
	{
		if((enu_gpio_pin_id >= ENU_PIN_0) && (enu_gpio_pin_id < ENU_MAX_PIN))
		{
			if(p_value != NULL_PTR)
			{
				GPIO_digitalRead(enu_gpio_port_id,enu_gpio_pin_id,&u8_value);
				*p_value = u8_value;
			}
			else
			{
				enu_error_state = ENU_BUTTON_INVALID;
			}
		}
		else
		{
			enu_error_state = ENU_BUTTON_INVALID;
		}
	}
	else
	{
		enu_error_state = ENU_BUTTON_INVALID;
	}
	return enu_error_state;
	
}

