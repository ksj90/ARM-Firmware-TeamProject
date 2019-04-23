/*
 * =====================================================================
 * NAME         : Lcd.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	  
 * =====================================================================
 */

#include "2450addr.h"
#include "my_lib.h"


#define CLKVAL  	13
#define HOZVAL 	   (LCD_SIZE_X-1)
#define LINEVAL    (LCD_SIZE_Y-1)

#define VBPD (10)	
#define VFPD (1)	
#define VSPW (1)	
#define HBPD (43)
#define HFPD (1)	
#define HSPW (1)	

void Graphic_Init(void)
{
     Lcd_Port_Init();
     Lcd_Init();   
}

void Lcd_Port_Init(void)
{
	rGPCUDP = 0xffffffff; 
	rGPCCON &= ~(0xffffffff);
	rGPCCON |= 0xaaaa02aa; //GPC5,6,7 = output
	
	rGPDUDP = 0xffffffff; 
	rGPDCON &= ~(0xffffffff);
	rGPDCON |= 0xaaaaaaaa;
	
	/* GPG12 is setted as LCD_Display ON/OFF */
	rGPGCON &= ~(3<<24); 	//GPG12=OUTPUT
	rGPGCON |= (1<<24);
	
	rGPGDAT|=(1<<12);
	
	/* GPB0 backlight Enable */
	rGPBCON &= ~(3<<0);
	rGPBCON |= (1<<0);
	
	rGPBDAT|= (1<<0);
}

void Lcd_Init()
{		
	rVIDW00ADD0B0 = FRAME_BUFFER;
	rVIDW00ADD1B0 = 0;
	rVIDW00ADD2B0 = (0<<13)|((LCD_SIZE_X*4*2)&0x1fff);

	rVIDW00ADD1B0 = 0+(LCD_SIZE_X*LCD_SIZE_Y);
	
	
	rVIDCON0=(0x0<<22)+(0x1<<13)+((CLKVAL)<<6)+(1<<5)+(1<<4)+(0<<2);
	rVIDCON1= (1<<6)+(1<<5);
	
	rVIDTCON0=((VBPD)<<16)+((VFPD)<<8)+(VSPW);
	rVIDTCON1=((HBPD)<<16)+((HFPD)<<8)+(HSPW);
	
	rVIDTCON2=(LINEVAL<<11)+(HOZVAL);	//size set
	
	rVIDOSD0A		= 	(((0)&0x7FF)<<11) | (((0)&0x7FF)<<0);
	rVIDOSD0B	 	= 	(((LCD_SIZE_X-1)&0x7FF)<<11) | (((LCD_SIZE_Y-1)&0x7FF)<<0);//size set

	rVIDOSD1A 		= 	(((0)&0x7FF)<<11) | (((0)&0x7FF)<<0);
	rVIDOSD1B	 	= 	(((LCD_SIZE_X-1)&0x7FF)<<11) | (((LCD_SIZE_Y-1)&0x7FF)<<0);//size set


	rWINCON0=(0x1<<16)+(0x7<<2)+(1<<0); //Half swap Enable, 5:5:5:I format, Window0 ON

	rVIDCON0 |= (3<<0);	//ENVID enable
}

