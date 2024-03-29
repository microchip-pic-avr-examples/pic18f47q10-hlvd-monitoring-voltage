/**
 * HLVD Generated Driver File.
 * 
 * @file hlvd.c
 * 
 * @ingroup  hlvd
 * 
 * @brief This file contains the API implementation for the HLVD driver.
 *
 * @version HLVD Driver Version 2.11.0
*/
/*
� [2023] Microchip Technology Inc. and its subsidiaries.

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

/**
  Section: Included Files
*/

#include "../hlvd.h"

static void (*HLVD_Callback)(void);
static void HLVD_DefaultCallback(void);

/**
  Section: HLVD Module APIs
*/

void HLVD_Initialize(void)
{
    // set the HLVD module to the options selected in the User Interface
    //HLVDL Min:3.00 Max:3.18; 
    HLVDCON1 = 0x7;
    //HLVDINTL enabled; HLVDINTH disabled; HLVDEN enabled; 
    HLVDCON0 = 0x81;
    
    HLVD_CallbackRegister(HLVD_DefaultCallback);
    PIR2bits.HLVDIF = 0;
    // Enable HLVD interrupt.
    PIE2bits.HLVDIE = 1;
}

bool HLVD_IsBandGapVoltageStable(void)
{

    //return band gap voltage status
    return (HLVDCON0bits.HLVDRDY);
}

void HLVD_Enable(void)
{
    // enable HLVD module

    HLVDCON0bits.HLVDEN = 1;
    PIR2bits.HLVDIF = 0;
    // Enable HLVD interrupt.
    PIE2bits.HLVDIE = 1;
}

void HLVD_Disable(void)
{
    
    // disable HLVD module
    HLVDCON0bits.HLVDEN = 0; 
    // clear interrupt flag
    PIR2bits.HLVDIF = 0;
    // Disable HLVD interrupt.
    PIE2bits.HLVDIE = 0;
}

void HLVD_TripPointSetup(bool Negative_Trip, bool Positive_Trip, HLVD_TRIP_POINTS trip_points)
{
   //set Negative trip
   HLVDCON0bits.HLVDINTL = Negative_Trip;
   //set Positive trip
   HLVDCON0bits.HLVDINTH = Positive_Trip;
   // Set trip points
   HLVDCON1 = trip_points;
}

bool HLVD_OutputStatusGet(void)
{
    //return HLVD voltage status
    return(HLVDCON0bits.HLVDOUT);
}

void HLVD_ISR(void)
{
    // Clear the HLVD interrupt flag
    PIR2bits.HLVDIF = 0;
    HLVD_Callback();

}

void HLVD_CallbackRegister(void (* CallbackHandler)(void))
{
    HLVD_Callback = CallbackHandler;
}

static void HLVD_DefaultCallback(void)
{
    //Add your interrupt code here or
    //Use HLVD_CallbackRegister() function to use Custom ISR
}

/**
 End of File
*/
