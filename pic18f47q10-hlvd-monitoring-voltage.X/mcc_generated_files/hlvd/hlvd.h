/**
  HLVD Generated Driver API Header File
 
  @Company
    Microchip Technology Inc.
 
  @File Name
    hlvd.h
 
  @Summary
    This is the generated header file for the HLVD driver
 
  @Description
    This header file provides APIs for driver for HLVD.
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

#ifndef HLVD_H
#define HLVD_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif

/**
  Section: Enum Declarations
*/

/** HLVD Trip points
 
 @Summary 
   This defines trip point values.
 
 @Description
   This defines trip point values.

 */

typedef enum
{
    HLVD_TRIP_POINT_1p81V =  0, //0x0
    HLVD_TRIP_POINT_2p00V =  1, //0x1
    HLVD_TRIP_POINT_2p20V =  2, //0x2
    HLVD_TRIP_POINT_2p40V =  3, //0x3
    HLVD_TRIP_POINT_2p50V =  4, //0x4
    HLVD_TRIP_POINT_2p70V =  5, //0x5
    HLVD_TRIP_POINT_2p80V =  6, //0x6
    HLVD_TRIP_POINT_3p00V =  7, //0x7
    HLVD_TRIP_POINT_3p30V =  8, //0x8
    HLVD_TRIP_POINT_3p50V =  9, //0x9
    HLVD_TRIP_POINT_3p60V =  10, //0xa
    HLVD_TRIP_POINT_3p80V =  11, //0xb
    HLVD_TRIP_POINT_4p00V =  12, //0xc
    HLVD_TRIP_POINT_4p20V =  13, //0xd
    HLVD_TRIP_POINT_4p50V =  14 //0xe

}HLVD_TRIP_POINTS;

/**
  Section: HLVD Module APIs
*/

/**
  @Summary
    Initializes the HLVD

  @Description
    This routine initializes the Initializes the HLVD.
    This routine must be called before any other HLVD routine is called.
    This routine should only be called once during system initialization.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    bool gAppShutdown = false;
    {
      //initialize the module
      HLVD_Initialize();
      //check if reference voltage is stable 
      while(!HLVD_IsBandGapVoltageStable());
      while(1)
      {
         //Polling
          HLVD_Tasks();
      }
    }
    void HLVD_TripDetectionCallback(void)
    {
       //process application code here
       gAppShutdown = true; 
    }   
    </code> 
*/
void HLVD_Initialize(void);

/**
  @Summary
    This function enables the HLVD peripheral.

  @Description
    This function enables the HLVD peripheral.

  @Preconditions
    HLVD_Initialize Is_HLVD_Ref_Voltage_Stable
   function should be called first.

  @Param
    None

  @Returns
    None.

  @Example
  <code>
      HLVD_Disable();
      //Set the trip points and voltage direction
      HLVD_TripPointSetup(EXCEED_TRIP_POINT,
        HLVD_TRIP_POINT_1p85v);
      //Enable the module
       HLVD_Enable();
      //check if reference voltage is stable 
      while(!HLVD_IsBandGapVoltageStable());
      while(1)
      {
         
      }
    void HLVD_TripDetectionCallback(void)
    {
       //process application code here      
    }
   </code>     
 */
void HLVD_Enable(void);

/**
  @Summary
    This function disables the HLVD peripheral.

  @Description
    This function disables the HLVD peripheral.

  @Preconditions
    HLVD_Initialize and
    HLVD_IsBandGapVoltageStable
    function should be called first.

  @Param
    None

  @Returns
    None.

  @Example
   Refer the HLVD_Enable code example
*/
void HLVD_Disable(void);

/**
  @Summary
    This function returns the status of band gap voltage.

  @Description
    This function returns the status of band gap voltage.

  @Preconditions
    HLVD_Initialize function should be called first

  @Param
    None

  @Returns
    bool - true - Band gap voltage is stable
           false - Band gap voltage is unstable

  @Example
  Refer the HLVD_Enable code example
*/
bool HLVD_IsBandGapVoltageStable(void);

/**
  @Summary
    This function sets the Positive, Negative voltage trip and trip value

  @Description
    This function sets the Positive, Negative voltage trip and trip value

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
   Refer the HLVD_Enable code example
*/
void HLVD_TripPointSetup(bool Negative_Trip, bool Positive_Trip, HLVD_TRIP_POINTS trip_points);

/**
  @Summary
    Returns output status as High or Low voltage 

  @Description
    This routine returns output status of the HLVD module.

  @Param
    None.

  @Returns
    Output status
 
  @Example 
    <code>
    bool outputStatus;
    outputStatus = HLVD_OutputStatusGet();
    </code>
*/
bool HLVD_OutputStatusGet(void);

/**
  @Summary
    Sets HLVD Callback Handler

  @Description
    This routine is used to set the callback handler for the HLVD interrupt flag.

  @Returns
    None

  @Param
    Callback Function to be called
*/
void HLVD_CallbackRegister(void (* CallbackHandler)(void));

/**
  @Summary
    Implements ISR

  @Description
    This routine is used to implement the ISR for the interrupt-driven
    implementations.

  @Returns
    None

  @Param
    None
*/
void HLVD_ISR(void);
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif	//HLVD_H
/**
 End of File
*/