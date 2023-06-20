/*
 * 	File:						systick.c
 *	Module:					systick
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "systick.h"

/*=========MACRO DEFINITIONS========*/
#define MAX_RELOAD 0xFFFFFF

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/
enu_clock_source_t gl_enu_clock_source = MAX_SOURCE;
static void (*gl_ptrCallback) (void) = NULL_PTR;

/*=========TYPE DEFINITIONS=========*/

/*=========APIs DECLERATIONS========*/

enu_systick_error_t systick_init 	(str_systick_config_t* str_systick_config)
{
	enu_systick_error_t enu_systick_error = VALID_OPERATION;
	if(str_systick_config != NULL_PTR)
	{
		//clear the enable bit in STCTRL to turn off SYSTICK during the initialization
		CLEAR_BIT(STCTRL,STCTRL_ENABLE);
		//set the reload value to initial value
		STRELOAD = MAX_RELOAD - 1;
		//clear counter bit by clear STCURRENT register
		STCURRENT = 0;
		//set clock source
		if(str_systick_config->enu_clock_source == PIOSC)
		{
			CLEAR_BIT(STCTRL,STCTRL_CLK_SRC);
			gl_enu_clock_source = PIOSC;
		}
		else if(str_systick_config->enu_clock_source == SYSYEM_CLOCK)
		{
			SET_BIT(STCTRL,STCTRL_CLK_SRC);
			gl_enu_clock_source = SYSYEM_CLOCK;
		}
		else
		{
			enu_systick_error = INVALID_OPERATION;
			gl_enu_clock_source = MAX_SOURCE;
		}
		//set interrupt settings
		if(str_systick_config->enu_sys_interrupt == DISABLE_INT)
		{
			CLEAR_BIT(STCTRL,STCTRL_INTEN);
		}
		else if(str_systick_config->enu_clock_source == ENABLE_INT)
		{
			SET_BIT(STCTRL,STCTRL_INTEN);
			NVIC_EnableIRQ(SysTick_IRQn);
			__enable_irq();
		}
		else
		{
			enu_systick_error = INVALID_OPERATION;
		}
		//enable systick timer
		//SET_BIT(STCTRL,STCTRL_ENABLE);
	}
	else
	{
		enu_systick_error = INVALID_OPERATION;
	}
	return enu_systick_error;
}

void systick_enableInt(void)
{
	SET_BIT(STCTRL,STCTRL_INTEN);
}

void systick_disableInt(void)
{
	CLEAR_BIT(STCTRL,STCTRL_INTEN);
}


void systick_delay_ms	(uint32 delay)
{
	uint32  u32_num_of_ticks;
	float32 f32_tick_time;
	
	if (gl_enu_clock_source == PIOSC)
	{
			f32_tick_time = (4.0F/PIOSC_CLOCK_FREQ);
			u32_num_of_ticks = ((float32)(delay*1000) / (f32_tick_time));
	}
	else if(gl_enu_clock_source == SYSYEM_CLOCK)
	{
			f32_tick_time = (1.0F/SYS_CLOCK_FREQ) ;
			u32_num_of_ticks = ((float32)(delay*1000) / (f32_tick_time));
	}
	else
	{
		//do nothing
	}
	//clear counter bit by clear STCURRENT register
	STCURRENT = 0;
	STRELOAD = u32_num_of_ticks - 1;
	//enable systick timer
	SET_BIT(STCTRL,STCTRL_ENABLE);
	/* 
		wait until thew COUNT flag = 1 which mean SysTick Timer reaches ZERO value
		COUNT flag is cleared after read the CTRL register value 
	*/
	while(BIT_IS_CLEAR(STCTRL,STCTRL_COUNT));
	CLEAR_BIT(STCTRL,STCTRL_ENABLE);
}

void systick_timeout_ms (uint32 delay)
{
	//todo implemented 
}


enu_systick_error_t systick_waitEvent 	(uint32 delay, void (*F_ptr)(void))
{
	enu_systick_error_t enu_systick_error = VALID_OPERATION;
	uint32  u32_num_of_ticks;
	float32 f32_tick_time;
	
	if (gl_enu_clock_source == PIOSC)
	{
			f32_tick_time = (4.0F/PIOSC_CLOCK_FREQ);
			u32_num_of_ticks = ((float32)(delay*1000) / (f32_tick_time));
	}
	else if(gl_enu_clock_source == SYSYEM_CLOCK)
	{
			f32_tick_time = (1.0F/SYS_CLOCK_FREQ) ;
			u32_num_of_ticks = ((float32)(delay*1000) / (f32_tick_time));
	}
	else
	{
		//do nothing
	}
	if(F_ptr != NULL_PTR)
	{
		gl_ptrCallback = F_ptr;
		//clear counter bit by clear STCURRENT register
		STCURRENT = 0;
		STRELOAD = u32_num_of_ticks - 1;
		//enable systick timer & enable the interrupt
		SET_BIT(STCTRL,STCTRL_INTEN);
		SET_BIT(STCTRL,STCTRL_ENABLE);
	}
	else
	{
		enu_systick_error = INVALID_OPERATION;
	}

	return enu_systick_error;
}

enu_systick_error_t systick_setCallBack (void (*F_ptr)(void))
{
	enu_systick_error_t enu_systick_error = VALID_OPERATION;
	if(F_ptr != NULL_PTR)
	{
		gl_ptrCallback = F_ptr;
	}
	else
	{
		enu_systick_error = INVALID_OPERATION;
	}
	return enu_systick_error;
}


void SysTick_Handler (void)
{
	if(gl_ptrCallback != NULL_PTR)
	{
		gl_ptrCallback();
	}
	CLEAR_BIT(STCTRL,STCTRL_INTEN);
}
