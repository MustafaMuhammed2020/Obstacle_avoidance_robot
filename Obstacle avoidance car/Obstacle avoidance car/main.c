/***************************************************************/
/** Author  : Mustafa Mohammed Abdou                          **/
/** Date    : 16 May , 2021                                   **/
/** Version : V01                                             **/
/***************************************************************/


// #include <avr/io.h>

//#include "APP/APP.h"
#include "SERVICE/standard_types.h"
#include "MCAL/timer0/TMR0_interface.h"
#include "MCAL/timer1/timer1_interface.h"
#include "HAL/lcd/LCD_interface.h"
#include "MCAL/dio/DIO_interface.h"



int main(void)
{
	//APP_init();
	
	DIO_setpindir(DIO_PORTB, DIO_PIN5, DIO_PIN_OUTPUT);
	DIO_setpindir(DIO_PORTB, DIO_PIN6, DIO_PIN_OUTPUT);
	DIO_setpindir(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);
	
	TMR0_init();
	
	LCD_init();
	TMR0_delayms(50);
	
	
	TMR0_delayms(50);
    /* Replace with your application code */
    LCD_writestr("Mohab");
	
	USONIC_init();
	while (1) 
    {
		uint8_t distance;
		USONIC_getdistance(&distance);
		LCD_sendcmd(LCD_CLEAR);
		
		TMR0_delayms(50);
		LCD_goto(0,0);
		LCD_writestr("Distance");
		LCD_goto(1,0);
		LCD_writeint(distance);	
		DIO_setpinvalue(DIO_PORTB, DIO_PIN6, DIO_PIN_LOW);
		TMR0_delayms(1000);
		DIO_setpinvalue(DIO_PORTB, DIO_PIN5, DIO_PIN_LOW);
		DIO_setpinvalue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW);
		//APP_start();
    }
}

