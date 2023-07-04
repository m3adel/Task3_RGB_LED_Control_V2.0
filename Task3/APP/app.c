/*
 * APP
 * Created: 6/22/2023 11:14:30 PM
 * Author : MOHAMED ABDELSALAM
 */ 
/*- INCLUDES
----------------------------------------------*/
#include "app.h"

/*- LOCAL MACROS
------------------------------------------*/

/*- GLOBAL STATIC VARIABLES
-------------------------------*/
str_gpio_config_t RED_LED;
str_gpio_config_t GREEN_LED;
str_gpio_config_t BLUE_LED;
str_gpio_config_t SW1;

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/


/*- APIs IMPLEMENTATION
-----------------------------------*/
void APP_init(void)
{
	RED_LED.enm_gpio_pinNumber = P1;
	RED_LED.enm_gpio_portNumber = F;
	BLUE_LED.enm_gpio_pinNumber = P2;
	BLUE_LED.enm_gpio_portNumber = F;
	GREEN_LED.enm_gpio_pinNumber = P3;
	GREEN_LED.enm_gpio_portNumber = F;
	SW1.enm_gpio_pinNumber = P0;
	SW1.enm_gpio_portNumber = F;
	LED_init(RED_LED);
	LED_init(GREEN_LED);
	LED_init(BLUE_LED);
	BUTTON_init (SW1);	
}
void APP_start(void)
{
		static u8 app_u8_l_Counter = STATE_1;
		while (BUTTON_read(SW1)== TRUE );
		while (BUTTON_read(SW1)== FALSE );
		(app_u8_l_Counter)++;
	
	if (app_u8_l_Counter == STATE_NUMBER)
		{
			app_u8_l_Counter = STATE_1;
		}
		switch(app_u8_l_Counter)
		{
			case STATE_1:
			LED_off(RED_LED);
			LED_off(GREEN_LED);
			LED_off(BLUE_LED);			
			case STATE_2:
			LED_on(RED_LED);
			case STATE_3:
			LED_on(GREEN_LED);
			case STATE_4:
			LED_on(BLUE_LED); 
			case STATE_5:
			LED_on(RED_LED);
			LED_on(GREEN_LED);
			LED_on(BLUE_LED);
			break;
			default:
			//
			break;					
		}
		Delay_ms(ONE_SEC);
		LED_off(RED_LED);
		LED_off(GREEN_LED);
		LED_off(BLUE_LED);
}

