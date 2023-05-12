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
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/PBD/PBD_interface.h"
#include "../HAL/DC_MOTOR/DC_MOTOR.h"

/* Section : Macro Declarations */
#define Timer2_Max_Counts		31
#define Timer2_Preload_Value	124

/* Section : Macro Functions Declarations */

/* Section : Data Type Declarations */
volatile u8 Timer2_Counter, Timer2_Flag;

/* Section : Function Declarations */
void app_init();
void app_main();

#endif /* APP_APP_H_ */
