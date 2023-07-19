/*
 * 	File:						pwm.c
 *	Module:					PWM
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "pwm.h"

/*=========MACRO DEFINITIONS=========*/
#define MAX_DUTY_CYCLE 100.0F

/*=========EXTERN VARIABLES=========*/

/*=========STATIC GLOBAL VARIABLES=========*/
static enu_gpio_port_id_t gs_enu_gpio_port_id = ENU_MAX_PORT;	
static enu_gpio_pin_id_t gs_enu_gpio_pin_id 	= ENU_MAX_PIN;
static enu_timer_id_t gs_enu_timer_id 				= MAX_TIMER_ID;
static enu_tick_unit_t gs_enu_tick_unit				= MAX_TICK_UNIT;
static boolean gs_bo_pwm_flag				= FALSE;
static float32 gs_f32_on_time				= 0;
static float32 gs_f32_off_time			=	0;
static uint8 	 gs_u8_duty_cycle			=	0;


/*=========TYPE DEFINITIONS=========*/


/*=========PRIVATE FUNCTIONS=========*/
static void PWM_callback	(void);

/*=========APIs DEFINITIONS=========*/

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

enu_pwm_error_t PWM_Init(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_timer_id_t enu_timer_id)
{
	enu_pwm_error_t enu_pwm_error = VALID;
	//check the passing parameters
	if((enu_gpio_port_id < ENU_MAX_PORT) && (enu_gpio_pin_id < ENU_MAX_PIN) && (enu_timer_id < MAX_TIMER_ID))
	{
		
		gs_enu_gpio_port_id = enu_gpio_port_id;
		gs_enu_gpio_pin_id 	= enu_gpio_pin_id;
		gs_enu_timer_id			= enu_timer_id;
		//init GPT
		str_gpt_config_t str_gpt_config = 
		{
			.enu_timer_id 				= enu_timer_id,
			.enu_timer_mode 			= PERIODIC,
			.ptr_callback					=	PWM_callback,
			.enu_timer_int_state 	= TIMER_ENABLE_INT,
		};
		//init GPIO
		str_gpio_config_t str_gpio_config =
		{
			.enu_gpio_current_level 		= ENU_PIN_CUR_8MA,
			.enu_gpio_internal_attach 	= ENU_PIN_PUR,
			.enu_gpio_pin_direction 		= ENU_PIN_OUTPUT,
			.enu_gpio_pin_id 						= enu_gpio_pin_id,
			.enu_gpio_pin_level 				= ENU_PIN_LOW,
			.enu_gpio_pin_mode 					= ENU_DIGITAL_MODE,
			.enu_gpio_port_id 					= enu_gpio_port_id,
		};
		GPIO_init(&str_gpio_config);
		gpt_Init(&str_gpt_config);
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
}


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
enu_pwm_error_t PWM_start(enu_timer_id_t enu_timer_id,uint32 u32_periodic_time,enu_tick_unit_t enu_tick_unit,uint8 u8_duty_cycle)
{
	enu_pwm_error_t enu_pwm_error = VALID;
	float32 f32_on_time	=	0;
	float32 f32_off_time	=	0;
	gs_u8_duty_cycle = u8_duty_cycle;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		if(u32_periodic_time > 0)
		{
			if((u8_duty_cycle < MAX_DUTY_CYCLE) && (u8_duty_cycle > 0))
			{
				f32_off_time=((float32)u32_periodic_time*u8_duty_cycle)/MAX_DUTY_CYCLE;	//calculate on time delay
				f32_on_time=u32_periodic_time-f32_off_time;
				gs_f32_on_time = f32_on_time;
				gs_f32_off_time = f32_off_time;
				gs_enu_tick_unit = enu_tick_unit;
				gpt_startTimer(enu_timer_id,f32_on_time,enu_tick_unit);
			}
			else 
			{
				gpt_startTimer(enu_timer_id,u32_periodic_time,enu_tick_unit);
			}
		}
		else
		{
			enu_pwm_error = INVALID;
		}
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
}

/**
 * @brief       PWM_stop        		: Function used to stop generate PWM signal  
 * 
 * @param[in]		enu_timer_id				:	Timer ID should be		[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]

 * @return      VALID								: in case of successful operation     
 *							INVALID							:	in case of wrong value       
 */
enu_pwm_error_t PWM_stop(enu_timer_id_t enu_timer_id)
{	
	enu_pwm_error_t enu_pwm_error = VALID;
	if(enu_timer_id < MAX_TIMER_ID)
	{
		gpt_stopTimer(enu_timer_id);
		gpt_disable_notification(enu_timer_id);
	}
	else
	{
		enu_pwm_error = INVALID;
	}
	return enu_pwm_error;
}

/**
 * @brief       PWM_callback        : Function used for callback function when interrupt occur 
 * 
 * @param[in]		void								:	
 *
 * @return      void								:     
 *							     
 */
void PWM_callback	(void)
{
	if((gs_u8_duty_cycle < MAX_DUTY_CYCLE) && ((gs_u8_duty_cycle > 0)))
	{
		if(gs_bo_pwm_flag == FALSE)		
		{
			gpt_startTimer(gs_enu_timer_id,gs_f32_off_time,gs_enu_tick_unit);
			gs_bo_pwm_flag = TRUE;
			GPIO_togglePin(gs_enu_gpio_port_id,gs_enu_gpio_pin_id);	
		}
		else
		{
			gpt_startTimer(gs_enu_timer_id,gs_f32_on_time,gs_enu_tick_unit);
			gs_bo_pwm_flag = FALSE;
			GPIO_togglePin(gs_enu_gpio_port_id,gs_enu_gpio_pin_id);	
		}
	}
	else if (gs_u8_duty_cycle == 100)
	{
		GPIO_digitalWrite(gs_enu_gpio_port_id,gs_enu_gpio_pin_id,ENU_PIN_HIGH);
	}
	else
	{
		GPIO_digitalWrite(gs_enu_gpio_port_id,gs_enu_gpio_pin_id,ENU_PIN_LOW);
	}
}



