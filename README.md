[![MCHP](images/microchip.png)](https://www.microchip.com)

# Monitoring Supply Voltage using HLVD

# Introduction
Many of the PIC microcontrollers have a High/Low-Voltage Detect (HLVD) module that can be used to monitor the device voltage (VDD) and indicate the user if voltage has decreased below a specified voltage or increased above a specified voltage.  This is a programmable circuit that sets a device voltage trip point and the direction of change from that point (positive going, negative going or both).  This feature is useful in battery monitoring applications.
This example demonstrates using an HLVD module to quickly detect when the supply voltage of the microcontroller has decreased below the specified trip point or increased above the specified trip point.

# Useful Links
- [PIC18-Q10 Product Family Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- [PIC18F47Q10 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf)
- [PIC18F47Q10 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=pic18f47q10-cnano)

# HLVD
The HLVD is a necessary power supply monitoring feature in numerous battery powered applications, where the supply voltage of a microcontroller could fall below the specified threshold level and require battery replacement or recharging for uninterrupted operation of the microcontroller.  The HLVD feature is capable of monitoring supply voltage of a microcontroller which is directly powered from a battery power source. The HLVD based voltage monitoring circuitry has several advantages over an ADC based voltage monitoring circuit. When the HLVD module is enabled, a comparator within HLVD uses an internally generated voltage reference as the set point. The set point is compared with the trip point. The “trip point” voltage is the voltage level at which the device detects a high or low voltage event, depending on the configuration of the HLVD module. When the supply voltage is equal to the trip point, the comparator generates an interrupt signal by setting the HLVDIF bit. The trip point voltage is software programmable to any of 16 values as shown in the below Table 1. The trip point is selected by programming the SEL bits.


![Table HLVD sel](images/Table_HLVD_SEL.png)

			Table 1:HLVD Trip point Voltages


***Note: Refer the device datasheet for the typical Trip Point Voltage (V) settings. And refer MCC configuration GUI of HLVD peripheral for minimum and maximum Trip Point Voltage (V) settings.***

# Demo Description

![Block Diagram](images/Block_diagram.jpg)
		Figure 1: Block diagram of application demo

* PIC18F47Q10 Curiosity Nano board and external power supply are used to demonstrate the configuration and usage of the HLVD module. HLVD is used to monitor the microcontroller supply voltage for low and high voltage detect.
* After power up the trip-point voltage of HLVD is configures to 3.15V to detect low supply voltage.    
* If the supply voltage is decreased below the setpoint the HLVD module generates interrupt. EUSART is used to send messages   to the terminal window that low voltage is detected.
* Once the low voltage is detected the trip point is changed to 4.35V to detect high supply voltage using HLVD.
* If the supply voltage is increased, above the setpoint the HLVD module generates interrupt. EUSART is used to send a message to the terminal that high voltage is detected.
* After detection of the high supply voltage, the set point is changed back to 3.15V to detect low supply voltage. The process is repeated.

# Hardware used
* [PIC18F47Q10 Curiosity nano evaluation board](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
With full program and debug capabilities, the PIC18F47Q10 Curiosity Nano evaluation kit offers complete support for the new design. With the award-winning MPLAB X integrated development platform and MPLAB Code Configurator (MCC), the kit provides access to the Intelligent analog and Core Independent Peripherals on the PIC18F47Q10. Figure 2 shows the PIC18F47Q10 Curiosity Nano board.

![PIC18F47Q10 Curiosity Nano board](images/PIC18F47Q10_Curiosity_Nano_board.jpg)

		Figure 2: PIC18F47Q10 Curiosity Nano board

# Software Tools:

Microchip’s free MPLAB X IDE, compiler and MPLAB Code Configurator (MCC) graphical code generator are used throughout the application firmware development to provide easy and hassle-free user experience. Following are the tool versions used for this demo application:

* [MPLAB® X IDE v5.30](http://www.microchip.com/mplab/mplab-x-ide)
* [XC8 Compiler v2.10](http://www.microchip.com/mplab/compilers)
* [MPLAB® Code Configurator (MCC) v3.85.1](https://www.microchip.com/mplab/mplab-code-configurator)
* [MCC Device Libraries PIC10 / PIC12 / PIC16 / PIC18  MCUs v1.78.0](microchip.com/mplab/mplab-code-configurator)
* [Microchip PIC18F-Q Series Device Support 1.3.89](https://packs.download.microchip.com/)
* [Data Visualizer] (https://gallery.microchip.com/packages/AtmelDataVisualizerInstaller-Standalone/)
***Note: For running the demo, the installed tool versions should be the same or later. This example is not tested with previous versions.***
## Data Visualizer:
Data Visualizer is a software tool used to process and visualize data. The Data Visualizer can receive data from various sources such as the Embedded Debugger Data Gateway Interface (DGI) and COM ports. Data Visualizer is made up of several modules such as Graph, Oscilloscope, Terminal, Power debugging, Custom dashboard etc. In this example, Standalone data visualizer tool is used to receive messages from the Curiosity Nano board. The terminal window is used to display the messages upon detection of low or high supply voltage using HLVD. For more details on the Data Visualizer tool refer to the Data Visualizer user guide.

# Demo realization
## Peripherals Configuration using MCC
### System Configuration
The system configuration window of MCC is used for MCU oscillator, PLL, Watchdog timer and low voltage programming configuration. The Internal oscillator of 1MHz frequency with clock divider as 1 is used as a system clock and the Watchdog timer is disabled in this example. Figure 3 shows the system configuration settings used in this example.

![System Configuration](images/System_Configuration.png)

			Figure 3: System Configuration

### HLVD Configuration

Configurations to be done on HLVD peripheral:
* Check the Enable HLVD checkbox
* Set the Trip point as Min:3.00 Max:3.18
* Check Enable Negative going Interrupt checkbox
* Check Enable HLVD interrupt checkbox

![HLVD_Configuration](images/HLVD_Configuration.png)

			Figure 4: HLVD Configuration

###         Eusart2 Configuration
In this demo, EUSART2 is used to transmit data on the terminal window upon detection of the low/high supply voltage using the HLVD module.
Configurations to be done on EUSART2 peripheral:
* Check the Enable EUSART checkbox
* Check the Enable Transmit checkbox
* Set the Baud Rate to 9600
* Check the Redirect STDIO to USART checkbox

![EUSART_2_Configuration ](images/EUSART_2_Configuration.png)

			Figure 5: EUSART 2 Configuration                                                                       

### Pin Configuration
The I/O pin mapping of the PIC18F47Q10 MCU for the EUSART2 interface and on-board LED is shown in the Figure 6.
Configurations to be done in the Pin Manager window:
* Select pin RD0 as an EUSART2 TX pin.
* Configure Pin RE0 as output to connect to LED0.

![Pin Manager](images/Pin_Manager.png)
			Figure 6: Pin Manager

Add custom name to the PE0 output pin as LED using Pin module. Check the Start High check box for LED pin PE0 for turning off the LED during initialization.

![Pin Module](images/Pin_Module.png)
				Figure 7: Pin Module

# Hardware Setup
 Follow the steps for Hardware setup:
1.	To power the PIC18F47Q10 device using external power supply the VOFF pin on the CNANO board should be connected to ground. Connect the pins VOFF pin to GND pin using the jumper.  Refer Figure 8 for VOFF pin.
2.	Connect external power supply to VTG and GND pins of the curiosity nano board to power the PIC18F47Q10 device using external power supply. Make sure external supply voltage is 3.3V. Refer Figure 8 for VTG pin.
3.	Setup the hardware, as shown in 9.

![VTG_and_VOFF_pins](images/VTG_and_VOFF_pins.png)

			Figure 8: VTG and VOFF pins

![Hardware_setup](images/Hardware_setup.jpg)

			Figure 9: Hardware setup

4.	Connect a micro USB cable from micro USB socket on the Curiosity nano board to the PC for programming the board and viewing the messages on the PC terminal window.

Follow the steps listed below, to open the Terminal window in Data Visualizer. Any other terminal emulator can be used for this purpose.

## Steps to open Terminal window in Data Visualizer:
Open the standalone Data Visualizer tool.
1.	In the Data Visualizer window, click on the **Configuration** tab.
2.	In the **Modules** **section**, click and expand the External connection option and then double click on Serial Port.
3.	Select the **Curiosity Virtual Com Port** in Serial Port Control Panel.
4.	Set the Baud rate to 9600.
5.	Check the **Open Terminal** option.
6.	Click on the **Connect** button.

![Open_terminal_window_in_Data_visualizer](images/Open_terminal_window_in_Data_visualizer.jpg)

		Figure 10: Open terminal window in Data visualizer

# Device Programming
1.	To Program the MCU, click Make and Program Device icon on MPLAB XPRESS IDE as shown in Figure 11.

![Programming_the_device](images/Programming_the_device.png)

			Figure 11: Programming the device

2.	IDE generates the .hex file. Save the file in local PC
3.	Drag the .hex from the downloads section and drop the file on to the Curiosity drive. This should program the device

# Demo Operation:
* Upon power on the trip-point of HLVD is set at 3.15V to detect low supply voltage.   
* A message will be displayed on the terminal window to lower the supply voltage for detecting low supply voltage event. Start decreasing the supply voltage.

![Initial_message](images/Initial_message_on_the_terminal_window.png)

		Figure 12: Initial message on the terminal window

* If the supply voltage is decreased below the trip point i.e 3.15 V, the HLVD module generates interrupt. Observe the message on the terminal window that low voltage is detected.

![Message_after_detecting_low_voltage](images/Message_after_detecting_low_voltage.png)

		Figure 13: Message after detecting low voltage

* Once the low voltage is detected the HLVD configuration is changed to detect high supply voltage. The trip point is changed to 4.35V and INTH bit of HLVDCON0 register is set.
* Start increasing the supply voltage.
* If the supply voltage is increased above the trip point i.e. 4.35V, the HLVD module generates interrupt. Observe the message on the terminal window that the high voltage is detected.

![Message_after_detecting_high_voltage](images/Message_after_detecting_high_voltage.png)

		Figure 14:  Message after detecting high voltage

* After detection of the high supply voltage, the trip point is changed back to 3.15V and INTL bit is set to detect low supply voltage. The process is repeated.

# Conclusion
High/Low-Voltage Detect (HLVD) module of a PIC microcontroller is a valuable feature for monitoring the supply voltage of a microcontroller that is directly battery powered. The usage of HLVD module doesn’t require any extra port pin for supply voltage monitoring.

# Related Documents / Application Notes

* [TB3237 - Getting Started with HLVD Technical Brief](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1001037)



.
