/*
 * DCMOTOR_program.c
 *
 *  Created on: Aug 11, 2023
 *      Author: Islam Shaaban
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MACROS.h"
#define F_CPU 8000000UL
#include <util/delay.h>
/*MCAL*/
#include "../../MCAL/DIO/DIO_interface.h"

#include "DCMOTOR_interface.h"

void DCMOTOR_voidInit(){
	DIO_voidSetupPinDirection(DCMOTOR_PORT,DCMOTOR_HB_PIN0,DIO_OUTPUT );
	DIO_voidSetupPinDirection(DCMOTOR_PORT,DCMOTOR_HB_PIN1,DIO_OUTPUT );
}


void DCMOTOR_voidCWRotate(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_HIGH );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_LOW );

}
void DCMOTOR_voidCCWRotate(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_LOW );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_HIGH );

}
void DCMOTOR_voidStop(){
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN0,DIO_LOW );
	DIO_voidSetPinValue(DIO_PORTD,DCMOTOR_HB_PIN1,DIO_LOW );

}





