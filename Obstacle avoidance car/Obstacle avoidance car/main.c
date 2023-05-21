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
	APP_init();
	
	while (1) 
    {
		APP_start();
    }
}

