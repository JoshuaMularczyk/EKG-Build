//***************************************************************************
//  file:  ADC.c
//***************************************************************************

#include <MKL25Z4.H>
#define MASK(x) (1UL << (x))
#define ADC_POS (20)

unsigned int Future = 0;
volatile unsigned count_time=0;
volatile unsigned count=0;
volatile unsigned int flag = 0;
volatile int saveBPM[5] = {0,0,0,0,0};
extern int storedValues[1024];
extern int FutureValues[1024];
volatile unsigned int countIndex = 0;
unsigned int max = 0;
extern volatile unsigned int chosenData;
extern int DacOn;
//***************************************************************************
//  ADC initialization function															Joshua Mularczyk
//***************************************************************************

void Init_ADC(void){
	
	// Enable clock to ADC and Port E
	
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Set pin signal type to analog
	
	PORTE->PCR[ADC_POS]&=~PORT_PCR_MUX_MASK;
	PORTE->PCR[ADC_POS]|=PORT_PCR_MUX(0);
	
	// ADCO alternate trigger enable, ADC0 pretriger select, ADC0 trigger select
	
	SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1);
	SIM->SOPT7 |= SIM_SOPT7_ADC0PRETRGSEL(0);
	SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(4);
	
	// Normal power config, divide ratio of 1, short sample time, 12 bit sigle-ended conversion,
	// (Bus clock)/2 input
	
	ADC0_CFG1 = ADC_CFG1_ADLPC(0) | ADC_CFG1_ADIV(0) | ADC_CFG1_ADLSMP(0) | ADC_CFG1_MODE(1) | ADC_CFG1_ADICLK(1);
	
	//hardware tigger selected, compare functin disabled, DMA disabled, Default voltage reference pair pin
	
	ADC0_SC2 |= ADC_SC2_ADTRG(1) | ADC_SC2_ACFE(0) | ADC_SC2_DMAEN(0) | ADC_SC2_REFSEL(0);
	
	// one conversion or sets of conversions, hardware average function enabled, 4 samples averaged
	
	ADC0_SC3 |= ADC_SC3_ADCO(0) | ADC_SC3_AVGE(1) | ADC_SC3_AVGS(0);
	
	// Diff mode enable, input chanel select
	
	ADC0_SC1A |= ADC_SC1_DIFF(0);
	
	ADC0_SC1A &= ~ADC_SC1_ADCH_MASK;
};

//***************************************************************************
//  ADC initialization of inerrupt function									Joshua Mularczyk
//***************************************************************************

void Init_ADC_Interrupts(void){
	
	// interrupt enable
	
	ADC0_SC1A |= ADC_SC1_AIEN(1);
	
	
	NVIC_SetPriority(ADC0_IRQn, 128); // 0, 64, 128 or 192
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(ADC0_IRQn);
	
};

//***************************************************************************
//  ADC IRQ initialization																	Joshua Mularczyk
//***************************************************************************

void ADC0_IRQHandler(void){
	
	NVIC_ClearPendingIRQ(ADC0_IRQn);
	unsigned int analogValue;
	unsigned int high;
	unsigned int low;
	// Read result from ADC
	
	analogValue =  ADC0_RA;
	
	//read analog value directly to dac when dac mode is enabled
	
	if (DacOn == 1){
		
	DAC0->DAT[0].DATL = DAC_DATL_DATA0(analogValue);
	DAC0->DAT[0].DATH = DAC_DATH_DATA1(analogValue >> 8);
	
	ADC0_SC1A |= ADC_SC1_AIEN(0);
	ADC0_SC1A |= ADC_SC1_AIEN(1);
		
	};
	
	//Determine the amplitude of our waveform
	
	if (analogValue > max){
		max = analogValue;
	};
	
	high = 0.8*(max);
	low = 0.7*(max);
	
// Storing the input from ADC directly into an array to be called for later
	
	storedValues[count] = analogValue;
	count++;
	if(count > 1023){
	count = 0;
	};
	
	
// Stores the input from the ADC into an array once a button in mode 3 has been pressed
	
	while (Future == 1){
				FutureValues[count] = analogValue;
				count++;
				if(count > chosenData){
					Future = 0;
				};
			}	
	
// Do code here for accessing previously saved data at the press of button in mode 2
	
	count_time++;
	
	if((analogValue > high)&&(flag == 0)){
		saveBPM[countIndex] = count_time;
		count_time = 0;
		countIndex++;
		if (countIndex == 5){
			countIndex = 0;
		};
		flag = 1;
	};
	
	if((analogValue < low)&&(flag == 1)){
		flag = 0;
	};	
};
