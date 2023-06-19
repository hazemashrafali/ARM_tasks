/*
 * 	File:						gpio.c
 *	Module:					gpio
 *	Description: 		source file 
 * 	Author: 				HAZEM ASHRAF
 */ 

/*=========FILE INCLUSION=========*/
#include "gpio_config.h"

/*=========MACRO DEFINITIONS=========*/
#define PORT_LOCK_VALUE		(uint32)(0x4C4F434B)


/*=========EXTERN VARIABLES=========*/


/*=========GLOBAL VARIABLES=========*/
static  void(*fptr_A)(void);
static  void(*fptr_B)(void);
static  void(*fptr_C)(void);
static  void(*fptr_D)(void);
static  void(*fptr_E)(void);
static  void(*fptr_F)(void);


static volatile enu_gpio_port_id_t enu_gpio_portA_id = ENU_MAX_PORT;
static volatile enu_gpio_port_id_t enu_gpio_portB_id = ENU_MAX_PORT;
static volatile enu_gpio_port_id_t enu_gpio_portC_id = ENU_MAX_PORT;
static volatile enu_gpio_port_id_t enu_gpio_portD_id = ENU_MAX_PORT;
static volatile enu_gpio_port_id_t enu_gpio_portE_id = ENU_MAX_PORT;
static volatile enu_gpio_port_id_t enu_gpio_portF_id = ENU_MAX_PORT;
/*=========TYPE DEFINITIONS=========*/


