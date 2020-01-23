/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC18F47Q10
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define TRIP1pt9 0b0000     // trip point voltage = 1.9V
#define TRIP2pt1 0b0001     // trip point voltage = 2.1V
#define TRIP2pt25 0b0010    // trip point voltage = 2.25V
#define TRIP2pt5 0b0011     // trip point voltage = 2.5V
#define TRIP2pt6 0b0100     // trip point voltage = 2.6V
#define TRIP2pt75 0b0101    // trip point voltage = 2.75V
#define TRIP2pt9 0b0110     // trip point voltage = 2.9V
#define TRIP3pt15 0b0111    // trip point voltage = 3.15V
#define TRIP3pt35 0b1000    // trip point voltage = 3.35V
#define TRIP3pt6 0b1001     // trip point voltage = 3.6V
#define TRIP3pt75 0b1010    // trip point voltage = 3.75V
#define TRIP4pt0 0b1011     // trip point voltage = 4.0V
#define TRIP4pt2 0b1100     // trip point voltage = 4.2V
#define TRIP4pt35 0b1101    // trip point voltage = 4.35V
#define TRIP4pt65 0b1110    // trip point voltage = 4.65V

#define WAIT4LED 1000
#define LED_OFF() LED_SetHigh() //LED will be turned off when the port pin is set high
#define LED_ON() LED_SetLow() //LED will be turned On when the port pin is set low

volatile uint8_t hlvdIntFlag=0;// Set in HLVD ISR when the HLVD interrupt has occurred
static uint16_t wait4ledCnt= WAIT4LED;// used to turn off the indication LED after some delay

static void SetUpLowVoltageDetect(uint8_t setPoint);
static void SetUpHighVoltageDetect(uint8_t setPoint);

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

    printf("\rDecrease the Supply voltage.\n");
    printf("\rTrip point is 3.15V to detect if the supply voltage is less than set point.\n\n");
    while (1)
    {
        // Add your application code

        if (hlvdIntFlag)// check if HLVD interrupt has occurred
        {
            hlvdIntFlag=0;
            LED_ON();// turn on the LED for indicating HLVD has detected either low voltage or high voltage event as configured
            wait4ledCnt= WAIT4LED;

            if(HLVD_OutputStatusGet())
            {
                //HLVD output status bit is set so the supply voltage is below the trip point
                printf("\rSupply voltage has decreased below 3.15V set point.\n\n");
                SetUpHighVoltageDetect(TRIP4pt35);// set up the high voltage detect with trip point voltage of 4.35V
            }
            else
            {
                //HLVD output status bit is cleared so the supply voltage is above the trip point
                printf("\rSupply voltage has increased above 4.35V set point.\n\n");
                SetUpLowVoltageDetect(TRIP3pt15);// set up the low voltage detect with trip point voltage of 3.15V
            }        
        }
        else
        {
            wait4ledCnt--;
            if(!wait4ledCnt)
            {
                LED_OFF();// turn off the indication LED 
                wait4ledCnt=WAIT4LED;
            }  
            
        }
    }
}
/**
 * @Param
    HLVD trip point
 * @Returns
    None
 * @Description
    This function is used to configure HLVD for detecting the low voltage event.
    HLVD will generate an interrupt once supply voltage falls below the set trip point voltage.
 * @Example
    SetUpLowVoltageDetect(tripPoint);
 */
static void SetUpLowVoltageDetect(uint8_t setPoint)
{
    HLVD_TripPointSetup(1,0, setPoint);
    printf("\rDecrease the Supply voltage.\n");
    printf("\rNew trip point is 3.15V to detect if the supply voltage is less than set point.\n\n");
}

/**
 * @Param
    HLVD trip point
 * @Returns
    None
 * @Description
    This function is used to configure HLVD for detecting the high voltage event.
    HLVD will generate an interrupt once supply voltage goes above the set trip point voltage.
 * @Example
    SetUpHighVoltageDetect(tripPoint);
 */
static void SetUpHighVoltageDetect(uint8_t setPoint)
{
    HLVD_TripPointSetup(0,1, setPoint);
    printf("\rIncrease the Supply voltage.\n");
    printf("\rNew trip point is 4.35V to detect if the supply voltage is greater than set point.\n\n");
}
/**
 End of File
*/