//********************���������� ������� Siemens C75, ��75*******************
//           	  	������� ��������� LPH9157-2
//             		     132�176 ��������
//                   		  v 1.1
//                  Copyright (c) ����� ����� aka Igoryosha
//			  Website : lobotryasy.net 
//***************************************************************************

#include <delay.h>

//*************************************************************
//�������/������
#define CMD 0
#define DAT 1
char RS_old;
//*************************************************************

/* � ������� ���� ������� ������� �������� ������-����, �����-�������. 
����� - 5�8 ��������, �������� �� ����� ASCII. 
������� � ������ 0-31 � 128 - 191 ����������� �� �������������! */

flash unsigned char font_5x8[][5]  = {
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  32
0x00, 0x00, 0x5F, 0x00, 0x00,// !        33
0x00, 0x07, 0x00, 0x07, 0x00,// "        34
0x14, 0x7F, 0x14, 0x7F, 0x14,// #        35
0x24, 0x2A, 0x7F, 0x2A, 0x12,// $        36
0x23, 0x13, 0x08, 0x64, 0x62,// %        37
0x36, 0x49, 0x55, 0x22, 0x50,// &        38
0x00, 0x05, 0x03, 0x00, 0x00,// '        39
0x00, 0x1C, 0x22, 0x41, 0x00,// (        40
0x00, 0x41, 0x22, 0x1C, 0x00,// )        41
0x08, 0x2A, 0x1C, 0x2A, 0x08,// *        42
0x08, 0x08, 0x3E, 0x08, 0x08,// +        43
0x00, 0x50, 0x30, 0x00, 0x00,// ,        44
0x08, 0x08, 0x08, 0x08, 0x08,// -        45
0x00, 0x30, 0x30, 0x00, 0x00,// .        46
0x20, 0x10, 0x08, 0x04, 0x02,// /        47
0x3E, 0x51, 0x49, 0x45, 0x3E,// 0        48
0x00, 0x42, 0x7F, 0x40, 0x00,// 1        49
0x42, 0x61, 0x51, 0x49, 0x46,// 2        50
0x21, 0x41, 0x45, 0x4B, 0x31,// 3        51
0x18, 0x14, 0x12, 0x7F, 0x10,// 4        52
0x27, 0x45, 0x45, 0x45, 0x39,// 5        53
0x3C, 0x4A, 0x49, 0x49, 0x30,// 6        54
0x01, 0x71, 0x09, 0x05, 0x03,// 7        55
0x36, 0x49, 0x49, 0x49, 0x36,// 8        56
0x06, 0x49, 0x49, 0x29, 0x1E,// 9        57
0x00, 0x36, 0x36, 0x00, 0x00,// :        58
0x00, 0x56, 0x36, 0x00, 0x00,// ;        59
0x00, 0x08, 0x14, 0x22, 0x41,// <        60
0x14, 0x14, 0x14, 0x14, 0x14,// =        61
0x41, 0x22, 0x14, 0x08, 0x00,// >        62
0x02, 0x01, 0x51, 0x09, 0x06,// ?        63
0x32, 0x49, 0x79, 0x41, 0x3E,// @        64
0x7E, 0x11, 0x11, 0x11, 0x7E,// A        65
0x7F, 0x49, 0x49, 0x49, 0x36,// B        66
0x3E, 0x41, 0x41, 0x41, 0x22,// C        67
0x7F, 0x41, 0x41, 0x22, 0x1C,// D        68
0x7F, 0x49, 0x49, 0x49, 0x41,// E        69
0x7F, 0x09, 0x09, 0x01, 0x01,// F        70
0x3E, 0x41, 0x41, 0x51, 0x32,// G        71
0x7F, 0x08, 0x08, 0x08, 0x7F,// H        72
0x00, 0x41, 0x7F, 0x41, 0x00,// I        73
0x20, 0x40, 0x41, 0x3F, 0x01,// J        74
0x7F, 0x08, 0x14, 0x22, 0x41,// K        75
0x7F, 0x40, 0x40, 0x40, 0x40,// L        76
0x7F, 0x02, 0x04, 0x02, 0x7F,// M        77
0x7F, 0x04, 0x08, 0x10, 0x7F,// N        78
0x3E, 0x41, 0x41, 0x41, 0x3E,// O        79
0x7F, 0x09, 0x09, 0x09, 0x06,// P        80
0x3E, 0x41, 0x51, 0x21, 0x5E,// Q        81
0x7F, 0x09, 0x19, 0x29, 0x46,// R        82
0x46, 0x49, 0x49, 0x49, 0x31,// S        83
0x01, 0x01, 0x7F, 0x01, 0x01,// T        84
0x3F, 0x40, 0x40, 0x40, 0x3F,// U        85
0x1F, 0x20, 0x40, 0x20, 0x1F,// V        86
0x7F, 0x20, 0x18, 0x20, 0x7F,// W        87
0x63, 0x14, 0x08, 0x14, 0x63,// X        88
0x03, 0x04, 0x78, 0x04, 0x03,// Y        89
0x61, 0x51, 0x49, 0x45, 0x43,// Z        90
0x00, 0x00, 0x7F, 0x41, 0x41,// [        91
0x02, 0x04, 0x08, 0x10, 0x20,// "\"      92
0x41, 0x41, 0x7F, 0x00, 0x00,// ]        93
0x04, 0x02, 0x01, 0x02, 0x04,// ^        94
0x40, 0x40, 0x40, 0x40, 0x40,// _        95
0x00, 0x01, 0x02, 0x04, 0x00,// `        96
0x20, 0x54, 0x54, 0x54, 0x78,// a        97
0x7F, 0x48, 0x44, 0x44, 0x38,// b        98
0x38, 0x44, 0x44, 0x44, 0x20,// c        99
0x38, 0x44, 0x44, 0x48, 0x7F,// d        100
0x38, 0x54, 0x54, 0x54, 0x18,// e        101
0x08, 0x7E, 0x09, 0x01, 0x02,// f        102
0x08, 0x14, 0x54, 0x54, 0x3C,// g        103
0x7F, 0x08, 0x04, 0x04, 0x78,// h        104
0x00, 0x44, 0x7D, 0x40, 0x00,// i        105
0x20, 0x40, 0x44, 0x3D, 0x00,// j        106
0x00, 0x7F, 0x10, 0x28, 0x44,// k        107
0x00, 0x41, 0x7F, 0x40, 0x00,// l        108
0x7C, 0x04, 0x18, 0x04, 0x78,// m        109
0x7C, 0x08, 0x04, 0x04, 0x78,// n        110
0x38, 0x44, 0x44, 0x44, 0x38,// o        111
0x7C, 0x14, 0x14, 0x14, 0x08,// p        112
0x08, 0x14, 0x14, 0x18, 0x7C,// q        113
0x7C, 0x08, 0x04, 0x04, 0x08,// r        114
0x48, 0x54, 0x54, 0x54, 0x20,// s        115
0x04, 0x3F, 0x44, 0x40, 0x20,// t        116
0x3C, 0x40, 0x40, 0x20, 0x7C,// u        117
0x1C, 0x20, 0x40, 0x20, 0x1C,// v        118
0x3C, 0x40, 0x30, 0x40, 0x3C,// w        119
0x44, 0x28, 0x10, 0x28, 0x44,// x        120
0x0C, 0x50, 0x50, 0x50, 0x3C,// y        121
0x44, 0x64, 0x54, 0x4C, 0x44,// z        122
0x00, 0x08, 0x36, 0x41, 0x00,// {        123
0x00, 0x00, 0x7F, 0x00, 0x00,// |        124
0x00, 0x41, 0x36, 0x08, 0x00,// }        125
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  126
0x00, 0x00, 0x00, 0x00, 0x00,// (space)  127
0x7E, 0x11, 0x11, 0x11, 0x7E,// A        192
0x7F, 0x45, 0x45, 0x45, 0x39,// �        193
0x7F, 0x49, 0x49, 0x49, 0x36,// B        194
0x7F, 0x01, 0x01, 0x01, 0x03,// �        195
0xC0, 0x7E, 0x41, 0x7F, 0xC0,// �        196
0x7F, 0x49, 0x49, 0x49, 0x41,// E        197
119,8,127,8,119,             // �        198
34,73,73,73,54,              // �        199
127,32,16,8,127,             // �        200
127,32,19,8,127,             // �        201
0x7F, 0x08, 0x14, 0x22, 0x41,// K        202
64,62,1,1,127,               // �        203
0x7F, 0x02, 0x04, 0x02, 0x7F,// M        204
0x7F, 0x08, 0x08, 0x08, 0x7F,// H        205
0x3E, 0x41, 0x41, 0x41, 0x3E,// O        206
127,1,1,1,127,               // �        207
0x7F, 0x09, 0x09, 0x09, 0x06,// P        208
0x3E, 0x41, 0x41, 0x41, 0x22,// C        209
0x01, 0x01, 0x7F, 0x01, 0x01,// T        210
39,72,72,72,63,              // �        211
30,33,127,33,30,             // �        212
0x63, 0x14, 0x08, 0x14, 0x63,// X        213
127,64,64,127,192,           // �        214
15,16,16,16,127,             // �        215
127,64,124,64,127,           // �        216
127,64,124,64,255,           // �        217
1,127,72,72,48,              // �        218
127,72,48,0,127,             // �        219
127,72,72,72,48,             // �        220
34,73,73,73,62,              // �        221
127,8,62,65,62,              // �        222
118,9,9,9,127,               // �        223
0x20, 0x54, 0x54, 0x54, 0x78,// a        224
124, 84, 84, 84, 36,         // �        225
124, 84, 84, 84, 40,         // �        226
124, 4, 4, 4, 12,            // �        227
192, 120, 68, 124, 192,      // �        228
0x38, 0x54, 0x54, 0x54, 0x18,// e        229
108, 16, 124, 16, 108,       // �        230
40, 68, 84, 84, 40,          // �        231
124, 32, 16, 8, 124,         // �        232
124, 33, 18, 8, 124,         // �        233
124, 16, 16, 40, 68,         // �        234
64, 56, 4, 4, 124,           // �        235
124, 8, 16, 8, 124,          // �        236
124, 16, 16, 16, 124,        // �        237
0x38, 0x44, 0x44, 0x44, 0x38,// o        238
124, 4, 4, 4, 124,           // �        239
0x7C, 0x14, 0x14, 0x14, 0x08,// p        240
0x38, 0x44, 0x44, 0x44, 0x20,// c        241
4, 4, 124, 4, 4,             // �        242
0x0C, 0x50, 0x50, 0x50, 0x3C,// y        243
24, 36, 124, 36, 24,         // �        244
0x44, 0x28, 0x10, 0x28, 0x44,// x        245
124, 64, 64, 124, 192,       // �        246
12, 16, 16, 16, 124,         // �        247
124, 64, 120, 64, 124,       // �        248
124, 64, 120, 64, 252,       // �        249
124, 84, 80, 80, 32,         // �        250
124,80,32,0,124,             // �        251
124, 80, 80, 80, 32,         // �        252
40, 68, 84, 84, 56,          // �        253
124, 16, 56, 68, 56,         // �        254
72, 52, 20, 20, 124          // �        255
};

