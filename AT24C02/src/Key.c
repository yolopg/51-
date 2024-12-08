#include"Key.h"
#include"Delay.h"
#define KEY_PRESSED 0
#define KEY_RELEASE 1
//独立按键 P30到P33
sbit key1=P3^1;
sbit key2=P3^0;
sbit key3=P3^2;
sbit key4=P3^3;
unsigned char key()
{
    unsigned char keyNum=0;
    if(key1==0){delay(20);while(key1==0);delay(20); keyNum=1;}//开发板k1和k2反了
    if(key2==0){delay(20);while(key2==0);delay(20); keyNum=2;}
    if(key3==0){delay(20);while(key3==0);delay(20); keyNum=3;}
    if(key4==0){delay(20);while(key4==0);delay(20); keyNum=4;}
    return keyNum;
}
