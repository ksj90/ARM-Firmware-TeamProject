#include "2450addr.h"
#include <stdarg.h>
#include "my_lib.h"
#include "option.h"


void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
char Uart_Get_Char();

void Uart_Init(int baud)
{
	int pclk;
	pclk = PCLK;
	
	rGPHCON &= ~(0xf<<4);
	rGPHCON |= (0xa<<4);	

	
	rUFCON1 = 0x0;
	rUMCON1 = 0x0;
	
	rULCON1 = 0x3;

	rUCON1  = (1<<2)|(1);

	rUBRDIV1= ((unsigned int)(PCLK/16./baud+0.5)-1 );
}

void Uart_Printf(char *fmt,...)
{
    va_list ap;
    char string[256];

    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_Send_String(string);
    va_end(ap);		
}

void Uart_Send_String(char *pt)
{
	while(*pt)
	{
		Uart_Send_Byte(*pt++);			
	}	
}

void Uart_Send_Byte(int data)
{
	if(data=='\n')
	{
		while(!(rUTRSTAT1 & 0x2));
		WrUTXH1('\r');
	}
	while(!(rUTRSTAT1 & 0x2));	
	WrUTXH1(data);
}

char Uart_Get_Char()
{
	while(!(rUTRSTAT1 & 0x1));	
	return RdURXH1();
}