#ifdef _USE_SOFT_SPI
//===============================================================
//			        ����������� SPI
//===============================================================
void Send_spi(unsigned char data)
{ 

    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 128) == 128)   SetBit(LCD_PORT, LCD_DATA); 
    SetBit(LCD_PORT, LCD_CLK);
    ClearBit(LCD_PORT, LCD_CLK);  
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 64) == 64) SetBit(LCD_PORT, LCD_DATA); 
    SetBit(LCD_PORT, LCD_CLK);  
    ClearBit(LCD_PORT, LCD_CLK);
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 32) == 32) SetBit(LCD_PORT, LCD_DATA); 
    SetBit(LCD_PORT, LCD_CLK);  
    ClearBit(LCD_PORT, LCD_CLK); 
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 16) ==16)  SetBit(LCD_PORT, LCD_DATA);
    SetBit(LCD_PORT, LCD_CLK);   
    ClearBit(LCD_PORT, LCD_CLK);
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 8) == 8)   SetBit(LCD_PORT, LCD_DATA);
    SetBit(LCD_PORT, LCD_CLK);    
    ClearBit(LCD_PORT, LCD_CLK);   
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 4) == 4)   SetBit(LCD_PORT, LCD_DATA);
    SetBit(LCD_PORT, LCD_CLK);  
    ClearBit(LCD_PORT, LCD_CLK); 
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 2) == 2)   SetBit(LCD_PORT, LCD_DATA);
    SetBit(LCD_PORT, LCD_CLK); 
    ClearBit(LCD_PORT, LCD_CLK);
    ClearBit(LCD_PORT, LCD_DATA);
    if ((data & 1) == 1)   SetBit(LCD_PORT, LCD_DATA); 
    SetBit(LCD_PORT, LCD_CLK);  
    ClearBit(LCD_PORT, LCD_CLK);
}

