

# Obstacle Avoidance Car - ATMEGA32
#### A car that detects obstacles ahead of it and tries to avoid hitting them

[Obstacle Avoidance Car (ATmega32 Proteus Simulation) - YouTube](https://www.youtube.com/watch?v=qatJDsOZP04&list=PLC3Wwc_IeCN8d-kV1xPaiXWGpabYQGxY_&index=8)

![Arduino 4x4 car](https://botland.store/blog/wp-content/uploads/2022/07/robot-arduino-rc.jpg)

## Description:

 This project was done on Eclipse IDE using the gcc compiler and simulation is done on Proteus.



- After power on and initialization, the program asks the user for the direction of rotation, the default direction is right, and the user is given a 5 seconds window to choose between left or right direction by pressing the push button once to toggle the direction.

- After the 5 seconds window, the program waits 2 seconds, then the program starts to read the distance from the ultrasonic sensor, and based on the distance between the car and the nearest obstacle it takes decisions.
- If the distance is more than 70cm, the car moves forward at 30% speed, and after 5 seconds, it increases the speed to 50%
- If the distance is between 30cm and 70cm, the car will move forward at 30% speed
- If the distance is between 20cm and 30cm, the car rotates 90 degrees to left/right, based on the default direction chosen by user at the start of the application, if the distance is still between 20cm and 30cm, the car will keep rotating until it finds a passable route
- If the distance is lower than 20cm, the car moves backward at 30% speed until the distance is more than 20cm, then it takes a decision based on that distance.

 #### LCD Interface:
 ![LCD.png](https://github.com/Piistachyoo/Obstacle_Avoidance_Car/blob/main/LCD.png?raw=true)

 - **Speed**: Speed of the rotating motors (**0%** - **100%**)
 - **Dir**: Direction of the car (**F**orward - **B**ackward - **R**otating - **S**topped)
 - **Dist**: Distance measured by the ultrasonic sensor (**3cm** - **400cm**)

## Project Design:
### The project is based on Layered Architecture and operates on a Super Loop.

### Peripherals used:

 1. DIO: Used for controlling the motors, generating the TRIG signal for the ultrasonic sensor, and reading the push button state.
 2. Timer0: Used in normal mode to generate PWM signal using interrupts.
 3. Timer1: Used in normal mode to calculate time periods for the ICU
 4. ICU: Used for calculating the time for the ECHO pulse generated from the ultrasonic sensor
 5. Timer2: Used in normal mode to create delays for the system

### Files:
- #### Application Layer:
	1. Config_Interface: Provides an interface for direction selection
	2. Motor_Control: Provides interfaces for controlling all the DC Motors
 - #### Hardware Abstraction Layer:
	 1. DC_MOTOR: Driver used for controlling DC Motors 
	 2. HC-SR04 Ultrasonic Sensor: Driver used to control the HC-SR04
	 3. 16x2 LCD 4-bit data mode: Driver used to control the 16x2 LCD in 4-bit data mode
	 4. Push button: Driver used to control the push button
 - #### Hardware Abstraction Layer:
	 1. DIO: Driver used to control the GPIO pins
	 2. TMR: Driver used for controlling timers 0/1/2
	 3. GIE: Driver used to control the global interrupt enable for the MCU
- #### Service Layer:
	1. BIT_MATH: Contains bit-wise operations
	2. STD_TYPES: Contains all the data types used
## Project design:

![Project Design](https://github.com/Piistachyoo/Obstacle_Avoidance_Car/blob/main/design.png?raw=true)

  
