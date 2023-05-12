/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car									 */
/* File          : main.h                                  	    		 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#ifndef APP_MAIN_H_
#define APP_MAIN_H_

/* Section : Includes */
#include "../HAL/HCSR04_Ultrasonic_Sensor/HCSR04.h"
#include "../HAL/LCD_4bit/lcd_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/PBD/PBD_interface.h"
#include "../HAL/DC_MOTOR/DC_MOTOR.h"

/* Section : Macro Declarations */

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
dc_motor_t M1 = {.motor_port = PORTB, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN2};
dc_motor_t M2 = {.motor_port = PORTB, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
dc_motor_t M3 = {.motor_port = PORTD, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN3};
dc_motor_t M4 = {.motor_port = PORTD, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
PB_cfg myPB = {.PortName = PORTC, .PinNum = PIN0, .PBmode = MODE_PULLUP};
LCD_4bit_cfg myLCD = {.LCD_PORT = PORTC, .LCD_RS_PIN = PIN2, .LCD_EN_PIN = PIN3};
KPD_cfg myKPD = {.KPD_Port = PORTA, .R1_PIN = PIN0, .R2_PIN = PIN1, .R3_PIN = PIN2, .R4_PIN = PIN3,
				 .C1_PIN = PIN4, .C2_PIN = PIN5, .C3_PIN = PIN6, .C4_PIN = PIN7};

/* Section : Function Declarations */
void app_init();

#endif /* APP_MAIN_H_ */
