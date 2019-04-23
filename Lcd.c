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
#include <stdarg.h>
#include "2450addr.h"
#include "my_lib.h"
#include "global_var.h"

#include "./fonts/ENG8X16.H"
#include "./fonts/HAN16X16.H"
#include "./fonts/HANTABLE.H"




static unsigned char _first[]={0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
static unsigned char _middle[]={0,0,0,1,2,3,4,5,0,0,6,7,8,9,10,11,0,0,12,13,14,15,16,17,0,0,18,19,20,21};
static unsigned char _last[]={0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,0,17,18,19,20,21,22,23,24,25,26,27};
static unsigned char cho[]={0,0,0,0,0,0,0,0,0,1,3,3,3,1,2,4,4,4,2,1,3,0};
static unsigned char cho2[]={0,5,5,5,5,5,5,5,5,6,7,7,7,6,6,7,7,7,6,6,7,5};
static unsigned char jong[]={0,0,2,0,2,1,2,1,2,3,0,2,1,3,3,1,2,1,3,3,1,1};
#define LCD_XSIZE 		(480)	
#define LCD_YSIZE 		(272)



#define COPY(A,B) for(loop=0;loop<32;loop++) *(B+loop)=*(A+loop);
#define OR(A,B) for(loop=0;loop<32;loop++) *(B+loop)|=*(A+loop);


static unsigned short bfType;
static unsigned int bfSize;
static unsigned int bfOffbits;
static unsigned int biWidth, biWidth2;
static unsigned int biHeight;

static unsigned int Fbuf[2] = {0x33800000, 0x33c00000};

unsigned int fullscreen_buffer[272][480]; 	//background image buffer
unsigned int cookie_buffer[44][44]; 		//cookie image buffer
unsigned int slide_buffer[22][56];			//slide image buffer
unsigned int clear_buffer[272][100];

void Lcd_Printf1(int x, int y, int color, int bkcolor, int zx, int zy, char *fmt,...);
void Lcd_Put_Rvs_Pixel(int y,int x,int color)
{
    y = LCD_YSIZE-y;
	Fb_ptr[y][x] = (unsigned short int)color;	
}
void Lcd_Eng_Putch(int x,int y,int color,int bkcolor,int data, int zx, int zy)
{
	unsigned offset,loop;
	unsigned char xs,ys;
	unsigned char temp[32];
	unsigned char bitmask[]={128,64,32,16,8,4,2,1};     

	offset=(unsigned)(data*16);
	COPY(eng8x16+offset,temp);

	for(ys=0;ys<16;ys++)
	{
		for(xs=0;xs<8;xs++)
		{
			if(temp[ys]&bitmask[xs])
			{
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs,y+ys,color);
                    Lcd_Put_Rvs_Pixel(x+xs,y+ys,color);
                }
				else if( (zx==2)&&(zy==1) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+ys,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+ys,color);
				}
				else if( (zx==1)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+xs,y+2*ys,color);
					//Lcd_Put_Pixel(x+xs,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys+1,color);
				}
				else if( (zx==2)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+2*ys+1,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys,color);
					//Lcd_Put_Pixel(x+2*xs,y+2*ys,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys+1,color);
				}
			} 
			else
			{
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs,y+ys,bkcolor);
                    Lcd_Put_Rvs_Pixel(x+xs,y+ys,bkcolor);
                }
				else if( (zx==2)&&(zy==1) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+ys,bkcolor);
				}
				else if( (zx==1)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+xs,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+xs,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys+1,bkcolor);
				}
				else if( (zx==2)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+2*ys+1,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys+1,bkcolor);
				}	   	
			} 
		}
	}
}

