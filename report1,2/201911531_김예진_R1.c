#include <mega128.h>  
#include <stdlib.h>
#include <math.h>
#include <delay.h>

void main(void)

{

char key, oldkey, led,led_all;

char position = 0;
char flag = 0;
PORTC = led;
DDRC = 0b11111111;
DDRD = 0b00000000; 

led = 0b11111111; 
oldkey = PIND & 0b00000100;

while(1){

key = PIND & 0b00000100;

if(oldkey!=0&&key==0)
{

flag=flag+1;

if(flag%2==1){

position = (char)(rand()%8);
PORTC = (char) pow(2, position)^0xFF;
}

else if(flag%2==0){
PORTC = (char) pow(2, position);

}
}
oldkey = key;
delay_ms(250);
}
}
