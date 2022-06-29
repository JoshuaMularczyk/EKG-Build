# EKG-Build

The goal of this project is to use embedded systems design to create a hand-held portable EKG that is able to analyze periodic analog input signals and determine heart rate, while producing an output analog signal that can be stored in Microcontroller memory

## Objectives

#### General

The following general objectives were given:

- Needs a User Interface
- Required User Interaction
- Needs Connections (USB)
- Physical Casing

#### Modes for User Interface

I was tasked with creating the following modes as well:

1. EKG mode. Sample an EKG analog signal and display rate in beats per minute. DAC output will continuously reproduce the analog input that is being sampled. (Sample rate will be fixed at a predetermined and programmed rate for this mode). This is to be the default start-up mode).
2. Sample the analog input (at a previously set rate) and when a user presses a button and store the preceding XX number of data samples in RAM memory for use by the DAC (refer to this as DAC Memory). XX number of samples will have previously been set. XX can take on values of 128, 256, 512, or 1024. (Default start-up value is to be 256)
3. Do the same as mode 2 except store XX number of values starting when the user pressesa button.
4. Set the ADC sample rate (keep track of this rate so that if EKG mode is selected after setting ADC rate and then operation mode becomes something other than EKG mode the previously set ADC rate will be in effect)
5. Set the number of data points XX in a waveform
6. With the DAC create an output waveform using data stored in DAC Memory. (Note: the number of data points in one “cycle” of the waveform will be the number of data points sampled using mode 3 or 4). The rate of updating the DAC will be the current rate as selected in Mode 4.
7. Load a waveform into DAC memory from the asynchronous serial port (via a connection to a Comm port on a PC or USB emulation of a Comm Port). NOTE: actually making the asynchronous port functional in our project is considered a stretch goal.

#### Stretch Goal

There is only16k bytes of memory space for data in the MKL25Z128VLH4 microcontroller that will be used for this project. Thus an external EEPROM memory component, specifically a Microchip 25LC1024-I/SM part, will be used to expand memory. It will be connected to the microcontroller using the Serial Peripheral Interface (SPI) bus.

## Overview

For this project, the task was to design a hand-held portable instrument 
that would analyze a periodic analog input signal i.e. an EKG (electrocardiogram). I was tasked with determining the rate of the analog input signal (heart rate) as well as producing an output analog signal, voltage, that could be stored in Microcontroller memory. Over a period of three months, I learned and designed the software for the PIT, Switches, ADC (analog to digital converter), DAC (digital to analog converter), LCD display, and my menu. I assembled the hardware for my NXP FRDM-KL25Z board attachments (circuit board with switches, LEDs, and LCD), and connected them to the NXP Microcontroller. At the end of the project, I assembled the hardware for a complete circuit board including the MKL25Z processor, 25LC128 memory, switches, and LCD display. I have completed about 90% of the project. I have 5 out of the 7 working modes. These include: EKG Mode, storing of a ADC sample, selecting a sample rate, selecting the amount of data points taken, and outputting the waveform from the DAC. These are explained and can be view more in debth in the [User Manual](https://github.com/JoshuaMularczyk/EKG-Build/tree/main/User%20Manual) and the code can be viewed [here]()! I have not yet been able to accomplish storing a previously sampled data amount and downloading anything to external memory due to lack of time and I have not been able to communicate with the all-in-one designed circuit board for unknown reasons that still need to be troubleshooted.

## Theory

The device created in this project is a portable handheld 
electrocardiogram. This analyzed an analog input signal, 
specifically from the heart, and allows a user to do multiple 
things with this data. Data can be stored in customized 
amounts and at different rates. The analog signal can also be 
output to a device such as an oscilloscope. The device currently 
needs to be powered by a USB port, but has potential for being 
battery powered in the future. The handheld device is 2.03 in x 
1.02 in x 6.5 in (LxWxH). The device can operate at low 
frequencies to frequencies at about 15 Hz.

## Initial Hardware Design

The initial hardware that was used for testing and programming this EKG was a NXP FRDM-KL25Z microcontroller board with a mounted pcb board that was desgined by [Dr. Larry Aamodt]() and assembled by me. This pcb contained five buttons, three LEDs, as well as male and female ports for testing and attaching the ADC, DAC, and other ports. The final piece of hardware used was a LCD display that is mounted ontop of the custom pcb.

insert 3 pictures seperate plus a final with all 3 put together

## Testing

For testing out my modes I used the LCD display screen as well as an oscillosope and a wave generator to create a wave similar to a heartbeat. My LCD was able to display the given heartbeat in BPM.
## Results
## User Manual

Access the full user manual [here](https://github.com/JoshuaMularczyk/EKG-Build/tree/main/User%20Manual)!

## Final Hardware Design

### Schematic

<img width="879" alt="CompleteSchematic" src="https://user-images.githubusercontent.com/103919092/173730058-b952c228-87ac-44d9-90b6-5e05ef012646.PNG">

### PCB Design