void Lcd_Han_Putch(int x,int y,int color,int bkcolor, int data, int zx, int zy)
{
	unsigned int first,middle,last;	
	unsigned int offset,loop;
	unsigned char xs,ys;
	unsigned char temp[32];
	unsigned char bitmask[]={128,64,32,16,8,4,2,1};     

	first=(unsigned)((data>>8)&0x00ff);
	middle=(unsigned)(data&0x00ff);
	offset=(first-0xA1)*(0x5E)+(middle-0xA1);
	first=*(HanTable+offset*2);
	middle=*(HanTable+offset*2+1);
	data=(int)((first<<8)+middle);    

	first=_first[(data>>10)&31];
	middle=_middle[(data>>5)&31];
	last=_last[(data)&31];     

	if(last==0)
	{
		offset=(unsigned)(cho[middle]*640); 
		offset+=first*32;
		COPY(han16x16+offset,temp);

		if(first==1||first==24) offset=5120;  
		else offset=5120+704;
		offset+=middle*32;
		OR(han16x16+offset,temp);
	}
	else 
	{
		offset=(unsigned)(cho2[middle]*640); 
		offset+=first*32;
		COPY(han16x16+offset,temp);

		if(first==1||first==24) offset=5120+704*2; 
		else offset=5120+704*3;
		offset+=middle*32;
		OR(han16x16+offset,temp);

		offset=(unsigned)(5120+2816+jong[middle]*896);
		offset+=last*32;
		OR(han16x16+offset,temp);
	}

	for(ys=0;ys<16;ys++)
	{
		for(xs=0;xs<8;xs++)
		{
			if(temp[ys*2]&bitmask[xs])
			{
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs,y+ys,color);
                    Lcd_Put_Rvs_Pixel(x+xs,y+ys,color);
                }
				else if( (zx==2)&&(zy==1) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+ys,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+ys,color);
				}
				else if( (zx==1)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+xs,y+2*ys,color);
					//Lcd_Put_Pixel(x+xs,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys+1,color);
				}
				else if( (zx==2)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+2*ys+1,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys,color);
					//Lcd_Put_Pixel(x+2*xs,y+2*ys,color);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys+1,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys,color);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys+1,color);
				}
			}
			else
			{
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs,y+ys,bkcolor);
                    Lcd_Put_Rvs_Pixel(x+xs,y+ys,bkcolor);
                }
				else if( (zx==2)&&(zy==1) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+ys,bkcolor);
				}
				else if( (zx==1)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+xs,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+xs,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+xs,y+2*ys+1,bkcolor);
				}
				else if( (zx==2)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+2*xs,y+2*ys+1,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*xs+1,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*xs+1,y+2*ys+1,bkcolor);
				}	   	
			}
		}

		for(xs=0;xs<8;xs++)
		{
			if(temp[ys*2+1]&bitmask[xs])
			{
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs+8,y+ys,color);
                    Lcd_Put_Rvs_Pixel(x+xs+8,y+ys,color);
                }
				else if( (zx==2)&&(zy==1) ){
                    //Lcd_Put_Pixel(x+2*(xs+8),y+ys,color);
                    //Lcd_Put_Pixel(x+2*(xs+8)+1,y+ys,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+ys,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+ys,color);
                }
                else if( (zx==1)&&(zy==2) ){
                    //Lcd_Put_Pixel(x+(xs+8),y+2*ys,color);
                    //Lcd_Put_Pixel(x+(xs+8),y+2*ys+1,color);
                    Lcd_Put_Rvs_Pixel(x+(xs+8),y+2*ys,color);
                    Lcd_Put_Rvs_Pixel(x+(xs+8),y+2*ys+1,color);
                }
                else if( (zx==2)&&(zy==2) ){
                    //Lcd_Put_Pixel(x+2*(xs+8),y+2*ys+1,color);
                    //Lcd_Put_Pixel(x+2*(xs+8)+1,y+2*ys,color);
                    //Lcd_Put_Pixel(x+2*(xs+8),y+2*ys,color);
                    //Lcd_Put_Pixel(x+2*(xs+8)+1,y+2*ys+1,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+2*ys+1,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+2*ys,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+2*ys,color);
                    Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+2*ys+1,color);
                }
			}

			else
			{	   	
				if( (zx==1)&&(zy==1) ) {
                    //Lcd_Put_Pixel(x+xs+8,y+ys,bkcolor);
                    Lcd_Put_Rvs_Pixel(x+xs+8,y+ys,bkcolor);
                }
				else if( (zx==2)&&(zy==1) )
				{
					//Lcd_Put_Pixel(x+2*(xs+8),y+ys,bkcolor);
					//Lcd_Put_Pixel(x+2*(xs+8)+1,y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+ys,bkcolor);
				}
				else if( (zx==1)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+(xs+8),y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+(xs+8),y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+(xs+8),y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+(xs+8),y+2*ys+1,bkcolor);
				}
				else if( (zx==2)&&(zy==2) )
				{
					//Lcd_Put_Pixel(x+2*(xs+8),y+2*ys+1,bkcolor);
					//Lcd_Put_Pixel(x+2*(xs+8)+1,y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*(xs+8),y+2*ys,bkcolor);
					//Lcd_Put_Pixel(x+2*(xs+8)+1,y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+2*ys+1,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8),y+2*ys,bkcolor);
					Lcd_Put_Rvs_Pixel(x+2*(xs+8)+1,y+2*ys+1,bkcolor);
				}	   	
			}
		}
	}
}



