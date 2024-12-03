#include"DS1302.h"

void DS1302_Init(void)
{
    //由于DS1302接电时，会将CE和SCLK置于高电平;
    DS1302_CE=0; //拉低CE 准备开始通信
    DS1302_SCLK=0; // 拉低SCLK 保证时钟信号的初始状态


       // 解除写保护，允许修改寄存器
    DS1302_WriteByte(0x8E, 0x00);  // 0x8E: WP 寄存器，0x00 解除写保护
    
    // 启动时钟，确保时钟开始计时
    DS1302_WriteByte(0x80, 0x00);  // 0x80: 秒数寄存器，0x00 表示启用时钟（去掉停止位）
}

void DS1302_WriteByte(unsigned char Command,unsigned char Data)
{
    unsigned char i;
    DS1302_CE=1; //拉高CE
    //拉高 CE 主要是为了 防止外部干扰。
    //在初始化阶段，CE 被拉高可以保证 DS1302 不会受到外部时钟或数据线上的任何信号影响。
    //先写入地址
    for(i=0;i<8;i++)
    {
    DS1302_IO=Command&(0x01<<i);
    DS1302_SCLK=1; //时序上升
    DS1302_SCLK=0; //时序下降
    }
    //再写入数据
    for(i=0;i<8;i++)
    {
    DS1302_IO=Data&(0x01<<i);
    DS1302_SCLK=1; //时序上升 //写发生在SCLK的上升沿
    DS1302_SCLK=0; //时序下降
    }
    DS1302_CE=0;
}

unsigned char DS1302_ReadByte(unsigned char Command)
{
    unsigned char i,Data=0x00;
    Command|=0x01;  //将指令或上0x01将最低位置1，转换为读指令;
    DS1302_CE=1;
    for(i=0;i<8;i++)
	{
		DS1302_IO=Command&(0x01<<i);   //先读指令
		DS1302_SCLK=0; //读发生在SCLK 的下降沿
		DS1302_SCLK=1; 
		//在这里，先将SCLK先置0，后置1，便于对SCLK一个凹凸位多次利用
	}
    for(i=0;i<8;i++)
    {
        DS1302_SCLK=1;
        DS1302_SCLK=0;
        
        if(DS1302_IO){Data|=(0x01<<i);} //判断指令是否为空 根据数据线上的电平进行读取数据
    }
    DS1302_CE=0;
    DS1302_IO=0;   //读取后需要将IO置为0，否则将会出现错误；
    return Data;
}

void DS1302_SetTime(DS1302_Time*time)
{
      // 设置时间之前解除写保护
    DS1302_WriteByte(DS1302_WP, 0x00);  // 解除写保护

    // 设置秒、分、时、日期、月、年等
    DS1302_WriteByte(DS1302_SECOND, time->second/10*16+time->second%10);  // 秒
    DS1302_WriteByte(DS1302_MINUTE, time->minute/10*16+time->hour%10);  // 分
    DS1302_WriteByte(DS1302_HOUR, time->hour/10*16+time->hour%10);    // 时
    DS1302_WriteByte(DS1302_DATE, time->date/10*16+time->date%10);    // 日期
    DS1302_WriteByte(DS1302_MONTH, time->month/10*16+time->month%10);   // 月
    DS1302_WriteByte(DS1302_YEAR, time->year/10*16+time->year%10);    // 年
    DS1302_WriteByte(DS1302_DAY, time->day/10*16+time->day%10);     // 星期几

    DS1302_WriteByte(DS1302_WP, 0x80);  // 恢复写保护
}

// 从 DS1302 读取时间
void DS1302_ReadTime(DS1302_Time* time)
{
    unsigned char tmp=0;
    tmp = DS1302_ReadByte(DS1302_SECOND);  //BCD码转十进制数
    time->second=tmp/16*10+tmp%16;
    tmp= DS1302_ReadByte(DS1302_MINUTE);  // 分
    time->minute=tmp/16*10+tmp%16;
    tmp  = DS1302_ReadByte(DS1302_HOUR);    // 时
    time->hour=tmp/16*10+tmp%16;
    tmp   = DS1302_ReadByte(DS1302_DATE);    // 日期
    time->date=tmp/16*10+tmp%16;
    tmp  = DS1302_ReadByte(DS1302_MONTH);   // 月
    time->month=tmp/16*10+tmp%16;
    tmp  = DS1302_ReadByte(DS1302_YEAR);    // 年
    time->year=tmp/16*10+tmp%16;
    tmp   = DS1302_ReadByte(DS1302_DAY);     // 星期几
    time->day=tmp/16*10+tmp%16;
}