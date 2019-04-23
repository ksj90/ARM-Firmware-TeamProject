/*
 * =====================================================================
 * NAME: 
 *       rtc.c
 *
 * Descriptions : 
 *       RTC Test Driver
 *
 * Developing Environment : 
 *       CodeWarrior 2.0 or Later
 *
 * =====================================================================
 */

#include "2450addr.h"
#include "my_lib.h"

void Rtc_Init(void)
{	
	rRTCCON  |= (0x1); 
	
	rRTCCON |= (0x1<<3);
	rRTCCON &= ~(0x1<<3);

	rBCDMIN  = 0x0;
	rBCDSEC  = 0x0; 

	rRTCCON  &= ~(0x1);
}

