#ifndef _AT24C02_H
#define _AT24C02_H
//AT24C02 ��һ�� I2C �ӿڵ� 2Kb EEPROM�������ڴ��Ϊ 256 ���ֽڣ���ַ��Χ�� 0x00 �� 0xFF����
//�����ͨ��ָ�� �ֽڵ�ַ ��ѡ��Ҫд����ȡ��λ�á�
void AT_24C02_WriteByte(unsigned char WordAddress,unsigned char Data);
unsigned char AT_24C02_ReadByte(unsigned char WorkAddress);
#endif