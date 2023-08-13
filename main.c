/*
 * main.c
 *
 *  Created on: Aug 9, 2023
 *      Author: Islam Shaaban
 */


#include <util/delay.h>
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MACROS.h"
#include "MCAL/DIO/DIO_interface.h"
#include "HAL/LED/LED_interface.h"
#include "HAL/SSD/SSD_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "HAL/KPAD/KPAD_interface.h"
#include "HAL/DC_MOTOR/DCMOTOR_interface.h"
#include "HAL/STEPPER_MOTOR/STEPPER_interface.h"
#define F_CPU		8000000UL


#define DEFAULT_PW 1234

int main(){

	// Initialization
	LED_t RedLed ={DIO_PORTD, DIO_PIN7, LED_ACTIVE_HIGH};
	LED_t GreenLed = {DIO_PORTD, DIO_PIN6, LED_ACTIVE_HIGH};
	LED_voidInit(&GreenLed);
	LED_voidInit(&RedLed);
	CLCD_voidInit();
	KPAD_voidInit();

	// H-bridge Setup
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT ); // T1
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT ); // T2

	DCMOTOR_voidInit();

	CLCD_voidSetPosition(1,1);

	u32 Local_u8Password = 0;
	u8 Logged=0;


	CLCD_voidSendString((u8 *)"Welcome to Sys");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Enter your PW");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Then Press ON");
	_delay_ms(1000);
	CLCD_voidCLearDisplay();
	CLCD_voidSendString((u8 *)" Password: ");
	u8 Local_u8Pressed = 0xff;
	while(1){


		//while still not logged, try to get the password
		while(Logged== 0){
			Local_u8Pressed = KPAD_u8GetPressed();
			CLCD_voidSetPosition(2,2);

			while(Local_u8Pressed != 'C' && Local_u8Pressed != 0xff){
				CLCD_voidSendData('*');
				Local_u8Password = (Local_u8Password * 10) + (Local_u8Pressed - 48);
				Local_u8Pressed = KPAD_u8GetPressed();
				// while the button is not pressed,
				// wait until get the pressed button.
				while(Local_u8Pressed == 0xff){
					Local_u8Pressed = KPAD_u8GetPressed();
				}
			}
			if(Local_u8Pressed=='C'){
				if(Local_u8Password == DEFAULT_PW)
				{
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					LED_voidOFF(&RedLed);//LED RED OFF
					LED_voidON(&GreenLed); // LED green ON
					Logged =1;
				}
				else{
					// if PW is wrong.
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					CLCD_voidSendString((u8 *)" Wronge PW");
					LED_voidOFF(&GreenLed); // LED Green OFF
					LED_voidON(&RedLed);//LED RED ON
					_delay_ms(2000);
					CLCD_voidCLearDisplay();
					LED_voidOFF(&RedLed);//LED RED OFF
					CLCD_voidSendString((u8 *)" Password: ");
				}
			}
		}

		do{
			CLCD_voidSetPosition(1,1);
			CLCD_voidSendString((u8 *)"Welcometo Motor");
			CLCD_voidSetPosition(2,1);
			CLCD_voidSendString((u8 *)" Dash Board");
			_delay_ms(2000);
			CLCD_voidCLearDisplay();
			CLCD_voidSetPosition(1,1);

			CLCD_voidSendString((u8 *)"1-DC");
			CLCD_voidSetPosition(1,5);
			CLCD_voidSendString((u8 *)" 2-STEPPER.");
			CLCD_voidSetPosition(2,1);
			CLCD_voidSendString((u8 *)" 0-Exit System.");
			_delay_ms(2000);
			CLCD_voidCLearDisplay();
			CLCD_voidSetPosition(1,1);
			CLCD_voidSendString((u8 *)"Option Number:");


			Local_u8Pressed = KPAD_u8GetPressed();
			// while the button is not pressed,
			// wait until get the pressed button.
			while(Local_u8Pressed == 0xff){
				Local_u8Pressed = KPAD_u8GetPressed();
			}
			CLCD_voidSendData(Local_u8Pressed);
			_delay_ms(1000);

			CLCD_voidCLearDisplay();
			switch(Local_u8Pressed){
			case '1': // DC Motor
				do {
					CLCD_voidSendString((u8 *)" 1-CW.");
					CLCD_voidSetPosition(1,7);
					CLCD_voidSendString((u8 *)" 2-CCW.");
					CLCD_voidSetPosition(2,1);
					CLCD_voidSendString((u8 *)" 3-Back.");
					_delay_ms(2000);
					CLCD_voidCLearDisplay();
					CLCD_voidSetPosition(1,1);
					CLCD_voidSendString((u8 *)"Option Number:");
					Local_u8Pressed = KPAD_u8GetPressed();
					while(Local_u8Pressed == 0xff){
						Local_u8Pressed = KPAD_u8GetPressed();
					}
					CLCD_voidSendData(Local_u8Pressed);
					_delay_ms(1000);
					CLCD_voidCLearDisplay();

					switch(Local_u8Pressed){
					case '1':
						DCMOTOR_voidCWRotate();
						_delay_ms(2000);
						break;
					case '2':
						DCMOTOR_voidCCWRotate();
						_delay_ms(2000);
						break;
					case '3':
						CLCD_voidCLearDisplay();
						break;
					default:
						break;

					}

				}while(Local_u8Pressed != '3');

				break;
			case '2':// Stepper Motor
				do {
					CLCD_voidSendString((u8 *)" 1-CW.");
					CLCD_voidSetPosition(1,7);
					CLCD_voidSendString((u8 *)" 2-CCW.");
					CLCD_voidSetPosition(2,1);
					CLCD_voidSendString((u8 *)" 3-Back.");
					_delay_ms(2000);
					CLCD_voidCLearDisplay();
					CLCD_voidSetPosition(1,1);
					CLCD_voidSendString((u8 *)"Option Number:");
					Local_u8Pressed = KPAD_u8GetPressed();
					while(Local_u8Pressed == 0xff){
						Local_u8Pressed = KPAD_u8GetPressed();
					}
					CLCD_voidSendData(Local_u8Pressed);
					_delay_ms(1000);
					CLCD_voidCLearDisplay();

					switch(Local_u8Pressed){
					case '1':
						STEPPER_voidRotate(STEPPER_CLOCK_WISE);
						_delay_ms(2000);
						break;
					case '2':
						STEPPER_voidRotate(STEPPER_COUNTER_CLOCK_WISE);
						_delay_ms(2000);
						break;
					case '3':
						CLCD_voidCLearDisplay();
						break;
					default:
						break;

					}

				}while(Local_u8Pressed != '3');

				break;
			case '0':
				CLCD_voidCLearDisplay();
				CLCD_voidSendString((u8 *)" Password: ");
				Logged = 0;
				DCMOTOR_voidStop();
				STEPPER_voidOff();
				LED_voidOFF(&GreenLed); // LED Green OFF

				break;
			default:
				break;
			}

		}while(Local_u8Pressed !='0');

	}
	return 1;
}
