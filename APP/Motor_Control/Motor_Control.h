/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* File          : Motor_Control.h                                    	     */
/* Date          : May 13, 2023                                           */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/
#ifndef APP_MOTOR_CONTROL_MOTOR_CONTROL_H_
#define APP_MOTOR_CONTROL_MOTOR_CONTROL_H_

/* Section : Includes */
#include "../app.h"

/* Section : Macro Declarations */
#define MOTOR_MOVE_FORWARD		motor_direction_right
#define MOTOR_MOVE_BACKWARD		motor_direction_left

#define MOTOR_DIR_FORWARD		0
#define MOTOR_DIR_BACKWARD		1
#define MOTOR_DIR_ROTATING		2
#define MOTOR_DIR_STOPPED		3

#define MOTOR_SPEED_0			0
#define MOTOR_SPEED_30_R		1
#define MOTOR_SPEED_30_F		2
#define MOTOR_SPEED_30_B		3
#define MOTOR_SPEED_50_F		4
#define MOTOR_SPEED_50_B		5

#define MOTOR_EN_PWM_PORT		PORTA
#define MOTOR_EN_PWM_PIN		PIN7

/* Section : Function Declarations */

/*
 * A function that changes the motor speed and starts movement
 */
void Change_Motor_Speed(u8 Copy_u8Speed);

/*
 * A function that changes the direction of the movement on the LCD
 */
void Change_Motor_Direction(u8 Copy_u8Motor_Direction);


#endif /* APP_MOTOR_CONTROL_MOTOR_CONTROL_H_ */
