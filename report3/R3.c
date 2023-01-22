#include <mega128.h>
#include <delay.h>

void main(void)
{
unsigned char led = 0xFF;
unsigned char led_bar = 0xFE;
  
DDRE=0b00000000; // PE7 �Է� ����       
DDRC=0b11111111; // PORTC ��� ����
PORTC=led_bar;  // ��Ʈ C�� led_bar �ʱⰪ ���
DDRA=0b00000001;  //PORTA ����
PORTA=led;     //��Ʈ A�� led �ʱⰪ ���
  
EIMSK=0b10000000;  // �ܺ� ���ͷ�Ʈ7 �ο��̺�
EICRB=0b01100000; // �ܺ� ���ͷ�Ʈ7 ��¿���
SREG=0b10000000;  // ���� ���ͷ�Ʈ �ο��̺�
  
while(1)

{

while(led_bar!=0x7F){
PORTC=led_bar; // ��Ʈ C�� ���
delay_ms(200);   // �ð� ����
led_bar<<=1;  // led ������ �� ����Ʈ
led_bar|=0x01;  // ����Ʈ �Ŀ� 0 ��Ʈ���� 0�� �ԷµǹǷ� '1'�� ��

}  // MSB�� ������ ���� ����

while(led_bar!=0xFE){

PORTC=led_bar; // ��Ʈ C�� ���
delay_ms(200);
led_bar>>=1;
led_bar|=0x80; // ����Ʈ �Ŀ� 7 ��Ʈ���� 0�� �ԷµǹǷ� 1�� ��
} 
 
}
} // �ܺ� ���ͷ�Ʈ7 ���� ��ƾ

interrupt[EXT_INT7]void external_int7(void)
{
char led,led_bar;     // ��������
PORTC=led_bar;        //bar_led ����
PORTA=led;
    
while((PINE&0b10000000)==0){     // ����ġ(INT7)�� �����ִ����� üũ

if(led_bar==0b01111111||led_bar==0b10111111||led_bar==0b11011111||led_bar==0b11101111){

PORTA=led;

led=0b00000000;

}   

}
           
}