#include"REG52.H"
#include"I2C.h"
#include"AT24C02.h"
#define AT24C02_ADDRESS  0xA0
//内存：AT24C02 有 256 字节的存储空间，地址范围从 0x00 到 0xFF。
//设备地址：I2C 地址为 0xA0（写操作）和 0xA1（读操作），地址中的最低一位表示读写操作。
//向AT24C02中写入一个字节
void AT_24C02_WriteByte(unsigned char WorkAddress,unsigned char Data)
{
     unsigned char Ack;
    // 启动信号，开始通信
    I2C_Start();
    // 发送设备地址（AT24C02 地址）和写操作标志（0xA0 表示写操作）
    I2C_Send_Byte(AT24C02_ADDRESS);
    // 接收设备确认信号（ACK）
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0xFF;  // 错误状态，未收到 ACK
        return;
    }

    // 发送目标字节地址（WordAddress）
    I2C_Send_Byte(WorkAddress);
    // 接收地址确认信号（ACK）
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0x00;  // 错误状态，未收到 ACK
        return;
    }
    // 发送数据字节
    I2C_Send_Byte(Data);
    // 接收数据确认信号（ACK）
    Ack = I2C_ReceiveACK();
    if (Ack != 0)
    {
        P2 = 0x00;  // 错误状态，未收到 ACK
        return;
    }
    // 发送停止信号，结束通信
    I2C_Stop();
}

/*
AT24C02写入一个字节
WorkAddress 要写入字节的地址
Data 要写入的数据
*/
unsigned char AT_24C02_ReadByte(unsigned char WorkAddress)
{
    unsigned char Data;
    // 启动信号，开始通信
    I2C_Start();
    // 发送设备地址（AT24C02 地址）和写操作标志（0xA0 表示写操作）
    I2C_Send_Byte(AT24C02_ADDRESS);
    // 接收设备确认信号（ACK）
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0xFF;  // 错误状态，未收到 ACK
        return 0;
    }
    // 发送目标字节地址（WordAddress）
    I2C_Send_Byte(WorkAddress);
    // 接收地址确认信号（ACK）
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0x00;  // 错误状态，未收到 ACK
        return 0;
    }
    //连接成功

    // 发送重复启动信号，准备进行读取操作
    I2C_Start();
    // 发送设备地址（AT24C02 地址）和读操作标志（0xA1 表示读操作）
    I2C_Send_Byte(AT24C02_ADDRESS + 1);
    // 接收设备确认信号（ACK）
    if (I2C_ReceiveACK() != 0)
    {
        P2 = 0xFF;  // 错误状态，未收到 ACK
        return 0;
    }
    // 从 AT24C02 读取数据字节
    Data = I2C_ReceiveByte();
    // 发送 NACK 信号，结束读取
    I2C_NACK();
    // 停止信号，结束通信
    I2C_Stop();
    // 可以返回或处理读取的数据
    return Data;
}