void Lcd_Puts1(int x, int y, int color, int bkcolor, char *str, int zx, int zy)
{
     unsigned data;
   
     while(*str)
     {
        data=*str++;
        if(data>=128) 
        { 
             data*=256;
             data|=*str++;
             Lcd_Han_Putch(x, y, color, bkcolor, (int)data, zx, zy);
             x+=zx*16;
        }
        else 
        {
             Lcd_Eng_Putch(x, y, color, bkcolor, (int)data, zx, zy);
             x+=zx*8;
        }
     } 
} 



void Lcd_Printf1(int x, int y, int color, int bkcolor,int zx, int zy, char *fmt,...)
{
	va_list ap;
	char string[256];

	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	Lcd_Puts1(x, y, color, bkcolor, string, zx, zy);
	va_end(ap);
}



void Lcd_Copy(unsigned int from, unsigned int to)
{
	unsigned int i;

	for(i=0; i< (LCD_SIZE_X * LCD_SIZE_Y) ; i++)
	{
		*((unsigned short *)(Fbuf[to])+i) = *((unsigned short *)(Fbuf[from])+i);
	}
}

void Lcd_Select_Frame_Buffer(unsigned int id)
{
    	Fb_ptr = (unsigned short (*)[LCD_SIZE_X])Fbuf[id];
}

void Lcd_Display_Frame_Buffer(unsigned int id)
{
	Lcd_Set_Address(Fbuf[id]);
}

void Lcd_Set_Address(unsigned int fp)
{
	rVIDW00ADD0B0 = fp;					//滚欺林家 
	rVIDW00ADD1B0 = 0;					//辆丰林家 
	rVIDW00ADD2B0 = (0<<13)|((LCD_SIZE_X*4*2)&0x1fff);
	rVIDW00ADD1B0 = 0+(LCD_SIZE_X*LCD_SIZE_Y);	//农扁 
}

void Lcd_Draw_BMP(int x, int y, const unsigned char *fp)
{
	int xx=0, yy=0;	
	unsigned int tmp;
	unsigned char tmpR, tmpG, tmpB;
	
	bfType=*(unsigned short *)(fp+0);
	bfSize=*(unsigned short *)(fp+2);
	tmp=*(unsigned short *)(fp+4);
	bfSize=(tmp<<16)+bfSize;
	bfOffbits=*(unsigned short *)(fp+10);
	biWidth=*(unsigned short *)(fp+18);    
	biHeight=*(unsigned short *)(fp+22);    

	biWidth2=(bfSize-bfOffbits)/biHeight;	

	for(yy=0;yy<biHeight;yy++)
	{
		for(xx=0;xx<biWidth;xx++)
		{
			tmpB=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+0);
			tmpG=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+1);
			tmpR=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+2);
			tmpR>>=3;
			tmpG>>=3;
			tmpB>>=3;
			
			if(xx<biWidth2) LCD_PUT_PIXEL(x+xx,y+yy,(tmpR<<10)+(tmpG<<5)+(tmpB<<0));
		} 
	}   
}

