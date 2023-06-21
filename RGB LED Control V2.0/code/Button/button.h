#ifndef BUTTON_H_
#define BUTTON_H_

/*=========FILE INCLUSION=========*/
#include "gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_BUTTON_INVALID		=0,
	ENU_BUTTON_VALID		=1,
	ENU_BUTTON_MAX_ERROR	=2
}enu_button_error_t;
/*=========APIs DECLERATIONS=========*/
enu_button_error_t BUTTON_init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);
enu_button_error_t BUTTON_digitalRead(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,uint8* p_value);

#endif	/* BUTTON_H_ */

