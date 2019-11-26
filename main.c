/************************************************************************************************
** File:        main.c
** Description: The program initially display a key value and beep when touch happens.
				TA works as the 1KHz PWM to driver the buzzer. T1 works as the 1ms systick.
**              LVR dectection is at 2.3V as configured in the Project Settings-> FlashOption
**              SmartOptions
**          
**  S/W debug libray:
**              Due to the lack of an on-chip debugger, a software debug library(ISP_DbgR.lib)
**              was created and is included in this project. The library allows the ISP hardware
**              to interact with the ZDSII debugger and offers a limited debug features:
**                o Execute programb by a RESET+GO
**                o Halt program execution
**                o Insert S/W break by insert a call to the ISP debug breakpoint handler
**                o Examine ROM memory and disassembly windows plus the registers which are saved
**                  by the debug library at the upper programm memory after encountering a S/W 
**                  breakpoint or a user-request of CPU execution halt.
**              
**              Limitation:
**                o must be integrated with user's code
**                o part of the device resources are used as listed below:
**                   - program memory to hold the ISP Debug library, S/W breakpoints, and saved data.
**                   - stack
**                   - IRQ6 is used as a highest interrupt for the debug library
**                   - SDA and SCL pins 
**                o  Can not resume the execution after a breakpoint or a halt of CPU execution.
**                   The reason is that all the contents of the debug windows must be retrieved
**                   from the flash memory whose access requires a S3 reset before entering the 
**                   flash mode. Thus, program can be executed by a RESET+GO.
**                o  An insertion of a S/W breakpoint requires a the rebuild of project.
**             
**              Usage:
**                o The ISP_Dbg library provides two APIs(DBG_Init() and DBG_Break()) declared in the
**                  S3_ISP_Dbg.h
**                o The "DBG_Init()" API must be called usually at the start of the program.
**                o The "DBG_Break()" function can be used to trigger a S/W breakpoint. For example, 
**                  place the following breakpoint function call in any part of your program but
**                  after the DBG_Init() as shown:
**                           
**                           .............
**                           DBG_Break();       // S/W breakpoint
**                  
**                o  Breakpoint can also be inserted or removed by doublclicking on the left gutter 
**                   of the source editor or clicking on the HAND icon of the toolbar and the ZDS II 
**                   will automatically place or remove the S/W breakpoint instruction, "DBG_Break()"
**                   in the source code for you.
**                     
**                o  Clicking on the crossed-out hand icon instructs the ZDSII to remove all the S/W
**                   breakpoint instructions from source programs.
**    
**                
** Copyright 2014 Zilog Inc. ALL RIGHTS RESERVED.
*
*************************************************************************************************
* The source code in this file was written by an authorized Zilog employee or a licensed 
* consultant. The source code has been verified to the fullest extent possible. 
*
* Permission to use this code is granted on a royalty-free basis. However, users are cautioned to
* authenticate the code contained herein. 
* 
* ZILOG DOES NOT GUARANTEE THE VERACITY OF THIS SOFTWARE; ANY SOFTWARE CONTAINED HEREIN IS
* PROVIDED "AS IS." NO WARRANTIES ARE GIVEN, WHETHER EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
* IMPLIED WARRANTIES OF FITNESS FOR PARTICULAR PURPOSE OR MERCHANTABILITY. IN NO EVENT WILL ZILOG
* BE LIABLE FOR ANY SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES OR ANY LIABILITY IN TORT,
* NEGLIGENCE, OR OTHER LIABILITY INCURRED AS A RESULT OF THE USE OF THE SOFTWARE, EVEN IF ZILOG 
* HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. ZILOG ALSO DOES NOT WARRANT THAT THE USE 
* OF THE SOFTWARE, OR OF ANY INFORMATION CONTAINED THEREIN WILL NOT INFRINGE ANY PATENT, 
* COPYRIGHT, OR TRADEMARK OF ANY THIRD PERSON OR ENTITY.
;
* THE SOFTWARE IS NOT FAULT-TOLERANT AND IS NOT DESIGNED, MANUFACTURED OR INTENDED FOR USE IN 
* CONJUNCTION WITH ON-LINE CONTROL EQUIPMENT, IN HAZARDOUS ENVIRONMENTS, IN APPLICATIONS 
* REQUIRING FAIL-SAFE PERFORMANCE, OR WHERE THE FAILURE OF THE SOFTWARE COULD LEAD DIRECTLY TO 
* DEATH, PERSONAL INJURY OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE (ALL OF THE FOREGOING, 
* "HIGH RISK ACTIVITIES"). ZILOG SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY TO HIGH 
* RISK ACTIVITIES.
*
************************************************************************************************/

