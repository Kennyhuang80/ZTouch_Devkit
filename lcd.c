/************************************************************************************************
;** File:        lcd.asm
;** Description: include a LCD APIS to display data on a 7-segment LCD display, VIM-404
;**
;** Copyright 2014 Zilog Inc. ALL RIGHTS RESERVED.
;*
;*************************************************************************************************
;* The source code in this file was written by an authorized Zilog employee or a licensed 
;* consultant. The source code has been verified to the fullest extent possible. 
;*
;* Permission to use this code is granted on a royalty-free basis. However, users are cautioned to
;* authenticate the code contained herein. 
;* 
;* ZILOG DOES NOT GUARANTEE THE VERACITY OF THIS SOFTWARE; ANY SOFTWARE CONTAINED HEREIN IS
;* PROVIDED "AS IS." NO WARRANTIES ARE GIVEN, WHETHER EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
;* IMPLIED WARRANTIES OF FITNESS FOR PARTICULAR PURPOSE OR MERCHANTABILITY. IN NO EVENT WILL ZILOG
;* BE LIABLE FOR ANY SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES OR ANY LIABILITY IN TORT,
;* NEGLIGENCE, OR OTHER LIABILITY INCURRED AS A RESULT OF THE USE OF THE SOFTWARE, EVEN IF ZILOG 
;* HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. ZILOG ALSO DOES NOT WARRANT THAT THE USE 
;* OF THE SOFTWARE, OR OF ANY INFORMATION CONTAINED THEREIN WILL NOT INFRINGE ANY PATENT, 
;* COPYRIGHT, OR TRADEMARK OF ANY THIRD PERSON OR ENTITY.
;
;* THE SOFTWARE IS NOT FAULT-TOLERANT AND IS NOT DESIGNED, MANUFACTURED OR INTENDED FOR USE IN 
;* CONJUNCTION WITH ON-LINE CONTROL EQUIPMENT, IN HAZARDOUS ENVIRONMENTS, IN APPLICATIONS 
;* REQUIRING FAIL-SAFE PERFORMANCE, OR WHERE THE FAILURE OF THE SOFTWARE COULD LEAD DIRECTLY TO 
;* DEATH, PERSONAL INJURY OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE (ALL OF THE FOREGOING, 
;* "HIGH RISK ACTIVITIES"). ZILOG SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY TO HIGH 
;* RISK ACTIVITIES.
;*
;************************************************************************************************/
#include <s3.h>
#include "s3_flash_isp.h"
#include "lcd.h"
#include "utility.h"


#define SEGS(x)   ((x)>>16) \
                  ,((x)>>8) \
                  ,(x)
static const _Rom UINT8  Digit_AddrTable[4][3] =
{
   {DIGIT_ADDR_1B1C1P, DIGITI_ADDR_1D1G1A, DIGIT_ADDR_1E1F},
   {DIGIT_ADDR_2B2C2P, DIGITI_ADDR_2D2G2A, DIGIT_ADDR_2E2F},
   {DIGIT_ADDR_3B3C3P, DIGITI_ADDR_3D3G3A, DIGIT_ADDR_3E3F},
   {DIGIT_ADDR_4B4C4P, DIGITI_ADDR_4D4G4A, DIGIT_ADDR_4E4F}
};

typedef struct
{
   UINT8 segbc;
   UINT8 segadg;
   UINT8 segef;
}SEGMENTS;

static const _Rom SEGMENTS  Symbol_Table [] =
{
   { SEGS(SEGA|SEGB|SEGC|SEGD|SEGE|SEGF)},           /* Digit 0  */
   { SEGS(SEGB|SEGC)},                               /* Digit 1  */
   { SEGS(SEGA|SEGB|SEGD|SEGE|SEGG)},                /* Digit 2  */
   { SEGS(SEGA|SEGB|SEGC|SEGD|SEGG)},                /* Digit 3  */
   { SEGS(SEGB|SEGC|SEGF|SEGG)},                     /* Digit 4  */
   { SEGS(SEGA|SEGC|SEGD|SEGF|SEGG)},                /* Digit 5  */
   { SEGS(SEGA|SEGC|SEGD|SEGE|SEGF|SEGG)},           /* Digit 6  */
   { SEGS(SEGA|SEGB|SEGC)},                          /* Digit 7  */
   { SEGS(SEGA|SEGB|SEGC|SEGD|SEGE|SEGF|SEGG)},      /* Digit 8  */
   { SEGS(SEGA|SEGB|SEGC|SEGD|SEGF|SEGG)},           /* Digit 9  */
   { SEGS(SEGA|SEGB|SEGC|SEGE|SEGF|SEGG)},           /* Letter a */
   { SEGS(SEGC|SEGD|SEGE|SEGF|SEGG)},                /* Letter b */
   { SEGS(SEGA|SEGF|SEGE|SEGD)},                     /* Letter c */
   { SEGS(SEGB|SEGC|SEGD|SEGE|SEGG)},                /* Letter d */
   { SEGS(SEGA|SEGD|SEGE|SEGF|SEGG)},           	/* Letter e */
   { SEGS(SEGA|SEGE|SEGF|SEGG)},                     /* Letter F */

};

