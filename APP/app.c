/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : main.c                                  	    		 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "app.h"

motor_direction_t Configured_Motor_Direction = motor_direction_right;

dc_motor_t M1 = {.motor_port = PORTA, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN2};
dc_motor_t M2 = {.motor_port = PORTA, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
dc_motor_t M3 = {.motor_port = PORTD, .motor_pin1 = PIN0, .motor_pin2 = PIN1, .motor_en_pin = PIN2};
dc_motor_t M4 = {.motor_port = PORTD, .motor_pin1 = PIN3, .motor_pin2 = PIN4, .motor_en_pin = PIN5};
PB_cfg myPB = {.PortName = PORTC, .PinNum = PIN0, .PBmode = MODE_PULLUP};
LCD_4bit_cfg myLCD = {.LCD_PORT = PORTC, .LCD_RS_PIN = PIN2, .LCD_EN_PIN = PIN3};

/* Timer0 frequency = 8MHZ/1024
 * Tick time = 128 usec
 * Overflow time = 32.768 msec
 *
 * This timer is used for generating delays, incrementing (Timer2_Flag) variable every 1 second
 */
TMR_cfg_t myTimer2 = {.TMR_TimerChannel = TIMER2_NORMAL, .TMR_Prescale = TMR_PRE_1024,
		.TMR_ToggleMode = TMR_InterruptMode, .TMR_OCMode = OC_Disconnected};


/* Timer2 frequency = 8MHZ/1024
 * Tick time = 32 usec
 * Overflow time = 8.192 msec
 * Will be used in normal mode to generate PWM signal
 */
TMR_cfg_t myTimer0 = {.TMR_TimerChannel = TIMER0_NORMAL, .TMR_Prescale = TMR_PRE_256,
		.TMR_ToggleMode = TMR_InterruptMode, .TMR_OCMode = OC_Disconnected};

f64 Sensor_Reading;
u8 Sensor_Reading_String[7];
volatile u8 Timer2_Counter, Timer2_Flag;
volatile u8 Timer0_Counter, Timer0_Compare_Value;

/* A function that initializes hardware components */
void app_init(){
	LCD_4bit_vInit(&myLCD);
	PBD_vInit(&myPB);
	HCSR04_vInit();
	DC_MOTOR_vInit(&M1);
	DC_MOTOR_vInit(&M2);
	DC_MOTOR_vInit(&M3);
	DC_MOTOR_vInit(&M4);
	TMR_vInit(&myTimer0);
	TMR_vSetCallback(&myTimer0, Timer0_ISR);
	TMR_vInit(&myTimer2);
	TMR_vSetCallback(&myTimer2, Timer2_ISR);
	DIO_vPinInit(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, OUTPUT, LOW);
}

/* Program main super loop */
void app_main(){
	/* Wait 2 seconds before starting */
	Print_LCD_Default();
	Change_Motor_Direction(MOTOR_DIR_STOPPED);
	Timer2_Flag = 0;
	TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
	TMR_vStartTimer(&myTimer2);
	while(2 != Timer2_Flag); // Wait 2 seconds
	TMR_vStop(&myTimer2);
	/* Start program */
	while(1){
		Read_Print_Sensor(); // Read sensor periodically and print value on LCD
		/* If distance is more than 70cm, move forward with 30% speed for 5 seconds
		 * After 5 seconds, move with 50% speed until an obstacle is detected under 70cm
		 */
		if(70 < (u16)Sensor_Reading){
			DC_MOTOR_Turn_On(&M1, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M2, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M3, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M4, MOTOR_MOVE_FORWARD);
			Change_Motor_Speed(MOTOR_SPEED_30_F);
			TMR_vStartTimer(&myTimer0);
			Timer2_Flag = 0;
			TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
			TMR_vStartTimer(&myTimer2);
			while(70 < (u16)Sensor_Reading){
				Read_Print_Sensor();
				if(4 == Timer2_Flag){
					Change_Motor_Speed(MOTOR_SPEED_50_F);
					Timer2_Flag = 0;
					TMR_vStop(&myTimer2);
				}
			}
			TMR_vStop(&myTimer2);
			TMR_vStop(&myTimer0);
			//Change_Motor_Speed(MOTOR_SPEED_0);
		}
		/* If 30cm < distance <= 70cm, move forward with 30% speed */
		else if((70 >= (u16)Sensor_Reading) && (30 < (u16)Sensor_Reading)){
			DC_MOTOR_Turn_On(&M1, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M2, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M3, MOTOR_MOVE_FORWARD);
			DC_MOTOR_Turn_On(&M4, MOTOR_MOVE_FORWARD);
			Change_Motor_Speed(MOTOR_SPEED_30_F);
			TMR_vStartTimer(&myTimer0);
			while((70 >= (u16)Sensor_Reading) && (30 < (u16)Sensor_Reading)){
				Read_Print_Sensor();
			}
			TMR_vStop(&myTimer0);
			//Change_Motor_Speed(MOTOR_SPEED_0);
		}
		/* If 20cm < distance <= 30, move right or left, based on configuration set
		 * when starting the app in (CFG_Direction) function
		 * The car with move 90 degrees and checks if there's an obstacle with a distance
		 * between 20 and 30
		 */
		else if((30 >= (u16)Sensor_Reading) && (20 < (u16)Sensor_Reading)){
			/* Rotate 90 degrees to configured direction */

			DC_MOTOR_Turn_Off(&M1);
			DC_MOTOR_Turn_Off(&M2);
			DC_MOTOR_Turn_Off(&M3);
			DC_MOTOR_Turn_Off(&M4);
			if(motor_direction_right == Configured_Motor_Direction){
				DC_MOTOR_Turn_On(&M1, MOTOR_MOVE_FORWARD);
			}
			else if(motor_direction_left == Configured_Motor_Direction){
				DC_MOTOR_Turn_On(&M2, MOTOR_MOVE_FORWARD);
			}
			Change_Motor_Speed(MOTOR_SPEED_30_R);
			/* Delay 2 seconds */
			Timer2_Flag = 0;
			TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
			TMR_vStartTimer(&myTimer2);
			TMR_vStartTimer(&myTimer0);
			while(2 != Timer2_Flag){
				Read_Print_Sensor();
			}
			TMR_vStop(&myTimer0);
			TMR_vStop(&myTimer2);
			Change_Motor_Speed(MOTOR_SPEED_0);
		}
		/* If distance is less than 20, the car moves backward with 30% speed
		 * until the distance is more than 20, based on the distance it takes
		 * the next decision
		 */
		else if(20 > (u16)Sensor_Reading){
			DC_MOTOR_Turn_On(&M1, MOTOR_MOVE_BACKWARD);
			DC_MOTOR_Turn_On(&M2, MOTOR_MOVE_BACKWARD);
			DC_MOTOR_Turn_On(&M3, MOTOR_MOVE_BACKWARD);
			DC_MOTOR_Turn_On(&M4, MOTOR_MOVE_BACKWARD);
			Change_Motor_Speed(MOTOR_SPEED_30_B);
			while(20 > (u16)Sensor_Reading){
				Read_Print_Sensor();
			}
		}
		else{ /* Do Nothing */ }
	}
}

/* This function prints the defaults parameters on the LCD */
void Print_LCD_Default(){
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"Speed:", LCD_SPEED_ROW, LCD_SPEED_TEXT_COL);
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"Dir:", LCD_DIR_ROW, LCD_DIR_TEXT_COL);
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"Dist.:", LCD_DISTANCE_ROW, LCD_DISTANCE_TEXT_COL);
}

