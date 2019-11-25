/************************************************************************************************
;** File:        utility.c
;** Description: include the commonly-used routines utilized by other modules.
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
#include "utility.h"

/*=================================================================================
*  Subroutine: intToDec
*  inputs: RR0 the 16-bit integer value being converted to decimal string
*          R2  contains the address of the decimal string buffer
*  output: 
*         - the buffer pointed by RR2 is filled with the resulting decimal.
*         - return the string length in R3
*=================================================================================*/
UINT8 intToDec(UINT16 intVal, INT8* outBuff)
{
   INT8 *ptr = outBuff;
   UINT8 i, len;
   INT8 temp;
   UINT8 remainder;
   do
   {
      remainder = intVal % 10;
      intVal = intVal / 10;
      *ptr++ = remainder + 0x30;
   }while(intVal);
   
   *ptr = '\0';

   //reverse the string
  len = ptr - outBuff;
  for(i=0; i < len/2; i++)
  {
      temp = outBuff[i];
      outBuff[i] = outBuff[len-i-1];
      outBuff[len-i-1] = temp;
  }
  
  return len;
}