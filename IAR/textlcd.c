#include "textlcd.h"


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
		TextLcd_Dimension _TextLcd_Dimension,
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
		uint16_t			D7_PINx)
{
	/* Store Information in Pointer Lcd_HandleTypeDef */
	Lcd_HandleTypeDef->_TextLcd_Dimension=_TextLcd_Dimension;

	Lcd_HandleTypeDef->RS_GPIOx=RS_GPIOx;
	Lcd_HandleTypeDef->RS_PINx=RS_PINx;

	Lcd_HandleTypeDef->EN_GPIOx=EN_GPIOx;
	Lcd_HandleTypeDef->EN_PINx=EN_PINx;

	Lcd_HandleTypeDef->D4_GPIOx=D4_GPIOx;
	Lcd_HandleTypeDef->D4_PINx=D4_PINx;

	Lcd_HandleTypeDef->D5_GPIOx=D5_GPIOx;
	Lcd_HandleTypeDef->D5_PINx=D5_PINx;

	Lcd_HandleTypeDef->D6_GPIOx=D6_GPIOx;
	Lcd_HandleTypeDef->D6_PINx=D6_PINx;

	Lcd_HandleTypeDef->D7_GPIOx=D7_GPIOx;
	Lcd_HandleTypeDef->D7_PINx=D7_PINx;


	/* Initialize all pin as output */
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->RS_GPIOx,Lcd_HandleTypeDef->RS_PINx);
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	GPIO_setAsOutputPin(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);

	Delay_ms(40);

	PIN_LOW(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	PIN_HIGH(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	PIN_LOW(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	PIN_LOW(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);
	PIN_LOW(Lcd_HandleTypeDef->RS_GPIOx,Lcd_HandleTypeDef->RS_PINx);

	PIN_HIGH(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);
	PIN_LOW(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);

	textlcd_write(Lcd_HandleTypeDef,0,0x28);
	textlcd_write(Lcd_HandleTypeDef,0,0x0c);
	textlcd_write(Lcd_HandleTypeDef,0,0x06);
	textlcd_write(Lcd_HandleTypeDef,0,0x01);
}


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
		uint8_t type, uint8_t data)
{
	Delay_ms(2);
	if(type)
	{
		PIN_HIGH(Lcd_HandleTypeDef->RS_GPIOx,Lcd_HandleTypeDef->RS_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->RS_GPIOx,Lcd_HandleTypeDef->RS_PINx);
	}

	//Send High Nibble
	if(data&0x80)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);
	}

	if(data&0x40)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	}

	if(data&0x20)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	}

	if(data&0x10)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	}
	PIN_HIGH(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);
	PIN_LOW(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);


	//Send Low Nibble
	if(data&0x08)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D7_GPIOx,Lcd_HandleTypeDef->D7_PINx);
	}

	if(data&0x04)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D6_GPIOx,Lcd_HandleTypeDef->D6_PINx);
	}

	if(data&0x02)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D5_GPIOx,Lcd_HandleTypeDef->D5_PINx);
	}

	if(data&0x01)
	{
		PIN_HIGH(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	}else
	{
		PIN_LOW(Lcd_HandleTypeDef->D4_GPIOx,Lcd_HandleTypeDef->D4_PINx);
	}
	PIN_HIGH(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);
	PIN_LOW(Lcd_HandleTypeDef->EN_GPIOx,Lcd_HandleTypeDef->EN_PINx);
}



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
		uint8_t row, uint8_t column, uint8_t *string, uint8_t length)
{
	uint8_t i=0;
	//Set Cursor Position
	switch (Lcd_HandleTypeDef->_TextLcd_Dimension)
	{
	case TextLcd_Dimension16xN: //For LCD16x2 or LCD16x4
		switch(row)
		{
		case 0: //Row 0
			textlcd_write(Lcd_HandleTypeDef,0,0x80+0x00+column);
			break;
		case 1: //Row 1
			textlcd_write(Lcd_HandleTypeDef,0,0x80+0x40+column);
			break;
		case 2: //Row 2
			textlcd_write(Lcd_HandleTypeDef,0,0x80+0x10+column);
			break;
		case 3: //Row 3
			textlcd_write(Lcd_HandleTypeDef,0,0x80+0x50+column);
			break;
		}
		break;
		case TextLcd_Dimension20xN: //For LCD20x2 or LCD20x4
			switch(row)
			{
			case 0: //Row 0
				textlcd_write(Lcd_HandleTypeDef,0,0x80+0x00+column);
				break;
			case 1: //Row 1
				textlcd_write(Lcd_HandleTypeDef,0,0x80+0x40+column);
				break;
			case 2: //Row 2
				textlcd_write(Lcd_HandleTypeDef,0,0x80+0x14+column);
				break;
			case 3: //Row 3
				textlcd_write(Lcd_HandleTypeDef,0,0x80+0x54+column);
				break;
			}
			break;
	}

	while(length--)
	{
		textlcd_write(Lcd_HandleTypeDef,1,*(string+i));
		i++;
	}
}



/* @Brief	: 	Clear screen of text lcd
 *
 * @Para	:	+ Lcd_HandleTypeDef - This is pointer to text lcd struct store text lcd information
 *
 * @Return	:	None
 * @Note	:   None
 */
void textlcd_clear(TextLcd_4Bit_HandleTypeDef * Lcd_HandleTypeDef)
{
	textlcd_write(Lcd_HandleTypeDef,0,0x01);
}
