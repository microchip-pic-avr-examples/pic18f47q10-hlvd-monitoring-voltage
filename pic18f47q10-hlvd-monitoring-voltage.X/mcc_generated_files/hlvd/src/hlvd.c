/**
  HLVD Generated Driver File
 
  @Company
    Microchip Technology Inc.
 
  @File Name
    hlvd.c
 
  @Summary
    This is the generated driver implementation file for the HLVD driver
 
  @Description
    This source file provides APIs for driver for HLVD.
    Generation Information :
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.20
        MPLAB             :  MPLAB X v5.40
*/

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