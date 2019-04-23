/*
 * =====================================================================
 * NAME: 
 *       key.c
 *
 * Descriptions : 
 *       External Interrupt Test
 *
 * Developing Environment : 
 *       CodeWarrior 2.0 or Later
 *
 * =====================================================================
 */

#include "2450addr.h"
#include "my_lib.h"
#include "global_var.h"

//extern unsigned char bg2[];
extern unsigned char ttt[];
extern unsigned int HandleEINT8_23;

extern unsigned int fullscreen_buffer[272][480];
extern unsigned int cookie_buffer[44][44];
extern unsigned int slide_buffer[22][56]; 

void SWITCH_Port_Init(void) /*init*/
{
	HandleEINT8_23 = (unsigned int)EINT8_23_handler;
	
	rEINTMASK &= ~(0x1<<8);
	rINTMSK1 &= ~BIT_EINT8_23;
	
	rEXTINT1 |= (0x4<<0);
	
	rGPFCON &= ~(0x3FF<<4);	//2,3,4,5,6 input
	
	rGPFCON |= (0x1<<4);		//jump,slide switch output
	rGPFCON |= (0x1<<12);
	
	rGPGCON &= ~(0x3);
	rGPGCON |= (0x2);	
}

void EINT8_23_handler(void) /*switch Interrupt Handler*/
{

	rEINTMASK |= (0x1<<8);				
	rINTMSK1 |= BIT_EINT8_23;		/**********************/
													/**********************/				
	rEINTPEND |= (0x1<<8);				/* Mask On and ClearPending*/
	rSRCPND1 |= BIT_EINT8_23;		/**********************/
	rINTPND1 |= BIT_EINT8_23;		/**********************/
	
	rGPGCON &= ~(0x3);
	rGPGCON |= (0x1);
	
	rGPGDAT &= ~(0x1);
		
	if(((rGPFDAT>>4) & 0x1) == 0)		//reset
	{

		score = 0;								/*init const*/
		start_x1 = 480;
		start_x2 = 0;
		temp_start_x1 = 0;
		random1 = rand()%4;
		random2 = rand()%4;

		level = 0;
		position = 0;
		hit_check1 = 0;
		hit_check2 = 0;

		Lcd_Select_Frame_Buffer(1);
	    Lcd_Draw_BMP(0, 0, ttt);		
		Lcd_Copy(1,0);						/*Draw Ingame Image*/
		Lcd_Select_Frame_Buffer(0);
		
		Lcd_Printf(30,10,0xffff,fullscreen_buffer,"Time : ");   /*Time,state,score LCD Print with fullscreen_buffer*/
		Lcd_Printf(170,10,0xffff,fullscreen_buffer,"State : ");
		Lcd_Printf(330,10,0xffff,fullscreen_buffer,"Score : ");
		
		rGPFCON &= ~(0x3FF<<4);		//switch on
		rINTSUBMSK &= ~(0x1<<9);	//touch on
		rINTMSK1 &= ~(0x1<<31);			
		Rtc_Init();					//rtc reset
		Timer2_start(100);//timer start_x2 
		Timer1_start(30);
									//Go! timer.c
	}

	rGPGDAT |= 0x1;
	
	rGPGCON &= ~(0x3);
	rGPGCON |= (0x2);	
	
	rEINTMASK &= ~(0x1<<8);	
	rINTMSK1 &= ~BIT_EINT8_23; 
}