/*=========APIs DEFINITIONS=========*/
enu_gpio_error_state_t GPIO_init 	(const str_gpio_config_t* str_gpio_config)
{
	enu_gpio_port_id_t 			enu_gpio_port_id;
	enu_gpio_pin_id_t				enu_gpio_pin_id;
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	
	if(str_gpio_config != NULL_PTR)
	{
			enu_gpio_port_id 	= str_gpio_config->enu_gpio_port_id;
			enu_gpio_pin_id 	= str_gpio_config->enu_gpio_pin_id;

			if(enu_gpio_port_id == ENU_PORT_A)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_0);
			}
			else if (enu_gpio_port_id == ENU_PORT_B)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_1);
			}
			else if (enu_gpio_port_id == ENU_PORT_C)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_2);
			}
			else if (enu_gpio_port_id == ENU_PORT_D)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_3);
			}
			else if (enu_gpio_port_id == ENU_PORT_E)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_4);
			}
			else if (enu_gpio_port_id == ENU_PORT_F)
			{
				SET_BIT(RCGC2GPIO,ENU_PIN_5);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//unlock the GPIO 
			GPIOLOCK(enu_gpio_port_id) = PORT_LOCK_VALUE;
			//enable changes to pin
			SET_BIT(GPIOCR(enu_gpio_port_id),enu_gpio_pin_id);
			//step 1:initialize the clock
			//step 2:setup the direction
			if(str_gpio_config->enu_gpio_pin_direction == ENU_PIN_OUTPUT)
			{
				SET_BIT(GPIODIR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				CLEAR_BIT(GPIODIR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			//step 4:setup the internal attach
			if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_PUR)
			{
				SET_BIT(GPIOPUR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_PDR)
			{
				SET_BIT(GPIOPDR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_internal_attach == ENU_PIN_ODR)
			{
				SET_BIT(GPIOODR(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 5:setup the current level
			if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_2MA)
			{
				SET_BIT(GPIODR2R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_4MA)
			{
				SET_BIT(GPIODR4R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_current_level == ENU_PIN_CUR_8MA)
			{
				SET_BIT(GPIODR8R(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 6:setup digital mode
			if(str_gpio_config->enu_gpio_pin_mode == ENU_DIGITAL_MODE)
			{
				//disable the alternative functionality on this pin by clear the corresponding bit on GPIOAFSEL
				CLEAR_BIT(GPIOAFSEL(enu_gpio_port_id),enu_gpio_pin_id);
				//enable the digital functionality on this pin by set the corresponding bit on GPIODEN
				SET_BIT(GPIODEN(enu_gpio_port_id),enu_gpio_pin_id);
				//disable the analog functionality on this pin by clear the corresponding bit on GPIOAMSEL
				CLEAR_BIT(GPIOAMSEL(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_mode == ENU_ANALOG_MODE)
			{
				//disable the alternative functionality on this pin by clear the corresponding bit on GPIOAFSEL
				CLEAR_BIT(GPIOAFSEL(enu_gpio_port_id),enu_gpio_pin_id);
				//disable the digital functionality on this pin by set the corresponding bit on GPIODEN
				CLEAR_BIT(GPIODEN(enu_gpio_port_id),enu_gpio_pin_id);
				//enable the analog functionality on this pin by clear the corresponding bit on GPIOAMSEL
				SET_BIT(GPIOAMSEL(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_mode == ENU_ALTERNATE)
			{
				//TODO implmented in the future version
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
			//step 3:setup the output level
			if(str_gpio_config->enu_gpio_pin_level == ENU_PIN_LOW)
			{
				CLEAR_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(str_gpio_config->enu_gpio_pin_level == ENU_PIN_HIGH)
			{
				SET_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}



enu_gpio_error_state_t GPIO_digitalWrite(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,enu_gpio_pin_level_t enu_gpio_pin_level)
{
	
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if((enu_gpio_port_id >= ENU_PORT_A) && (enu_gpio_port_id < ENU_MAX_PORT))
	{
		if((enu_gpio_pin_id >= ENU_PIN_0) && (enu_gpio_pin_id < ENU_MAX_PIN))
		{
			if(enu_gpio_pin_level == ENU_PIN_LOW)
			{
				CLEAR_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else if(enu_gpio_pin_level == ENU_PIN_HIGH)
			{
				SET_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
	
}


enu_gpio_error_state_t GPIO_digitalRead	(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id,uint8* P_value)
{
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if(P_value != NULL_PTR)
	{
		if((enu_gpio_port_id >= ENU_PORT_A) && (enu_gpio_port_id < ENU_MAX_PORT))
		{
			if((enu_gpio_pin_id >= ENU_PIN_0) && (enu_gpio_pin_id < ENU_MAX_PIN))
			{
				if(BIT_IS_CLEAR(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id))
				{
					*P_value = LOGIC_HIGH;
				}
				else 
				{
					*P_value = LOGIC_LOW;
				}
			}
			else
			{
				enu_gpio_error_state = ENU_INVALID;
			}
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


enu_gpio_error_state_t GPIO_togglePin		(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_gpio_error_state_t 	enu_gpio_error_state = ENU_VALID;
	if((enu_gpio_port_id >= ENU_PORT_A) && (enu_gpio_port_id < ENU_MAX_PORT))
	{
		if((enu_gpio_pin_id >= ENU_PIN_0) && (enu_gpio_pin_id < ENU_MAX_PIN))
		{
				TOGGLE_BIT(GPIODATA(enu_gpio_port_id),enu_gpio_pin_id);
		}
		else
		{
			enu_gpio_error_state = ENU_INVALID;
		}
	}
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


enu_gpio_error_state_t GPIO_interruptEnable(enu_interrupt_edge_t enu_interrupt_edge,enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
				enu_gpio_error_state_t enu_gpio_error_state = ENU_VALID;
	      switch(enu_interrupt_edge)
				{
						case ENU_LEVEL:
						SET_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						break;
						case ENU_RISING:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						case ENU_FALLING:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						CLEAR_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						case ENU_ANY_EDGE_CHANGE:
						CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
						SET_BIT(GPIOICR(enu_gpio_port_id),enu_gpio_pin_id);
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;	
					}
					SET_BIT(GPIOIM(enu_gpio_port_id),enu_gpio_pin_id);
					switch (enu_gpio_port_id)
					{
						case ENU_PORT_A:
						NVIC_EnableIRQ(GPIOA_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_B:
						NVIC_EnableIRQ(GPIOB_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_C:
						NVIC_EnableIRQ(GPIOC_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_D:
						NVIC_EnableIRQ(GPIOD_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_E:
						NVIC_EnableIRQ(GPIOE_IRQn);
            __enable_irq();
						break;
						case ENU_PORT_F:
						NVIC_EnableIRQ(GPIOF_IRQn);
            __enable_irq();
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;	
					}
	return enu_gpio_error_state;
}


void GPIO_interruptDisable(enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	        CLEAR_BIT(GPIOIM(enu_gpio_port_id),enu_gpio_pin_id);
					CLEAR_BIT(GPIOIS(enu_gpio_port_id),enu_gpio_pin_id);	
					CLEAR_BIT(GPIOIBE(enu_gpio_port_id),enu_gpio_pin_id);	
					CLEAR_BIT(GPIOIEV(enu_gpio_port_id),enu_gpio_pin_id);
}

enu_gpio_error_state_t GPIO_Setcallback(void (*Fptr)(void),enu_gpio_port_id_t enu_gpio_port_id,enu_gpio_pin_id_t enu_gpio_pin_id)
{
	enu_gpio_error_state_t enu_gpio_error_state = ENU_VALID;
	if (Fptr!=NULL_PTR)
	{
	switch (enu_gpio_port_id)
					{
						case ENU_PORT_A:
						fptr_A=Fptr;
						enu_gpio_portA_id	=	enu_gpio_port_id;
						break;
						case ENU_PORT_B:
						fptr_B=Fptr;
						enu_gpio_portB_id	=	enu_gpio_port_id;
						break;
						case ENU_PORT_C:
						fptr_C=Fptr;
						enu_gpio_portC_id	=	enu_gpio_port_id;
						break;
						case ENU_PORT_D:
						fptr_D=Fptr;
						enu_gpio_portD_id	=	enu_gpio_port_id;
						break;
						case ENU_PORT_E:
						fptr_E=Fptr;
						enu_gpio_portE_id	=	enu_gpio_port_id;
						break;
						case ENU_PORT_F:
						fptr_F=Fptr;
						enu_gpio_portF_id	=	enu_gpio_port_id;
						break;
						default:
						enu_gpio_error_state = ENU_INVALID;
					}
	 }
	else
	{
		enu_gpio_error_state = ENU_INVALID;
	}
	return enu_gpio_error_state;
}


/*================interrupt handler================*/
void GPIOA_Handler(void) 
{
   if (fptr_A!=NULL_PTR)
	 {
		 fptr_A();
		 SET_BIT(GPIOICR(enu_gpio_portA_id),ENU_PIN_0);
	 }
	 else
	 {
		 //do nothing
	 }
}


void GPIOB_Handler(void) 
{
    if (fptr_B!=NULL_PTR)
	 {
		 fptr_B();
		 SET_BIT(GPIOICR(enu_gpio_portB_id),ENU_PIN_1);
	 }
	 else
	 {
		 //do nothing
	 }
}


void GPIOC_Handler(void)
{
    if (fptr_C!=NULL_PTR)
	 {
		 fptr_C();
		 SET_BIT(GPIOICR(enu_gpio_portC_id),ENU_PIN_2);
	 }
	 else
	 {
		 //do nothing
	 }
}


void GPIOD_Handler(void) 
{
    if (fptr_D!=NULL_PTR)
	 {
		 fptr_D();
		 SET_BIT(GPIOICR(enu_gpio_portD_id),ENU_PIN_3);
	 }
	 else
	 {
		 //do nothing
	 }
}


void GPIOE_Handler(void)
{
    if (fptr_E!=NULL_PTR)
	 {
		 fptr_E();
		 SET_BIT(GPIOICR(enu_gpio_portE_id),ENU_PIN_4);
	 }
	 else
	 {
		 //do nothing
	 }
}


void GPIOF_Handler(void) 
{
    if (fptr_F!=NULL_PTR)
	 {
		 fptr_F();
		 SET_BIT(GPIOICR(enu_gpio_portF_id),ENU_PIN_5);
	 }
	 else
	 {
		 //do nothing
	 }
}

