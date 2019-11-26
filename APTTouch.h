/************************************************************************************************
** File:        APTTouch key demo source
** Description: Read Touch key value with IIC
** Pin define : SCL  ----  P3.6
**              SDA  ----  P3.5
**              INT  ----  P0.2
** Copyright 2014 Zilog Inc. ALL RIGHTS RESERVED.
*  
*************************************************************************************************/
#define      _APT8L16
#define      APT_SDA_HIGH         P3 |=0x20
#define      APT_SDA_LOW          P3 &=0xdf
#define      APT_SCL_HIGH		  P3 |=0x40
#define      APT_SCL_LOW		  P3 &=0xbf

#define      APT_SCL_PIN_INPUT	  P3CONH &=0xcf;P3PUR |=0x40   //P3.6 is SCL with internal pull-up
#define      APT_SCL_PIN_OUTPUT	  P3CONH |=0x30

#define		 APT_SDA_PIN_INPUT    P3CONH &=0xf3;P3PUR |=0x20   //P3.5 is SDA with internal pull-up
#define		 APT_SDA_PIN_OUTPUT   P3CONH |=0x0c

#define      APT_INT_PIN_INPUT    P1CONL &=0xCF;P1CONL |=0x10   //P1.2 is INT pin wirh internal pull-up

#define      READ_SDA_STATUS      P3&0x20         //Read SDA status
#define      PartAdd              0xac            //chip address

#define      GSR_ADD        0x20
#define      MCONL_ADD      0x21
#define      BUR_ADD        0x22
#define      K0ENB_ADD      0x23
#define      K1ENB_ADD      0x24
#define      SENSECON_ADD   0x25
#define      SENSES_ADD     0x26
#define      GSRA_ADD       0x27
#define      GSRB_ADD       0x28
#define      REFUTH_ADD     0x29
#define      KEYATH_ADD     0x2a
#define      DSMIT_ADD      0x2b
#define      MCONH_ADD      0x2c
#define      FILTER1_ADD    0x2d

#define      GSR            0x03    //5
#if defined (_APT8L08) 
#define      MCONL          0x50
#define      K1ENB          0xff
#define      KeyNumber      8
#endif
#if defined (_APT8L16)
#define      MCONL          0x00
#define      K1ENB          0x00
#define      KeyNumber      16
#endif
#if defined (_EFT4KVPowerBad)
#define      BUR            0x30
#else
#define      BUR            0x20
#endif
#define      K0ENB          0x00
#define      SENSECON       0x00
#define      SENSES         0x08
#define      GSRA           0x02
#define      GSRB           0x02
#define      REFUTH         0x04
#define      KEYATH         0x10
#define      DSMIT          0x04
#if defined (_LTouchnReset)
#define      MCONH          0x40
#else
#define      MCONH          0x00
#endif
#define      FILTER1        0x00

#define      EFT4KVPowerG   0x20
#define      EFT4KVPowerB   0x30
#define      LTouchReset    0x40
#define      LTouchnReset   0x00

unsigned char _Rom APTRegAdd[]={GSR_ADD,MCONL_ADD,BUR_ADD,K0ENB_ADD,K1ENB_ADD,SENSECON_ADD,SENSES_ADD,GSRA_ADD,GSRB_ADD,REFUTH_ADD,KEYATH_ADD,DSMIT_ADD,MCONH_ADD,FILTER1_ADD};
unsigned char _Rom APTRegData[]={GSR,   MCONL,    BUR,    K0ENB,    K1ENB,    SENSECON,    SENSES,    GSRA,    GSRB,    REFUTH,    KEYATH,    DSMIT,    MCONH,    FILTER1};

#if defined (_APT8L08)
unsigned char _Rom APTTouchSensingTab[8]={8,7,6,8,6,8,6,7};   //change with touch board
#endif

#if defined (_APT8L16)
//unsigned char _Rom APTTouchSensingTab[16]={8,7,6,8,6,8,6,7,6,6,6,6,6,6,6,6};  //change with touch board
unsigned char _Rom APTTouchSensingTab[16]={7,5,6,7,7,11,7,7,9,10,10,9,7,7,10,8};  //change with touch board
#endif

/*************************************************************************************
 *Note: If you want to get through CS10V,please add R=20K into each touch channel
 *************************************************************************************/

