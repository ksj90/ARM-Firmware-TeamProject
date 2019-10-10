#include "2450addr.h"
#include "my_lib.h"
#include "global_var.h"


extern unsigned int  HandleTIMER0;
extern unsigned int  HandleTIMER1;
extern unsigned int  HandleTIMER2;

extern int Perfect;
extern int Miss;


extern unsigned int fullscreen_buffer[272][480]; 

void Timer_Init(void) /*init*/
{
	rTCFG0 = ((rTCFG0 & (~0xff)) | (0xff));				//timer0,1 
	rTCFG0 = ((rTCFG0 & (~(0xff<<8))) | (0xff<<8));		//timer2,3,4

	rTCFG1 = ((rTCFG1 & (~(0xf<<4))) | (0x3<<4));		//timer1
	rTCFG1 = ((rTCFG1 & (~(0xf<<8))) | (0x3<<8));		//timer2



	rTCON |= (0x1<<11);		//timer1 auto_reload
	rTCON |= (0x1<<15);		//timer2 auto_reload
	
	rTCNTB0 = 0;
	rTCMPB0 = 0;
	
	rTCNTB1 = 0;
	rTCMPB1 = 0;
		
	rTCNTB2 = 0;
	rTCMPB2 = 0;
		
	HandleTIMER1 = (unsigned int)timer1_handler;
	HandleTIMER2 = (unsigned int)timer2_handler;
	

	rINTMSK1 &= ~BIT_TIMER1;
	rINTMSK1 &= ~BIT_TIMER2;
}


void Timer1_start(int msec)
{
	rTCNTB1 = msec;
	rTCON |= (1<<9) | (0x0<<8);
	rTCON &= ~(1<<9);
	rTCON |= (0x1<<8);	
}

void Timer2_start(int msec)
{
	rTCNTB2 = 16.113*msec;	
	rTCON |= (1<<13) | (0x0<<12);
	rTCON &= ~(1<<13);
	rTCON |= (0x1<<12);
}

#define MAKE_NOTE(START_X,RANDOM,HIT_CHECK,COLOR) {\
	int y;\
	if(HIT_CHECK!=1)\
	{\
	if(START_X >=0 && (START_X <=480))\
	{\
		switch(RANDOM)\
		{\
			case 0:\
				for(y=32;y<83;y++)\
					LCD_PUT_PIXEL(START_X,y,COLOR);\
				break;\
			case 1:\
				for(y=92;y<140;y++)\
					LCD_PUT_PIXEL(START_X,y,COLOR);\
				break;\
			case 2:\
				for(y=150;y<205;y++)\
					LCD_PUT_PIXEL(START_X,y,COLOR);\
				break;\
			case 3:\
				for(y=215;y<265;y++)\
					LCD_PUT_PIXEL(START_X,y,COLOR);\
				break;\
		}\
	}\
	}\
	if((START_X+SIZE_OF_BUMB) >=0 && (START_X+SIZE_OF_BUMB) <= 480)\
	{\
		int temp = START_X+SIZE_OF_BUMB;\
		switch(RANDOM)\
		{\
			case 0:\
				for(y=32;y<83;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 1:\
				for(y=92;y<140;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 2:\
				for(y=150;y<205;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 3:\
				for(y=215;y<265;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
		}\
	}\
	START_X--;\
if(HIT_CHECK == 0 && (START_X>5 && START_X<60))\
{\
			switch(RANDOM)\
			{\
				case 0:\
					if(position==1)\
					{\
						score += 50;\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[0]);\
						HIT_CHECK++;\
						Perfect++;\
					}\
					else\
					{\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[1]);\
						HIT_CHECK--;\
						Miss++;\
					}\
					break;\
				case 1:\
					if(position==2)\
					{\
						score += 50;\
						HIT_CHECK++;\
						Perfect++;\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[0]);\
					}\
					else\
					{\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[1]);\
						HIT_CHECK--;\
						Miss++;\
					}\
					break;\
				case 2:\
					if(position==3)\
					{\
						score += 50;\
						HIT_CHECK++;\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[0]);\
						Perfect++;\
						}\
					else\
					{\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[1]);\
						HIT_CHECK--;\
						Miss++;\
					}\
					break;\
				case 3:\
					if(position==4)\
					{\
						score += 50;\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[0]);\
						HIT_CHECK++;\
						Perfect++;\
					}\
					else\
					{\
						Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[1]);\
						HIT_CHECK--;\
						Miss++;\
					}\
					break;\
		}\
	}\
if(HIT_CHECK==1)\
{\
	int temp =50;\
		switch(RANDOM)\
		{\
			case 0:\
				for(y=32;y<83;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 1:\
				for(y=92;y<140;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 2:\
				for(y=150;y<205;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
			case 3:\
				for(y=215;y<265;y++)\
					LCD_PUT_PIXEL(temp,y,fullscreen_buffer[y][temp]);\
				break;\
		}\
	}\
}\

void timer1_handler(void) /*timer 1 handler associate with Make note & drop Note*/
{ 
	rINTMSK1 |= BIT_TIMER1;
	
	rSRCPND1 |= BIT_TIMER1;
	rINTPND1 |= BIT_TIMER1;

	MAKE_NOTE(start_x1,random1,hit_check1,0x001f) /*call MAKE_NOTE macro & start_x1 is 480 in init */
	if(start_x1 < -SIZE_OF_BUMB) /*start_x1 was decresed in MAKE_NOTE , So if start_x1 less than 0 */
	{
		start_x1 =  480; 			/*re init*/
		if(level == 1)
			random1 = rand()%4;
		else
			random1 = rand()%4;
		if(hit_check1<0)				/*if hit_check=0, you didn't touch Nth button --> status MISS ---> Score is decreased */
			score-=10;
		hit_check1 = 0;             /*re init */
	}
	
	if(level == 1)   /*level is associate with timer2 handler */
	{
		MAKE_NOTE(start_x2,random2,hit_check2,0x7c00) /*different kind Note is made*/
		if(start_x2 < -SIZE_OF_BUMB)
		{
			start_x2 =  480;
			if(random1 == 3)
				random2 = 0;
			else
				random2 = rand()%4;
			if(hit_check2<0)
				score-=10;
			hit_check2 = 0;
		}
	}

	rINTMSK1 &= ~BIT_TIMER1;
}

void timer2_handler(void)
{
	rINTMSK1 |= BIT_TIMER2;
	
	rSRCPND1 |= BIT_TIMER2;
	rINTPND1 |= BIT_TIMER2;
	int d_min,d_sec = 0;
	/*time*/
	d_min = (rBCDMIN & 0xf) + 10 * ((rBCDMIN>> 4) & 0x7);
	d_sec = (rBCDSEC & 0xf) + 10 * ((rBCDSEC >> 4) & 0x7);
	
	if(level == 0 && d_sec >= 7) /*after 7seconds level Up --> increase Note*/
	{
		level = 1;
		temp_start_x1 = start_x1;
		if(temp_start_x1 >= 240)
			start_x2 = 240+temp_start_x1;
		else
			start_x2 = 480+temp_start_x1;
	}
	if(score<-100)
	{
		game_over();
	}

	if(d_min==0 && d_sec==40)
	{
		game_over();
		my_clear=1;
	}

	Lcd_Printf(86,10,0xffff,fullscreen_buffer,"%02d:%02d",d_min,d_sec);	
	//Lcd_Printf(234,10,0xffff,fullscreen_buffer,"%s",ptr[2]);
	Lcd_Printf(394,10,0xffff,fullscreen_buffer,"%5d",score);
	
	rINTMSK1 &= ~BIT_TIMER2;
}