/* This function reads the ultrasonic sensor reading and display it on the LCD */
void Read_Print_Sensor(){
	HCSR04_vGet_Reading(&Sensor_Reading);
	dtostrf(Sensor_Reading, 2, 2, (char*)Sensor_Reading_String);
	LCD_4bit_vSendString_pos(&myLCD, (u8*)"        ", LCD_DISTANCE_ROW, LCD_DISTANCE_VALUE_COL);
	LCD_4bit_vSendString_pos(&myLCD, Sensor_Reading_String, LCD_DISTANCE_ROW, LCD_DISTANCE_VALUE_COL);
	LCD_4bit_vSendString(&myLCD, (u8*)"cm");
}

/* ISR for Timer0 over flow */
void Timer0_ISR(void){
	Timer0_Counter++;
	if(Timer0_Compare_Value == Timer0_Counter){
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, LOW);
	}
	else if(Timer0_Max_Counts == Timer0_Counter){
		Timer0_Counter = 0;
		DIO_vSetPinValue(MOTOR_EN_PWM_PORT, MOTOR_EN_PWM_PIN, HIGH);
	}
}

/* ISR for Timer2 over flow */
void Timer2_ISR(void){
	Timer2_Counter++;
	if(Timer2_Max_Counts == Timer2_Counter){
		Timer2_Flag++;
		Timer2_Counter = 0;
		TMR_vSetTCNTValue(&myTimer2, Timer2_Preload_Value);
	}
}
