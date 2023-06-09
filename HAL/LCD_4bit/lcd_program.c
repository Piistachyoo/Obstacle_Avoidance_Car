/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : lcd_program.c                                  	     */
/* Date          : Mar 26, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "../LCD_4bit/lcd_interface.h"

void LCD_4bit_vInit(const LCD_4bit_cfg *PTR_LCD){
	DIO_vSetGroupDir(PTR_LCD->LCD_PORT, OUTPUT);

	/* Send Function Set */
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RW_PIN, LOW);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RS_PIN, LOW);
	_delay_us(40);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, HIGH);
	_delay_us(150);
	DIO_vSet4MSBValue(PTR_LCD->LCD_PORT, (TWO_LINE_4BIT_BIG_FONT));
	_delay_us(80);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, LOW);
	_delay_us(300);

	LCD_4bit_vSendCmd(PTR_LCD, TWO_LINE_4BIT_BIG_FONT);
	_delay_us(40);

	/* Send Display On/Off control */
	LCD_4bit_vSendCmd(PTR_LCD, CURSOR_OFF);
	_delay_us(50);

	/* Display Clear */
	LCD_4bit_vSendCmd(PTR_LCD, CLEAR_DISPLAY);
	_delay_ms(2);

	/* Entry mode set */
	LCD_4bit_vSendCmd(PTR_LCD, START_FROM_LEFT);
}

void LCD_4bit_vSendCmd(const LCD_4bit_cfg *PTR_LCD, u8 Copy_u8Cmd){
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RW_PIN, LOW);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RS_PIN, LOW);
	_delay_us(40);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, HIGH);
	_delay_us(150);
	DIO_vSet4MSBValue(PTR_LCD->LCD_PORT, (Copy_u8Cmd));
	_delay_us(80);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, LOW);
	_delay_us(300);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, HIGH);
	_delay_us(150);
	DIO_vSet4MSBValue(PTR_LCD->LCD_PORT, (Copy_u8Cmd<<4));
	_delay_us(80);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, LOW);
	_delay_us(300);
}

void LCD_4bit_vSendChar(const LCD_4bit_cfg *PTR_LCD, u8 Copy_u8Char){
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RW_PIN, LOW);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_RS_PIN, HIGH);
	_delay_us(40);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, HIGH);
	_delay_us(150);
	DIO_vSet4MSBValue(PTR_LCD->LCD_PORT, (Copy_u8Char));
	_delay_us(80);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, LOW);
	_delay_us(300);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, HIGH);
	_delay_us(150);
	DIO_vSet4MSBValue(PTR_LCD->LCD_PORT, (Copy_u8Char<<4));
	_delay_us(80);
	DIO_vSetPinValue(PTR_LCD->LCD_PORT, PTR_LCD->LCD_EN_PIN, LOW);
	_delay_us(300);
}

void LCD_4bit_vSendChar_pos(const LCD_4bit_cfg *PTR_LCD, u8 Copy_u8Char, u8 row, u8 column){
	LCD_4bit_SetCursorPosition(PTR_LCD, column, row);
	LCD_4bit_vSendChar(PTR_LCD, Copy_u8Char);
}

void LCD_4bit_vSendString(const LCD_4bit_cfg *PTR_LCD, u8 *Copy_u8String){
	for(int StrIndex=0;Copy_u8String[StrIndex] != '\0';StrIndex++){
		LCD_4bit_vSendChar(PTR_LCD, (u8)(Copy_u8String[StrIndex]));
	}
}

void LCD_4bit_vSendString_pos(const LCD_4bit_cfg *PTR_LCD, u8 *Copy_u8String, u8 row, u8 column){
	LCD_4bit_SetCursorPosition(PTR_LCD, column, row);
	LCD_4bit_vSendString(PTR_LCD, Copy_u8String);
}

void LCD_4bit_vSendNumber(const LCD_4bit_cfg *PTR_LCD, u16 Copy_u16Number){
	if(Copy_u16Number == 0){
		LCD_4bit_vSendChar(PTR_LCD, 48);
	}
	else{
		u8 size=0;
		u8 temp_array[5];
		while(Copy_u16Number != 0){
			temp_array[size] = Copy_u16Number%10;
			size++;
			Copy_u16Number /= 10;
		}
		for(int ArrIndex=size-1; ArrIndex>=0;ArrIndex--){
			LCD_4bit_vSendChar(PTR_LCD, temp_array[ArrIndex]+48);
		}
	}
}

void LCD_4bit_SetCursorPosition(const LCD_4bit_cfg *PTR_LCD, u8 column, u8 row){
	column--;
	switch(row){
		case ROW1: LCD_4bit_vSendCmd(PTR_LCD, (ROW1_Address + column)); break;
		case ROW2: LCD_4bit_vSendCmd(PTR_LCD, (ROW2_Address + column)); break;
		default: /* Do Nothing */ break;
	}
}