void Lcd_Puts(int x, int y, int color, unsigned int (* buffer)[480], char *str)
{
    	unsigned data;
  	unsigned offset,loop;
	unsigned char xs,ys;
	unsigned char temp[32];
	unsigned char bitmask[]={128,64,32,16,8,4,2,1};   
	while(*str)
	{
		data=*str++;
		offset=(unsigned)(data*16);
		COPY(eng8x16+offset,temp);
		
		for(ys=0;ys<16;ys++)
		{
			for(xs=0;xs<8;xs++)
			{
				if(temp[ys]&bitmask[xs])
				{
					LCD_PUT_PIXEL(x+xs,y+ys,color);
				} 
				else
				{
					LCD_PUT_PIXEL(x+xs,y+ys,buffer[y+ys][x+xs]);
				} 
			}
		}
		x+=8;
	}
} 

void Lcd_Printf(int x, int y, int color, unsigned int (* buffer)[480],char *fmt,...)
{
	va_list ap;
	char string[256];

	va_start(ap,fmt);
	vsprintf(string,fmt,ap);
	Lcd_Puts(x, y, color, buffer, string);
	va_end(ap);
}

void Lcd_Puts_big(int x, int y, int color, unsigned int (* buffer)[480], char *str)
{
    unsigned data;
   	unsigned offset,loop;
	unsigned char xs,ys;
	unsigned char temp[32];
	unsigned char bitmask[]={128,64,32,16,8,4,2,1};     
	
    while(*str)
    {
		data=*str++;
        	offset=(unsigned)(data*16);
		COPY(eng8x16+offset,temp);
		
		for(ys=0;ys<16;ys++)
		{
			for(xs=0;xs<8;xs++)
			{
				if(temp[ys]&bitmask[xs])
				{
					LCD_PUT_PIXEL(x+2*xs,y+2*ys+1,color);
					LCD_PUT_PIXEL(x+2*xs+1,y+2*ys,color);
					LCD_PUT_PIXEL(x+2*xs,y+2*ys,color);
					LCD_PUT_PIXEL(x+2*xs+1,y+2*ys+1,color);
				}
				else
				{
					LCD_PUT_PIXEL(x+2*xs,y+2*ys+1,buffer[y+ys][x+xs]);
					LCD_PUT_PIXEL(x+2*xs+1,y+2*ys,buffer[y+ys][x+xs]);
					LCD_PUT_PIXEL(x+2*xs,y+2*ys,buffer[y+ys][x+xs]);
					LCD_PUT_PIXEL(x+2*xs+1,y+2*ys+1,buffer[y+ys][x+xs]);
				}	   	
			} 
		}
		x+=16;
	}	
} 

/*====================================================================================*/
/*====================================================================================*/
/*====================================================================================*/
/*====================================================================================*/
/*====================================================================================*/

#define MAKE_BUFFER(BUFFER) {\
	int xx=0, yy=0;\
	unsigned int tmp;\
	unsigned char tmpR, tmpG, tmpB;\
	bfType=*(unsigned short *)(fp+0);\
	bfSize=*(unsigned short *)(fp+2);\
	tmp=*(unsigned short *)(fp+4);\
	bfSize=(tmp<<16)+bfSize;\
	bfOffbits=*(unsigned short *)(fp+10);\
	biWidth=*(unsigned short *)(fp+18);\
	biHeight=*(unsigned short *)(fp+22);\
	biWidth2=(bfSize-bfOffbits)/biHeight;\
	for(yy=0;yy<biHeight;yy++)\
	{\
		for(xx=0;xx<biWidth;xx++)\
		{\
			tmpB=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+0);\
			tmpG=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+1);\
			tmpR=*(unsigned char *)(fp+bfOffbits+(biHeight-yy-1)*biWidth*3+xx*3+2);\
			tmpR>>=3;\
			tmpG>>=3;\
			tmpB>>=3;\
			if(xx<biWidth2)\
			{\
				(BUFFER)[y+yy][x+xx] = (unsigned short)((tmpR<<10)+(tmpG<<5)+(tmpB<<0));\
			}\
		}\
	}\
}
void Lcd_Make_fullscreen_Buffer (int x, int y, const unsigned char *fp)
{
	MAKE_BUFFER(fullscreen_buffer)
}
