#include <mega128.h>
#include <math.h>
#include <delay.h>

void main(void)

{


char key, oldkey, led;

DDRD=0b00000000; // PD2 �Է� ����            
DDRC=0b11111111; // PORTC ��� ����             
led=0b11111110;  // 0�� ��Ʈ�� on
PORTC=led;  // PORTC ���

oldkey = PIND & 0b00000100;
    
while(1){           // ���ѷ���(1) ����

while(led!=0b01111111)

{

key=PIND&0b00000100; 

if (oldkey!=0&&key==0)

{

PORTC=led; 
delay_ms(200);
led = (led<<1)|0x01; //1��Ʈ ����Ʈ

}
            
if(led==0b011111111)

{
led=0b01111111;
}
oldkey = key;
}
              
while(led!=0b11111110)
{
key=PIND&0b00000100; 

if (oldkey!=0&&key==0)
{
PORTC=led; 
delay_ms(200);
led = (led>>1) | 0x80;       //�ݴ�� ����Ʈ
}
             
if(led==0b11111110)

{

led=0b11111110;

}

oldkey = key;

}

}
    
}