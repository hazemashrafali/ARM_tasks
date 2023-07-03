#ifndef DELAY_H_
#define DELAY_H_

/*=========FILE INCLUSION=========*/
#include "gpt.h"

/*=========MACRO DEFINITIONS=========*/

/*=========EXTERN VARIABLES=========*/

/*=========GLOBAL VARIABLES=========*/

/*=========TYPE DEFINITIONS=========*/
typedef enum{
	INVALID_OPERATION,
	VALID_OPERATION,
	MAX_DELAY_ERROR
}enu_delay_error_t;


/*=========APIs DECLERATIONS=========*/
/**
 * @brief       delay_us        		: Function used to make delay in microsecond
 * 
 * @param[in]		enu_timer_id				:	Timer ID should be[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]
* @param[in]		u32_time						: the value of dealy in microsecond
 *
 * @return      VALID_OPERATION			: in case of successful operation     
 *							INVALID_OPERATION		:	in case of wrong value       
 */
enu_delay_error_t delay_us (enu_timer_id_t enu_timer_id,uint32 u32_time);

/**
 * @brief       delay_ms        		: Function used to make delay in microsecond
 * 
 * @param[in]		enu_timer_id				:	Timer ID should be[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]
* @param[in]		u32_time						: the value of dealy in millisecond
 *
 * @return      VALID_OPERATION			: in case of successful operation     
 *							INVALID_OPERATION		:	in case of wrong value       
 */
enu_delay_error_t delay_ms (enu_timer_id_t enu_timer_id,uint32 u32_time);

/**
 * @brief       delay_sec        		: Function used to make delay in second
 * 
 * @param[in]		enu_timer_id				:	Timer ID should be[TIMER0_ID,TIMER1_ID,TIMER2_ID,TIMER3_ID,TIMER4_ID,TIMER5_ID,TIMER6_ID,TIMER7_ID,TIMER8_ID,TIMER9_ID,TIMER10_ID,TIMER11_ID]
* @param[in]		u32_time						: the value of dealy in second
 *
 * @return      VALID_OPERATION			: in case of successful operation     
 *							INVALID_OPERATION		:	in case of wrong value       
 */
enu_delay_error_t delay_sec (enu_timer_id_t enu_timer_id,uint32 u32_time);

#endif	/* DELAY_H_ */


