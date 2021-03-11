/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
#include "mcc_generated_files/system/system.h"

#define SET (1)
#define CLEAR (0)
#define SET_NEGATIVE_TRIP (1)
#define CLEAR_NEGATIVE_TRIP (0)
#define SET_POSITIVE_TRIP (1)
#define CLEAR_POSITIVE_TRIP (0)
#define LED_OFF() LED_SetHigh() //LED will be turned off when the port pin is set high
#define LED_ON() LED_SetLow() //LED will be turned On when the port pin is set low
#define WAIT4LED (1000) // used to turn off the indication LED after some delay

static uint16_t wait4ledCnt = WAIT4LED;// used to turn off the indication LED after some delay
volatile uint8_t hlvdIntFlag = CLEAR ;// Set in HLVD ISR when the HLVD interrupt has occurred

static void HLVD_UserCallback(void);

/*
                         Main application
 */
void main(void)
{
    
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //user call back function for HLVD interrupt
    HLVD_CallbackRegister(HLVD_UserCallback);
    
    //print initial message
    printf("\rMonitoring supply voltage using HLVD.\n");
    printf("\rDecrease the Supply voltage.\n");
    printf("\rTrip point is 3.15V to detect if the supply voltage is less than set point.\n\n");
    while(1)
    {

        if (hlvdIntFlag == SET )// check if HLVD interrupt has occurred
        {
            hlvdIntFlag = CLEAR;
            LED_ON();// turn on the LED for indicating HLVD has detected either low voltage or high voltage event as configured
            wait4ledCnt = WAIT4LED;

            //check HLVD output status bit to determine if the supply voltage is below or above the trip point
            if(HLVD_OutputStatusGet()== SET)
            {                
                //HLVD output status bit is set so the supply voltage is below the trip point
                printf("\rSupply voltage has decreased below 3.15V set point.\n\n");
                // set up the high voltage detect with trip point voltage of 4.35V
                HLVD_TripPointSetup(CLEAR_NEGATIVE_TRIP, SET_POSITIVE_TRIP, HLVD_TRIP_POINT_4p20V);
                printf("\rIncrease the Supply voltage.\n");
                printf("\rNew trip point is 4.35V to detect if the supply voltage is greater than set point.\n\n");
            }
            else
            {                
                //HLVD output status bit is clear so the supply voltage is above the trip point
                printf("\rSupply voltage has increased above 4.35V set point.\n\n");
                // set up the low voltage detect with trip point voltage of 3.15V
                HLVD_TripPointSetup(SET_NEGATIVE_TRIP, CLEAR_POSITIVE_TRIP, HLVD_TRIP_POINT_3p00V);
                printf("\rDecrease the Supply voltage.\n");
                printf("\rNew trip point is 3.15V to detect if the supply voltage is less than set point.\n\n");
            }        
        }
        else
        {
            wait4ledCnt--;// decrement the wait count to add delay before turning off the Indication LED
            if(!wait4ledCnt)
            {
                LED_OFF();// turn off the indication LED 
                wait4ledCnt = WAIT4LED;
            }             
        }
    } 
}
/**
  @Description
    This is a custom ISR handler for HLVD ISR.

  @Param
    None

  @Returns
    None

  @Example
    <code>
    HLVD_CallbackRegister(HLVD_UserCallback);
    </code>
*/
static void HLVD_UserCallback(void)
{
    hlvdIntFlag = SET;
}