#include <s3.h>
#include "main.h"
#include "s3_flash_isp.h"
#include "APTTouch.h"
#include "S3SfrBits.h"
#include "lcd.h"
#include "utility.h"

/*smart option*/
_Rom unsigned char SMT1 _At 0x3C = 0xFF;
_Rom unsigned char SMT2 _At 0x3D = 0xFF;
_Rom unsigned char SMT3 _At 0x3E = 0xF8;	//normal vector
_Rom unsigned char SMT4 _At 0x3F = 0xBF;	//LVR 2.3V, internal 8MHz RCOsc

/*******************
 *  global variables
 */

unsigned short delayTick;

/*===============================================================================================
 * Function: delay
 * Description: simple delay routine
 *==============================================================================================*/
void delay()
{
   UINT32 i;
   for (i=0; i < 30000; i++);
}

/***
 * Function:     isr_timer1
 * Description:  The timer1 interrupt occurs approximately every 1ms. 
 *               When delayTime is greater than UPDADATE_DElay, the delayTick 
 *               is reset to zero and progStat is updated with RUN status.
 */
void interrupt isr_timer1()
{
   T1CON &= 0xFD;               // clear T1 interrupt pending
   delayTick++;                 // increate delay Tick
}

/***
 * Function:    init_timer1
 * Description: initialize timer 1 resources
 *              Timer interrupt occurs at approximately every 1ms.
 */
void init_timer1()
{
   IMR |= 0x08;                  // select IRQ3
   T1PS = 0x3;                   // divided by 8
   T1DATAL = TIMER_PERIOD;       // 1ms interval
   T1DATAH = TIMER_PERIOD >> 8;  //
   T1CON   = 0x38;               // interval mode
                                 // clear timer counter
                                 // T1 Match interrupt
   delayTick = 0;                
   
   SET_VECTOR(T1MTCH, isr_timer1);  // setup timer 1 interrupt vector
}


/***************************************************
 * APT touch source
 **************************************************/
void DelayUs(unsigned int nCount)
{ 
  for(; nCount != 0; nCount--);
}

