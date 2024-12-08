#include"REG52.H"
#include"I2C.h"
#include"AT24C02.h"
#define AT24C02_ADDRESS  0xA0
//�ڴ棺AT24C02 �� 256 �ֽڵĴ洢�ռ䣬��ַ��Χ�� 0x00 �� 0xFF��
//�豸��ַ��I2C ��ַΪ 0xA0��д�������� 0xA1��������������ַ�е����һλ��ʾ��д������
//��AT24C02��д��һ���ֽ�
void AT_24C02_WriteByte(unsigned char WorkAddress,unsigned char Data)
{
     unsigned char Ack;
    // �����źţ���ʼͨ��
    I2C_Start();
    // �����豸��ַ��AT24C02 ��ַ����д������־��0xA0 ��ʾд������
    I2C_Send_Byte(AT24C02_ADDRESS);
    // �����豸ȷ���źţ�ACK��
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0xFF;  // ����״̬��δ�յ� ACK
        return;
    }

    // ����Ŀ���ֽڵ�ַ��WordAddress��
    I2C_Send_Byte(WorkAddress);
    // ���յ�ַȷ���źţ�ACK��
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0x00;  // ����״̬��δ�յ� ACK
        return;
    }
    // ���������ֽ�
    I2C_Send_Byte(Data);
    // ��������ȷ���źţ�ACK��
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0x00;  // ����״̬��δ�յ� ACK
        return;
    }
    // ����ֹͣ�źţ�����ͨ��
    I2C_Stop();
}

/*
AT24C02д��һ���ֽ�
WorkAddress Ҫд���ֽڵĵ�ַ
Data Ҫд�������
*/
unsigned char AT_24C02_ReadByte(unsigned char WorkAddress)
{
    unsigned char Data;
    // �����źţ���ʼͨ��
    I2C_Start();
    // �����豸��ַ��AT24C02 ��ַ����д������־��0xA0 ��ʾд������
    I2C_Send_Byte(AT24C02_ADDRESS);
    // �����豸ȷ���źţ�ACK��
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0xFF;  // ����״̬��δ�յ� ACK
        return 0;
    }
    // ����Ŀ���ֽڵ�ַ��WordAddress��
    I2C_Send_Byte(WorkAddress);
    // ���յ�ַȷ���źţ�ACK��
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0x00;  // ����״̬��δ�յ� ACK
        return 0;
    }
    //���ӳɹ�

    // �����ظ������źţ�׼�����ж�ȡ����
    I2C_Start();
    // �����豸��ַ��AT24C02 ��ַ���Ͷ�������־��0xA1 ��ʾ��������
    I2C_Send_Byte(AT24C02_ADDRESS + 1);
    // �����豸ȷ���źţ�ACK��
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0xFF;  // ����״̬��δ�յ� ACK
        return 0;
    }
    // �� AT24C02 ��ȡ�����ֽ�
    Data = I2C_ReceiveByte();
    // ���� NACK �źţ�������ȡ
    I2C_NACK();
    // ֹͣ�źţ�����ͨ��
    I2C_Stop();
    // ���Է��ػ����ȡ������
    return Data;
}