#else // _USE_SOFT_SPI
//===============================================================
//			            ���������� SPI
//===============================================================
//void Send_spi(unsigned char data)
//{
//	//������� ������� SCK: F������/16
//    SPCR = (0<<SPIE)|(1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(0<<SPR1)|(1<<SPR0);	
//    SPDR = data;
//    while(!(SPSR & (1<<SPIF)));
//    SPCR = 0;
//}

#endif // _USE_SOFT_SPI

//===============================================================
//������� ������ �������/������ � LCD (RS==0 - �������, RS==1 - ������)
//===============================================================
void Send_to_lcd (unsigned char RS, unsigned char data)
{  
    ClearBit(LCD_PORT, LCD_CLK);
    ClearBit(LCD_PORT, LCD_DATA);
    if ((RS_old != RS) || (!RS_old && !RS)) //��������� ������ �������� RS 
    { 
        SetBit(LCD_PORT, LCD_CS);	// ��������� CS 
        if(RS)    SetBit(LCD_PORT, LCD_RS);
        else      ClearBit(LCD_PORT, LCD_RS);	
        ClearBit(LCD_PORT, LCD_CS);	// ����� CS 
    } 
 
    Send_spi (data); 
 
    RS_old=RS;  //���������� �������� RS	
    ClearBit(LCD_PORT, LCD_DATA);
}    

