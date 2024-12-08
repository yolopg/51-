#ifndef _KEY_H_ 
#define _KEY_H_
#include"REG52.H"


//按下的键码,范围:0~4 无按键按下时返回0
unsigned char key();
void Key_Loop(void);
unsigned char key_GetState(void);
#endif