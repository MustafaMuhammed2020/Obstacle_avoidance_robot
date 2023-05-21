/*
 * APP.c
 *
 * Created: 5/21/2023 12:05:05 AM
 *  Author: mohab
 */ 
#include "APP.h"
#include "../SERVICE/standard_types.h"
#include "../MCAL/timer0/TMR0_interface.h"
#include "../MCAL/timer1/timer1_interface.h"
#include "../HAL/lcd/LCD_interface.h"
#include "../MCAL/dio/DIO_interface.h"
#include "../HAL/ultrasonic/ultrasonic.h"

#define frd_mask  0b00001111
#define left_mask 0b00111100
#define right_mask 0b11000011
#define back_mask 0b11110000
static uint8_t dir_mask = 0b10100101;

void APP_init(void)
{
	KEYPAD_init();
	
	for(int i=0;i<8;i++)
	{
		MOTOR_init(i, DIO_PORTC);
	}
	DIO_setpindir(DIO_PORTB, DIO_PIN0, DIO_PIN_INPUT);
	uint8_t count_5_sec=0;
	uint8_t PB0_state=0;
	TMR0_init();
	
	LCD_init();
	
	TMR0_delayms(50);
			
	USONIC_init();
	while(KEYPAD_getpressedkey() != '1' );
	LCD_goto(0,0);
	LCD_writestr("Set def. rotation");
	LCD_goto(1,0);
	LCD_writestr("right");
	while(count_5_sec<100)
	{
		while(!PB0_state)
		DIO_readpin(DIO_PORTB, DIO_PIN0, &PB0_state);
		
		while(PB0_state)
		if(PB0_state==1)
		{
			dir_mask = dir_mask==left_mask? right_mask:left_mask;
		}
		while(PB0_state)
		DIO_readpin(DIO_PORTB, DIO_PIN0, &PB0_state);
		TMR0_delayms(50);
		LCD_goto(1,0);
		if(dir_mask==left_mask)
		{
			LCD_writestr("left ");
		}
		else
		LCD_writestr("right");
		count_5_sec++;
	}
	
}


void APP_start(void)
{
	
	static uint8_t count_5_sec=0;
	uint8_t distance;
	uint8_t next_mask=0;
	uint8_t next_speed;
	if(KEYPAD_getpressedkey() == '2')
	{
		count_5_sec=0;
		MOTOR_off(0xff,DIO_PORTC);
		LCD_sendcmd(LCD_CLEAR);
		TMR0_delayms(10);
		LCD_goto(0,0);
		LCD_writestr("Stop");
		while(KEYPAD_getpressedkey()!= '1');
	}
	USONIC_getdistance(&distance);
	if(distance>=70)
	{
		if(count_5_sec<33)
		{
			next_speed=30;
			count_5_sec++;
		}
		
		else
		next_speed=50;
		next_mask = frd_mask;	
	}
	else if(distance>=30)
	{
		count_5_sec=0;
		next_speed=30;
		next_mask = frd_mask;
	}
	else if(distance>=20)
	{
		count_5_sec=0;
		MOTOR_off(0xff,DIO_PORTC);
		TMR0_delayms(100);
		next_speed=30;
		next_mask=dir_mask;
		for(int i=0;i<5;i++)
		MOTOR_control(next_mask, DIO_PORTC, next_speed);
	}
	else
	{
		count_5_sec=0;
		next_speed=30;
		next_mask=back_mask;
	}
	MOTOR_control(next_mask, DIO_PORTC, next_speed);
	LCD_sendcmd(LCD_CLEAR);
	TMR0_delayms(10);
	LCD_goto(0,0);
	LCD_writestr("Speed:");
	LCD_writeint(next_speed);
	LCD_writestr("% dir:");
	switch (next_mask)
	{
		case frd_mask:
		LCD_writestr("F");
		break;
		case back_mask:
		LCD_writestr("B");
		break;
		case right_mask:
		LCD_writestr("R");
		break;
		case left_mask:
		LCD_writestr("L");
		break;
	}
	LCD_goto(1,0);
	LCD_writestr("Dist.:");
	LCD_writeint(distance);
	
	
}