/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : CFG.c                                  	    		 */
/* Date          : May 13, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "CFG_interface.h"

static u8 remaining_seconds = 5;
extern motor_direction_t Configured_Motor_Direction;
extern PB_cfg myPB;
extern LCD_4bit_cfg myLCD;
extern TMR_cfg_t myTimer2;
extern volatile u8 Timer2_Flag;

/* A function that is called to set the default rotation for the car when stuck */
void CFG_Direction(){
	u8 Button_State = 99;
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"Set Def. Rot.", ROW1, 3);
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"Right", ROW2, 6);
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"5", ROW2, 16);
	Timer2_Flag = 0;
	TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
	TMR_vStartTimer(&myTimer2);
	while(5 != Timer2_Flag){
		PBD_vGetButtonState(&myPB, &Button_State);
		if(BUTTON_PRESSED == Button_State){
			if(motor_direction_right == Configured_Motor_Direction){
				Configured_Motor_Direction = motor_direction_left;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"     ", ROW2, 6);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"Left", ROW2, 6);
			}
			else if(motor_direction_left == Configured_Motor_Direction){
				Configured_Motor_Direction = motor_direction_right;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"     ", ROW2, 6);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"Right", ROW2, 6);
			}
			else{ /* Do Nothing */ }
		}
		if(1 == Timer2_Flag){
			if(4 != remaining_seconds){
				remaining_seconds = 4;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)" ", ROW2, 16);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"4", ROW2, 16);
			}
		}
		else if(2 == Timer2_Flag){
			if(3 != remaining_seconds){
				remaining_seconds = 3;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)" ", ROW2, 16);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"3", ROW2, 16);
			}
		}
		else if(3 == Timer2_Flag){
			if(2 != remaining_seconds){
				remaining_seconds = 2;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)" ", ROW2, 16);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"2", ROW2, 16);
			}
		}
		else if(4 == Timer2_Flag){
			if(1 != remaining_seconds){
				remaining_seconds = 1;
				LCD_4bit_vSendString_pos(&myLCD, (u8*)" ", ROW2, 16);
				LCD_4bit_vSendString_pos(&myLCD, (u8*)"1", ROW2, 16);
			}
		}
		else{ /* Do Nothing */ }
	}
	TMR_vStop(&myTimer2);
	LCD_4bit_vSendCmd(&myLCD, CLEAR_DISPLAY);
}
