#include"Delay.h"

void delay(unsigned int Xms)		//@12.000MHz
{
	unsigned char i, j;
	while(Xms--)
	{
		i = 12;
		j = 169;
		do
		{
			while (--j);
		} while (--i);
	}
}
