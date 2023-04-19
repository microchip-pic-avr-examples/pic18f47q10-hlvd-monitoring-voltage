 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
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

int main(void)
{
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
    printf("\r\t ** Monitoring supply voltage using HLVD **\r\n\n\n");
    printf("Trip point is 3.15 V.\r\n");
    printf("Decrease the supply voltage to detect if the supply voltage is less than the trip point.\r\n\n\n\n");
    
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
                printf("Supply voltage has decreased below 3.15 V.\r\n\n");
                // set up the high voltage detect with trip point voltage of 4.35V
                HLVD_TripPointSetup(CLEAR_NEGATIVE_TRIP, SET_POSITIVE_TRIP, HLVD_TRIP_POINT_4p20V);
                printf("New trip point is 4.35 V.\r\n");
                printf("Increase the supply voltage to detect if the supply voltage is greater than the trip point.\r\n\n\n\n");
            }
            else
            {                
                //HLVD output status bit is clear so the supply voltage is above the trip point
                printf("Supply voltage has increased above 4.35 V.\r\n\n");
                // set up the low voltage detect with trip point voltage of 3.15V
                HLVD_TripPointSetup(SET_NEGATIVE_TRIP, CLEAR_POSITIVE_TRIP, HLVD_TRIP_POINT_3p00V);
                printf("New trip point is 3.15 V.\r\n");
                printf("Decrease the supply voltage to detect if the supply voltage is less than the trip point.\r\n\n\n\n");
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