//===============================================================
//                        �������������
//===============================================================
void LCD_init(void)
{
 Init_Port();
 ClearBit(LCD_PORT, LCD_RESET);
 delay_ms(500);
 SetBit(LCD_PORT, LCD_RESET);
 delay_ms(500);
 Send_to_lcd(CMD, 0x01); //����������� �����
 Send_to_lcd(CMD, 0x36); //Memory Access Control (����������� ���������� ������� ������� (������): 0bVHRXXXXX, V - ���������� �� ��������� (0 - ������-����, 1 - �����-�����), 
                         //H - ���������� �� ����������� (0 - �����-�������, 1 - ������-������), R - �������� ������� ������ � ������� (��� ���� ���������� �������� ������-����, �����-�������))
 Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������
 Send_to_lcd(CMD, 0x11); //����� �� ������� ������
 delay_ms(20);
 Send_to_lcd(CMD, 0x3a); //��������� �������� �������
 #ifdef _8_BIT_COLOR
 Send_to_lcd(DAT, 0x02); //���� �� ������� 256 ������
 #else
 Send_to_lcd(DAT, 0x05); //��� ����� �� ������� 65536 ������
 #endif
 delay_ms(20);
 Send_to_lcd(CMD, 0x29); //��������� ������� 
}  

//===============================================================
//         ������� ���� �������� ������
//===============================================================
void SetRotation (unsigned int angle)
{
    rot=angle;
    Send_to_lcd(CMD, 0x36);
    switch (rot)
    {
        case 0:    
        Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������
        break;
        //================================
        case 90:
        Send_to_lcd(DAT, 0x40); //��������� ����� ���� � � � - ������ ������� ���� ������� 
        break;
        //================================
        case 180:       
        Send_to_lcd(DAT, 0xC0); //��������� ����� ���� � � � - ������ ������ ���� ������� 
        break;
        //================================
        case 270:
        Send_to_lcd(DAT, 0x80); //��������� ����� ���� � � � - ����� ������ ���� �������  
        break;
        //================================           
    };  
}    
  
//===============================================================
//              ������� ������������� ������� ������
//===============================================================
void SetArea(char x1, char x2, char y1, char y2)
{
    Send_to_lcd( CMD, 0x2A );  //������ ������� �� X
    Send_to_lcd( DAT, x1 );    //���������
    Send_to_lcd( DAT, x2 );    //��������

    Send_to_lcd( CMD, 0x2B );  //������ ������� �� Y
    Send_to_lcd( DAT, y1 );    //��������� 
    Send_to_lcd( DAT, y2 );    //��������

    Send_to_lcd( CMD, 0x2C );  //���������� ������� �� ������ ������ � ������ � �������� �������� ������
}                 

//===============================================================
//                        ������ ����� 
//=============================================================== 
void Put_Pixel (char x, char y, unsigned int color) 
{
    SetArea( x, x, y, y ); 
    SetBit(LCD_PORT, LCD_RS); //���������� ������   
 
    #ifdef _8_BIT_COLOR		//(8-�� ������� �������� ������� (256 ������))
    Send_to_lcd( DAT, color );	//������ - ����� ���� ������� 
    #else			        //(16-�� ������� �������� ������� (65536 ������))
    Send_to_lcd( DAT, (color >> 8) ); 
    Send_to_lcd( DAT, color );
    #endif
}  
                   
//===============================================================
//           ������� ���������� ������� �� �������
//===============================================================
void Send_Symbol (unsigned char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height) 
{
 unsigned char temp_symbol, a, b, zw, zh, mask; 
  
 if (symbol>127) symbol-=64;    //������� ������������� ����� ������� ASCII
 for ( a = 0; a < 5; a++) //��������� 5 ����, ������������ ������
 {
    temp_symbol = font_5x8[symbol-32][a];
    zw = 0; 
    while(zw != zoom_width) //����� ����� ����������� zw ��� 
    {    
        mask=0x01;  
        switch(rot)
        {
            case 0: case 180: SetArea( x+zw, x+zw, y, y+(zoom_height*8)-1 ); break;
            case 90: case 270: SetArea( x, x+(zoom_height*8)-1, y+zw, y+zw ); break;                  
        } 
        SetBit(LCD_PORT, LCD_RS); //���������� ������          
        for ( b = 0; b < 8; b++ ) //���� ����������� 8 ��� �����
        {         
            zh = zoom_height; //� zoom_height ��� ���������� ������ �������
            while(zh != 0) //����� ������� ����������� z ���
            {
                if (temp_symbol&mask) 
                {
                    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, t_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (t_color >> 8) ); Send_to_lcd( DAT, t_color );
                    #endif
                }
                else 
               {
                    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, b_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (b_color >> 8) ); Send_to_lcd( DAT, b_color );
                    #endif
                }
                zh--;
            }
            mask<<=1; //������ ���������� mask �� 1 ��� �����;    
        }
        zw++;
    }
  switch(rot)
  {
   case 0: case 180: x=x+zoom_width;  break; //�������� ����� ���������� ������� �� ��� x ��� ������ ���������� �����
   case 90: case 270: y=y+zoom_width; break; //�������� ����� ���������� ������� �� ��� y ��� ������ ���������� �����            
  }                  
 }
}  

