#ifndef _LCD_H_
#define _LCD_H_

/************************************************************************************************
** File:        lcd.h
** Description: 
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
#ifndef __TYPES_H__
  #include "types.h"
#endif 
#include "lcd_sfr.h"

/*******************************
 *  VIM404 map
 *******************************/

#define SEGA                       (COM0 << 8)
#define SEGB                       (COM0 << 16)
#define SEGC                       (COM1 << 16)
#define SEGD                       (COM2 << 8)
#define SEGE                       (COM1 << 0)
#define SEGF                       (COM0 << 0)
#define SEGG                       (COM1 << 8)

#if 0
#define DIGIT_ADDR_1B1C1P          SEG1
#define DIGITI_ADDR_1D1G1A         SEG6
#define DIGIT_ADDR_1E1F            SEG5
#define DIGIT_ADDR_2B2C2P          SEG2
#define DIGITI_ADDR_2D2G2A         SEG8
#define DIGIT_ADDR_2E2F            SEG7
#define DIGIT_ADDR_3B3C3P          SEG3
#define DIGITI_ADDR_3D3G3A         SEG14
#define DIGIT_ADDR_3E3F            SEG9
#define DIGIT_ADDR_4B4C4P          SEG4
#define DIGITI_ADDR_4D4G4A         SEG16
#define DIGIT_ADDR_4E4F            SEG15
#else
#define DIGIT_ADDR_1B1C1P          SEG2
#define DIGITI_ADDR_1D1G1A         SEG7
#define DIGIT_ADDR_1E1F            SEG6
#define DIGIT_ADDR_2B2C2P          SEG3
#define DIGITI_ADDR_2D2G2A         SEG9
#define DIGIT_ADDR_2E2F            SEG8
#define DIGIT_ADDR_3B3C3P          SEG4
#define DIGITI_ADDR_3D3G3A         SEG13
#define DIGIT_ADDR_3E3F            SEG10
#define DIGIT_ADDR_4B4C4P          SEG5
#define DIGITI_ADDR_4D4G4A         SEG15
#define DIGIT_ADDR_4E4F            SEG14
#endif


#define LCD_On      LCON  |= LCD_CTRL
#define LCD_Off     LCON  &= ~LCD_CTRL

extern void lcdInit();
extern void lcdClear();
extern void lcdWriteDigit(UINT8 digit, UINT8 pos);
extern void lcdWriteChar(INT8 ch, UINT8 pos);
extern void lcdWriteUDecimal(UINT16 value);
extern void lcdWriteString(INT8 *pszString);
extern void lcdWriteHex(UINT16 value);

#endif //_LCD_H_