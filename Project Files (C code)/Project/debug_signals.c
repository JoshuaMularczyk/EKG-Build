//***************************************************************************
//   File:   debug_signals.c
//***************************************************************************

// #include "gpio_defs.h"
#include <MKL25Z4.h>

#define MASK(x) (1UL << (x))

// Debug status bits
#define DBG_ISR_POS (3)
#define DBG_MAIN_POS (1)
#define DEBUG_PORT PTD

//***************************************************************************
//  debug initialization function																Larry Aamodt
//***************************************************************************

void init_debug_signals(void) {
	SIM->SCGC5 |=  SIM_SCGC5_PORTD_MASK; /* enable clock for port B */

	/* Select GPIO for pins connected to debug signals*/
	PORTD->PCR[DBG_ISR_POS] |= PORT_PCR_MUX(1);	
	PORTD->PCR[DBG_MAIN_POS] |= PORT_PCR_MUX(1);	
	
	/* Set bits to outputs */
	PTD->PDDR |= MASK(DBG_ISR_POS) | MASK(DBG_MAIN_POS); 
	
	/* Clear output signals initially */
	PTD->PCOR |= MASK(DBG_ISR_POS) | MASK(DBG_MAIN_POS);
}