//===============================================================
// ������� ������ ������ ������� ASCII-���� 
//===============================================================
void LCD_Putchar(char symbol, char x, char y, int t_color, int b_color, char zoom_width, char zoom_height)
{
    unsigned char m;
    if(zoom_width == 0)   zoom_width = 1;
    if(zoom_height == 0)  zoom_height = 1;
    switch (rot)  
    {         
        case 90: case 270:  m=y; y=x; x=m;        
                            break;                      
    };
    Send_Symbol( symbol, x, y, t_color, b_color, zoom_width, zoom_height);  
}

//===============================================================
//          ������� ������ ������, ������������� � ram 
//===============================================================
void LCD_Puts(char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height)
{
    unsigned char i=0;
              
    if(zoom_width == 0)   zoom_width = 1;
    if(zoom_height == 0)  zoom_height = 1;
   
    while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
    {      
        LCD_Putchar(str[i], x+(i*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height);
        i++;
    }  
}

//===============================================================
//          ������� ������ ������, ������������� �� flash
//===============================================================
void LCD_Putsf(flash char *str, int x, int y,  int t_color, int b_color, char zoom_width, char zoom_height)
{
 unsigned char i=0;
        
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
 {      
  LCD_Putchar(str[i], x+(i*6*zoom_width), y, t_color, b_color, zoom_width, zoom_height);
  i++;
 }  
}    

//===============================================================
//     ������� ���������� ������� �� ������� ��� ����� ����
//===============================================================
void Send_Symbol_Shadow (unsigned char symbol, char x, char y, int t_color, char zoom_width, char zoom_height) 
{
 unsigned char temp_symbol, a, b, zw, zh, mask; 
 char m, n;
 m=x; 
 n=y;
 if (symbol>127) symbol-=64;    //������� ������������� ����� ������� ASCII
 for ( a = 0; a < 5; a++) //��������� 5 ����, ������������ ������
 {  
  temp_symbol = font_5x8[symbol-32][a];
  zw = 0; 
  while(zw != zoom_width) //����� ����� ����������� zw ��� 
  {    
   switch(rot)
   {
    case 0: case 180: n=y; break;
    case 90: case 270: m=x; break;
   } 
   mask=0x01;     
   for ( b = 0; b < 8; b++ ) //���� ����������� 8 ��� �����
   {         
    zh = 0; //� zoom_height ��� ���������� ������ �������
    while(zh != zoom_height) //����� ������� ����������� z ���
    {
     switch(rot)
     {
      case 0: case 180:  
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zw, n+zh, t_color);
      }
      break; 
      case 90: case 270: 
      if (temp_symbol&mask) 
      {
       Put_Pixel (m+zh, n+zw, t_color);
      }
      break; //�������� ����� ���������� ������� �� ��� y ��� ������ ���������� �����            
     }            
     zh++;
    }
    mask<<=1; //������ ���������� mask �� 1 ��� �����;
    switch(rot)
    {
     case 0: case 180: n=n+zoom_height; break;
     case 90: case 270: m=m+zoom_height; break;
    }          
   }
   zw++;   
  }
  switch(rot)
  {
   case 0: case 180: m=m+zoom_width; break;
   case 90: case 270: n=n+zoom_width; break;
  }           
 }
} 

//===============================================================
// ������� ������ ������ ������� ASCII-���� ��� ����� ����
//===============================================================
void LCD_Putchar_Shadow (char symbol, char x, char y, int t_color, char zoom_width, char zoom_height)
{
 unsigned char m;
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
 switch (rot)
 {  
    case 90: case 270:  m=y; y=x; x=m;
                        break;    
 };
 Send_Symbol_Shadow( symbol, x, y, t_color, zoom_width, zoom_height);  
}

//===============================================================
//   ������� ������ ������, ������������� � ram ��� ����� ���� 
//===============================================================
void LCD_Puts_Shadow(char *str, int x, int y,  int t_color, char zoom_width, char zoom_height)
{
 unsigned char i=0;
                    
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i]) //x � y - ����� ������� ��������� �������; � ����������� ���������� i ����� ������ ���������� ������� ��������� �� i*6 (��� ������������ ������� �������)  
 {      
  LCD_Putchar_Shadow(str[i], x+(i*6*zoom_width), y, t_color, zoom_width, zoom_height);
  i++;
 }  
}

//===============================================================
// ������� ������ ������, ������������� �� flash ��� ����� ����
//===============================================================
void LCD_Putsf_Shadow(flash char *str, int x, int y,  int t_color, char zoom_width, char zoom_height)
{
 unsigned char i=0;
           
 if(zoom_width == 0)   zoom_width = 1;
 if(zoom_height == 0)  zoom_height = 1;
   
 while (str[i])   
 {      
  LCD_Putchar_Shadow(str[i], x+(i*6*zoom_width), y, t_color, zoom_width, zoom_height);
  i++;
 }  
} 
   
//===============================================================
//                  ������� ������ ������ 
//===============================================================
void LCD_FillScreen (unsigned int color)
{ 
 unsigned int x; 
 SetArea( 0, 131, 0, 175 );   //������� ����� ������ 
 SetBit(LCD_PORT, LCD_RS);    
 
 //������ - ����� ���� �������
 for (x = 0; x < 132*176; x++)  
 {   
  #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
  Send_to_lcd( DAT, color ); //������ - ����� ���� ������� 
  #else			//(16-�� ������� �������� ������� (65536 ������))
  Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, color );
  #endif
 }                 
} 

