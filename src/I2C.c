#include"REG52.H"
// I2C ���߳�ʼ��
sbit I2C_SCL=P2^1;
sbit I2C_SDA=P2^0;
//��ʼ�źţ�Start Condition����
//������ʾһ���µ����ݴ���Ŀ�ʼ�������������豸�����豸�������ͻ�������ݡ�
// ���� I2C �����ź�
void I2C_Start(void)
{
    I2C_SDA=1; //�� SDA ��Ϊ�ߵ�ƽ������״̬��
    I2C_SCL=1; //�� SCL ��Ϊ�ߵ�ƽ������״̬��
    I2C_SDA=0; // ���������ź� SDA �ɸߵ���
    I2C_SCL=0; // ���������ź� SCL ����
}
//ֹͣ�źţ�Stop Condition����
//������ʾ��ǰ�����ݴ����Ѿ�������ͨ�ſ��Թرա���Ҳ֪ͨ�����豸�����ݴ����Ѿ���ɡ�
// ���� I2C ֹͣ�ź�
void I2C_Stop(void)
{
    I2C_SDA=0;
    I2C_SCL=1;
    I2C_SDA=1;
}
//I2C Э���������Ǵ� ��λ����λ ���д���
// ����һ���ֽ�
void I2C_Send_Byte(unsigned char byte)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
    I2C_SDA=byte&(0x80>>i);  //���͸�λ
    I2C_SCL=1; // ʱ��������  ���ݱ�����
    I2C_SCL=0;  // ʱ���½��� 
    }
}

unsigned char I2C_ReceiveByte(void)
{
    unsigned char byte=0x00,i=0;
    I2C_SDA=1;//���ģʽ
    for(i=0;i<8;i++)
    {
        I2C_SCL=1; //ʱ��������
        //�� I2C ����Э���У�SDA �ϵĸߵ�ƽ��ʾ����λΪ 1���͵�ƽ��ʾ����λΪ 0
        if(I2C_SDA){byte|=(0x80>>i);} //����Ӧ��λ����Ϊ 1�����δӸ�λ����λ���� byte
        I2C_SCL=0;
    }
    return byte;
}
//ACK / NACK�� 
//�����豸���ÿ���ֽڷ��� ACK��ȷ�ϣ��źţ����߷����豸�����Ƿ�ɹ����ա�
//������ɹ������� NACK����ȷ�ϣ���
//0ΪӦ��,1Ϊ��Ӧ��
void I2C_ACK()
{
    I2C_SDA = 0;  // ���� ACK��SDA ����
    I2C_SCL = 1;
    I2C_SCL = 0;
} 

void I2C_NACK(void)
{
    I2C_SDA = 1;  // ���� NACK��SDA ����
    I2C_SCL = 1;
    I2C_SCL = 0;
}
unsigned char I2C_ReceiveACK(void)
{
    unsigned char ackBit;

    // �� SDA ����Ϊ���룬׼�����մ��豸�� ACK �� NACK �ź�
    I2C_SDA = 1; // SDA ���ߣ�����Ϊ����ģʽ

    // ����ʱ�ӵ�������
    I2C_SCL = 1; // ���� SCL ��
    ackBit = I2C_SDA; // ��ȡ SDA ���ϵĵ�ƽ״̬

    I2C_SCL = 0; // ����ʱ�����ڣ����� SCL ��

    // ���� ACK��0������ NACK��1��
    return ackBit; // ackBit Ϊ 0 ʱ��ʾ ACK��ȷ�ϣ���Ϊ 1 ʱ��ʾ NACK����ȷ�ϣ�
}