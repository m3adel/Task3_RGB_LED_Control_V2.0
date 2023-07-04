#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "systick_lcfg.h"
#include "TM4C123.h"

void SYSTICK_init (systick_st_cfg_t systick_st_cfg);
void SYSTICK_set (u32 u32_a_reload_value);
void SYSTICK_interrupt_en(void);
void SYSTICK_interrupt_dis(void);
u8 SYSTICK_getStatus(void);
void SYSTICK_Stop (void);
#endif /*SYSTICK_H_*/
