/*
 * 	File:						gpio_config.c
 *	Module:					gpio
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "gpio.h"
#include "gpio_config.h"

/*=========MACRO DEFINITIONS=========*/


/*=========EXTERN VARIABLES=========*/


/*=========GLOBAL VARIABLES=========*/

const str_gpio_config_t str_gpio_config[PORT_PIN_NUM] = {
		{ENU_DIGITAL_MODE, ENU_PIN_INPUT , ENU_PIN_LOW, ENU_PIN_PUR, ENU_PIN_CUR_8MA, ENU_PORT_F, ENU_PIN_0},
		{ENU_DIGITAL_MODE, ENU_PIN_OUTPUT, ENU_PIN_LOW, ENU_PIN_PUR, ENU_PIN_CUR_8MA, ENU_PORT_F, ENU_PIN_1},
		{ENU_DIGITAL_MODE, ENU_PIN_OUTPUT, ENU_PIN_LOW, ENU_PIN_PUR, ENU_PIN_CUR_8MA, ENU_PORT_F, ENU_PIN_2},
		{ENU_DIGITAL_MODE, ENU_PIN_OUTPUT, ENU_PIN_LOW, ENU_PIN_PUR, ENU_PIN_CUR_8MA, ENU_PORT_F, ENU_PIN_3},
		{ENU_DIGITAL_MODE, ENU_PIN_INPUT , ENU_PIN_LOW, ENU_PIN_PUR, ENU_PIN_CUR_8MA, ENU_PORT_F, ENU_PIN_4},
};

/*=========TYPE DEFINITIONS=========*/



/*=========APIs DECLERATIONS=========*/
