#ifndef _I2C_H_
#define _I2C_H_
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send_Byte(unsigned char byte);
unsigned char I2C_ReceiveByte(void);
void I2C_ACK();
unsigned char I2C_NACK(void);
unsigned char I2C_ReceiveACK(void);
#endif