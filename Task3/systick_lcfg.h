
#ifndef SYSTICK_LCFG_H_
#define SYSTICK_LCFG_H_
#include "common.h"
typedef enum
{
	PRECISION_INTERNAL_OSCILLATOR	,
	SYSTEM_CLOCK
}systick_en_clock_source_t;

typedef enum
{
	DISABLED	,
	ENABLED
}systick_en_interrupt_t;

typedef enum
{
	COUNTER_DISABLED	,
	MULTI_SHOT
}systick_en_mode_t;


typedef struct
{
	systick_en_clock_source_t	systick_en_clock_source;
	systick_en_interrupt_t		systick_en_interrupt;
	systick_en_mode_t					systick_en_mode;
	u32												systick_u32_reload_value;
	
}systick_st_cfg_t;

#endif /*SYSTICK_LCFG_H_*/
