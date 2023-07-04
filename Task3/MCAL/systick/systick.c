/*
 * systick.c
 *
 * Created: 6/22/2023 8:55:14 AM
 *  Author: MOHAMED ABDELSALAM
 */
/*----------------------------------------------------------/
/- INCLUDES -----------------------------------------------/
/----------------------------------------------------------*/
#include "systick.h"
/*- LOCAL MACROS ------------------------------------------/
/---------------------------------------------------------*/
/*Module Registers*/

/*
Base Addresses For System Timers
*/
#define SYSTICK_BASE		(0xE000E000)

/*------------------------------------------------------------------------------------------------------*/
/*Macros*/
#define STCTRL									(*((volatile u32*)((SYSTICK_BASE)+(0x010))))				//SysTick Control and Status Register
#define SYSTICK_COUNT						16																											//Count Flag
#define SYSTICK_CLK_SRC					2																												//Clock Source
#define SYSTICK_INTEN						1																												//Interrupt Enable
#define SYSTICK_ENABLE					0																												//FOR 0 The counter is disabled.
#define STRELOAD								(*((volatile u32*)((SYSTICK_BASE)+(0x014))))				//SysTick Reload Value Register
#define STCURRENT								(*((volatile u32*)((SYSTICK_BASE)+(0x018))))				//SysTick Current register contains the current value of the SysTick counter.
#define SYSTICK_CURRENT_CLEAR		(u32)(0x00)
/*------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------/
/- STRUCTS AND UNIONS -------------------------------------/
/----------------------------------------------------------*/

/*---------------------------------------------------------/
/- GLOBAL STATIC VARIABLES -------------------------------/
/---------------------------------------------------------*/
static void ( *avpf_gs_systickInterruptsAction ) ( void ) =  NULL ;

/*---------------------------------------------------------/
/- LOCAL FUNCTIONS IMPLEMENTATION ------------------------/
/---------------------------------------------------------*/
/*******************************************************************************************************************************************************************/
/*
 Name: SYSTICK_init
 Input: systick_st_cfg_t systick_st_cfg
 Output: u8
 Description: Function to initialize Pin direction.
*/
void SYSTICK_init (systick_st_cfg_t systick_st_cfg)
{
	//step 1:
	STRELOAD = systick_st_cfg.systick_u32_reload_value;
	//step 2:
	STCURRENT = SYSTICK_CURRENT_CLEAR;
	//step 3:
	if (PRECISION_INTERNAL_OSCILLATOR == systick_st_cfg.systick_en_clock_source)
	{
		CLR_BIT(STCTRL,SYSTICK_CLK_SRC);
	}
	else if (SYSTEM_CLOCK == systick_st_cfg.systick_en_clock_source)
	{
		SET_BIT(STCTRL,SYSTICK_CLK_SRC);
	}
	else
	{
		//error
	}	
	if (DISABLED == systick_st_cfg.systick_en_interrupt)
	{
		CLR_BIT(STCTRL,SYSTICK_INTEN);
	}
	else if (ENABLED == systick_st_cfg.systick_en_interrupt)
	{
		SET_BIT(STCTRL,SYSTICK_INTEN);
		/* Step 2: Enable Interrupt in the NVIC peripheral. */
		NVIC_EnableIRQ( SysTick_IRQn );
		/* Step 3: Enable Interrupts. */
		__enable_irq();
	}
	else
	{
		//error
	}	
	if (COUNTER_DISABLED ==	systick_st_cfg.systick_en_mode)
	{
		CLR_BIT(STCTRL,SYSTICK_ENABLE);
	}
	else if (MULTI_SHOT == systick_st_cfg.systick_en_mode)
	{
		SET_BIT(STCTRL,SYSTICK_ENABLE);
	}
	else
	{
		//error
	}	
}
void SYSTICK_set (u32 u32_a_reload_value)
{
	STRELOAD = u32_a_reload_value;
}
void SYSTICK_interrupt_en(void)
{
	SET_BIT(STCTRL,SYSTICK_INTEN);
}
void SYSTICK_interrupt_dis(void)
{
	CLR_BIT(STCTRL,SYSTICK_INTEN);
}
u8 SYSTICK_getStatus(void)
{
	u8 u8_l_return;
		if ((GET_BIT_STATUS( STCTRL, SYSTICK_COUNT )) == 0)
	{
		u8_l_return = 0x01;
	}
	else if ((GET_BIT_STATUS( STCTRL, SYSTICK_COUNT )) == 1)
	{
		u8_l_return = 0x00;
		SET_BIT(STCTRL,SYSTICK_COUNT);
	}
	else
	{
		//nothing
	}
	return u8_l_return;
}
void SYSTICK_Stop (void)
{
	STCTRL = 0x00;
}
/*******************************************************************************************************************************************************************/
/*
 Name: SYSTICK_setCallback
 Input: Pointer to Function that takes void and returns void
 Output: void
 Description: Function to receive an address of a function ( in an Upper Layer ) to be called back in IRQ function of the passed Systick ,
							the address is passed through a pointer to function ( SystickInterruptAction ), and then pass this address to IRQ function.
*/
void SYSTICK_setCallback(  void ( *vpf_a_systickInterruptAction ) ( void ) )
{
	
	/* Check 1: TimerId and TimerUse are in the valid range, and Pointer to Function is not equal to NULL. */
	if (  vpf_a_systickInterruptAction != NULL )
	{
		avpf_gs_systickInterruptsAction = vpf_a_systickInterruptAction;
	}
	/* Check 2: TimerId or TimerUse is not in the valid range, or Pointer to Function is equal to NULL. */
	else
	{
		/* Update error state = NOK, Wrong TimerId or TimerUse, or Pointer is NULL! */
	}
}

/*******************************************************************************************************************************************************************/
/* IRQ handler implementation of SYSTICK */
void SysTick_Handler( void )
{
	/* Check 1: Pointer to Function is not equal to NULL. */
	if ( avpf_gs_systickInterruptsAction != NULL )
	{
		/* Call Back the function ( in an Upper Layer ), which its address is stored in the Global of Array of Pointers to Functions ( TimersInterruptsAction ). */
		avpf_gs_systickInterruptsAction();
	}
	/* Check 2: Pointer to Function is equal to NULL. */
	else
	{
		/* Do Nothing. */
	}	
}


