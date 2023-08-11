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
#define F_CPU		8000000UL


#define DEFAULT_PW 1234

int main(){


	LED_t RedLed ={DIO_PORTD, DIO_PIN7, LED_ACTIVE_HIGH};
	LED_t GreenLed = {DIO_PORTD, DIO_PIN6, LED_ACTIVE_HIGH};
	LED_voidInit(&GreenLed);
	LED_voidInit(&RedLed);
	CLCD_voidInit();
	KPAD_voidInit();
	// H-bridge
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN0,DIO_OUTPUT ); // T1
	DIO_voidSetupPinDirection(DIO_PORTD,DIO_PIN1,DIO_OUTPUT ); // T2
	DCMOTOR_voidInit();
	CLCD_voidSetPosition(1,2);

	u32 Local_u8Password = 0;

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
	CLCD_voidSetPosition(2,2);
	while(1){

		u8 Local_u8Pressed = KPAD_u8GetPressed();
		//CLCD_voidSendData(Local_u8Pressed);
		if (Local_u8Pressed != 0xff)
		{
			// Writing password till pressing ON/C.
			if(Local_u8Pressed != 'C'){
				CLCD_voidSendData('*');
				Local_u8Password = (Local_u8Password * 10) + (Local_u8Pressed - 48);
			}
			// If correct PW, System is ON
			else{
				if(Local_u8Password == DEFAULT_PW){
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					LED_voidOFF(&RedLed);//LED RED OFF
					LED_voidON(&GreenLed); // LED green ON
					back:

					CLCD_voidSetPosition(1,1);
					CLCD_voidSendString((u8 *)"Welcometo Motor");
					CLCD_voidSetPosition(2,1);
					CLCD_voidSendString((u8 *)" Dash Board");
					_delay_ms(2000);
					CLCD_voidCLearDisplay();

					CLCD_voidSendString((u8 *)" 1-DC Motor.");
					CLCD_voidSetPosition(2,1);
					CLCD_voidSendString((u8 *)" 2-Exit.");
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
					if (Local_u8Pressed != 0xff){
						CLCD_voidCLearDisplay();
						if(Local_u8Pressed=='1'){
							Dashboard:
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
							if (Local_u8Pressed != 0xff){
								CLCD_voidCLearDisplay();
								if(Local_u8Pressed=='1'){
									DCMOTOR_voidCWRotate();
									_delay_ms(2000);
									goto Dashboard;

								}
								else if(Local_u8Pressed=='2'){
									DCMOTOR_voidCCWRotate();
									_delay_ms(2000);
									goto Dashboard;

								}
								else if(Local_u8Pressed=='3'){
									//back
									goto back;
								}
							}
							else{

							}
						}
						else if(Local_u8Pressed=='2'){
							//exit
							DCMOTOR_voidStop();
							LED_voidOFF(&GreenLed); // LED Green OFF

							CLCD_voidSendString((u8 *)" Welcome to Sys");
							_delay_ms(1000);
							CLCD_voidCLearDisplay();
							CLCD_voidSendString((u8 *)" Enter your PW");
							_delay_ms(1000);
							CLCD_voidCLearDisplay();
							CLCD_voidSendString((u8 *)" Then Press ON");
							_delay_ms(1000);
							CLCD_voidCLearDisplay();
							CLCD_voidSendString((u8 *)" Password: ");
							CLCD_voidSetPosition(2,2);
						}
					}

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
					CLCD_voidSetPosition(2,2);

				}
			}

		}
		else{
			// Do no thing
		}


	}
	return 1;
}
