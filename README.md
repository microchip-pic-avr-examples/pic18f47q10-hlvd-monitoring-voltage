[![MCHP](images/microchip.png)](https://www.microchip.com)

# Monitoring Supply Voltage using HLVD of PIC18F47Q10 microcontroller

# Introduction
Many of the PIC® microcontrollers have a High/Low-Voltage Detect (HLVD) module that are be used to monitor the device voltage (V<sub>DD</sub>) and indicate the user if voltage has decreased below a specified voltage or increased above a specified voltage.  This is a programmable circuit that sets a device voltage trip point and the direction of change from that point (positive going, negative going or both).  This feature is useful in battery monitoring applications.
This example demonstrates using an HLVD module to quickly detect when the supply voltage of the microcontroller has decreased below the specified trip point or increased above the specified trip point.

# Related Documents / Useful Links

- [TB3237 - Getting Started with HLVD Technical Brief](https://www.microchip.com/DS90003237)
- [PIC18-Q10 Product Family Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- [PIC18F47Q10 Data Sheet](http://www.microchip.com/DS40002043)
- [PIC18F47Q10 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=pic18f47q10)

# HLVD

The HLVD is a necessary power supply monitoring feature in numerous battery powered applications, where the supply voltage of a microcontroller falls below the specified threshold level and requires battery replacement or recharging for an uninterrupted operation of the microcontroller. The HLVD feature is capable of monitoring the supply voltage of a microcontroller which is directly powered up from a battery power source. The HLVD based voltage monitoring circuitry has several advantages over an ADC based voltage monitoring circuit. When the HLVD module is enabled, a comparator within HLVD uses an internally generated voltage reference as the set point. The set point is compared with the trip point. The “trip point” voltage is the voltage level at which the device detects a high or low voltage event, depending on the configuration of the HLVD module. When the supply voltage is equal to the trip point, the comparator generates an interrupt signal by setting the HLVDIF bit. The trip point voltage is software programmable to any of 16 values as shown in the below Table 1. The trip point is selected by programming the SEL bits.


![Table HLVD sel](images/Table_HLVD_SEL.png)

			Table 1: HLVD Trip point Voltages


***Note: Refer to the device data sheet for the typical Trip Point Voltage (V) settings and the MCC configuration GUI of HLVD peripheral for minimum and maximum Trip Point Voltage (V) settings.***

# Demo Description

![Block Diagram](images/Block_diagram.jpg)

		Figure 1: Block diagram of application demo

* PIC18F47Q10 Curiosity Nano board and external power supply are used to demonstrate the configuration and usage of the HLVD module. HLVD is used to monitor the microcontroller supply voltage for low and high voltage detect.
* After power-up the trip-point voltage of the HLVD is configured to 3.15V to detect low supply voltage.    
* If the supply voltage is decreased below the set-point, the HLVD module generates an interrupt. UART is used to send messages to the terminal window, that low voltage is detected.
* Once the low voltage is detected, the trip point is changed to 4.35V, to detect high supply voltage using HLVD.
* If the supply voltage is increased above the set-point, the HLVD module generates an interrupt. UART is used to send a message to the terminal, that high voltage is detected.
* After detection of the high supply voltage, the set point is changed back to 3.15V to detect low supply voltage. The process is repeated.

# Hardware used
* [PIC18F47Q10 Curiosity nano evaluation board](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)

With full program and debug capabilities, the PIC18F47Q10 Curiosity Nano evaluation kit offers complete support for the new design. The kit uses the MPLAB® X IDE and MPLAB® Code Configurator (MCC), providing access to the Intelligent Analog and Core Independent Peripherals on the PIC18F47Q10.
Figure 2 shows the PIC18F47Q10 Curiosity Nano board.

![PIC18F47Q10 Curiosity Nano board](images/PIC18F47Q10_Curiosity_Nano_board.png)

		Figure 2: PIC18F47Q10 Curiosity Nano board

# Software Tools:

Microchip’s free MPLAB X IDE, compiler and MPLAB Code Configurator (MCC) graphical code generator are used throughout the application firmware development to provide an easy and hassle-free user experience. Following are the tool versions used for this demo application:

* MPLAB X IDE [v6.05 or newer](https://www.microchip.com/mplab/mplab-x-ide)
* XC8 Compiler [v2.41 or newer](https://www.microchip.com/mplab/compilers)
* MPLAB Code Configurator (MCC) [v5.3.0 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
* Microchip PIC18F-Q Series Device Support [v1.17.379 or newer](https://packs.download.microchip.com/)
* HLVD Driver [v4.3.1 or newer]
* UART Driver [v1.8.0 or newer]

***Note: For running the demo, the installed tool versions must be the same or later. This example is not tested with previous versions.***


## Data Visualizer:
Data Visualizer is a software tool used to process and visualize data. The Data Visualizer can receive data from various sources, such as the Embedded Debugger Data Gateway Interface (DGI) and COM ports. Data Visualizer is made up of several modules, such as Graph, Oscilloscope, Terminal, Power debugging, Custom dashboard etc. In this example, MPLAB data visualizer tool is used to receive messages from the Curiosity Nano board. The terminal window is used to display the messages upon detection of low or high supply voltage using HLVD. For more details on the Data Visualizer tool refer to the [Data Visualizer user guide](https://www.microchip.com/DS40001903).

# Demo realization
## Peripherals Configuration using MCC
### Clock Configuration

Open the **Clock Control** setup present under "System" dropdown menu in the **Project Resources** tab.
* Set Clock Source as HFINTOSC
* Set HF Internal Clock as 1_MHz
* Set Clock Divider as 1


![Clock Control](images/clock_control.png)

		Figure 3: Clock Control


### Add peripherals to the project

Add HLVD and UART2 peripherals to the project.
Make sure to add peripherals present under **Drivers** dropdown menu in **Device Resources** tab.

![peripherals](images/peripherals.png)

        Figure 4: Peripherals

### HLVD Configuration

Configurations to be done for HLVD peripheral:
* Make sure that HLVD is enabled
* Set the Trip points as Min:3.00 Max:3.18
* Enable HLVD interrupt
* Enable Negative going Interrupt

![HLVD_Configuration](images/hlvd.png)

		Figure 5: HLVD Configuration

### UART2 Configuration
In this demo, UART2 is used to transmit data on the terminal window upon detection of the low/high supply voltage using the HLVD module.
Configurations to be done for UART2 peripheral:
* Enable the Redirect Printf to UART
* Set baud rate as 9600

![uart-driver](images/uart-driver.png)

		Figure 6: UART Driver Configuration                                                                  

### Pin Configuration
The I/O pin mapping of the PIC18F47Q10 MCU for the UART2 interface and on-board LED is shown in the Figure 7.
Configurations to be done in the Pins grid view window:
* Select pin RD0 as an EUSART2 TX2 pin.
* Pin RB7 for EUSART2 RX2 can be deselected.
* Configure Pin RE0 as output for connecting to LED0.

![Pins Grid View](images/pins_grid_view.png)

		Figure 7: Pins grid view

Add custom name to the RE0 output pin as LED using Pins window. Check the Start High check box for LED pin RE0 for turning OFF the LED during initialization.

![Pins](images/Pins.png)

		Figure 8: Pins

**Generate the Project files**
* Click the Generate button next to the project Resources to generate initializers and drivers for configured peripherals.

### Hardware Setup
 Follow the below steps for Hardware setup:
1. To power-up the PIC18F47Q10 device using external power supply, the VOFF pin on the Curiosity Nano Board should be connected to the ground. Connect the VOFF pin to GND pin using a jumper cable. Refer to the below figures.
2.	Connect external power supply to VTG pin of the Curiosity Nano Board to power-up the PIC18F47Q10 device using an external power supply. Make sure the external supply voltage is 3.3V. Refer to the below figures.
3.	Set up the hardware, as shown in Figure 10.

![VTG_and_VOFF_pins](images/VTG_and_VOFF_pins.png)

		Figure 9: VTG and VOFF pins

![Hardware_setup](images/Hardware_setup.jpg)

		Figure 10: Hardware set up

4.	Connect PIC18F47Q10 Curiosity Nano to the PC using an USB cable.

Open the Terminal window in Data Visualizer. Use 9600 baud rate. Any other terminal emulator can be used for this purpose.

 **Program the device**
* Program the microcontroller by clicking **Make and Program Device** icon on MPLAB X IDE as shown in below figure.

![program](images/program.png)

        Figure 11: Programming the device

# Demo Operation:
* Upon power on the trip-point of HLVD is set at 3.15V to detect low supply voltage.   
* A message will be displayed on the terminal window, to lower the supply voltage for detecting low supply voltage event. Start decreasing the supply voltage.

![Initial_message](images/Initial_message_on_the_terminal_window.png)

		Figure 12: Initial message on the terminal window

* If the supply voltage is decreased below the trip point i.e 3.15V, the HLVD module generates interrupt. Observe the message on the terminal window that low voltage is detected.

![Message_after_detecting_low_voltage](images/Message_after_detecting_low_voltage.png)

		Figure 13: Message after detecting low voltage

* Once the low voltage is detected, the HLVD configuration is changed to detect high supply voltage. The trip point is changed to 4.35V and INTH bit of HLVDCON0 register is set.
* Start increasing the supply voltage.
* If the supply voltage is increased above the trip point i.e. 4.35V, the HLVD module generates an interrupt. Observe the message on the terminal window that the high voltage is detected.

![Message_after_detecting_high_voltage](images/Message_after_detecting_high_voltage.png)

		Figure 14:  Message after detecting high voltage

* After detection of the high supply voltage, the trip point is changed back to 3.15V and INTL bit is set to detect low supply voltage. The process is repeated.

# Conclusion
High/Low-Voltage Detect (HLVD) module of a PIC® microcontroller is a valuable feature for monitoring the supply voltage of a microcontroller that is directly battery powered. The usage of HLVD module doesn’t require any extra port pin for supply voltage monitoring.
