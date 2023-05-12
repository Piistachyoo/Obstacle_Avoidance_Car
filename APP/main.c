/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : main.c                                  	    		 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "main.h"

int main(){
	u8 Button_State;
	app_init();
	DC_MOTOR_Turn_On(&M1);
	DC_MOTOR_Turn_On(&M2);
	DC_MOTOR_Turn_On(&M3);
	DC_MOTOR_Turn_On(&M4);
	while(1){
		PBD_vGetButtonState(&myPB, &Button_State);
		if(BUTTON_PRESSED == Button_State){
			DC_MOTOR_Turn_On(&M1);
			DC_MOTOR_Turn_On(&M2);
			DC_MOTOR_Turn_On(&M3);
			DC_MOTOR_Turn_On(&M4);
		}
		else{
			DC_MOTOR_Turn_Off(&M1);
			DC_MOTOR_Turn_Off(&M2);
			DC_MOTOR_Turn_Off(&M3);
			DC_MOTOR_Turn_Off(&M4);
		}
	}
	return 0;
}

void app_init(){
	LCD_4bit_vInit(&myLCD);
	KPD_vInit(&myKPD);
	PBD_vInit(&myPB);
	HCSR04_vInit();
	DC_MOTOR_vInit(&M1);
	DC_MOTOR_vInit(&M2);
	DC_MOTOR_vInit(&M3);
	DC_MOTOR_vInit(&M4);
}
