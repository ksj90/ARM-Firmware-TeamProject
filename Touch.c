#include "2450addr.h"
#include "my_lib.h"
#include "global_var.h"


#define C1      523     // Do
#define C1_     554
#define D1      587     // Re
#define D1_     622
#define E1      659     // Mi
#define F1      699     // Pa
#define F1_     740
#define G1      784     // Sol
#define G1_     831
#define A1      880     // La
#define A1_     932
#define B1      988     // Si
#define C2      C1*2    // Do
#define C2_     C1_*2
#define D2      D1*2    // Re
#define D2_     D1_*2
#define E2      E1*2    // Mi
#define F2      F1*2    // Pa
#define F2_     F1_*2
#define G2      G1*2    // Sol
#define G2_     G1_*2
#define A2      A1*2    // La
#define A2_     A1_*2
#define B2      B1*2    // Si



void Touch_Init(void);

#define DURATION_1SEC	1000

extern unsigned int HandleADC;
extern unsigned int fullscreen_buffer[272][480];
extern unsigned int cookie_buffer[44][44];
extern unsigned int slide_buffer[22][56]; 

void Touch_Init(void)
{
	rADCDLY = (50000); 
	
	rADCCON |= (0x1<<14);
	rADCCON |= (39<<6);
	rADCCON &= ~(0x1<<3);
	rADCCON &= ~(0x1<<2);
	rADCCON &= ~(0x1<<1);
	rADCCON &= ~(0x1);

	rADCTSC = (0x0d3);	//interrupt mode & detect stylus down 
		
	HandleADC = (unsigned int)Touch_ISR;
}

volatile  int ADC_x, ADC_y;

void Touch_ISR()
{
	rINTSUBMSK |= (0x1<<9);
	rINTMSK1 |= (0x1<<31);	
	
	rSUBSRCPND |= (0x1<<9);
	rSRCPND1 |= (0x1<<31);
	rINTPND1 |= (0x1<<31);

	if(rADCTSC & 0x100)
	{
		rADCTSC &= (0xff); 
		position =0;
	}
	
	else
	{
		rADCTSC &=~(0x1<<8);				//detect stylus down
		
		rADCTSC &= ~(0x3);
		rADCTSC |= (0x1<<2);
		
		rADCCON |= (0x1);
		while(!(rADCCON & (1<<15)));
		rADCCON &= ~(0x1);
		
		ADC_x = (rADCDAT0 & 0x3ff);
		ADC_y = (rADCDAT1 & 0x3ff);
		
		if((ADC_x >=760) && (ADC_x <= 840) && (ADC_y >=578) && (ADC_y <= 640))
		{
			position =1;
			Buzzer_Beep(C1, 20);
		}
		if((ADC_x >=760) && (ADC_x <= 840) && (ADC_y >=488) && (ADC_y <= 562))
		{
			position =2;
			Buzzer_Beep(D1, 20);
		}
		if((ADC_x >=760) && (ADC_x <= 840) && (ADC_y >=400) && (ADC_y <= 465))
		{
			position =3;
			Buzzer_Beep(E1, 20);
		}
		if((ADC_x >=760) && (ADC_x <= 840) && (ADC_y >=320) && (ADC_y <= 380))
		{
			position =4;
			Buzzer_Beep(F1, 20);	
		}
		
		/*if(press_slide == 0 && press_jump < 2 && ADC_x >= 650 && ADC_y <= 440)
		{
			CLEAR_COOKIE
			press_jump++;
		}
		else if(press_jump == 0 && ADC_x <= 360 && ADC_y <= 440)
		{
			CLEAR_COOKIE
			press_slide = 1;
		}*/
		rADCTSC = (0x1d3);	//interrupt mode & detect stylus up 
	}
	rINTSUBMSK &= ~(0x1<<9);
	rINTMSK1 &= ~(0x1<<31);
}
