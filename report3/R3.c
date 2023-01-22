#include <mega128.h>
#include <delay.h>

void main(void)
{
unsigned char led = 0xFF;
unsigned char led_bar = 0xFE;
  
DDRE=0b00000000; // PE7 입력 설정       
DDRC=0b11111111; // PORTC 출력 설정
PORTC=led_bar;  // 포트 C에 led_bar 초기값 출력
DDRA=0b00000001;  //PORTA 설정
PORTA=led;     //포트 A에 led 초기값 출력
  
EIMSK=0b10000000;  // 외부 인터럽트7 인에이블
EICRB=0b01100000; // 외부 인터럽트7 상승에지
SREG=0b10000000;  // 전역 인터럽트 인에이블
  
while(1)

{

while(led_bar!=0x7F){
PORTC=led_bar; // 포트 C에 출력
delay_ms(200);   // 시간 지연
led_bar<<=1;  // led 변수의 좌 쉬프트
led_bar|=0x01;  // 쉬프트 후에 0 비트에는 0이 입력되므로 '1'로 셋

}  // MSB가 켜지면 루프 종료

while(led_bar!=0xFE){

PORTC=led_bar; // 포트 C에 출력
delay_ms(200);
led_bar>>=1;
led_bar|=0x80; // 쉬프트 후에 7 비트에는 0이 입력되므로 1로 셋
} 
 
}
} // 외부 인터럽트7 서비스 루틴

interrupt[EXT_INT7]void external_int7(void)
{
char led,led_bar;     // 변수선언
PORTC=led_bar;        //bar_led 설정
PORTA=led;
    
while((PINE&0b10000000)==0){     // 스위치(INT7)가 눌려있는지를 체크

if(led_bar==0b01111111||led_bar==0b10111111||led_bar==0b11011111||led_bar==0b11101111){

PORTA=led;

led=0b00000000;

}   

}
           
}