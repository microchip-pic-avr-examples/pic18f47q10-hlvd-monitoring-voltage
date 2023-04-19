/**
 * HLVD Generated Driver API Header File.
 * 
 * @file hlvd.h
 * 
 * @defgroup  hlvd HLVD
 * 
 * @brief This file contains the API protoypes and related data structures for the HLVD driver.
 *
 * @version HLVD Driver Version 2.11.0
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

/**
 * @ingroup hlvd
 * @enum  HLVD_TRIP_POINTS
 * @brief Trip point values for the HLVD driver.
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
  Section: HLVD APIs
*/

/**
 * @ingroup hlvd
 * @brief Initializes the HLVD module. This is called only once before calling other HLVD APIs.
 * @param None.
 * @return None.
 */
void HLVD_Initialize(void);

/**
 * @ingroup hlvd
 * @brief Enables the HLVD.
 * @param None.
 * @return None.
 */
void HLVD_Enable(void);

/**
 * @ingroup hlvd
 * @brief Disables the HLVD.
 * @pre HLVD_Initialize() and HLVD_IsBandGapVoltageStable() are already called.
 * @param None.
 * @return None.
 */
void HLVD_Disable(void);

/**
 * @ingroup hlvd
 * @brief Returns the status of the band gap reference voltage.
 * @pre HLVD_Initialize() is already called.
 * @param None.
 * @retval True - Band gap voltage is stable.
 * @retval False - Band gap voltage is unstable.
 */
bool HLVD_IsBandGapVoltageStable(void);

/**
 * @ingroup hlvd
 * @brief Sets the positive, negative or both voltage trip interrupts and sets the trip point value.
 * @param Negative_Trip - Negative going (Low-Voltage) interrupt is enabled (1) or disabled (0).
 * @param Positive_Trip - Positive going (High-Voltage) interrupt is enabled (1) or disabled (0).
 * @param trip_points - Trip point value.
 * @return None.
 */
void HLVD_TripPointSetup(bool Negative_Trip, bool Positive_Trip, HLVD_TRIP_POINTS trip_points);

/**
 * @ingroup hlvd
 * @brief Returns the HLVD comparator output status.
 * @param None.
 * @retval True - Voltage is lower than the selected trip point.
 * @retval False - Voltage is higher than the selected trip point.
 */
bool HLVD_OutputStatusGet(void);

/**
 * @ingroup hlvd
 * @brief Sets the callback handler for the HLVD interrupt events.
 * @param (*CallbackHandler)(void) - Function pointer to the HLVD interrupt handler.
 * @return None.
 */
void HLVD_CallbackRegister(void(*CallbackHandler)(void));

/**
 * @ingroup hlvd
 * @brief Implements the Interrupt Service Routine (ISR) for the HLVD interrupt.
 * @param None.
 * @return None.
 */
void HLVD_ISR(void);
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif	//HLVD_H
/**
 End of File
*/
