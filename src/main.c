/**
 * *********************************************
 * 
 * 8051 blink demo
 * 
 * PIN: P11
 * 
 * *********************************************
*/

#include "REG52.H"
#include"LCD1602.h"
#include"Key.h" 
#include"AT24C02.h"
#include"Delay.h"
#include"Timer.h"
#include"DisPlay.h"
unsigned char KeyNum;
unsigned char min,sec,MiniSec,Runningflag;
void main()
{
    Timer0_Init();
    while (1)
    {
       KeyNum=key();
       if(KeyNum==1)
       {
        Runningflag=!Runningflag;
       }
       if(KeyNum==2)
       {
        MiniSec=0;
        min=0;
        sec=0;
       }
       if (KeyNum==3)
       {
        AT_24C02_WriteByte(0,min);
        delay(5);
        AT_24C02_WriteByte(1,sec);
        delay(5);
        AT_24C02_WriteByte(2,MiniSec);
        delay(5);
       }
       if(KeyNum==4)
       {
        min=AT_24C02_ReadByte(0);
        sec=AT_24C02_ReadByte(1);
        MiniSec=AT_24C02_ReadByte(2);
       }
         DisPlay_SetBuf(1,min/10);
         DisPlay_SetBuf(2,min%10);
         DisPlay_SetBuf(3,11);
         DisPlay_SetBuf(4,sec/10);
         DisPlay_SetBuf(5,sec%10);
         DisPlay_SetBuf(6,11);
         DisPlay_SetBuf(7,MiniSec/10);
         DisPlay_SetBuf(8,MiniSec%10);
   }
}

void Sec_Loop(void)
{
    if(Runningflag)
    {
    MiniSec++;
    if(MiniSec>=100)
    {
        MiniSec=0;
        sec++;
        if(sec>=60)
        {
            sec=0;
            min++;
            if(min>=60)
            {
                min=0;
            }
        }
    }
    }
}
void Time0_Routine()  interrupt 1
{
    static unsigned int T0Count1=0,T0Count2=0,T0Count3=0;
    TL0=0x18;
    TH0=0xFC;
    T0Count1++;
    if(T0Count1>=20)
    {
        T0Count1=0;
        Key_Loop(); 
    }
    T0Count2++;
    if(T0Count2>=2)
    {
        T0Count2=0;
        DisPlay_Loop();
    }
    T0Count3++;
    if(T0Count3>=10)
    {
        T0Count3=0;
        Sec_Loop();
    }
}