/*
 * delay.c
 *
 * Created: 6/20/2023 8:16:02 PM
 *  Author: Mohamed Abdelsalam
 */ 
#include "delay.h"

 /*******************************************************************************************************************************************************************/
/* APP External Variables */

extern systick_st_cfg_t st_g_systick_PinsLinkConfig;

/*******************************************************************************************************************************************************************/

void Delay_ms(u32 milliseconds)
{
	SYSTICK_init (st_g_systick_PinsLinkConfig);
	u32 i;
	
	milliseconds = 1000 * milliseconds;
	for(i=0;i< milliseconds ;i++)
	{
			while((SYSTICK_getStatus()) == 1);
	}
	SYSTICK_Stop ();
}
