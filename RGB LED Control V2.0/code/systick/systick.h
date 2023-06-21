#ifndef SYSTICK_H_
#define SYSTICK_H_

/*=========FILE INCLUSION=========*/
#include "common_macros.h"
#include "std_types.h"
#include "registers.h"
#include "TM4C123.h"

/*=========MACRO DEFINITIONS=========*/
#define SYS_CLOCK_FREQ		16
#define PIOSC_CLOCK_FREQ	16
#if SYS_CLOCK_FREQ < 8
#error "the system clock must be more than 8 MHz"
#endif

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	PIOSC 			 = 0,
	SYSYEM_CLOCK = 1,
	MAX_SOURCE	 = 2
}enu_clock_source_t;

typedef enum{
	DISABLE_INT = 0,
	ENABLE_INT	= 1,
	MAX_INT			= 2
}enu_sys_interrupt_t;

typedef enum{
	INVALID_OPERATION,
	VALID_OPERATION
}enu_systick_error_t;

typedef struct{
	enu_clock_source_t enu_clock_source;
	enu_sys_interrupt_t enu_sys_interrupt;
}str_systick_config_t;

/*=========APIs DECLERATIONS=========*/
/**
 * @brief       systick_init    		: Function used to initialize systick timer
 * 
 * @param[in]   str_systick_config	:	pointer to structure configuration of type str_systick_config_t

 * 
 * @return      VALID_OPERATION			: in case of successful operation     
 *              INVALID_OPERATION 	: in case of wrong passing parameters     
 */
enu_systick_error_t systick_init (str_systick_config_t* str_systick_config);


/**
 * @brief       systick_enableInt   : Function used to enable systick interrupt
 * 
 * @param[in]   void	
 *
 * @return      void		    
 *               
 */
void systick_enableInt	(void);

/**
 * @brief       systick_disableInt   : Function used to disable systick interrupt
 * 
 * @param[in]   void	
 *
 * @return      void		    
 *               
 */
void systick_disableInt (void);

/**
 * @brief       systick_delay_ms    : function used to start delay in ms
 * 
 * @param[in]   delay								:	the required time of delay in ms
 * 
 * @return      void    
 */
void systick_delay_ms (uint32 delay);


void systick_timeout_ms (uint32 delay); //todo implemented

/**
 * @brief       systick_waitEvent   : Function used to initialize systick timer
 * 
 * @param[in]   delay								:	the required time of delay in ms
 * @param[in]   F_ptr								:	pointer to callback function 
 * 
 * @return      VALID_OPERATION			: in case of successful operation     
 *              INVALID_OPERATION 	: in case of wrong passing parameters     
 */
enu_systick_error_t systick_waitEvent 	(uint32 delay, void (*F_ptr)(void));


/**
 * @brief       systick_setCallBack : Function used to set systick callback function 
 * 
 * @param[in]   F_ptr								:	pointer to callback function 
 * 
 * @return      VALID_OPERATION			: in case of successful operation     
 *              INVALID_OPERATION 	: in case of wrong passing parameters     
 */
enu_systick_error_t systick_setCallBack (void (*F_ptr)(void));

#endif	/* SYSTICK_H_ */

