// *************************************************************************//
// Program for EKG utilization							                    //
//                                                                          //
// Filename: Main.c										      			    //
// Author: Joshua Mularczyk													//
// Version: 03/2/22 written 												//
// Processor: NXP MKL25Z4 													//
// Compiler: Keil uVision5	                                                //
// Library: CMSIS core and device startup	                                //
// also needs lcd_lib_4bit_20b.c                                            //
//						debug_signals.c										//
//						switches.c											//
//						DAC.c												//
//						Pit.c												//
//						ADC.c												//
//            EKG_Functions.c											    //
// Hardware: NXP Freedom board connected to a 16x2 LCD display              //
// Software note: This program is a "bare metal" application since it       //
// doesn't use an operating system.                                         //
// Operation: Uses a timer to create a periodic inerrupt 10 times a second  //
// *************************************************************************//

#include "MKL25Z4.h"
#include <stdint.h>
#define MASK(x) (1UL << (x))
#define DEBUG_PORT PTD

void delayMs(uint32_t n);
void LCD_init(void);
void LCD_command(uint32_t command);       
void LCD_send_data(uint32_t data);        
void init_debug_signals(void);
void init_switch(void);
void Init_DAC(void);
void Init_PIT(uint32_t period);
void Start_PIT(void);
void PIT_IRQHandler(void);
void Init_ADC(void);
void Init_ADC_Interrupts(void);
void display_string(char string[]);
void setRateDisplay(void);
void dataSelect(void);
void ekgMode(void);
void outputPrev(void);
void outputFuture(void);

extern unsigned int period;
volatile unsigned int ratesel = 0;
extern unsigned int Future;
int dataSel = 0;
int screen = 1;
int DacOn = 0;
int rate = 1;
int datas = 2;
extern int mode2;
extern int mode3;
extern int mode6;
extern int ekgselect;
int storedValues[1024];
int FutureValues[1024];
volatile unsigned int sampleRate = 0;

//***************************************************************************
//  Main function																						Joshua Mularczyk
//***************************************************************************
int main (void) {

	// initialization of the PIT
	
	Init_PIT(24000);
	Start_PIT();

	// Set clock
	
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	
	__enable_irq();
	init_debug_signals();
	Init_DAC();
	Init_ADC();
	Init_ADC_Interrupts();
	LCD_init();
	LCD_command(0x01);
	init_switch();
	
	while(1){
		
		delayMs(500);
		LCD_command(0x80);
	
		//Menu for EKG
		
		switch (screen){
			case 1:
				display_string("EKG.MODE");
				LCD_command(0xC0);
				ekgMode();
				break;
			case 2:
				display_string("Samp.ADC");
				LCD_command(0xC0);
				display_string("Stor--->");
			if(mode2 == 1){
				outputPrev();
			};
			break;
			case 3:
				display_string("Samp.ADC");
				LCD_command(0xC0);
				display_string("Futr--->");
			if(mode3 == 1){
				Future = 1;
			};
			break;
			case 4:
				display_string("sampRate");
				LCD_command(0xC0);
				display_string("   ---->");
			if(ratesel == 1){
					setRateDisplay();
				};
			break;
			case 5:
				display_string("set.Data");
				LCD_command(0xC0);
				display_string("   ---->");
			if(dataSel == 1){
					dataSelect();
				};
			break;
			case 6:
				display_string("DAC.outp");
				LCD_command(0xC0);
				display_string("   ---->");
			if(mode6 == 1){
				DacOn = 1;
			}
			else {
				DacOn = 0;
			};
			break;
			case 7:
				display_string("Download");
				LCD_command(0xC0);
				display_string("   ---->");
			break;
		}
	}
};
