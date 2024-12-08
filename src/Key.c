#include"Key.h"
#include"Delay.h"
#define KEY_PRESSED 0
#define KEY_RELEASE 1
//独立按键 P30到P33
sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
unsigned char Key_KeyNumber;
unsigned char Key(void)
{
    unsigned char Temp=0;
    Temp=Key_KeyNumber;
    Key_KeyNumber=0;
    return Temp;
}
unsigned char key_GetState()
{
    unsigned char keyNum=0;
    if(key1==0){keyNum=1;}//开发板k1和k2反了
    if(key2==0){keyNum=2;}
    if(key3==0){keyNum=3;}
    if(key4==0){keyNum=4;}
    return keyNum;
}

void Key_Loop(void)
{
static unsigned char NowState,LastState; //记录按键状态
LastState=NowState;
NowState=Key_GetState();
if(LastState==1&&NowState==0)
{
    Key_KeyNumber=1;
}
if(LastState==2&&NowState==0)
{
    Key_KeyNumber=2;
}
if(LastState==3&&NowState==0)
{
    Key_KeyNumber=3;
}
if(LastState==4&&NowState==0)
{
    Key_KeyNumber=4;
}
}
