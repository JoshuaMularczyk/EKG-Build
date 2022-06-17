//***************************************************************************
//  file:  EKG_Functions
//***************************************************************************

#include <MKL25Z4.H>
#include <stdint.h>
#define MASK(x) (1UL << (x))

extern int rate;
extern int datas;
extern volatile int saveBPM[5];
extern volatile unsigned int sampleRate;
volatile unsigned int chosenData = 255;
volatile unsigned int origPit = 24000;

/*----------------------------------------------------------------------------
   functions 
 *----------------------------------------------------------------------------*/
void LCD_command(uint32_t command);       // use to send LCD commands
void LCD_send_data(uint32_t data);        // use to send one char to screen
void setRateDisplay(void);
void dataSelect(void);
void display_string(char string[]);
void outputPrev(void);
void outputFuture(void);
void ekgMode(void);
void PIT_change(uint32_t period);

//***************************************************************************
//  Function to set up menu to choose rates									Joshua Mularczyk
//***************************************************************************

void setRateDisplay(void){
	switch (rate){
			case 1:
				LCD_command(0x01);
				display_string("50");
				LCD_command(0xC0);
				display_string("Hz      ");
				sampleRate = origPit*2.9;
				PIT_change(sampleRate);
			
			break;
			case 2:
				LCD_command(0x01);
				display_string("100");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*2.8;
				PIT_change(sampleRate);
			break;
			case 3:
				LCD_command(0x01);
				display_string("200");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*2.6;
				PIT_change(sampleRate);
			break;
			case 4:
				LCD_command(0x01);
				display_string("300");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*2.4;
				PIT_change(sampleRate);
			break;
			case 5:
				LCD_command(0x01);
				display_string("400");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*2.2;
				PIT_change(sampleRate);
			break;
			case 6:
				LCD_command(0x01);
				display_string("500");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*2;
				PIT_change(sampleRate);
			break;
			case 7:
				LCD_command(0x01);
				display_string("600");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*1.8;
				PIT_change(sampleRate);
			break;
			case 8:
				LCD_command(0x01);
				display_string("700");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*1.6;
				PIT_change(sampleRate);
			break;
			case 9:
				LCD_command(0x01);
				display_string("800");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*1.4;
				PIT_change(sampleRate);
			break;
			case 10:
				LCD_command(0x01);
				display_string("900");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit*1.2;
				PIT_change(sampleRate);
			break;
			case 11:
				LCD_command(0x01);
				display_string("1000");
				LCD_command(0xC0);
				display_string("Hz      ");
			sampleRate = origPit;
				PIT_change(sampleRate);
			break;
		}
	};

//***************************************************************************
//  Function to set up data menu														Joshua Mularczyk
//***************************************************************************
	
void dataSelect(void){
	switch (datas){
			case 1:
				LCD_command(0x01);
				display_string("128");
				LCD_command(0xC0);
				display_string("Points  ");
				chosenData = 127;
			break;
			case 2:
				LCD_command(0x01);
				display_string("256");
				LCD_command(0xC0);
				display_string("Points  ");
				chosenData = 255;
			break;
			case 3:
				LCD_command(0x01);
				display_string("512");
				LCD_command(0xC0);
				display_string("Points  ");
				chosenData = 511;
			break;
			case 4:
				LCD_command(0x01);
				display_string("1024");
				LCD_command(0xC0);
				display_string("Points  ");
				chosenData = 1023;
			break;
		
		}
	};

//***************************************************************************
//  Function to display EKG BPM															Joshua Mularczyk
//***************************************************************************
	
void ekgMode(void){
		int	averageBPM =  ((saveBPM[0] + saveBPM[1] + saveBPM[2] + saveBPM[3] + saveBPM[4])/5);
		averageBPM = 60000/averageBPM;
		LCD_command(0xC0);
		LCD_send_data((averageBPM/100)+48);
		LCD_send_data(((averageBPM/10)%10)+48);
		LCD_send_data((averageBPM%10)+48);
		display_string(" BPM ");
};
void outputPrev(void){
//code to save the array to mem
};
void outputFuture(void){
//code to save the array to mem	
};
