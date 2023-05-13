/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Motor_Control.c                                    	 */
/* Date          : May 13, 2023                                          */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "Motor_Control.h"

extern LCD_4bit_cfg myLCD;
extern TMR_cfg_t myTimer0;
extern volatile u8 Timer0_Compare_Value;

/*
 * A function that changes the motor speed and starts movement
 */
void Change_Motor_Speed(u8 Copy_u8Speed){
	switch(Copy_u8Speed){
	case MOTOR_SPEED_0:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"0%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_STOPPED);
		TMR_vStop(&myTimer0);
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, LOW);
		break;
	case MOTOR_SPEED_30_R:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"30%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_ROTATING);
		Timer0_Compare_Value = 3;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
		TMR_vStartTimer(&myTimer0);
		break;
	case MOTOR_SPEED_30_F:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"30%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_FORWARD);
		Timer0_Compare_Value = 3;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
		TMR_vStartTimer(&myTimer0);
		break;
	case MOTOR_SPEED_30_B:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"30%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_BACKWARD);
		Timer0_Compare_Value = 3;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
		TMR_vStartTimer(&myTimer0);
		break;
	case MOTOR_SPEED_50_F:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"50%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_FORWARD);
		Timer0_Compare_Value = 5;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
		TMR_vStartTimer(&myTimer0);
		break;
	case MOTOR_SPEED_50_B:
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"    ", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		LCD_4bit_vSendString_pos(&myLCD, (u8*)"50%", LCD_SPEED_ROW, LCD_SPEED_VALUE_COL);
		Change_Motor_Direction(MOTOR_DIR_BACKWARD);
		Timer0_Compare_Value = 5;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
		TMR_vStartTimer(&myTimer0);
		break;
	default: /* Do Nothing */ break;
	}
}

/*
 * A function that changes the direction of the movement on the LCD
 */
void Change_Motor_Direction(u8 Copy_u8Motor_Direction){
	switch(Copy_u8Motor_Direction){
	case MOTOR_DIR_FORWARD:
		LCD_4bit_vSendChar_pos(&myLCD, 'F', LCD_DIR_ROW, LCD_DIR_VALUE_COL);
		break;
	case MOTOR_DIR_BACKWARD:
		LCD_4bit_vSendChar_pos(&myLCD, 'B', LCD_DIR_ROW, LCD_DIR_VALUE_COL);
		break;
	case MOTOR_DIR_ROTATING:
		LCD_4bit_vSendChar_pos(&myLCD, 'R', LCD_DIR_ROW, LCD_DIR_VALUE_COL);
		break;
	case MOTOR_DIR_STOPPED:
		LCD_4bit_vSendChar_pos(&myLCD, 'S', LCD_DIR_ROW, LCD_DIR_VALUE_COL);
		break;
	default: /* Do Nothing */ break;
	}
}
