#ifndef _LCD_SFR_H_
#define _LCD_SFR_H_
/************************************************************************************************
** File:        lcd_sfr.h
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
* BE LIABLE FOR ANY SPECIAL, INCIDENTAL, OR CONSENTIAL DAMAGES OR ANY LIABILITY IN TORT,
* NEGLIGENCE, OR OTHER LIABILITY INCURRED AS A RESULT OF THE USE OF THE SOFTWARE, EVEN IF ZILOG 
* HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. ZILOG ALSO DOES NOT WARRANT THAT THE USE 
* OF THE SOFTWARE, OR OF ANY INFORMATION CONTAINED THEREIN WILL NOT INFRINGE ANY PATENT, 
* COPYRIGHT, OR TRADEMARK OF ANY THIRD PERSON OR ENTITY.
;
* THE SOFTWARE IS NOT FAULT-TOLERANT AND IS NOT DESIGNED, MANUFACTURED OR INTENDED FOR USE IN 
* CONJUNCTION WITH ON-LINE CONTROL IPMENT, IN HAZARDOUS ENVIRONMENTS, IN APPLICATIONS 
* RIRING FAIL-SAFE PERFORMANCE, OR WHERE THE FAILURE OF THE SOFTWARE COULD LEAD DIRECTLY TO 
* DEATH, PERSONAL INJURY OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE (ALL OF THE FOREGOING, 
* "HIGH RISK ACTIVITIES"). ZILOG SPECIFICALLY DISCLAIMS ANY EXPRESS OR IMPLIED WARRANTY TO HIGH 
* RISK ACTIVITIES.
*
************************************************************************************************/

/****************************
 *  LCON Bit Defintions
 ****************************/
#define LCD_CLK_SHIFT           6
#define LCD_CLK_MASK            (0x00 << LCD_CLK_SHIFT)
#define LCD_CLK_128HZ           (0x00 << LCD_CLK_SHIFT)
#define LCD_CLK_256HZ           (0x01 << LCD_CLK_SHIFT)
#define LCD_CLK_513HZ           (0x02 << LCD_CLK_SHIFT)
#define LCD_CLK_1024HZ          (0x03 << LCD_CLK_SHIFT)

#define LCD_DUTY_BIAS_SHIFT     3
#define LCD_DUTY_BIAS_MASK      (0x03 << LCD_DUTY_BIAS_SHIFT)
#define LCD_1_8DUTY_1_4BIAS     (0x00 << LCD_DUTY_BIAS_SHIFT)
#define LCD_1_4DUTY_1_3BIAS     (0x01 << LCD_DUTY_BIAS_SHIFT)
#define LCD_1_3DUTY_1_3BIAS     (0x02 << LCD_DUTY_BIAS_SHIFT)
#define LCD_1_3DUTY_1_2BIAS     (0x03 << LCD_DUTY_BIAS_SHIFT)
#define LCD_1_2DUTY_1_2BIAS     (0x04 << LCD_DUTY_BIAS_SHIFT)

#define LCD_BIAS_TYPE_SHIFT     1
#define LCD_BIAS_TYPE_MASK      (0x03 << LCD_BIAS_TYPE_SHIFT)
#define LCD_BIAS_INVALID        (0x00 << LCD_BIAS_TYPE_SHIFT)
#define LCD_BIAS_CAP            (0x01 << LCD_BIAS_TYPE_SHIFT)
#define LCD_BIAS_INTERNAL       (0x02 << LCD_BIAS_TYPE_SHIFT)
#define LCD_BIAS_EXTERNAL       (0x03 << LCD_BIAS_TYPE_SHIFT)

#define LCD_CTRL                (1 << 0)

/********************
 *  LCD RAM
 *******************/
#define LCD_RAM_PAGE            8
#define LCD_RAM_START           0x30
#define LCD_RAM_END             0x45
#define LCD_RAM_LEN             (LCD_RAM_END - LCD_RAM_START + 1)

#define SEG0                    0x30
#define SEG1                    0x31
#define SEG2                    0x32
#define SEG3                    0x33
#define SEG4                    0x34
#define SEG5                    0x35
#define SEG6                    0x36
#define SEG7                    0x37
#define SEG8                    0x38
#define SEG9                    0x39
#define SEG10                   0x3A
#define SEG11                   0x3B
#define SEG12                   0x3C
#define SEG13                   0x3D
#define SEG14                   0x3E
#define SEG15                   0x3F
#define SEG16                   0x40
#define SEG17                   0x41
#define SEG18                   0x42
#define SEG19                   0x43
#define SEG20                   0x44
#define SEG21                   0x45

#define COM0                    (1UL << 0)
#define COM1                    (1UL << 1)
#define COM2                    (1UL << 2)
#define COM3                    (1UL << 3)
#define COM4                    (1UL << 4)
#define COM5                    (1UL << 5)
#define COM6                    (1UL << 6)
#define COM7                    (1UL << 7)

#endif //_LCD_SFR_H