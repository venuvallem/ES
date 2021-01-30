#include<lpc214x.h>
#include<stdio.h>

unsigned char mydata ;
unsigned int i;
int flag=0;

void initPLL()
{
PLL0CON = 0x01 ; // Enable PLL
PLL0CFG = 0x24 ; // Set Up PLL for CClk = 60MHz
PLL0FEED = 0xAA; PLL0FEED = 0x55; // Apply Feed Sequence
while( PLL0STAT && 0x400 ==0 ); // Check Whether CCO
PLL0CON = 0x03; // Enable & Connect PLL
PLL0FEED = 0xAA; PLL0FEED = 0x55; // Apply Feed Sequence
}

void initserial(void)
{
PINSEL0 =0X05;
// P0.0 = TxD , P0.1 = RxD
U0LCR = 0XC3;
// DLAB(7) = 1 , 8 Bit UART (1,0) = 1,
U0DLL = 0X87;
// = 60 x 10^6 / (9600 x 16) = 391 = 0x0187
U0DLM = 0X01; // 9600 Baud
U0LCR = 0X03; // DLAB(7) = 0,8 Bit UART (1,0) = 1,
}

void sendserial(unsigned char serdata)
{
U0THR = serdata;
// Move data to be transmitted to U0THR
while((U0LSR & 0x40)==0);
// wait until THR Empty Flag is set.
}

unsigned char receiveserial(void)
{
while((U0LSR & 0x01)==0);
// wait until RBR Full Flag is set.
mydata = U0RBR ;
// Move data Received to U0THR
return mydata;
}

int main()
{
	initPLL();
IO0DIR|=(1<<2)|(1<<3)|(1<<4)|(1<<5);
while(1)
{
initserial();
mydata=receiveserial();
sendserial(mydata);
if(mydata=='1')
	i=2;
else if(mydata=='2')
	i=3;
else if(mydata=='3')
	i=4;
else if(mydata=='4')
	i=5;
IO0SET=(1<<i);
}
}
