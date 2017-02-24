#ifndef __TEXT_LCD_H
#define __TEXT_LCD_H

#include "mymsp430.h"

/*
 * Description	:	This is libaray for Text LCD 16xN or 20xN (N=2 or N=4)
 * 					for MSP430 Microcontroller
 *
 * Author		:	Thiepnx
 *
 * Date			:	8/2/2017
 *
 * Include		:	+ Define private data type
 * 					+ Define Text lcd struct
 * 					+ Declaring function prototype.
 *
 * Note			:	Initialize Text Lcd work in mode
 * 					4 bit using RS,EN,D4,D5,D6,D7 Pin
 * 					Pin RW is connected to GND.
 */


/*----------- Define Private Struct and enum ------------*/


typedef enum
{
	TextLcd_Dimension16xN=1, /* For text lcd 16x2 or 16x4 */
	TextLcd_Dimension20xN=2  /* For text lcd 20x2 or 20x4 */

}TextLcd_Dimension;


typedef struct
{
	TextLcd_Dimension _TextLcd_Dimension;

	uint8_t				RS_GPIOx;
	uint16_t			RS_PINx;

	uint8_t				EN_GPIOx;
	uint16_t			EN_PINx;

	uint8_t				D4_GPIOx;
	uint16_t			D4_PINx;

	uint8_t				D5_GPIOx;
	uint16_t			D5_PINx;

	uint8_t				D6_GPIOx;
	uint16_t			D6_PINx;

	uint8_t				D7_GPIOx;
	uint16_t			D7_PINx;
}TextLcd_4Bit_HandleTypeDef;


/*------------ Define Private Macro -----------------*/

#define PIN_LOW(PORT,PIN) 	GPIO_setOutputLowOnPin(PORT,PIN);
#define PIN_HIGH(PORT,PIN) 	GPIO_setOutputHighOnPin(PORT,PIN);




/* @Brief	: 	Initialize Text LCD run in mode 4 bit using D4,D5,D6,D7,RS,EN pin
 * 				RW pin is connected to GND.
 *
 * @Para	:	+ Lcd_HandleTypeDef - This is struct of Text LCD to store information
 *
 * 				+ _TextLcd_Dimension - Specifies dimention of text lcd.
 *
 * 				+ RS_GPIOx - This is PORT of RS pin.
 * 				+ RS_PINx  - This is number of RS pin
 *
 * 				+ EN_GPIOx - This is PORT of EN pin.
 * 				+ EN_PINx  - This is number of EN pin
 *
 * 				+ D4_GPIOx - This is PORT of D4 pin.
 * 				+ D4_PINx  - This is number of D4 pin
 *
 * 				+ D5_GPIOx - This is PORT of D5 pin.
 * 				+ D5_PINx  - This is number of D5 pin
 *
 * 				+ D6_GPIOx - This is PORT of D6 pin.
 * 				+ D6_PINx  - This is number of D6 pin
 *
 * 				+ D7_GPIOx - This is PORT of D7 pin.
 * 				+ D7_PINx  - This is number of D7 pin
 *
 * @Return	:	None
 *
 * @Note	:   This function use Delay_ms() function so user must be implement
 * 				Delay_Using_TimerA2_Init() function and Delay_Using_TimerA2_ISR() function
 * 				before call this function.
 */
void textlcd_init(TextLcd_4Bit_HandleTypeDef * Lcd_HandleTypeDef,
		TextLcd_Dimension 	_TextLcd_Dimension,
		uint8_t				RS_GPIOx,
		uint16_t			RS_PINx,
		uint8_t				EN_GPIOx,
		uint16_t			EN_PINx,
		uint8_t				D4_GPIOx,
		uint16_t			D4_PINx,
		uint8_t				D5_GPIOx,
		uint16_t			D5_PINx,
		uint8_t				D6_GPIOx,
		uint16_t			D6_PINx,
		uint8_t				D7_GPIOx,
		uint16_t			D7_PINx);


/* @Brief	: 	Write a data or command to text lcd
 *
 * @Para	:	+ Lcd_HandleTypeDef - This is pointer to text lcd struct store text lcd information
 * 				+ type	- If type=0 write a command to text lcd
 * 						- If type!= write a data to text lcd
 * 				+ data	- This is data or command is writen to text lcd.
 *
 * @Return	:	None
 * @Note	:   None
 */
void textlcd_write(TextLcd_4Bit_HandleTypeDef * Lcd_HandleTypeDef,
		uint8_t type, uint8_t data);


/* @Brief	: 	Write a string to current position of text lcd
 *
 * @Para	:	+ Lcd_HandleTypeDef - This is pointer to text lcd struct store text lcd information
 *
 * 				+ row	- This is start row to write
 * 				+ column - This is start column to write
 *
 * 				+ string - This is pointer of string, which is writen to text lcd
 *
 * 				+ length - This is number of character in string.
 *
 * @Return	:	None
 * @Note	:   The value of row and column depend on the dimention of text lcd.
 */
void textlcd_puts(TextLcd_4Bit_HandleTypeDef * Lcd_HandleTypeDef,
		uint8_t row, uint8_t column, uint8_t *string,uint8_t length);



/* @Brief	: 	Clear screen of text lcd
 *
 * @Para	:	+ Lcd_HandleTypeDef - This is pointer to text lcd struct store text lcd information
 *
 * @Return	:	None
 * @Note	:   None
 */
void textlcd_clear(TextLcd_4Bit_HandleTypeDef * Lcd_HandleTypeDef);

#endif

