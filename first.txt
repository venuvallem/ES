#include <lpc214x.h>
#define READ 0

void delay();

void main()
{
	unsigned int i = 0;
	IO0DIR = 0XFFFFFFFF;
	IO1DIR = 0X00;
	while(1)
	 {
		if((IO1PIN & (1<<16)) == READ)
		{
			for (i = 0; i < 8 ;i++)
			{
			IOSET0 |= (1<<i)  ;
			delay();
			IOCLR0 |= (1<<i);
			delay();
			}
	}
}
}
void delay()
{
 unsigned int i;
 for(i=0;i<30000;i++);
 }