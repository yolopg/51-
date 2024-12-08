#include <REG52.H>
#include "display.h"  // 包含头文件
#include"Delay.h"
sbit P2_4=P2^4;
sbit P2_3=P2^3;
sbit P2_2=P2^2;
unsigned char DisPlay_Buf[9]={0,10,10,10,10,10,10,10,10};
// 7段数码管段选码数组：0-9
unsigned char Segment[] = {
    0x3F,  // 0 - abcdef_
    0x06,  // 1 - __bc___
    0x5B,  // 2 - ab_cd_ef
    0x4F,  // 3 - abc__def
    0x66,  // 4 - _bc__fg_
    0x6D,  // 5 - ab__def_
    0x7D,  // 6 - abcdef_
    0x07,  // 7 - __bc__g_
    0x7F,  // 8 - abcdefg_
    0x6F,   // 9 - ab_cd_fg_
    0x00, //不显示
    0x40
};


void DisPlay_SetBuf(unsigned char Location,unsigned char Number)
{
    if(Location<1||Location>8) return;
    DisPlay_Buf[Location]=Number;
}
// 数码管显示函数
// num: 数码管编号 (1 到 8)
// digit: 显示的数字 (0 到 9)
void DisPlay_Scan(unsigned char num, unsigned char digit)
{
    // 选择对应的数码管
    switch (num)
    {
        case 1:P2_4=1;P2_3=1;P2_2=1;break;
		case 2:P2_4=1;P2_3=1;P2_2=0;break;
		case 3:P2_4=1;P2_3=0;P2_2=1;break;
		case 4:P2_4=1;P2_3=0;P2_2=0;break;
		case 5:P2_4=0;P2_3=1;P2_2=1;break;
		case 6:P2_4=0;P2_3=1;P2_2=0;break;
		case 7:P2_4=0;P2_3=0;P2_2=1;break;
		case 8:P2_4=0;P2_3=0;P2_2=0;break;
    }
    // 显示数字
    P0 = Segment[digit];  // 将段选码送到 P0
}

void DisPlay_Loop(void)
{
   static unsigned char i=1;
   DisPlay_Scan(i,DisPlay_Buf[i]);
   i++;
   if(i>=9){i=1;};
}
