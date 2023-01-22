#include <mega128.h>
#include <math.h>
#include <delay.h>

void main(void)

{


char key, oldkey, led;

DDRD=0b00000000; // PD2 입력 설정            
DDRC=0b11111111; // PORTC 출력 설정             
led=0b11111110;  // 0번 비트만 on
PORTC=led;  // PORTC 출력

oldkey = PIND & 0b00000100;
    
while(1){           // 무한루프(1) 시작

while(led!=0b01111111)

{

key=PIND&0b00000100; 

if (oldkey!=0&&key==0)

{

PORTC=led; 
delay_ms(200);
led = (led<<1)|0x01; //1비트 쉬프트

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
led = (led>>1) | 0x80;       //반대로 쉬프트
}
             
if(led==0b11111110)

{

led=0b11111110;

}

oldkey = key;

}

}
    
}