void DelayMs(unsigned int nMs)
{
	for(;nMs!=0;nMs--)
	{
		DelayUs(100);
	}
}
/******************************************************************************
* APT Touch Start
******************************************************************************/
void  APTTouchStart(void)
{
   APT_SCL_PIN_OUTPUT;
   APT_SDA_PIN_OUTPUT;
   DelayUs(50);
   APT_SDA_HIGH;
   DelayUs(5);
   APT_SCL_HIGH;
   DelayUs(5);
   APT_SDA_LOW;
   DelayUs(5);
   APT_SCL_LOW;
   DelayUs(5);
}
/*******************************************************************************
* APT Touch Stop
********************************************************************************/
void  APTTouchStop(void)
{
   APT_SDA_LOW;
   DelayUs(5);
   APT_SCL_HIGH;
   DelayUs(5);
   APT_SDA_HIGH;
   DelayUs(5);
   APT_SCL_LOW;
   DelayUs(5);
}
/*******************************************************************************
*  APT Touch Key IIC communication ACK
********************************************************************************/
void  APTTouchWaitAck(void)
{
   unsigned char WaitTimeCnt;
	
   APT_SDA_PIN_INPUT;
   APT_SCL_HIGH;   
   WaitTimeCnt=10;

   do
     {
	  DelayUs(5);
	  WaitTimeCnt--;
	 }while((READ_SDA_STATUS)&&WaitTimeCnt);
   APT_SCL_LOW;
   APT_SDA_PIN_OUTPUT;
}
/*******************************************************************************
* APT Touch Key IIC Communication ACK
********************************************************************************/
void  APTTouchACK(void)
{
   APT_SDA_LOW;
   DelayUs(5);
   APT_SCL_HIGH;
   DelayUs(5);
   APT_SCL_LOW;
   DelayUs(5);
}
/*******************************************************************************
* APT Touch Key IIC Communication no ACK
********************************************************************************/
void  APTTouchNoACK(void)
{
   APT_SDA_HIGH;
   DelayUs(5);
   APT_SCL_HIGH;
   DelayUs(5);
   APT_SCL_LOW;
   DelayUs(5);
}
/*******************************************************************************
* APT Touch Key Write data
********************************************************************************/
void  APTTouchWriteData(unsigned char WrData)
{
   unsigned char  WrDataCnt;

   for(WrDataCnt=0;WrDataCnt<8;WrDataCnt++)
      {
		if(WrData&0x80)
		   APT_SDA_HIGH;
		else
		   APT_SDA_LOW;
		DelayUs(5);
		APT_SCL_HIGH;
        DelayUs(5);
		APT_SCL_LOW;
		WrData=WrData<<1;
	  }
}
/*******************************************************************************
* APT Touch Key Read data
********************************************************************************/
unsigned char  APTTouchReadData(void)
{
   unsigned char  RdDataCnt,RdData;

   APT_SDA_PIN_INPUT;
   RdData=0x00;
   for(RdDataCnt=0;RdDataCnt<8;RdDataCnt++)
      {
		   RdData=RdData<<1;
		   APT_SCL_HIGH;
           DelayUs(5);
		   if(READ_SDA_STATUS)
		     RdData=RdData|0x01;
		   APT_SCL_LOW;
		   DelayUs(5);
	    }
   APT_SDA_PIN_OUTPUT;

   return(RdData);
}
/*******************************************************************************
* APT Touch Key Write one data
********************************************************************************/
void  APTTouchWrOneData(unsigned char APTWrAdd,unsigned char APTWrData)
{
   APTTouchStart();
   APTTouchWriteData(PartAdd);
   APTTouchWaitAck();
   APTTouchWriteData(APTWrAdd);
   APTTouchWaitAck();
   APTTouchWriteData(APTWrData);
   APTTouchWaitAck();
   APTTouchStop();
}
/*******************************************************************************
* APT Touch Key Read one address data
********************************************************************************/
unsigned char  APTTouchRdOneData(unsigned char APTRdAdd)
{
   unsigned char APTRdData,APTBuffer;
	
   APTRdData=0;
   APTTouchStart();
   APTTouchWriteData(PartAdd);
   APTTouchWaitAck();
   APTTouchWriteData(APTRdAdd);
   APTTouchWaitAck();
   APTTouchStart();
   APTBuffer=PartAdd|0x01;
   APTTouchWriteData(APTBuffer);
   APTTouchWaitAck();
   APTRdData=APTTouchReadData();
   APTTouchNoACK();
   APTTouchStop();
   return APTRdData;
}
/*******************************************************************************
* Init GPIO for APT Touch Key ;     Set 1,enter chip set;
*                                   Set 0,exit chip set
********************************************************************************/
void  APTTouchChipSetInOut(unsigned char ChipSetInOut)
{
   unsigned char  ChipSetValueA,ChipSetValueB,TimeCnt;

   if(ChipSetInOut==1)
      ChipSetValueA=0x5a;   //chip stop
   else
      ChipSetValueA=0x00;   //exit stop mode
	 
	 TimeCnt=10;
   
   do
     {
	  APTTouchWrOneData(0x3a,ChipSetValueA);
	  DelayUs(5);
	  ChipSetValueB=APTTouchRdOneData(0x3a);
	  if(ChipSetValueB!=ChipSetValueA)
		{
	     DelayMs(20);
		 TimeCnt--;
		}
	 }while((ChipSetValueB!=ChipSetValueA)&&(TimeCnt!=0));
}
/*******************************************************************************
* Init APT Touch Key Reg;    
*                                   
********************************************************************************/
void  APTTouchChipRegSet(unsigned char ChipRegAdd,unsigned char ChipRegValueA)
{
   unsigned char  ChipRegValueB,TimeCnt;
	
	 TimeCnt=10;

   do
     {
	   APTTouchWrOneData(ChipRegAdd,ChipRegValueA);
	   DelayUs(5);
	   ChipRegValueB=APTTouchRdOneData(ChipRegAdd);
	   if(ChipRegValueB!=ChipRegValueA)
		 {
	     DelayMs(10);
		 TimeCnt--;
		 if(TimeCnt==0)
			return;
		 }
	 }while(ChipRegValueB!=ChipRegValueA);
}
/*******************************************************************************
* Init APT Touch chip;    
*                                   
********************************************************************************/
void APT8L16Init(void)
{
	unsigned char cnt,DataBuffer;
	
	APTTouchChipSetInOut(1);
	DelayMs(10);
	APTTouchChipSetInOut(0);
	DelayMs(10);
	
	APTTouchChipSetInOut(1);
	for(cnt=0;cnt<14;cnt++)
	{
		APTTouchChipRegSet(APTRegAdd[cnt],APTRegData[cnt]);
	}
	for(cnt=0;cnt<KeyNumber;cnt++)
	{
		APTTouchChipRegSet(cnt,APTTouchSensingTab[cnt]);
	}
	APTTouchChipSetInOut(0);
	DelayMs(300);
}
/*******************************************************************************
* Read APT Touch key value;    
*                                   
********************************************************************************/
void ScanAPTTouchKey(void)
{
	unsigned char TouchBuffer;
	INT16 KeyValue;
	
	TouchBuffer=APTTouchRdOneData(0x34);
	KeyValue=APTTouchRdOneData(0x35);
	KeyValue = (KeyValue<<8)+TouchBuffer;
	switch(KeyValue)
	{
		case 0x01:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('0', 4);
		     BUZZER_ON();
			 break;
		case 0x02:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('1', 4);
		     BUZZER_ON();
		     break;
		case 0x04:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('2', 4);
		     BUZZER_ON();
		     break;
		case 0x08:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('3', 4);
		     BUZZER_ON();
		     break;
		case 0x10:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('4', 4);
		     BUZZER_ON();
		     break;
		case 0x20:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('5', 4);
		     BUZZER_ON();
		     break;
		case 0x40:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('6', 4);
		     BUZZER_ON();
		     break;
		case 0x80:
			 lcdClear();
			 lcdWriteChar('0', 3);
             lcdWriteChar('7', 4);
		     BUZZER_ON();
		     break;
		case 0x100:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('0', 4);
		     BUZZER_ON();
		     break;
		case 0x200:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('1', 4);
		     BUZZER_ON();
		     break;
		case 0x400:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('2', 4);
		     BUZZER_ON();
		     break;
		case 0x800:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('3', 4);
		     BUZZER_ON();
		     break;
		case 0x1000:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('4', 4);
		     BUZZER_ON();
		     break;
		case 0x2000:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('5', 4);
		     BUZZER_ON();
		     break;
		case 0x4000:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('6', 4);
		     BUZZER_ON();
		     break;
		case 0x8000:
			 lcdClear();
			 lcdWriteChar('1', 3);
             lcdWriteChar('7', 4);
		     BUZZER_ON();
		     break;
		default:
			 lcdClear();
		     BUZZER_OFF();
		     break;
	}
}

