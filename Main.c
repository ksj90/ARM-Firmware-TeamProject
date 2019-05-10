/*
 * =====================================================================
 * NAME         : Main.c
 *
 * Descriptions : Main routine for S3C2450
 *
 * IDE          : GCC-4.1.0
 *
 * Modification
 *	  
 * =====================================================================
 */
#include "./Images/BG2.H"
#include "./Images/START.H"
#include "./Images/RUN.H"
#include "./Images/SLIDE.H"
#include "./Images/ttt.h"
#include "./Images/tt.h"
#include "iis.c"
#include "sdi.c"
#include "buzzer.c"


#include "2450addr.h"
#include "my_lib.h"
#include "global_var.h"


#define UART0  0    

//16  color

#define BLACK	0x0000
#define WHITE	0xFFFF
#define BLUE	0x001F		//00000 00000 11111
#define GREEN	0x03E0		//00000 11111 00000
#define RED	    0x7C00			//11111 00000 00000


int random1 = 0;			//1st block rand var
int random2 = 0;			//2nd block rand var

int position = 0;		

int score = 0;				//current score

unsigned short (* Fb_ptr)[480];	//lcd0 buffer

int start_x1 = 480;			//block1 current Xposition
int start_x2 = 0;			//block2 current Xposition


int hit_check1 = 0;			//block1 hit check var
int hit_check2 = 0;			//block2 hit check var

int Miss=0;
int Perfect=0;
int my_clear;


int temp_start_x1 = 0;		//block1 & block2 distance store var
int temp_start_x2 = 0;

int level = 0;		//current game level var

char ptr[10][10] = {"PERFECT","MISS   ","       "};	//current lstatus

extern unsigned int fullscreen_buffer[272][480];
extern unsigned int clear_buffer[272][100];

void Main(void)
{
	MMU_Init();					/*driver init*/
	Uart_Init(115200);				
	Graphic_Init();
	SWITCH_Port_Init();
	Timer_Init();	
	Touch_Init();
	Buzzer_Init();

	Lcd_Select_Frame_Buffer(1);    
	Lcd_Draw_BMP(0, 0, tt);
	Lcd_Copy(1,0);
	Lcd_Select_Frame_Buffer(0);

	Lcd_Make_fullscreen_Buffer(0,0,ttt); /* in game screen save in buffer*/

	Lcd_Display_Frame_Buffer(0);	
}
	
void game_over(void)  /*timer over OR  -Score- less than -100*/
{
	static int first_score = 0;
	static int second_score = 0;
	static int third_score = 0;

	rTCON &= ~(0x1);			//timer stop
	rTCON &= ~(0x1<<8);
	rTCON &= ~(0x1<<12);
	
	rINTSUBMSK |= (0x1<<9);		//touch off
	rINTMSK1 |= (0x1<<31);
	
	if(my_clear==0)
	 Lcd_Puts_big(168,40,0xffff,fullscreen_buffer,"GAME OVER");
	else
	 Lcd_Puts_big(168,60,0x0000,fullscreen_buffer," CLEAR ");

	Lcd_Printf(198,126,0xFFFF,fullscreen_buffer,"PERFECT : %d",Perfect); /*Print Result*/
	Lcd_Printf(198,152,0xFFFF,fullscreen_buffer,"MISS : %d",Miss);
	Lcd_Printf(198,178,0xFFFF,fullscreen_buffer,"Score : %d",score);

	Miss=0;
	Perfect=0;
}
