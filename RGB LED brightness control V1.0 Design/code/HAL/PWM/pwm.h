#ifndef PWM_H_
#define PWM_H_

/*=========FILE INCLUSION=========*/
#include "gpt.h"
#include "gpio.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	INVALID		=0,
	VALID			=1,
	MAX_ERROR	=2
}enu_pwm_error_t;


/*=========APIs DECLERATIONS=========*/

/**
 * @brief       PWM_Init        		: Function used to initialize PWM module  
 * 
 * @param[in]   enu_gpio_port_id		:	port name ID should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   enu_gpio_pin_id			:	pin name ID should be	[ENU_PIN_0,ENU_PIN_1,ENU_PIN_2,ENU_PIN_3,ENU_PIN_4,ENU_PIN_5,ENU_PIN_6,ENU_PIN_7] 
 * @param[in]		enu_timer_id				:	Timer ID should be		[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]
 *
 * @return      VALID								: in case of successful operation     
 *							INVALID							:	in case of wrong value       
 */
enu_pwm_error_t PWM_Init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_timer_id_t enu_timer_id);


/**
 * @brief       PWM_start        		: Function used to start generate PWM signal  
 * 
 * @param[in]   enu_gpio_port_id		:	port name ID should be[ENU_PORT_A,ENU_PORT_B,ENU_PORT_C,ENU_PORT_D,ENU_PORT_E,ENU_PORT_F] 
 * @param[in]   u32_periodic_time		:	PWM periodic time
 * @param[in]		enu_tick_unit				:	time unit it should be [USEC,MSEC,SEC]
 * @param[in]   u8_duty_cycle				:	PWM duty cycle percentage it should be [0%--100%]
 * @return      VALID								: in case of successful operation     
 *							INVALID							:	in case of wrong value       
 */
enu_pwm_error_t PWM_start(enu_timer_id_t enu_timer_id,uint32 u32_periodic_time,enu_tick_unit_t enu_tick_unit,uint8 u8_duty_cycle);

/**
 * @brief       PWM_stop        		: Function used to stop generate PWM signal  
 * 
 * @param[in]		enu_timer_id				:	Timer ID should be		[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]

 * @return      VALID								: in case of successful operation     
 *							INVALID							:	in case of wrong value       
 */
enu_pwm_error_t PWM_stop(enu_timer_id_t enu_timer_id);

#endif	/* PWM_H_ */


