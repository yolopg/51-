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
void main()
{
    unsigned char KeyNum=0;
    unsigned int Num=0; //Á©×Ö½Ú
    LCD_Init();
    LCD_ShowNum(1,1,0,5);
    while (1)
    {
        KeyNum=key();
        if(KeyNum==1)
        {
            Num++;
            LCD_ShowNum(1,1,Num,5);
        }
        if(KeyNum==2)
        {
            Num--;
            LCD_ShowNum(1,1,Num,5);
        }
        if(KeyNum==3)
        {
            AT_24C02_WriteByte(0,Num%256);
            delay(5);
            AT_24C02_WriteByte(1,Num/256);
            LCD_ShowString(2,1,"Wirte Ok!");
            delay(1000);
            LCD_ShowString(2,1,"          ");
        }
        if(KeyNum==4)
        {
            Num=AT_24C02_ReadByte(0);
            Num|=AT_24C02_ReadByte(1)<<8;
            LCD_ShowNum(1,1,Num,5);
            LCD_ShowString(2,1,"Read Ok!");
            delay(1000);
            LCD_ShowString(2,1,"         ");
        }
    }
}