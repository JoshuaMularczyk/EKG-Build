//***************************************************************************
//  file:  switches.c
//***************************************************************************

#include <MKL25Z4.H>
#include <stdint.h>

#define MASK(x) (1UL << (x))

// Debug status bits
#define DBG_ISR_POS (0)
#define DBG_MAIN_POS (1)
#define DEBUG_PORT PTD

// Switches is on port D for interrupt support
#define SW1_POS (1)
#define SW2_POS (2)
#define SW3_POS (4)
#define SW4_POS (5)
#define SW5_POS (12)

extern void init_switch(void);
extern int ratesel;
extern int dataSel;
extern int screen;
extern int rate;
extern int datas;
int mode2 = 0;
int mode3 = 0;
int mode6 = 0;
int ekgselect;

//***************************************************************************
//  switch initialization function															Larry Aamodt
//***************************************************************************
void init_switch(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK; /* enable clock for port A (was D) */

	/* Select GPIO and enable pull-up resistors and interrupts 
		on falling edges for pins connected to switches */
	
	// Initialize button 1
	PORTA->PCR[SW1_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW1_POS);
	
	
	// Initialize button 2
	PORTA->PCR[SW2_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW2_POS);
	
	
	// Initialize button 3
	PORTA->PCR[SW3_POS] &= ~PORT_PCR_MUX_MASK;
	PORTA->PCR[SW3_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW3_POS);
	
	
	// Initialize button 4
	
	PORTA->PCR[SW4_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW4_POS);
	
	
	// Initialize button 5
	
	PORTA->PCR[SW5_POS] |= PORT_PCR_MUX(1) | PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_IRQC(0x0a);
	/* Set port A switch bit to inputs */
	PTA->PDDR &= ~MASK(SW5_POS);

	/* Enable Interrupts */
	NVIC_SetPriority(PORTA_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(PORTA_IRQn); 
	NVIC_EnableIRQ(PORTA_IRQn);
}
//***************************************************************************
//  Switch IRQ handler													        		Joshua Mularczyk
//***************************************************************************
void PORTA_IRQHandler(void) {  
	DEBUG_PORT->PSOR = MASK(DBG_ISR_POS);
	
	// clear pending interrupts
	
	NVIC_ClearPendingIRQ(PORTA_IRQn);
	
	// code to determine what occurs if switch 5 is pressed
	
	if ((PORTA->ISFR & MASK(SW5_POS))){
		if((ratesel == 0) && (dataSel == 0)){
			screen++;
		if (screen > 7){
			screen = 1;
			};
		};
		if (ratesel == 1){
			rate++;
		if(rate > 11){
			rate = 1;
		};		
	};	
		if (dataSel == 1){
		datas++;
		if(datas > 4){
			datas = 1;
			};		
		};
	};
	
	// code to determine what occurs if switch 1 is pressed
	
	if ((PORTA->ISFR & MASK(SW1_POS))){
		if((ratesel == 0) && (dataSel == 0)){
			screen--;
		if (screen == 0){
			screen = 7;
			};
		};
		if (ratesel == 1){
			rate--;
		if(rate == 0){
			rate = 11;
		};		
	};	
		if (dataSel == 1){
		datas--;
		if(datas == 0){
			datas = 4;
			};		
		};
	};
	
// code to determine what occurs if switch 3 is pressed
	
	if ((PORTA->ISFR & MASK(SW3_POS))) {
		if(screen == 1){
		ekgselect++;
		if(ekgselect > 1){
			ekgselect = 0;
			};
		};
		if(screen == 2){
		mode2++;
		if(mode2 > 1){
			mode2 = 0;
		};
	};
		if(screen == 3){
		mode3++;
		if(mode3 > 1){
			mode3 = 0;
		};
	};
		if(screen == 4){
		ratesel++;
		if(ratesel > 1){
			ratesel = 0;
		};
	};
		if(screen == 5){
		dataSel++;
		if(dataSel > 1){
			dataSel = 0;
		};
	};
		if(screen == 6){
		mode6++;
		if(mode6 > 1){
			mode6 = 0;
		};
	};
}
/*	
// code to determine what occurs if switch 2 is pressed

	if ((PORTA->ISFR & MASK(SW2_POS))) {
	};
	
	// code to determine what occurs if switch 4 is pressed
	
	if ((PORTA->ISFR & MASK(SW4_POS))) {
	};
	*/

	// clear status flags

	PORTA->ISFR = 0xffffffff;
	DEBUG_PORT->PCOR = MASK(DBG_ISR_POS);
}
