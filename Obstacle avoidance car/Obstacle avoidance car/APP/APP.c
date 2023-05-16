/***************************************************************/
/** Author  : Mustafa Mohammed Abdou                          **/
/** Date    : 16 May , 2021                                   **/
/** Version : V01                                             **/
/***************************************************************/

/** INCLUDE LIBRARIES **/
#include "avr/interrupt.h"

#include "../SERVICE/common_macros.h"
#include "../SERVICE/standard_types.h"

/** INCLUDE LOWER LAYERS FILES **/
#include "../MCAL/dio/DIO_interface.h"
#include "../MCAL/int0/INT_interface.h"
#include "../MCAL/timer1/timer1_interface.h"
#include "../HAL/lcd/LCD_interface.h"
#include "../MCAL/timer0/TMR0_interface.h"

/** INCLUDE DRIVER FILES **/
#include "APP.h"

uint8_t u8_g_edge = 0 ;  /** GLOBAL COUNTER FOR NUMBER OF EDGES **/
uint16t u16_g_t1 = 0 ;   /** GLOBAL VARIABLE FOR TIME1 VALUE **/
uint16t u16_g_t2 = 0 ;   /** GLOBAL VARIABLE FOR TIME1 VALUE **/
uint32_t u32_g_time = 0 ; /** GLOBAL VARIABLE FOR TIME **/

void APP_init()
{
	//u8_g_edge = 0 , u16_g_t1 = 0 , u16_g_t2 = 0 , u16_g_time = 0 ; /** INITIALIZATION FOR EDGES COUNTER **/
	
	DIO_setpindir(DIO_PORTD , DIO_PIN2 , DIO_PIN_INPUT); /** INT0 PIN **/
	
	INT0_init(); /** INITIALIZE INT0 **/
	
	TMR0_init(); /** INITIALIZE TIMER0 **/
	
	TMR1_init(); /** INITIALIZE TIMER1 **/
	
	LCD_init(); /** INITIALIZE LCD **/
	
	TMR0_delayms(50); /** DELAY FOR LCD INITIALIZATION **/
	
	TMR1_start();
	
}


void APP_start()
{

}


ISR(INT0_vect) /** ISR OF INT0 **/
{
	u8_g_edge++ ; /** COUNTER FOR EDGES **/
	
	if (u8_g_edge == 1) /** FIRST RISING EDGE **/
	{
		TMR1_getvalue(&u16_g_t1);
		LCD_goto(0,0);
		LCD_writestr("t1 = ");
		LCD_writeint(u16_g_t1);
	}
	
 	if (u8_g_edge == 2) /** SECOND RISING EDGE **/
 	{
 		TMR1_getvalue(&u16_g_t2);
 		
		LCD_goto(1,0);
		LCD_writestr("t2 = ");
		LCD_writeint(u16_g_t2);
		 
		u8_g_edge = 0 ; /** REINITIALIZE THE EDGES COUNTER TO 0 **/
	}
	
}