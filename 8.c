#include<lpc214x.h>
#include<stdio.h>

int main()
{
IO0DIR|=(1<<0)|(0<<1);
while(1)
{
if(IO0PIN==(1<<1))
{
IO0SET=(1<<0);
}
else
IO0CLR=(1<<0);
}
}