/*-----------------------------------------------------------------------------------------
; Function      initBuzzer
; description:  setup Buzzer pin and watch timer to generate buzzer signal.
;-----------------------------------------------------------------------------------------*/
void initBuzzer()
{                    
	P4CONL |= 0x40;	//P43 as TAOUT
	
	TADATA = 8;	//1KHz
	TAPS = 6;	
	TACON = 0xE0; //0b11100000, PWM mode, stop, disable interrupt
}


/***
 * Function: main
 */
void main()
{   
   DI();

   /**
    * clock and WDT initialization
    */
   CLKCON = 0x18;           // System clock = fosc/1   
   //CLKCON = 0x08;           // System clock = fosc/8
   BTCON  = 0xA3;           // 0A3H, Disable WDT | fosc/4096 |clear BT |Clear Frediv   
   
   // Enable ZDS debugging of this application.
   // To trigger a ZDS breakpoint during program execution insert a "call
   // _DBG_Break" instruction into the application code, rebuild the project, 
   // and instruct ZDS to do a Reset+Go. 
   DBG_Init();
  
   init_timer1();
   initBuzzer();
   lcdInit();   
   APT8L16Init();
   EI();             // For ISP debugger support, IRQ6 is used and interrupt must be enabled.

   // main loop
   while(1)
   {	  
	  if(delayTick > 10)	//10ms
	   {
		   delayTick = 0;
		   ScanAPTTouchKey();
	   }
   }
}

