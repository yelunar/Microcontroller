#include <mega128.h>        
#include <delay.h>
#include <stdlib.h>

#define LINE2    0xC0    // 2nd Line Move
#define HOME    0x02    // Cursor Home
#define RSHIFT    0x1C    // Display Right Shift
#define LSHIFT    0x18    // Display Left Shift
#define DISPON    0x0c     // Display On                       
#define DISPOFF    0x08    // Display Off
#define RCURSOR 0x14 // Cursor Right Shift
#define LCURSOR 0x10 // Cursor Left Shift
#define CURSOR_DISP 0x0E // Cursor display on
#define CURSOR_BLINK 0x0D // Cursor blink 

int N10=0, N1=0, num10=0, num1=0, num2=0, sum=0;

void LCD_init(void);
void LCD_String(char flash str[]);
void Busy(void);
void Command(unsigned char);
void Data(unsigned char);



unsigned char sw0_cnt = 0, sw1_cnt = 0;

void main(void){
DDRD = 0x00;
EIMSK = 0b00000011;
EICRA = 0b00001010;
SREG = 0b10000000;
LCD_init();
Command(HOME);
Command(CURSOR_BLINK);
while(1);
}




// LCD 초기화 함수 
void LCD_init(void)
{       
    DDRC = 0xFF;    // 포트 C 출력 설정
    PORTC &= 0xFB;    //E = 0;

    // 충분한 지연시간을 통한 안정화 과정                   
    delay_ms(15);    
    Command(0x20);    // D5=1
    delay_ms(5);
    Command(0x20);    // D5=1
    delay_us(100);
    Command(0x20);    // D5=1

    // 초기화 과정
    Command(0x28);    // function set
    Command(0x06);    // entry mode set
    Command(0x01);    // all clear
    Command(0x0c);    // display on
}

                 
// 인스트럭션 쓰기 함수
void Command(unsigned char byte)
{
    Busy();

    // 인스트럭션 상위 바이트
    PORTC = (byte & 0xF0);    // 데이터    
    PORTC &= 0xFE;        // RS = 0;           
    PORTC &= 0xFD;        // RW = 0;  
    delay_us(1);     
    PORTC |= 0x04;        // E = 1;
    delay_us(1);
    PORTC &= 0xFB;        // E = 0;

    // 인스트럭션 하위 바이트
    PORTC = ((byte<<4) & 0xF0);    // 데이터
    PORTC &= 0xFE;        // RS = 0;
    PORTC &= 0xFD;        // RW = 0;
    delay_us(1);         
    PORTC |= 0x04;        // E = 1;
    delay_us(1);
    PORTC &= 0xFB;        // E = 0;
}

// 문자열 출력 함수
void LCD_String(char flash str[])
{
    char flash *pStr=0;
    
    pStr = &str[0];    
    while(*pStr) Data(*pStr++);
}

// char flash : pointer declaration for program memory
// char eeprom : pointer declaration for EEPROM

//데이터 쓰기 함수
void Data(unsigned char byte)
{
    Busy();
        
    // 데이터 상위 바이트
    PORTC = (byte & 0xF0);    // 데이터
    PORTC |= 0x01;        //RS = 1;
    PORTC &= 0xFD;        //RW = 0;
    delay_us(1);         
    PORTC |= 0x04;        //E = 1;
    delay_us(1);
    PORTC &= 0xFB;        //E = 0;

    // 데이터 하위 바이트
    PORTC = ((byte<<4) & 0xF0);      // 데이터
    PORTC |= 0x01;        //RS = 1;
    PORTC &= 0xFD;        //RW = 0;     
    delay_us(1);         
    PORTC |= 0x04;        //E = 1;
    delay_us(1);
    PORTC &= 0xFB;        //E = 0;
}

// Busy Flag Check -> 일반적인 BF를 체크하는 것이 아니라
// 일정한 시간 지연을 이용한다.
void Busy(void)
{
    delay_ms(2);
}

interrupt [EXT_INT0] void menu(void){

LCD_init();
Command(HOME);
num1 = (char)(rand()%10);
LCD_String("a: ");
Data(0x30 +num1);
delay_ms(1);


}

interrupt [EXT_INT1] void enter(void){

 num2 = (char)(rand()%10);
 LCD_String("  b: ");
 Data(0x30 + num2);
 delay_ms(1);

 Command(LINE2);
 sum=num2+num1;
 LCD_String("a+b= ");
 N10 = sum/10;
 N1 = sum%10; 
 Data(0x30 + N10);
 Data(0x30 + N1);
 
 
 
 
  
}