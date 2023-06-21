#ifndef LED_H_
#define LED_H_

/*=========FILE INCLUSION=========*/
#include "gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	ENU_LED_INVALID		=0,
	ENU_LED_VALID		=1,
	ENU_LED_MAX_ERROR	=2
}enu_led_error_t;
/*=========APIs DECLERATIONS=========*/
enu_led_error_t LED_init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id);
enu_led_error_t LED_digitalWrite(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_gpio_pin_level_t enu_gpio_pin_level);

#endif	/* LED_H_ */

