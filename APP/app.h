/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : main.h                                  	    		 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef APP_APP_H_
#define APP_APP_H_

/* Section : Includes */

#include "../HAL/HCSR04_Ultrasonic_Sensor/HCSR04.h"
#include "../HAL/LCD_4bit/lcd_interface.h"
#include "../HAL/PBD/PBD_interface.h"
#include "../HAL/DC_MOTOR/DC_MOTOR.h"
#include "Config_Interface/CFG_interface.h"
#include "Motor_Control/Motor_Control.h"
#include <stdlib.h>

/* Section : Macro Declarations */
#define Timer0_Max_Counts		10
#define Timer2_Max_Counts		31
#define Timer2_Preload_Value	124

#define LCD_SPEED_ROW			ROW1
#define LCD_SPEED_TEXT_COL		1
#define LCD_SPEED_VALUE_COL		7
#define LCD_DIR_ROW				ROW1
#define LCD_DIR_TEXT_COL		12
#define LCD_DIR_VALUE_COL		16
#define LCD_DISTANCE_ROW		ROW2
#define LCD_DISTANCE_TEXT_COL	1
#define LCD_DISTANCE_VALUE_COL	7

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */

/* Section : Function Declarations */

/* A function that initializes hardware components */
void app_init();

/* Program main super loop */
void app_main();

/* This function prints the defaults parameters on the LCD */
void Print_LCD_Default();

/* This function reads the ultrasonic sensor reading and display it on the LCD */
void Read_Print_Sensor();

/* ISR for Timer0 over flow */
void Timer0_ISR(void);

/* ISR for Timer2 over flow */
void Timer2_ISR(void);

#endif /* APP_APP_H_ */
