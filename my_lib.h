#ifndef _MY_LIB_H_
#define _MY_LIB_H_

#define LCD_SIZE_X (480)
#define LCD_SIZE_Y (272)

#define LCD_PUT_PIXEL(X,Y,COLOR) Fb_ptr[(Y)][(X)] = (unsigned short)(COLOR)

#define SIZE_OF_BUMB  10

//main.c
void game_over(void);

//libc.c
void MMU_Init(void);

//Uart.c 
void Uart_Init(int baud);
void Uart_Printf(char *fmt,...);
void Uart_Send_String(char *pt);
void Uart_Send_Byte(int data);
//char Uart_Get_Char(void);

//lcd_init.c
void Graphic_Init(void);
void Lcd_Port_Init(void);
void Lcd_Init(void);

// Lcd.c
void Lcd_Select_Frame_Buffer(unsigned int id);
void Lcd_Draw_BMP(int x, int y, const unsigned char *fp);
void Lcd_Display_Frame_Buffer(unsigned int id);
void Lcd_Set_Address(unsigned int fp);
void Lcd_Copy(unsigned int from, unsigned int to);

void Lcd_Printf(int x, int y, int color, unsigned int (* buffer)[480],char *fmt,...);
void Lcd_Puts(int x, int y, int color, unsigned int (* buffer)[480], char *str);
void Lcd_Puts_big(int x, int y, int color, unsigned int (* buffer)[480], char *str);
				
void Lcd_Make_fullscreen_Buffer (int x, int y, const unsigned char *fp);

//key.c
void SWITCH_Port_Init(void);
void EINT8_23_handler(void) __attribute__ ((interrupt ("IRQ")));;

//timer.c
void Timer_Init(void);
void Timer0_start(int msec);
void Timer1_start(int msec);
void Timer2_start(int msec);
void timer0_handler(void) __attribute__ ((interrupt ("IRQ")));;
void timer1_handler(void) __attribute__ ((interrupt ("IRQ")));;
void timer2_handler(void) __attribute__ ((interrupt ("IRQ")));;

//rtc.c
void Rtc_Init(void);

//touch.c
void Touch_Init(void);
void Touch_ISR(void) __attribute__ ((interrupt ("IRQ")));;


//mmu
void MMU_Init(void);
void MMU_SetMTT(int vaddrStart,int vaddrEnd,int paddrStart,int attr);

int  SET_IF(void);
void WR_IF(int cpsrValue);
void CLR_IF(void);

void MMU_EnableICache(void);
void MMU_DisableICache(void);
void MMU_EnableDCache(void);
void MMU_DisableDCache(void);
void MMU_EnableAlignFault(void);
void MMU_DisableAlignFault(void);
void MMU_EnableMMU(void);
void MMU_DisableMMU(void);
void MMU_SetTTBase(unsigned long base);
void MMU_SetDomain(unsigned long domain);

void MMU_SetFastBusMode(void);          //GCLK=HCLK
void MMU_SetAsyncBusMode(void);         //GCLK=FCLK @(FCLK>=HCLK)

void MMU_InvalidateIDCache(void);
void MMU_InvalidateICache(void);
void MMU_InvalidateICacheMVA(unsigned long mva);
void MMU_PrefetchICacheMVA(unsigned long mva);
void MMU_InvalidateDCache(void);
void MMU_InvalidateDCacheMVA(unsigned long mva);
void MMU_CleanDCacheMVA(unsigned long mva);
void MMU_CleanInvalidateDCacheMVA(unsigned long mva);
void MMU_CleanDCacheIndex(unsigned long index);
void MMU_CleanInvalidateDCacheIndex(unsigned long index); 
void MMU_WaitForInterrupt(void);
        
void MMU_InvalidateTLB(void);
void MMU_InvalidateITLB(void);
void MMU_InvalidateITLBMVA(unsigned long mva);
void MMU_InvalidateDTLB(void);
void MMU_InvalidateDTLBMVA(unsigned long mva);

void MMU_SetDCacheLockdownBase(unsigned long base);
void MMU_SetICacheLockdownBase(unsigned long base);

void MMU_SetDTLBLockdown(unsigned long baseVictim);
void MMU_SetITLBLockdown(unsigned long baseVictim);

void MMU_SetProcessId(unsigned long pid);
#endif
