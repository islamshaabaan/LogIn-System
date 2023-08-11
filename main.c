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
#define F_CPU		8000000UL


#define DEFAULT_PW 1234

int main(){


	LED_t RedLed ={DIO_PORTD, DIO_PIN6, LED_ACTIVE_HIGH};
	LED_t GreenLed = {DIO_PORTD, DIO_PIN2, LED_ACTIVE_HIGH};
	LED_voidInit(&GreenLed);
	LED_voidInit(&RedLed);
	CLCD_voidInit();
	KPAD_voidInit();
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
			if(Local_u8Pressed != 'C'){
				CLCD_voidSendData('*');
				//CLCD_voidSendData(Local_u8Pressed);
				Local_u8Password = (Local_u8Password * 10) + (Local_u8Pressed - 48);
				//CLCD_voidSendu32Number(Local_u8Password);
				//_delay_ms(1000);
				//CLCD_voidCLearDisplay();
			}
			else{
				if(Local_u8Password == DEFAULT_PW){
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();

					CLCD_voidSendString((u8 *)" Welcome Islam");
					LED_voidOFF(&RedLed);//LED RED OFF
					LED_voidON(&GreenLed); // LED green ON

					_delay_ms(2000);
					CLCD_voidCLearDisplay();

					LED_voidOFF(&GreenLed); // LED green OFF
					CLCD_voidSendString((u8 *)" Password: ");
					CLCD_voidSetPosition(2,2);

				}
				else{
					Local_u8Password=0; // Reset PW
					CLCD_voidCLearDisplay();
					CLCD_voidSendString((u8 *)" Wrong PW");
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
