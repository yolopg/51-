#include "REG52.H"
#include "LCD1602.h"
#include "DS1302.h"
#include "Delay.h"
#include "Key.h"
#include"Timer.h"
unsigned char count=0;
unsigned char flash=0;

DS1302_Time currentTime = {55,57,16,3,3,12,24};  // 初始时间
//2020/1/1/星期6/17:37:00/

void TimeShow()
{
    DS1302_ReadTime(&currentTime);  // 从 DS1302 读取当前时间
    
    LCD_ShowNum(1, 1, currentTime.year, 2);
    LCD_ShowString(1, 3, "-");
    LCD_ShowNum(1, 4, currentTime.month, 2);
    LCD_ShowString(1, 6, "-");
    LCD_ShowNum(1, 7, currentTime.date, 2);
    LCD_ShowNum(2, 1, currentTime.hour, 2);
    LCD_ShowString(2, 3, ":");
    LCD_ShowNum(2, 4, currentTime.minute, 2);
    LCD_ShowString(2, 6, ":");
    LCD_ShowNum(2, 7, currentTime.second, 2);
    LCD_ShowString(2, 10, "week:");
    LCD_ShowNum(2, 15, currentTime.day, 1);
}



void setlimit()
{
   // 年：2000-2099年
    if (currentTime.year > 99) { currentTime.year %= 100; }
    if (currentTime.year < 0) { currentTime.year = 99; }

    // 月：1-12月
    if (currentTime.month > 12) { currentTime.month %= 13; currentTime.month++; }
    if (currentTime.month < 1) { currentTime.month = 12; }

    // 日：分闰年二月，分大小月
    if (currentTime.year % 4 == 0) { // 闰年二月 1-29号
        if (currentTime.month == 2) {
            if (currentTime.date > 29) { currentTime.date %= 30; currentTime.date++; }
            if (currentTime.date < 1) { currentTime.date = 29; }
        }
    }

    if (currentTime.year % 4 != 0) { // 不是闰年的二月 1-28号
        if (currentTime.month == 2) {
            if (currentTime.date > 28) { currentTime.date %= 29; currentTime.date++; }
            if (currentTime.date < 1) { currentTime.date = 28; }
        }
    }

    // 大月: 1,3,5,7,8,10,12 1-31号
    if (currentTime.month == 1 || currentTime.month == 3 || currentTime.month == 5 ||
        currentTime.month == 7 || currentTime.month == 8 || currentTime.month == 10 || currentTime.month == 12) {
        if (currentTime.date > 31) { currentTime.date %= 32; currentTime.date++; }
        if (currentTime.date < 1) { currentTime.date = 31; }
    }

    // 小月：4,6,9,11 1-30号
    if (currentTime.month == 4 || currentTime.month == 6 || currentTime.month == 9 || currentTime.month == 11) {
        if (currentTime.date > 30) { currentTime.date %= 31; currentTime.date++; }
        if (currentTime.date < 1) { currentTime.date = 30; }
    }

    // 时钟 0-23
    if (currentTime.hour > 23) { currentTime.hour %= 24; }
    if (currentTime.hour < 0) { currentTime.hour = 23; }

    // 分钟 0-59
    if (currentTime.minute > 59) { currentTime.minute %= 60; }
    if (currentTime.minute < 0) { currentTime.minute = 59; }

    // 秒钟 0-59
    if (currentTime.second > 59) { currentTime.second %= 60; }
    if (currentTime.second < 0) { currentTime.second = 59; }

    // 星期 1-7
    if (currentTime.day > 7) { currentTime.day %= 7; }
    if (currentTime.day < 1) { currentTime.day = 7; }
}


void num_flash() {
    if (count == 0) {
        if (flash == 0) {
            LCD_ShowString(1, 1, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(1, 1, currentTime.year, 2);
        }
        LCD_ShowNum(2, 15, currentTime.day, 1); //始终显示week
    }
    if (count == 1) {
        if (flash == 0) {
            LCD_ShowString(1, 4, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(1, 4, currentTime.month, 2);
        }
        LCD_ShowNum(1, 1, currentTime.year, 2); //始终显示年
    }
    if (count == 2) {
        if (flash == 0) {
            LCD_ShowString(1, 7, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(1, 7, currentTime.date, 2);
        }
        LCD_ShowNum(1, 4, currentTime.month, 2); //始终显示月份
    }
    if (count == 3) {
        if (flash == 0) {
            LCD_ShowString(2, 1, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(2, 1, currentTime.hour, 2);
        }
        LCD_ShowNum(1, 7, currentTime.date, 2);
    }
    if (count == 4) {
        if (flash == 0) {
            LCD_ShowString(2, 4, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(2, 4, currentTime.minute, 2);
        }
        LCD_ShowNum(2, 1, currentTime.hour, 2);
    }
    if (count == 5) {
        if (flash == 0) {
            LCD_ShowString(2, 7, "  ");
        }
        if (flash != 0) {
            LCD_ShowNum(2, 7, currentTime.second, 2);
        }
        LCD_ShowNum(2, 4, currentTime.minute, 2);
    }
    if (count == 6) {
        if (flash == 0) {
            LCD_ShowString(2, 15, " ");
        }
        if (flash != 0) {
            LCD_ShowNum(2, 15, currentTime.day, 1);
        }
        LCD_ShowNum(2, 7, currentTime.second, 2);
    }
}
//定时500ms中断
void Timer0_ISR() interrupt 1
{	
	static int num=0;
	num++;
	TH0=0xfc;
	TL0=0x18;
	if(num==500)//每隔500ms闪烁一下
	{
		num=0;
		flash=!flash;	
	} 
}

void main()
{
    unsigned char keynum = 0;
    unsigned char mode = 0;
    LCD_Init();
    DS1302_Init();
    DS1302_SetTime(&currentTime);
    Timer0_Init();
    while (1) {
        keynum = key();
        if (keynum != 0) {
            if (keynum == 1) { // 选择位
                count++;
                if (count >= 7) {
                    count = 0;
                }
            }
            if (keynum == 2) { // 加一
                if (count == 0) { currentTime.year++; }
                else if (count == 1) { currentTime.month++; }
                else if (count == 2) { currentTime.date++; }
                else if (count == 3) { currentTime.hour++; }
                else if (count == 4) { currentTime.minute++; }
                else if (count == 5) { currentTime.second++; }
                setlimit();
                DS1302_SetTime(&currentTime);
            }
            if (keynum == 3) { // 减一
                if (count == 0) { currentTime.year--; }
                else if (count == 1) { currentTime.month--; }
                else if (count == 2) { currentTime.date--; }
                else if (count == 3) { currentTime.hour--; }
                else if (count == 4) { currentTime.minute--; }
                else if (count == 5) { currentTime.second--; }
                setlimit();
                DS1302_SetTime(&currentTime);
            }
            if (keynum == 4) { // 设置时间和走时显示切换
                mode = !mode;
            }
        }

        if (mode == 0) { // 走时模式
            DS1302_ReadTime(&currentTime);
            TimeShow();
        }
        if (mode == 1) { // 设置时间模式
            num_flash();
        }
    }
  
}
