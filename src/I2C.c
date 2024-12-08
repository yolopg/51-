#include"REG52.H"
// I2C 总线初始化
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;
//起始信号（Start Condition）：
//用来表示一次新的数据传输的开始。它告诉所有设备，主设备即将发送或接收数据。
// 产生 I2C 启动信号
void I2C_Start(void)
{
    I2C_SDA=1; //将 SDA 设为高电平（空闲状态）
    I2C_SCL=1; //将 SCL 设为高电平（空闲状态）
    I2C_SDA=0; // 产生启动信号 SDA 由高到低
    I2C_SCL=0; // 结束启动信号 SCL 拉低
}
//停止信号（Stop Condition）：
//用来表示当前的数据传输已经结束，通信可以关闭。它也通知所有设备，数据传输已经完成。
// 产生 I2C 停止信号
void I2C_Stop(void)
{
    I2C_SDA=0;
    I2C_SCL=1;
    I2C_SDA=1;
}
//I2C 协议中数据是从 高位到低位 进行传输
// 发送一个字节
void I2C_Send_Byte(unsigned char byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
    I2C_SDA=byte&(0x80>>i);  //发送高位
    I2C_SCL=1; // 时钟上升沿  数据被采样
    I2C_SCL=0;  // 时钟下降沿 
    }
}

unsigned char I2C_ReceiveByte(void)
{
    unsigned char byte=0x00,i=0;
    I2C_SDA=1;//输出模式
    for(i=0;i<8;i++)
    {
        I2C_SCL=1; //时钟上升沿
        //在 I2C 总线协议中，SDA 上的高电平表示数据位为 1，低电平表示数据位为 0
        if(I2C_SDA){byte|=(0x80>>i);} //将对应的位设置为 1，依次从高位到低位存入 byte
        I2C_SCL=0;
    }
    return byte;
}
//ACK / NACK： 
//接收设备会对每个字节发送 ACK（确认）信号，告诉发送设备数据是否成功接收。
//如果不成功，返回 NACK（不确认）。
//0为应答,1为非应答
void I2C_ACK()
{
    I2C_SDA = 0;  // 发送 ACK，SDA 拉低
    I2C_SCL = 1;
    I2C_SCL = 0;
} 

void I2C_NACK(void)
{
    I2C_SDA = 1;  // 发送 NACK，SDA 拉高
    I2C_SCL = 1;
    I2C_SCL = 0;
}
unsigned char I2C_ReceiveACK(void)
{
    unsigned char ackBit;

    // 将 SDA 设置为输入，准备接收从设备的 ACK 或 NACK 信号
    I2C_SDA = 1; // SDA 拉高，设置为输入模式

    // 产生时钟的上升沿
    I2C_SCL = 1; // 拉高 SCL 线
    ackBit = I2C_SDA; // 读取 SDA 线上的电平状态

    I2C_SCL = 0; // 结束时钟周期，拉低 SCL 线

    // 返回 ACK（0）或者 NACK（1）
    return ackBit; // ackBit 为 0 时表示 ACK（确认），为 1 时表示 NACK（不确认）
}