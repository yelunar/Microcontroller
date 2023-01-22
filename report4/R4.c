#include <mega128.h>
#include <interrupt.h>
#include <delay.h>

unsigned char led  = 0xFF;
char flag;
char cnt;

void main(void)
{
   
       
DDRC = 0xFF;
PORTC = led;         
    
EIMSK = 0b00000011;
EICRA = 0b00001010;  
   
TIMSK = 0b00000100;
TCCR1A = 0b00000000;
TCCR1B = 0b00000101;

TCNT1 = 61629.75; 
       
ETIMSK = 0b00000100;
TCCR3A = 0b00000000;
TCCR3B = 0b00000101;

TCNT3H = 0x85; 
TCNT3L = 0xEE;
   
SREG = 0b10000000;  
   

while(1)
{

PORTC = led;    

if (led != 0x01)

{ 
PORTC = led;
}

else 
{ 

delay_ms(2000);

DDRC = 0;
}  
    
        
if (cnt==1)
{   

if (flag==0)
{ 
TIMSK = 0b00000100;
ETIMSK = 0b00000100;
} 

else if (flag==1)                                                                                                                                                                                 TIMSK = 0;
ETIMSK = 0;
} 
  
if (cnt==2)
{
DDRC = 0;
}     
} 
}
    
   
   
         
     
       




interrupt [TIM1_OVF] void timer_int1(void)
{
  TCNT1 = 61629.75;
  led = led ^ 0b00000001;
  PORTC = led; 
}


interrupt [TIM3_OVF] void timer_int3(void)
{
  TCNT3H = 0x85;  
  TCNT3L = 0xEE; 
  led = led & 0b11111110;
  led = (led<<1);
  PORTC = led;
  
}


interrupt [EXT_INT0] void sw(void)
{

if(((PIND & 0b00000001) == 0)){
cnt = 1;
flag = ++flag%2;
}
}



interrupt [EXT_INT1] void sw1(void)
{
 if(((PIND & 0b00000010) == 0))
 cnt = 2;
}