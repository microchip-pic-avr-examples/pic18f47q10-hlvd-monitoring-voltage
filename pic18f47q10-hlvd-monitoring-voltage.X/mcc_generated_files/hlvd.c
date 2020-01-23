/**
  HLVD Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
   hlvd.c

  @Summary
    This is the generated driver implementation file for the HLVD driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This source file provides implementations for driver APIs for HLVD.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.78
        Device            :  PIC18F47Q10
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB             :  MPLAB X 5.20
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "hlvd.h"
extern uint8_t hlvdIntFlag;

/**
  Section: HLVD Module APIs
*/

void HLVD_Initialize(void)
{
    // set the HLVD_Initialize module to the options selected in the User Interface
     // SEL Min:3.00 Max:3.18; 
    HLVDCON1 = 0x07;
     // HLVDINTL enabled; HLVDINTH disabled; HLVDEN enabled; 
    HLVDCON0 = 0x81;
    
    PIR2bits.HLVDIF = 0;
    // Enable HLVD interrupt.
    PIE2bits.HLVDIE = 1;
}


bool HLVD_IsBandGapVoltageStable(void)
{    
      
    //return band gap voltage status
    return(HLVDCON0bits.HLVDRDY);
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
     //clear interrupt flag
    PIR2bits.HLVDIF = 0;
     // Disable HLVD interrupt.
    PIE2bits.HLVDIE = 0;
}

void HLVD_TripPointSetup(bool Negative_Trip,bool Positive_Trip,
        HLVD_TRIP_POINTS trip_points)
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
    /* TODO : Add interrupt handling code */
    PIR2bits.HLVDIF = 0;
    
    hlvdIntFlag=1;  
}

/**
 End of File
*/