//===============================================================
//                 ������� ������ �����������
//===============================================================
void LCD_Output_image (char x, char y, char width, char height, flash char *img)
{ 
 unsigned char m;
 switch (rot)
 {
    case 90: case 270:  m=y; y=x; x=m;  
                        break;     
 };
 Send_Image (x, y, width, height, img);
}   

//===============================================================
//          ������� ��� ����������� ������ �����������   
//===============================================================
//����� �������� � Image2Lcd � NokiaImageCreator ������ ����������� �����-������� ������-����.
//x, y - ������ ������� ������ �����������; width � height - ������ � ������ �����������   
void Send_Image (char x, char y, char width, char height, flash char *img)  
{  
 char x1, y1; 
 
 switch (rot)
 {
  case 0: case 180:  
  for(y1=y; y1<(y+height); y1++)
  {
   SetArea( x, x+(width-1), y1, y1 );   
   for(x1=x; x1<x+width; x1++)
   {   
    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
    Send_to_lcd( DAT, *img++ ); //������ - ����� ���� ������� 
    #else			//(16-�� ������� �������� ������� (65536 ������))
    Send_to_lcd( DAT, *img++ ); Send_to_lcd( DAT, *img++ );  
    #endif
   }
  }
  break;
 
  case 90: case 270:
  for(x1=x; x1<x+height; x1++)
  {
   SetArea( x1, x1, y, y+(width-1) );       
   for(y1=y; y1<y+width; y1++)
   {
    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
    Send_to_lcd( DAT, *img++ ); //������ - ����� ���� ������� 
    #else			//(16-�� ������� �������� ������� (65536 ������))
    Send_to_lcd( DAT, *img++ ); Send_to_lcd( DAT, *img++ );      
    #endif  
   } 
  }
  break; 
 }; 
} 

#ifdef _GEOMETRICAL
//===============================================================
//                      ���������� �����
//===============================================================
void LCD_DrawLine (char x1, char y1, char x2, char y2, int color)
{ 
 short  x, y, d, dx, dy, i, i1, i2, kx, ky;
 signed char flag;
 unsigned char m;

 switch (rot)
 {
    case 90: case 270:  m=y1; y1=x1; x1=m; m=y2; y2=x2; x2=m; 
                        break;     
 };
 
 dx = x2 - x1;
 dy = y2 - y1;
 if (dx == 0 && dy == 0) Put_Pixel(x1, y1, color);  //�����
 else      //�����
 {
  kx = 1;
  ky = 1;
  if( dx < 0 )
  { 
   dx = -dx; 
   kx = -1; 
  }
  else
  if(dx == 0) kx = 0;
  if(dy < 0)
  { 
   dy = -dy; 
   ky = -1; 
  }
  if(dx < dy)
  { 
   flag = 0; 
   d = dx; 
   dx = dy; 
   dy = d; 
  }
  else flag = 1;
  i1 = dy + dy; 
  d = i1 - dx; 
  i2 = d - dx;
  x = x1; 
  y = y1;

  for(i=0; i < dx; i++)
  {
   Put_Pixel(x, y, color);
   if(flag) x += kx;
   else y += ky;
   if( d < 0 ) d += i1;
   else
   {
    d += i2;
    if(flag) y += ky;
    else x += kx;
   }
  }
  Put_Pixel(x, y, color);
 }
}   
  
//===============================================================
//             ���������� ����� � ���������� �������
//===============================================================
void LCD_FillLine (char tx1, char ty1, char tx2, char ty2, char width, int color)
{
    signed long x, y, addx, dx, dy;
    signed long P;
    int i;
    long x1,x2,y1,y2;
      
   if(ty1>ty2)  {y1=ty2; y2=ty1; x1=tx2; x2=tx1;}
   else         {y1=ty1; y2=ty2; x1=tx1; x2=tx2;}
    dx = x2 - x1;
    dy = y2 - y1;
   if(dx<0)     dx=-dx;
   if(dy<0)     dy=-dy;
    x = x1;
    y = y1;

   if(x1 > x2)  addx = -1;
   else         addx = 1;

   if(dx >= dy)
   {
    P = 2*dy - dx;

      for(i=0; i<=dx; ++i)
      {
        LCD_FillRect (x, y, width, width, color);
        
         if(P < 0)
         {
            P += 2*dy;
            x += addx;
         }
         else
         {
            P += 2*dy - 2*dx;
            x += addx;
            y ++;
         }
      }
   }
   else
   {
    P = 2*dx - dy;

      for(i=0; i<=dy; ++i)
      {
        LCD_FillRect (x, y, width, width, color);

         if(P < 0)
         {
            P += 2*dx;
            y ++;
         }
         else
         {
            P += 2*dx - 2*dy;
            x += addx;
            y ++;
         }
      }
   }
}   

