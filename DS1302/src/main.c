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
#include"DS1302.h"
#include"Delay.h"
unsigned char BCDToDecimal(unsigned char bcd)
{
    return ((bcd>>4))*10+(bcd&0x0F);  //&0x0F &0xF0 
}
// 定义时间结构体变量
DS1302_Time current_time = {0x00, 0x37, 0x17, 0x06, 0x01, 0x01, 0x20};  // 0秒，37分，17时，星期六，1号，1月，20年
void main()
{
    LCD_Init();
    DS1302_Init();
    DS1302_SetTime(&current_time);  // 设置初始时间
    LCD_ShowString(1, 1, "Current Time:");
    while(1)
    {
          // 定期读取当前时间
        DS1302_ReadTime(&current_time);  // 从 DS1302 读取当前时间
        
        // 显示小时
        LCD_ShowNum(2, 1, BCDToDecimal(current_time.hour), 2);  // 显示小时
        LCD_ShowString(2, 3, ":");

        // 显示分钟
        LCD_ShowNum(2, 4, BCDToDecimal(current_time.minute), 2);  // 显示分钟
        LCD_ShowString(2, 6, ":");

        // 显示秒钟
        LCD_ShowNum(2, 7, BCDToDecimal(current_time.second), 2);  // 显示秒钟
        delay(1000);
    }
}
