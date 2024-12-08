#ifndef _DISPLAY_H
#define _DISPLAY_H 

// 数码管显示相关
extern unsigned char Segment[];  // 数码管显示数字的段码数组

// 函数声明
void DisPlay_Scan(unsigned char num, unsigned char digit);  // 控制数码管显示数字
void DisPlay_SetBuf(unsigned char Location,unsigned char Number);
void DisPlay_Loop(void);
#endif