//===============================================================
//			���������� �����                
//===============================================================
void LCD_DrawRect (char x1, char y1, char width, char height, char size, int color)
{
 unsigned int i;
 char x2=x1+(width-1), y2=y1+(height-1); //�������� ������� ����� �� ���� � � �
 
  for( i=1; i<=size; i++)   // size - ������� �����
 {
  LCD_DrawLine(x1, y1, x1, y2, color);
  LCD_DrawLine(x2, y1, x2, y2, color);
  LCD_DrawLine(x1, y1, x2, y1, color);
  LCD_DrawLine(x1, y2, x2, y2, color);
  x1++; // ���������� ������� �����, ���� ��� ������
  y1++;
  x2--;
  y2--;
 }
}

//===============================================================
//              ��������� ������������� ������ COLOR
//===============================================================
void LCD_FillRect (char x1, char y1, char width, char height, int color)
{
 unsigned int x;
 unsigned char m;

 switch (rot)
 {
    case 90: case 270:  m=y1; y1=x1; x1=m; m=width; width=height; height=m; break;     
 };
       
 SetArea( x1, x1+(width-1), y1, y1+(height-1) );
 SetBit(LCD_PORT, LCD_RS);
 
 for (x = 0; x < width * height; x++) 
 {   
  #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
  Send_to_lcd( DAT, color ); //������ - ����� ���� ������� 
  #else			//(16-�� ������� �������� ������� (65536 ������))
  Send_to_lcd( DAT, (color >> 8) ); Send_to_lcd( DAT, color );
  #endif
 }   
}  
 
//===============================================================
//                  ���������� ����������
//===============================================================
void LCD_DrawCircle (char xcenter, char ycenter, char rad, int color)
{
    signed int k, b, P;
    unsigned char m;

    switch (rot)
    {
        case 90: case 270:  m=ycenter; ycenter=xcenter; xcenter=m; break;     
    };
    
    k = 0;
    b = rad;
    P = 1 - rad;
    do     
    {
        Put_Pixel(k+xcenter, b+ycenter, color);
        Put_Pixel(b+xcenter, k+ycenter, color);
        Put_Pixel(xcenter-k, b+ycenter, color);
        Put_Pixel(xcenter-b, k+ycenter, color);
        Put_Pixel(b+xcenter, ycenter-k, color);
        Put_Pixel(k+xcenter, ycenter-b, color);
        Put_Pixel(xcenter-k, ycenter-b, color);
        Put_Pixel(xcenter-b, ycenter-k, color);

        if(P < 0)   P+= 3 + 2*k++;
        else        P+= 5 + 2*(k++ - b--);
    } while(k <= b);
}      


//===============================================================
//                 ��������� ���� ������ COLOR
//===============================================================
void LCD_FillCircle (char xcenter, char ycenter, char rad, int color)
{
    signed int x1=0, y1, tswitch;
    y1 = rad;
    tswitch = 1 - rad;

    do
    {
        LCD_DrawLine(xcenter-x1, ycenter+y1, xcenter+x1, ycenter+y1, color);
        LCD_DrawLine(xcenter-x1, ycenter-y1, xcenter+x1, ycenter-y1, color);
        LCD_DrawLine(xcenter-y1, ycenter+x1, xcenter+y1, ycenter+x1, color);
        LCD_DrawLine(xcenter-y1, ycenter-x1, xcenter+y1, ycenter-x1, color);

    if(tswitch < 0)
    tswitch+= 3 + 2*x1++;
    else
    tswitch+= 5 + 2*(x1++ - y1--);
    } while(x1 <= y1);
}

//===============================================================
//                     ���������� �����������
//===============================================================
void LCD_DrawTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 LCD_DrawLine(x1, y1, x2, y2, color);
 LCD_DrawLine(x3, y3, x1, y1, color);
 LCD_DrawLine(x3, y3, x2, y2, color);  
}

//===============================================================
//              ��������� ����������� ������ COLOR
//===============================================================
void LCD_FillTriangle(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 LCD_FillTriangleA(x1, y1, x2, y2, x3, y3, color);
 LCD_FillTriangleA(x3, y3, x1, y1, x2, y2, color);
 LCD_FillTriangleA(x3, y3, x2, y2, x1, y1, color);
}    

//===============================================================
void LCD_FillTriangleA(char x1, char y1, char x2, char y2, char x3, char y3, int color)
{
 signed long x, y, addx, dx, dy;
 signed long P;
 int i;
 long a1,a2,b1,b2;
 if(y1>y2)  {b1=y2; b2=y1; a1=x2; a2=x1;}
 else       {b1=y1; b2=y2; a1=x1; a2=x2;}
 dx = a2 -a1;
 dy = b2 - b1;
 if(dx<0)dx=-dx;
 if(dy<0)dy=-dy;
 x = a1;
 y = b1;
   
 if(a1 > a2)    addx = -1;
 else           addx = 1;
   
 if(dx >= dy)
 {
  P = 2*dy - dx;
  for(i=0; i<=dx; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dy;
    x += addx;
   }
   else
   {
    P += 2*dy - 2*dx;
    x += addx;
    y ++;
   }
  }
 }
 else
 {
  P = 2*dx - dy;
  for(i=0; i<=dy; ++i)
  {
   LCD_DrawLine((int)x, (int)y, x3, y3, color);
   if(P < 0)
   {
    P += 2*dx;
    y ++;
   }
   else
   {
    P += 2*dx - 2*dy;
    x += addx;
    y ++;
   }
  }
 }
}

