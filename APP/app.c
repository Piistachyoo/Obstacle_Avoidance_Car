/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : main.c                                  	    		 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "app.h"

motor_direction_t Current_Motor_Direction = motor_direction_right;
void Timer0_ISR(void);

dc_motor_t M1 = {.motor_port = PORTB, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN2};
dc_motor_t M2 = {.motor_port = PORTB, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
dc_motor_t M3 = {.motor_port = PORTD, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN3};
dc_motor_t M4 = {.motor_port = PORTD, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
PB_cfg myPB = {.PortName = PORTC, .PinNum = PIN0, .PBmode = MODE_PULLUP};
LCD_4bit_cfg myLCD = {.LCD_PORT = PORTC, .LCD_RS_PIN = PIN2, .LCD_EN_PIN = PIN3};
KPD_cfg myKPD = {.KPD_Port = PORTA, .R1_PIN = PIN0, .R2_PIN = PIN1, .R3_PIN = PIN2, .R4_PIN = PIN3,
				 .C1_PIN = PIN4, .C2_PIN = PIN5, .C3_PIN = PIN6, .C4_PIN = PIN7};
/* Timer frequency = 8MHZ/1024
 * Tick time = 128 usec
 * Overflow time = 32.768 msec
 * No. of overflows to reach 1 seconds = 31
 * Preload value = 124
 */
TMR_cfg_t myTimer2 = {.TMR_TimerChannel = TIMER2_NORMAL, .TMR_Prescale = TMR_PRE_1024,
		.TMR_ToggleMode = TMR_InterruptMode, .TMR_OCMode = OC_Disconnected};


void app_init(){
	LCD_4bit_vInit(&myLCD);
	KPD_vInit(&myKPD);
	PBD_vInit(&myPB);
	HCSR04_vInit();
	DC_MOTOR_vInit(&M1);
	DC_MOTOR_vInit(&M2);
	DC_MOTOR_vInit(&M3);
	DC_MOTOR_vInit(&M4);
	TMR_vInit(&myTimer2);
	TMR_vSetCallback(&myTimer2, Timer0_ISR);
}

void app_main(){
	Timer2_Flag = 0;
	TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
	TMR_vStartTimer(&myTimer2);
	while(2 != Timer2_Flag); // Wait 2 seconds
	TMR_vStop(&myTimer2);
	DC_MOTOR_Turn_On(&M1, Current_Motor_Direction);
	DC_MOTOR_Turn_On(&M2, Current_Motor_Direction);
	DC_MOTOR_Turn_On(&M3, Current_Motor_Direction);
	DC_MOTOR_Turn_On(&M4, Current_Motor_Direction);
}

void Timer0_ISR(void){
	Timer2_Counter++;
	if(Timer2_Max_Counts == Timer2_Counter){
		Timer2_Flag++;
		Timer2_Counter = 0;
		TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
	}
}