/*===============================================================================================
 * Function: lcdInit
 * Description: Initialize LCD Control registers and  LCD pins
 *==============================================================================================*/
void lcdInit()
{   
   P2CONL = 0xEA;              // P2[3:0] = LCD Alternative functions (NC, COM2, COM1, COM0)
   P2CONH = 0xAA;              // P2[7:4] = LCD Alternative functions (SEG4, SEG3, SEG2, SEG1)   
   P3CONL = 0xAA;              // P3[3:0] = LCD Alternative functions (SEG8, SEG7, SEG6, SEG5)
   P3CONH = 0xBE;              // P3[7:4] = LCD Alternative functions (SEG10, SCL, SDA, SEG9)
   P4CONL = 0x7A;              // P4[2:0] = LCD Alternative functions (BUZZ, NC, SEG12, SEG11)
   
   /*******
    * LCD clock = 256HZ
    * LCD duty = 1/3 
    * LCD bias = 1/3
    * LCD bias type = internal resistor
    * LCD ON
    */
    LCON  = (LCD_CLK_256HZ |  LCD_1_3DUTY_1_3BIAS | LCD_BIAS_INTERNAL | LCD_CTRL);

   // Select sub osc(32KHz),enable watch timer
    WTCON = 0x82;

   lcdClear();
}

/*===============================================================================================
 * Function: lcdClear
 * Description: clear the LCD display
 *==============================================================================================*/
void lcdClear()
{
   UINT8 _Page8* pLcdRam;
   
   pLcdRam = (UINT8 _Page8*)(LCD_RAM_START);
   while( pLcdRam != (UINT8 _Page8*)(LCD_RAM_END+1))
   {
      *pLcdRam++ = 0;
   }
   
   //display "----"
   *(UINT8 _Page8*)(LCD_RAM_START + 7) = 0x02;
   *(UINT8 _Page8*)(LCD_RAM_START + 9) = 0x02;
   //*(UINT8 _Page8*)(LCD_RAM_START + 13) = 0x02;
   //*(UINT8 _Page8*)(LCD_RAM_START + 15) = 0x02;

}

/*===============================================================================================
 * Function: lcdWriteChar ('0-'9' or 'a' - 'f')
 * Input:  ch    the character to be displayed at the requested position
 *         pos   the character position(1-4) in the LCD display
 *        
 *===============================================================================================*/
void lcdWriteChar(INT8  ch, UINT8 pos)
{   
   if(pos  <1 || pos >4)
      return;
   
   if( (ch >= '0') && (ch <= '9'))
      ch -= '0';
   else if( (ch >= 'a') && (ch <= 'f'))
      ch = ch- 'a' + 10;
   else if( (ch >= 'A') && (ch <= 'F'))
      ch = ch - 'A' + 10;
   else
      return;
   
   lcdWriteDigit(ch, pos);
}

/*===============================================================================================
 * Function: lcdWriteDigit (0-9 or a - f)
 * Input:  digigit the digiit to be displayed at the requested position
 *         pos      the digit position in the LCD display (1-4)
 *        
 *===============================================================================================*/
void lcdWriteDigit(UINT8  digit, UINT8 pos)
{   
   UINT8 _Page8* pLcdRam;
   UINT8 i;

   /* map position to an index of the Digit_AddrTable
    */
   pos -=1;
   for(i = 0; i < 3; i++)
   {
      pLcdRam = (UINT8 _Page8* ) Digit_AddrTable[pos][i];
      *pLcdRam = *(((_Rom UINT8*) &Symbol_Table[digit]) + i);
   }
    
}

/*===============================================================================================
 * Function: lcdWriteUDecimal
 * Input:    value contains the 16-bit decimal number in the range(0 to 9999)
 *           pos  the digit position in the LCD display (1-4)
 *        
 *===============================================================================================*/
void lcdWriteUDecimal(UINT16 value)
{
   INT8 buff[5], buff1[6], i;
   UINT8 buffLen;
   
   if(value > 9999 )
      value = 9999;    
   
   buffLen = intToDec(value, buff);
   
   for(i=buffLen-1; i >=0 ; i--)
   {
      lcdWriteChar(buff[i], i+1);
   } 
}

/*===============================================================================================
 * Function: lcdWriteHex
 * Input:    value  the 16-bit integer being displayed in hex format
 *===============================================================================================*/
void  lcdWriteHex(UINT16 value)
{
   INT8 i;
   UINT8 hexDigit;
   UINT8 skipZeroLeading = 1;
      
   for(i=0; i < 3; i++)
   {
      hexDigit = (value >> (12 - i*4)) & 0xF;
      if(skipZeroLeading && hexDigit)
         skipZeroLeading = 0;
      
      if(!skipZeroLeading)
         lcdWriteDigit(hexDigit, i+1);
   }
   lcdWriteDigit(value & 0xF, 4);
}

/*===============================================================================================
 * Function: lcdWriteString
 * Input:    pszString   the null terminated string to be displayed. If string length is greater 
 *                       than 4, it will be right-truncated.
 *===============================================================================================*/
void lcdWriteString(INT8 *pszString)
{
   UINT8 i=0;
   while(*pszString && i < 4)
   {
      lcdWriteChar(*pszString++, i++ + 1);
   }
}