//===============================================================
//      ������� ���������� ������� ��������� 0-100%
//===============================================================
// percent - ����� �� 0 �� 100, x � y - ��������� ������� ������� (������� ����� ����), width - ������ �������, zoom_height - �� ������� ��� ��������� ������ ������� 
// (��� zoom_height=1 ������ ����� ������ ���������� 5 ��������)
void LCD_Put_Graph (char percent, char x, char y, int t_color, int b_color, char width, char zoom_height)
{
    char i, j=0, m, array[20];
    for (i = 0; i < percent; i += 5)
    {            
        if (i + 5 > percent)
        {
            array[j++] = percent-i;
        }
        else
        {              
            array[j++] = 5;
        }
    }
    for (i=j; i<20; i++) //���������� ���������� ����� ������
    {
        array[i] = 0;
    }    
    
    switch (rot)
    {          
        case 270:   // ���������� ������� �����-�����
                    Send_to_lcd(CMD, 0x36); 
                    Send_to_lcd(DAT, 0x80); //��������� ����� ���� � � � - ����� ������ ���� �������
                    break;
        default:    // ���������� ������� �����-�������, ������-���� 
                    Send_to_lcd(CMD, 0x36); 
                    Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������        
    }
        
    
    for (i=0; i<20; i++)
    {
        if (array[i]==5) //���������� ����������� ������ (5%)
        {
                switch (rot)
                {
                    case 0:     SetArea (x, x+(5*zoom_height-1), y, y+(width-1));
                                break;
                    default:    SetArea (x, x+(width-1), y, y+(5*zoom_height-1));             
                }                  
                
                for(j = 0; j < width*(5*zoom_height); j++)
                {
                    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, t_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (t_color >> 8) ); Send_to_lcd( DAT, t_color );
                    #endif
                }
                
                switch (rot)  
                {
                    case 0:     x+=(5*zoom_height);
                                break;
                    default:    y+=(5*zoom_height);             
                }
                
        }                               
        
        else if (array[i]==0) //���������� ������������� ������ (5%)
        {
                switch (rot)
                {
                    case 0:     SetArea (x, x+(5*zoom_height-1), y, y+(width-1));
                                break;
                    default:    SetArea (x, x+(width-1), y, y+(5*zoom_height-1));             
                }           
                
                for(j = 0; j < width*(5*zoom_height); j++)
                {
                    #ifdef _8_BIT_COLOR		//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, b_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (b_color >> 8) ); Send_to_lcd( DAT, b_color );
                    #endif
                }
                 switch (rot)
                {
                    case 0:     x+=(5*zoom_height);
                                break;
                    default:    y+=(5*zoom_height);             
                }
        }                        
                              
        else  //���������� ��������������� ������ (1-4%)
        {
            m=array[i];
            while (m--)
            {  
            
                switch (rot)
                {
                    case 0:     SetArea (x, x+(zoom_height-1), y, y+(width-1));
                                break;
                    default:    SetArea (x, x+(width-1), y, y+(zoom_height-1));             
                }        
                
                for(j = 0; j < width*zoom_height; j++)
                {
                    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, t_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (t_color >> 8) ); Send_to_lcd( DAT, t_color );
                    #endif
                }
                     switch (rot)
                {
                    case 0:     x+=zoom_height;
                                break;
                    default:    y+=zoom_height;             
                }                        
            }
         
            m=5-array[i];
            while (m--)
            {
                switch (rot)
                {
                    case 0:     SetArea (x, x+(zoom_height-1), y, y+(width-1));
                                break;
                    default:    SetArea (x, x+(width-1), y, y+(zoom_height-1));             
                }
                
                for(j = 0; j < width*zoom_height; j++)
                {
                    #ifdef _8_BIT_COLOR	//(8-�� ������� �������� ������� (256 ������))
                    Send_to_lcd( DAT, b_color ); //������ - ����� ���� ������� 
                    #else			        //(16-�� ������� �������� ������� (65536 ������))
                    Send_to_lcd( DAT, (b_color >> 8) ); Send_to_lcd( DAT, b_color );
                    #endif
                }
                     switch (rot)
                switch (rot)
                {
                    case 0:     x+=zoom_height;
                                break;
                    default:    y+=zoom_height;
                }                       
            }
        }
                    
    }
    Send_to_lcd(CMD, 0x36); 
    Send_to_lcd(DAT, 0x00); //��������� ����� ���� � � � - ����� ������� ���� �������
}

//===============================================================
#endif //_GEOMETRICAL