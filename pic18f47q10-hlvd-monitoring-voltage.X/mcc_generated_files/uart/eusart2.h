/**
  EUSART2 Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    eusart2.h

  @Summary
    This is the generated header file for the EUSART2 driver using CCL

  @Description
    This header file provides APIs for driver for EUSART2.
    Generation Information :
        Product Revision  :  CCL - 1.8.2
        Device            :  PIC18F47Q43
        Driver Version    :  2.1.0
    The generated drivers are tested against the following:
        Compiler          :  XC8 v2.2
        MPLAB 	          :  Standalone
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

#ifndef EUSART2_H
#define EUSART2_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "uart_interface.h"
#include <stdio.h>

/**
  Section: Macro Declarations
*/

#define EUSART2_DataReady  (EUSART2_IsRxReady())

/**
  Section: Data Type Definitions
*/

typedef union {
    struct {
        unsigned perr : 1;
        unsigned ferr : 1;
        unsigned oerr : 1;
        unsigned reserved : 5;
    };
    uint8_t status;
}eusart2_status_t;

//*********************************************************************************************************
/**
 * @deprecated
 * Deprecated APIs start
 */
//*********************************************************************************************************

bool __attribute__(( deprecated )) EUSART2_is_tx_ready(void);
bool __attribute__(( deprecated )) EUSART2_is_rx_ready(void);
bool __attribute__(( deprecated )) EUSART2_is_tx_done(void);
eusart2_status_t EUSART2_get_last_status(void);

/*************************************************************************************************************
 * Deprecated APIs end
 *************************************************************************************************************/

extern const struct UART_INTERFACE EUSART2_Interface;

/**
  Section: EUSART2 APIs
*/

/**
  @Summary
    Initialization routine that takes inputs from the EUSART2 GUI.

  @Description
    This routine initializes the EUSART2 driver.
    This routine must be called before any other EUSART2 routine is called.

  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Comment
    
*/
void EUSART2_Initialize(void);

/**
  @Summary
    Checks if the EUSART2 transmitter is ready to transmit data

  @Description
    This routine checks if EUSART2 transmitter is ready 
    to accept and transmit data byte

  @Preconditions
    EUSART2_Initialize() function should have been called
    before calling this function.
    EUSART2 transmitter should be enabled before calling 
    this function

  @Param
    None

  @Returns
    Status of EUSART2 transmitter
    TRUE: EUSART2 transmitter is ready
    FALSE: EUSART2 transmitter is not ready
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART2_IsRxReady())
            {
                rxData = UART1_Read();
                if(EUSART2_IsTxReady())
                {
                    EUSART2Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART2_IsTxReady(void);

/**
  @Summary
    Checks if the EUSART2 receiver ready for reading

  @Description
    This routine checks if EUSART2 receiver has received data 
    and ready to be read

  @Preconditions
    EUSART2_Initialize() function should be called
    before calling this function
    EUSART2 receiver should be enabled before calling this 
    function

  @Param
    None

  @Returns
    Status of EUSART2 receiver
    TRUE: EUSART2 receiver is ready for reading
    FALSE: EUSART2 receiver is not ready for reading
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART2_IsRxReady())
            {
                rxData = UART1_Read();
                if(EUSART2_IsTxReady())
                {
                    EUSART2_Write(rxData);
                }
            }
        }
    }
    </code>
*/
bool EUSART2_IsRxReady(void);

/**
  @Summary
    Checks if EUSART2 data is transmitted

  @Description
    This function return the status of transmit shift register

  @Preconditions
    EUSART2_Initialize() function should be called
    before calling this function
    EUSART2 transmitter should be enabled and EUSART2_Write
    should be called before calling this function

  @Param
    None

  @Returns
    Status of EUSART2 receiver
    TRUE: Data completely shifted out if the USART shift register
    FALSE: Data is not completely shifted out of the shift register
    
  @Example
    <code>
    void main(void)
    {
        volatile uint8_t rxData;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        while(1)
        {
            if(EUSART2_IsTxReady())
            {
				LED_0_SetHigh();
                EUSART2Write(rxData);
            }
			if(EUSART2_IsTxDone()
            {
                LED_0_SetLow();
            }
        }
    }
    </code>
*/
bool EUSART2_IsTxDone(void);

/**
  @Summary
    Gets the error status of the last read byte.

  @Description
    This routine gets the error status of the last read byte.

  @Preconditions
    EUSART2_Initialize() function should have been called
    before calling this function. The returned value is only
    updated after a read is called.

  @Param
    None

  @Returns
    the status of the last read byte

  @Example
	<code>
    void main(void)
    {
        volatile uint8_t rxData;
        volatile eusart2_status_t rxStatus;
        
        // Initialize the device
        SYSTEM_Initialize();
        
        // Enable the Global Interrupts
        INTERRUPT_GlobalInterruptEnable();
        
        while(1)
        {
            // Logic to echo received data
            if(EUSART2_IsRxReady())
            {
                rxData = EUSART2_Read();
                rxStatus = EUSART2_GetLastStatus();
                if(rxStatus.ferr){
                    LED_0_SetHigh();
                }
            }
        }
    }
    </code>
 */
eusart2_status_t EUSART2_GetLastStatus(void);

/**
  @Summary
    Read a byte of data from the EUSART2.

  @Description
    This routine reads a byte of data from the EUSART2.

  @Preconditions
    EUSART2_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if the receiver is not empty before calling this function.

  @Param
    None

  @Returns
    A data byte received by the driver.
*/
uint8_t EUSART2_Read(void);

 /**
  @Summary
    Writes a byte of data to the EUSART2.

  @Description
    This routine writes a byte of data to the EUSART2.

  @Preconditions
    EUSART2_Initialize() function should have been called
    before calling this function. The transfer status should be checked to see
    if transmitter is not busy before calling this function.

  @Param
    txData  - Data byte to write to the EUSART2

  @Returns
    None
*/
void EUSART2_Write(uint8_t txData);



/**
  @Summary
    Set EUSART2 Framing Error Handler

  @Description
    This API sets the function to be called upon EUSART2 framing error

  @Preconditions
    Initialize  the EUSART2 before calling this API

  @Param
    Address of function to be set as framing error handler

  @Returns
    None
*/
void EUSART2_SetFramingErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART2 Overrun Error Handler

  @Description
    This API sets the function to be called upon EUSART2 overrun error

  @Preconditions
    Initialize  the EUSART2 module before calling this API

  @Param
    Address of function to be set as overrun error handler

  @Returns
    None
*/
void EUSART2_SetOverrunErrorHandler(void (* interruptHandler)(void));

/**
  @Summary
    Set EUSART2 Error Handler

  @Description
    This API sets the function to be called upon EUSART2 error

  @Preconditions
    Initialize  the EUSART2 module before calling this API

  @Param
    Address of function to be set as error handler

  @Returns
    None
*/
void EUSART2_SetErrorHandler(void (* interruptHandler)(void));



#endif  // EUSART2_H
/**
 End of File
*/
