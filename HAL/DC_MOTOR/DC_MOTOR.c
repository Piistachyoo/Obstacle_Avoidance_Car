/*************************************************************************/
/* Author        : Omar Yamany                                    		 */
/* Project		 : Obstacle_Avoidance_Car								 */
/* File          : DC_MOTOR.c                                  	    	 */
/* Date          : May 12, 2023	                                         */
/* Version       : V1                                                    */
/* GitHub        : https://github.com/Piistachyoo             		     */
/*************************************************************************/

#include "DC_MOTOR.h"

void DC_MOTOR_vInit(const dc_motor_t *_MOTOR){
	if(NULL != _MOTOR){
		DIO_vPinInit(_MOTOR->motor_port, _MOTOR->motor_en_pin, OUTPUT, LOW);
		DIO_vPinInit(_MOTOR->motor_port, _MOTOR->motor_pin1, OUTPUT, LOW);
		DIO_vPinInit(_MOTOR->motor_port, _MOTOR->motor_pin2, OUTPUT, LOW);
	}
}

void DC_MOTOR_Turn_Right(const dc_motor_t *_MOTOR){
	if(NULL != _MOTOR){
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin1, HIGH);
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin2, LOW);
	}
}

void DC_MOTOR_Turn_Left(const dc_motor_t *_MOTOR){
	if(NULL != _MOTOR){
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin1, LOW);
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin2, HIGH);
	}
}

void DC_MOTOR_Turn_Off(const dc_motor_t *_MOTOR){
	if(NULL != _MOTOR){
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_en_pin, LOW);
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin1, LOW);
		DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_pin2, LOW);
	}
}

void DC_MOTOR_Turn_On(const dc_motor_t *_MOTOR, motor_direction_t _direction){
	if(motor_direction_right == _direction){
		DC_MOTOR_Turn_Right(_MOTOR);
	}
	else if(motor_direction_left == _direction){
		DC_MOTOR_Turn_Left(_MOTOR);
	}
	else{ /* Do Nothing */ }
	DIO_vSetPinValue(_MOTOR->motor_port, _MOTOR->motor_en_pin, HIGH);
}
