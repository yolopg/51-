#ifndef _AT24C02_H
#define _AT24C02_H
//AT24C02 是一种 I2C 接口的 2Kb EEPROM，它的内存分为 256 个字节（地址范围是 0x00 到 0xFF）。
//你可以通过指定 字节地址 来选择要写入或读取的位置。
void AT_24C02_WriteByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT_24C02_ReadByte(unsigned char WorkAddress);
#endif