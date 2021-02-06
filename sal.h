// lcd
// glcd
// soft i2c
// nRf24L01
// Sim900
// SM630
// keypad4X4
// P10
// 75HC595LedMatrix
// ds18b20

#ifndef SAL
#define SAL_H 1
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
//    LCD in 4Bit Mode
/////////////////////////////////////////////////////////
#ifdef usingLCD

/*
#define lcdRs PORTD_B2
#define lcdEn PORTD_B3
#define lcdD4 PORTD_B4
#define lcdD5 PORTD_B5
#define lcdD6 PORTD_B6
#define lcdD7 PORTD_B7

#define lcdRsDir DDRD_B2
#define lcdEnDir DDRD_B3
#define lcdD4Dir DDRD_B4
#define lcdD5Dir DDRD_B5
#define lcdD6Dir DDRD_B6
#define lcdD7Dir DDRD_B7

*/




#define LCD_FIRST_ROW           //Move cursor to the 1st row
#define LCD_SECOND_ROW          //Move cursor to the 2nd row
#define LCD_THIRD_ROW           //Move cursor to the 3rd row
#define LCD_FOURTH_ROW          //Move cursor to the 4th row
#define LCD_CLEAR              0x01          //Clear display
#define LCD_RETURN_HOME        0x02       //Return cursor to home position, returns a shifted display to its original position. Display data RAM is unaffected.
#define LCD_CURSOR_OFF         0x0C     //Turn off cursor
#define LCD_CURSOR_ON          0x0E
#define LCD_UNDERLINE_ON                       //Underline cursor on
#define LCD_BLINK_CURSOR_ON    0x0F      //Blink cursor on
#define LCD_MOVE_CURSOR_LEFT    //Move cursor left without changing display data RAM
#define LCD_MOVE_CURSOR_RIGHT   //Move cursor right without changing display data RAM
#define LCD_TURN_ON             //Turn Lcd display on
#define LCD_TURN_OFF            //Turn Lcd display off
#define LCD_SHIFT_LEFT         0x18       //Shift display left without changing display data RAM
#define LCD_SHIFT_RIGHT        0x1C




class lcd {
			
			public:
				lcd ( char columnNum, char rowNum );
				
	            void init(void);
				void write(char row, char column, char data);
				void writeText(char row, char column, const char* string);
				void writeAscii(char row, char column, char data);
				void writeDec(char row, char column, unsigned int Number);
				void writeHex(char row, char column, char Number);
				void clearLine(char Line, char col);
				void clear();
				void sendCommand(char in);
				void scroll(char Direction, char Num_Positions);
				void ramWrite(char nIdx, char d0, char d1, char d2, char d3, char d4, char d5, char d6, char d7);
                

            private:
			    
				void Lcd_RawSend(char in, char mask);
				void Lcd_PrintString(const char* String, char MSZ_String);
				void Lcd_Cursor(char y, char x);
				
				uint8_t LCD_ROWCNT; 
				uint8_t LCD_COLCNT;
 };


lcd::lcd(char columnNum, char rowNum )
:LCD_ROWCNT (rowNum), LCD_COLCNT(columnNum)
{
		
}


void lcd::init(void)
{
    if ( (LCD_ROWCNT !=1)&&(LCD_ROWCNT != 2)&&(LCD_ROWCNT != 4) ) { 
		  LCD_ROWCNT = 2;
		  LCD_COLCNT = 16;
	}
	else{
		  if ( (LCD_COLCNT!= 16 )&&(LCD_COLCNT!= 20) ) { 
			    LCD_ROWCNT = 2;
			    LCD_COLCNT = 16;
				 
		  }
	}
		
	
			
	lcdEnDir = 1;  lcdRsDir = 1; lcdD4Dir = 1; lcdD5Dir = 1; lcdD6Dir = 1; lcdD7Dir = 1;
	_delay_ms(12);

	Lcd_RawSend(0x33, 0);
	_delay_ms(2);
	Lcd_RawSend(0x33, 0);
	_delay_ms(2);
        Lcd_RawSend(0x33, 0);
	_delay_ms(2);
	Lcd_RawSend(0x32, 0);
	_delay_ms(2);
	Lcd_RawSend(0x28, 0);
	_delay_ms(2);
	Lcd_RawSend(0x06, 0);
	_delay_ms(2);
	Lcd_RawSend(0x0c, 0);
	_delay_ms(2);

	//clear the display
	Lcd_RawSend(0x01, 0);
	_delay_ms(2);
	Lcd_RawSend(0x02, 0);
	_delay_ms(2);

}

void lcd::writeText(char row, char column, const char* string){

	int i = LCD_COLCNT - column;

	Lcd_Cursor(row,column);

	Lcd_PrintString(string,i );


}


void lcd::write(char row, char column, char data){

	Lcd_Cursor(row,column);
	Lcd_RawSend(data, 0x10);
}

void lcd::writeAscii(char row, char column, char data){
char ascii = data + 48;

	Lcd_Cursor(row,column);
	Lcd_RawSend(ascii, 0x10);
}

void lcd::writeDec(char row, char column, unsigned int Number){
	unsigned short int tmp_int;
	char tmp_byte;

	Lcd_Cursor(row,column);


	if (Number < 0){
		Lcd_RawSend('-', 0x10);
		Number = 0 - Number;
	}

	tmp_int = Number;
	if (Number >= 10000) {
		tmp_byte = tmp_int / 10000;
		Lcd_RawSend('0' + tmp_byte, 0x10);

		while (tmp_byte > 0){
			tmp_int = tmp_int - 10000;
			tmp_byte--;
		}
	}

	if (Number >= 1000){
		tmp_byte = tmp_int / 1000;
		Lcd_RawSend('0' + tmp_byte, 0x10);

		while (tmp_byte > 0){
			tmp_int = tmp_int - 1000;
			tmp_byte--;
		}
	}

	if (Number >= 100){
		tmp_byte = tmp_int / 100;
		Lcd_RawSend('0' + tmp_byte, 0x10);

		while (tmp_byte > 0){
			tmp_int = tmp_int - 100;
			tmp_byte--;
		}
	}

	if (Number >= 10){
		tmp_byte = tmp_int / 10;
		Lcd_RawSend('0' + tmp_byte, 0x10);

		while (tmp_byte > 0){
			tmp_int = tmp_int - 10;
			tmp_byte--;
		}
	}

	Lcd_RawSend('0' + tmp_int, 0x10);

}

void lcd::writeHex(char row, char column, char Number){
char hexCode[] = { '0', '1', '2', '3',  '4',  '5' , '6',  '7' , '8',  '9' , 'A',  'B' , 'C',  'D' , 'E',  'F'   };
char string[] = "  ";
   		
	  string [0] = hexCode [ (( Number >> 4) &  0x0F ) ];
	  string [1] = hexCode [ ( Number & 0x0F) ];
	  writeText(row, column, string);
	  
}

void lcd::clear()
{

	Lcd_RawSend(0x01, 0);
	_delay_ms(2);
	Lcd_RawSend(0x02, 0);
	_delay_ms(2);

}

//void Lcd_PrintASCII(char Character)
//{
//        Lcd_RawSend(Character, 0x10);
//}

void lcd::sendCommand(char in) {

	Lcd_RawSend(in, 0);
	_delay_ms(2);
}

void lcd::scroll(char Direction, char Num_Positions)  {

	char cmd = 0;
	char count;

	//Choose the direction
	switch (Direction)
	{
		case 0:
		case 'l':
		case 'L':
		cmd = 0x18;
		break;

		case 1:
		case 'r':
		case 'R':

		cmd = 0x1C;
		break;

		default:
		break;
	}

	//If direction accepted then scroll the specified amount
	if (cmd) {
		for (count = 0; count < Num_Positions; count++)
		sendCommand(cmd);
	}

}

void lcd::clearLine(char Line, char col){
	char count;
	char rowcount = LCD_COLCNT;

	//Start at beginning of the line
	Lcd_Cursor ( Line, col);

	//Send out spaces to clear line
	for (count = 0; count < rowcount; count++)
	Lcd_RawSend(' ', 0x10);

	//Move back to the beginning of the line.
	Lcd_Cursor (Line, col);

}

void lcd::ramWrite(char nIdx, char d0, char d1, char d2, char d3, char d4, char d5, char d6, char d7) {

	//set CGRAM address
	Lcd_RawSend(64 + (nIdx << 3), 0);
	_delay_ms(2);

	//write CGRAM data
	Lcd_RawSend(d0, 0x10);
	Lcd_RawSend(d1, 0x10);
	Lcd_RawSend(d2, 0x10);
	Lcd_RawSend(d3, 0x10);
	Lcd_RawSend(d4, 0x10);
	Lcd_RawSend(d5, 0x10);
	Lcd_RawSend(d6, 0x10);
	Lcd_RawSend(d7, 0x10);

	//Clear the display
	Lcd_RawSend(0x01, 0);
	_delay_ms(2);
	Lcd_RawSend(0x02, 0);
	_delay_ms(2);
}




void lcd::Lcd_Cursor(char y, char x)
{
  
  if (LCD_ROWCNT == 1){  y = 0x80; }
  
  if (LCD_ROWCNT == 2){ 
      if (y == 0) {  y = 0x80; }
      else{  y = 0xc0;  }
  }

  if (LCD_ROWCNT == 4){
	  if (LCD_COLCNT == 16){ 
          if (y==0) { y=0x80; }
          else{
	           if (y==1) { y=0xc0; }
               else{
				     if (y==2) { y=0x90; }
				      else { y=0xd0; }
			   }
		  }
	  }
	  if (LCD_COLCNT == 20){}
	      if (y==0) { y=0x80; }
	      else{
		       if (y==1) { y=0xc0; }
	           else {
					  if (y==2) {y=0x94; }
	                  else { y=0xd4; }
			}
	  }
	  
    }
	
	Lcd_RawSend(y+x, 0);
	_delay_ms(2);

}



void lcd::Lcd_PrintString(const char *String, char MSZ_String) {


	char idx;
	for (idx=0; idx < MSZ_String; idx++) {
		if (*(String+idx)== 0) {  break;}
		if (idx == LCD_COLCNT) {break;}
		Lcd_RawSend(*(String+idx), 0x10);
	}

}

void lcd::Lcd_RawSend(char in, char mask){

	unsigned char pt;

	
        
        if (mask) lcdRs = 1; else lcdRs=0;
	pt = ((in >> 4) & 0x0f);
	if (pt & 0x01)  lcdD4 = 1; else lcdD4=0;
	if (pt & 0x02)  lcdD5 = 1; else lcdD5=0;
	if (pt & 0x04)  lcdD6 = 1; else lcdD6=0;
	if (pt & 0x08)  lcdD7 = 1; else lcdD7=0;

	lcdEn = 0;
	_delay_us(1);
	lcdEn = 1;
	_delay_us(1);
	lcdEn = 0;
	pt = (in & 0x0f);
	_delay_us(100);


         if (mask) lcdRs = 1; else lcdRs=0;
	if (pt & 0x01)  lcdD4 = 1; else lcdD4=0;
	if (pt & 0x02)  lcdD5 = 1; else lcdD5=0;
	if (pt & 0x04)  lcdD6 = 1; else lcdD6=0;
	if (pt & 0x08)  lcdD7 = 1; else lcdD7=0;

	lcdEn = 0;
	_delay_us(1);
	lcdEn = 1;
	_delay_us(1);
	lcdEn = 0;
	_delay_us(100);
}

#endif // usingLcd





//////////////////////////////////////////////////////////////////////////////////
//   GLCD
//////////////////////////////////////////////////////////////////////////////////
#ifdef usingGlcdT6963   

#include <avr/pgmspace.h>

/*
#define glcdD0	PORTA_B0
#define glcdD1	PORTA_B1
#define glcdD2	PORTA_B2
#define glcdD3	PORTA_B3
#define glcdD4  PORTA_B4
#define glcdD5	PORTA_B5
#define glcdD6  PORTA_B6
#define glcdD7	PORTA_B7

#define glcdD0Dir	DDRA_B0
#define glcdD1Dir	DDRA_B1
#define glcdD2Dir	DDRA_B2
#define glcdD3Dir	DDRA_B3
#define glcdD4Dir	DDRA_B4
#define glcdD5Dir	DDRA_B5
#define glcdD6Dir	DDRA_B6
#define glcdD7Dir	DDRA_B7

#define glcdD0Pin   PINA_B0
#define glcdD1Pin	PINA_B1
#define glcdD2Pin	PINA_B2
#define glcdD3Pin	PINA_B3
#define glcdD4Pin	PINA_B4
#define glcdD5Pin	PINA_B5
#define glcdD6Pin	PINA_B6
#define glcdD7Pin	PINA_B7

#define glcdWr	    PORTC_B0
#define glcdRd	    PORTC_B1
#define glcdCe	    PORTC_B2
#define glcdCd	    PORTC_B3
#define glcdRst	    PORTC_B4
#define glcdFs		PORTC_B5

#define glcdWrDir	 DDRC_B0
#define glcdRdDir	 DDRC_B1
#define glcdCeDir    DDRC_B2
#define glcdCdDir 	 DDRC_B3
#define glcdRstDir 	 DDRC_B4
#define glcdFsDir    DDRC_B5

// display properties
#define GLCD_NUMBER_OF_LINES				128
#define GLCD_PIXELS_PER_LINE				240
#define GLCD_FONT_WIDTH						6
//
#define GLCD_GRAPHIC_AREA					(GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH)
#define GLCD_TEXT_AREA						(GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH)
#define GLCD_GRAPHIC_SIZE					(GLCD_GRAPHIC_AREA * GLCD_NUMBER_OF_LINES)
#define GLCD_TEXT_SIZE						(GLCD_TEXT_AREA * (GLCD_NUMBER_OF_LINES/8))


#define GLCD_TEXT_HOME						0x00
#define GLCD_GRAPHIC_HOME					(GLCD_TEXT_HOME + GLCD_TEXT_SIZE)
#define GLCD_OFFSET_REGISTER				0x02
#define GLCD_EXTERNAL_CG_HOME				(GLCD_OFFSET_REGISTER << 11)
*/

#define T6963_SET_CURSOR_POINTER			0x21
#define T6963_SET_OFFSET_REGISTER			0x22
#define T6963_SET_ADDRESS_POINTER			0x24

#define T6963_SET_TEXT_HOME_ADDRESS			0x40
#define T6963_SET_TEXT_AREA					0x41
#define T6963_SET_GRAPHIC_HOME_ADDRESS		0x42
#define T6963_SET_GRAPHIC_AREA				0x43

#define T6963_MODE_SET						0x80
#define T6963_OR_MODE_SET					0x80
#define T6963_EXOR_MODE_SET					0x81
#define T6963_AND_MODE_SET					0x83
#define T6963_ATTRIBUTE_MODE_SET			0x84


#define T6963_DISPLAY_MODE					0x90
#define T6963_CURSOR_BLINK_ON			0x01
#define T6963_CURSOR_DISPLAY_ON			0x02
#define T6963_TEXT_DISPLAY_ON			0x04
#define T6963_GRAPHIC_DISPLAY_ON		0x08


#define T6963_CURSOR_PATTERN_SELECT			0xA0
#define T6963_CURSOR_1_LINE				0x00
#define T6963_CURSOR_2_LINE				0x01
#define T6963_CURSOR_3_LINE				0x02
#define T6963_CURSOR_4_LINE				0x03
#define T6963_CURSOR_5_LINE				0x04
#define T6963_CURSOR_6_LINE				0x05
#define T6963_CURSOR_7_LINE				0x06
#define T6963_CURSOR_8_LINE				0x07

#define T6963_SET_DATA_AUTO_WRITE			0xB0
#define T6963_SET_DATA_AUTO_READ			0xB1
#define T6963_AUTO_RESET					0xB2

#define T6963_DATA_WRITE_AND_INCREMENT		0xC0
#define T6963_DATA_READ_AND_INCREMENT		0xC1
#define T6963_DATA_WRITE_AND_DECREMENT		0xC2
#define T6963_DATA_READ_AND_DECREMENT		0xC3
#define T6963_DATA_WRITE_AND_NONVARIALBE	0xC4
#define T6963_DATA_READ_AND_NONVARIABLE		0xC5

#define T6963_SCREEN_PEEK					0xE0
#define T6963_SCREEN_COPY					0xE8





class glcdT6963 {
	       public:         
				    glcdT6963 ( uint8_t columnNum, uint8_t rowNum , uint8_t fontSize);
	                
	                void init(void);
	                void clearText(void);
	                void clearCG(void);
	                void clearGraphic(void);
	                void writeChar(char y, char x, char ch);
	                void writeText(char y, char x, char * str);
	                
	                void defineCharacter(char charCode, char * defChar);
	                void setPixel(char x, char y, char color);
	                
                    void drawRectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a);
	                void drawCircle(unsigned char cx, unsigned char cy ,unsigned char radius);
	                void drawLine(int X1, int Y1,int X2,int Y2);
	                //extern void setPixel(char x, char y, char color);
	                
                    void drawBitmap (char * myBitmap, char x, char y, char width, char height);

        private:    
		            void setCursor(char y, char x);
		            void graphicGoTo(char x, char y);
		            void writeDisplayData(char x);
					char chceckStatus(void);
					char readData(void);
					void writeData(char data);
	                void writeCommand(char command);
	                void delay(void);
					void setAddressPointer(uint16_t address);
					
					char color;
					uint8_t GLCD_NUMBER_OF_LINES;
					uint8_t GLCD_PIXELS_PER_LINE;
					uint8_t GLCD_FONT_WIDTH;
					
					uint8_t GLCD_GRAPHIC_AREA;
					uint8_t GLCD_TEXT_AREA;
					uint16_t GLCD_GRAPHIC_SIZE;
					uint16_t GLCD_TEXT_SIZE;

					uint8_t GLCD_TEXT_HOME;
					uint8_t GLCD_GRAPHIC_HOME;
					uint8_t GLCD_OFFSET_REGISTER;
					uint8_t GLCD_EXTERNAL_CG_HOME;

	
};

glcdT6963:: glcdT6963( uint8_t columnNum, uint8_t rowNum , uint8_t fontSize)
:GLCD_PIXELS_PER_LINE(columnNum),GLCD_NUMBER_OF_LINES(rowNum), GLCD_FONT_WIDTH(fontSize) 
{ 
	
	GLCD_GRAPHIC_AREA   = (GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH);
	GLCD_TEXT_AREA		= (GLCD_PIXELS_PER_LINE / GLCD_FONT_WIDTH);
	GLCD_GRAPHIC_SIZE	= (GLCD_GRAPHIC_AREA * GLCD_NUMBER_OF_LINES);
	GLCD_TEXT_SIZE	    = (GLCD_TEXT_AREA * (GLCD_NUMBER_OF_LINES/8));

    GLCD_TEXT_HOME			= 0x00;
	GLCD_GRAPHIC_HOME		= (GLCD_TEXT_HOME + GLCD_TEXT_SIZE);
	GLCD_OFFSET_REGISTER	= 0x02;
	GLCD_EXTERNAL_CG_HOME	= (GLCD_OFFSET_REGISTER << 11);
	color = 1;
}

void glcdT6963::init(void){
	
	glcdD0Dir = 1; glcdD1Dir = 1; glcdD2Dir = 1;  glcdD3Dir = 1; glcdD4Dir  = 1; glcdD5Dir = 1; glcdD6Dir = 1; glcdD7Dir = 1;    // configure port pins as output
	glcdWrDir = 1; glcdRdDir = 1; glcdCeDir = 1;  glcdCdDir = 1; glcdRstDir = 1; glcdFsDir = 1;                                // configure port pins as output
	glcdWr    = 1; glcdRd    = 1; glcdCe    = 1;  glcdCd    = 1; glcdRst    = 1; glcdFs    = 1;                                // set port pins high

	glcdRst = 0;
	_delay_ms(1);
	glcdRst = 1;
	
    if(GLCD_FONT_WIDTH == 6){ glcdFs = 1; }
    if(GLCD_FONT_WIDTH == 8){ glcdFs = 0; }
			 
	
	
	writeData(GLCD_GRAPHIC_HOME & 0xFF);
	writeData(GLCD_GRAPHIC_HOME >> 8);
	writeCommand(T6963_SET_GRAPHIC_HOME_ADDRESS);

	writeData(GLCD_GRAPHIC_AREA);
	writeData(0x00);
	writeCommand(T6963_SET_GRAPHIC_AREA);

	writeData(GLCD_TEXT_HOME  & 0xFF);
	writeData(GLCD_TEXT_HOME >> 8);
	writeCommand(T6963_SET_TEXT_HOME_ADDRESS);

	writeData(GLCD_TEXT_AREA);
	writeData(0x00);
	writeCommand(T6963_SET_TEXT_AREA);

	writeData(GLCD_OFFSET_REGISTER);
	writeData(0x00);
	writeCommand(T6963_SET_OFFSET_REGISTER);
	
	//GLCD_SetAddressPointer(0x0000);

	writeCommand(T6963_DISPLAY_MODE  | T6963_GRAPHIC_DISPLAY_ON   | T6963_TEXT_DISPLAY_ON  );
	writeCommand(T6963_OR_MODE_SET);
	
	clearText(); // Clear text area
	clearCG(); // Clear character generator area
	clearGraphic();
	
}


void glcdT6963::clearText(void){
  uint16_t  i;
	 setAddressPointer(GLCD_TEXT_HOME);

	 for(i = 0; i < GLCD_TEXT_SIZE; i++)
	 {
		 writeDisplayData(0);
	 }
	 
}
void glcdT6963::clearCG(void){
	 uint16_t  i;
	 setAddressPointer(GLCD_EXTERNAL_CG_HOME);

	 for(i = 0; i < 256 * 8; i++)
	 {
		 writeDisplayData(0);
	 }
}
void glcdT6963::clearGraphic(void){
  uint16_t  i;
	 setAddressPointer(GLCD_GRAPHIC_HOME);
	 for(i = 0; i < GLCD_GRAPHIC_SIZE; i++)
	 {
		 writeDisplayData(0x00);
	 }
}
void glcdT6963::writeChar( char y, char x, char ch){
	 setCursor(y, x);
	 writeDisplayData(ch-32);
}
void glcdT6963::writeText(char y, char x,  char * str){
	 
	 setCursor(y, x);
	 while(*str) {   
		 writeDisplayData((*str++) - 32); 
	}
}
void glcdT6963::setCursor(char y, char x){
  uint16_t  address;
	 address = GLCD_TEXT_HOME +  x + (GLCD_TEXT_AREA * y);
	 setAddressPointer(address);
	
}

void glcdT6963::graphicGoTo(char x, char y)
{
	uint16_t  address;
	address = GLCD_GRAPHIC_HOME + (x / GLCD_FONT_WIDTH) + (GLCD_GRAPHIC_AREA * y);
	setAddressPointer(address);
}

void  glcdT6963::defineCharacter(char charCode, char * defChar){
 uint16_t  address;
	  char i;

	  address = GLCD_EXTERNAL_CG_HOME + (8 * charCode);
	  setAddressPointer(address);

	  for(i = 0; i < 8 ; i++)
	  {
		  writeDisplayData(*(defChar + i));
	  }
}

void  glcdT6963::setPixel(char x, char y, char color){
  unsigned char tmp;
  uint16_t  address;

	  address = GLCD_GRAPHIC_HOME + (x / GLCD_FONT_WIDTH) + (GLCD_GRAPHIC_AREA * y);
	  setAddressPointer(address);
	  writeCommand(T6963_DATA_READ_AND_NONVARIABLE);
	  tmp = readData();

	  if(color)
	  tmp |= (1 <<  (GLCD_FONT_WIDTH - 1 - (x % GLCD_FONT_WIDTH)));
	  else
	  tmp &= ~(1 <<  (GLCD_FONT_WIDTH - 1 - (x % GLCD_FONT_WIDTH)));

	  writeDisplayData(tmp);
}

void  glcdT6963::writeDisplayData(char x){
	  writeData(x);
	  writeCommand(T6963_DATA_WRITE_AND_INCREMENT);
}
void  glcdT6963::drawRectangle(unsigned char x, unsigned char y, unsigned char b, unsigned char a){
	  unsigned char j; 
	 
	  for (j = 0; j < a; j++) {
		  setPixel(x, y + j, color);
		  setPixel(x + b - 1, y + j, color);
	  }
	  
	  for (j = 0; j < b; j++)	{
		  setPixel(x + j, y, color);
		  setPixel(x + j, y + a - 1, color);
	  }
	
}
void  glcdT6963::drawCircle(unsigned char cx, unsigned char cy ,unsigned char radius){
	  int x, y, xchange, ychange, radiusError;
	  x = radius;
	  y = 0;
	  xchange = 1 - 2 * radius;
	  ychange = 1;
	  radiusError = 0;
	  while(x >= y)
	  {
		  setPixel(cx+x, cy+y, color);
		  setPixel(cx-x, cy+y, color);
		  setPixel(cx-x, cy-y, color);
		  setPixel(cx+x, cy-y, color);
		  setPixel(cx+y, cy+x, color);
		  setPixel(cx-y, cy+x, color);
		  setPixel(cx-y, cy-x, color);
		  setPixel(cx+y, cy-x, color);
		  y++;
		  radiusError += ychange;
		  ychange += 2;
		  if ( 2*radiusError + xchange > 0 )
		  {
			  x--;
			  radiusError += xchange;
			  xchange += 2;
		  }
	  }
}
void  glcdT6963::drawLine(int X1, int Y1,int X2,int Y2){
	  int CurrentX, CurrentY, Xinc, Yinc,
	  Dx, Dy, TwoDx, TwoDy,
	  TwoDxAccumulatedError, TwoDyAccumulatedError;

	  Dx = (X2-X1);  
	  Dy = (Y2-Y1);  

	  TwoDx = Dx + Dx;  
	  TwoDy = Dy + Dy;  

	  CurrentX = X1;  
	  CurrentY = Y1;  

	  Xinc = 1;  
	  Yinc = 1;  

	  if(Dx < 0)  
	  {
		  Xinc = -1;  
		  Dx = -Dx;   
		  TwoDx = -TwoDx;  
	  }

	  if (Dy < 0)  
	  {
		  Yinc = -1;  
		  Dy = -Dy;  
		  TwoDy = -TwoDy;  
	  }

	  setPixel(X1,Y1, color); 

	  if ((Dx != 0) || (Dy != 0)) // sprawdzamy czy linia sk³ada siê z wiêcej ni¿ jednego punktu ;)
	  {
		  // sprawdzamy czy sk³adowa pionowa jest mniejsza lub równa sk³adowej poziomej
		  if (Dy <= Dx) // jeœli tak, to idziemy "po iksach"
		  {
			  TwoDxAccumulatedError = 0; // zerujemy zmienn¹
			  do // ruszamy w drogê
			  {
				  CurrentX += Xinc; // do aktualnej pozycji dodajemy krok
				  TwoDxAccumulatedError += TwoDy; // a tu dodajemy podwojon¹ sk³adow¹ pionow¹
				  if(TwoDxAccumulatedError > Dx)  // jeœli TwoDxAccumulatedError jest wiêkszy od Dx
				  {
					  CurrentY += Yinc; // zwiêkszamy aktualn¹ pozycjê w pionie
					  TwoDxAccumulatedError -= TwoDx; // i odejmujemy TwoDx
				  }
				  setPixel(CurrentX,CurrentY, color);// stawiamy nastêpny krok (zapalamy piksel)
			  }while (CurrentX != X2); // idziemy tak d³ugo, a¿ osi¹gniemy punkt docelowy
		  }
		  else // w przeciwnym razie idziemy "po igrekach"
		  {
			  TwoDyAccumulatedError = 0;
			  do
			  {
				  CurrentY += Yinc;
				  TwoDyAccumulatedError += TwoDx;
				  if(TwoDyAccumulatedError>Dy)
				  {
					  CurrentX += Xinc;
					  TwoDyAccumulatedError -= TwoDy;
				  }
				  setPixel(CurrentX,CurrentY, color);
			  }while (CurrentY != Y2);
		  }
	  }
	
}

void glcdT6963::drawBitmap(char * myBitmap, char x, char y, char width, char height) {
	
	unsigned char i, j;

	for(j = 0; j < height; j++)
	{
		graphicGoTo(x, y + j);
		for(i = 0; i < width/GLCD_FONT_WIDTH; i++)
		{
			writeDisplayData(pgm_read_byte(myBitmap + i + (GLCD_GRAPHIC_AREA * j)));
		}
	}
}


char  glcdT6963::chceckStatus(void){
     
	char tmp;
	
	  glcdD0Dir = 0; glcdD1Dir = 0; glcdD2Dir = 0; glcdD3Dir = 0; glcdD4Dir = 0; glcdD5Dir = 0; glcdD6Dir = 0; glcdD7Dir = 0;  // configure port pins as input
	  glcdRd = 0; glcdCe = 0;   //set pins  low
	  delay();
	  tmp = ( (glcdD7Pin<<7)|(glcdD6Pin<<6)|(glcdD5Pin<<5)|(glcdD4Pin<<4)|(glcdD3Pin<<3)|(glcdD2Pin<<2)|(glcdD1Pin<<1)|(glcdD0Pin<<0)  ) ;
	  glcdD0Dir = 1; glcdD1Dir = 1; glcdD2Dir = 1; glcdD3Dir = 1; glcdD4Dir = 1; glcdD5Dir = 1; glcdD6Dir = 1; glcdD7Dir = 1;    // configure port pins as output
	  glcdRd = 1; glcdCe = 1;   //set pins  high
	  
	  return tmp;
}
char  glcdT6963::readData(void){
char tmp;
	
	while(!(chceckStatus()&0x03));
	glcdD0Dir = 0; glcdD1Dir = 0; glcdD2Dir = 0; glcdD3Dir = 0; glcdD4Dir = 0; glcdD5Dir = 0; glcdD6Dir = 0; glcdD7Dir = 0;    // configure port pins as output
	glcdRd = 0; glcdCe = 0; glcdCd = 0;
	delay();
    tmp = ( (glcdD7Pin<<7)|(glcdD6Pin<<6)|(glcdD5Pin<<5)|(glcdD4Pin<<4)|(glcdD3Pin<<3)|(glcdD2Pin<<2)|(glcdD1Pin<<1)|(glcdD0Pin<<0)  ) ;
	glcdRd = 1; glcdCe = 1; glcdCd = 1;
	glcdD0Dir = 1; glcdD1Dir = 1; glcdD2Dir = 1; glcdD3Dir = 1; glcdD4Dir = 1; glcdD5Dir = 1; glcdD6Dir = 1; glcdD7Dir = 1;    // configure port pins as output
	
	return tmp;
	
}
void  glcdT6963::writeData(char data){
	  while(!(chceckStatus()&0x03));
	  
	  glcdD0 = 0; glcdD1 = 0; glcdD2 = 0; glcdD3 = 0; glcdD4 = 0; glcdD5 = 0; glcdD6 = 0; glcdD7 = 0;
	  if (data&128) glcdD7 = 1;
	  if (data&64)  glcdD6 = 1;
	  if (data&32)  glcdD5 = 1;
	  if (data&16)  glcdD4 = 1;
	  if (data&8)   glcdD3 = 1;
	  if (data&4)   glcdD2 = 1;
	  if (data&2)   glcdD1 = 1;
	  if (data&1)   glcdD0 = 1;
	  
	  
	  glcdWr = 0; glcdCe = 0; glcdCd = 0;   //set pins  low
	  delay();
	  
	  glcdWr = 1; glcdCe = 1; glcdCd = 1;  //set pins  low
	  
}
void  glcdT6963::writeCommand(char command){
	  
	  while(!(chceckStatus()&0x03));
	 
	  glcdD0 = 0; glcdD1 = 0; glcdD2 = 0; glcdD3 = 0; glcdD4 = 0; glcdD5 = 0; glcdD6 = 0; glcdD7 = 0;
	  if (command&128) glcdD7 = 1;
	  if (command&64)  glcdD6 = 1;
	  if (command&32)  glcdD5 = 1;
	  if (command&16)  glcdD4 = 1;
	  if (command&8)   glcdD3 = 1;
	  if (command&4)   glcdD2 = 1;
	  if (command&2)   glcdD1 = 1;
	  if (command&1)   glcdD0 = 1;
	  
	  glcdWr = 0; glcdCe = 0;   //set pins  low
	  delay();
	  glcdWr = 1; glcdCe = 1;   //set pins  high
	
}

void glcdT6963::setAddressPointer(uint16_t address){
	writeData( (uint8_t)(address & 0xFF));
	writeData( (uint8_t)(address >> 8));
	writeCommand(T6963_SET_ADDRESS_POINTER);
}

void glcdT6963::delay(void){
 volatile unsigned char i;
	for(i = 0; i < (F_CPU/1000000); i++)  {  asm("nop");   }	
}


#endif // usingGlcdT6963 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     usingI2Cdev
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef usingI2C


/*
#define i2c_scl PORTC_B5
#define i2c_sda PORTC_B4

#define i2c_scl_dir DDRC_B5
#define i2c_sda_dir DDRC_B4

#define i2c_sda_pin PINC_B4

*/
#define I2C_MASTER_RECEIVE  0x01
#define I2C_MASTER_TRANSMIT 0x00

#define I2C_RECEIVE_SINGLE 0x00
#define I2C_RECEIVE_BEGIN 0x01
#define I2C_RECEIVE_CONTINUE 0x01
#define I2C_RECEIVE_END 0x00

#define I2C_SEND_SINGLE 0x00
#define I2C_SEND_BEGIN 0x01
#define I2C_SEND_CONTINUE 0x01
#define I2C_SEND_END 0x00

#define I2C_ERROR   0x00
#define I2C_OK      0x01

#define I2C_8Bit  0x00
#define I2C_16Bit 0x01
#define I2C_24Bit 0x02
#define I2C_32Bit 0x03



// IIC port data pin definition


uint8_t i2cInit (uint8_t speed){
	
	i2cScl = 0;                    //Set Outputs to 0
	i2cSda = 0;

	i2cSclDir = 0;                //Configure SDA and SCL as Input
	i2cSdaDir = 0;
	
	
	return 1;
}

class i2c {
	public:
	
	i2c (uint8_t Address, uint8_t Size);
	
	uint8_t init(void);
	
	uint8_t readBit  (uint16_t regAdd, uint8_t *data, uint8_t bitNum);
	uint8_t readBits (uint16_t regAdd, uint8_t *data, uint8_t length, uint8_t bitStart );
	uint8_t readByte (uint16_t regAdd, uint8_t* data );
	uint8_t readBytes(uint16_t regAdd, uint8_t* data, uint8_t length );
	
	uint8_t writeBit  (uint16_t regAdd, uint8_t data, uint8_t bitNum);
	uint8_t writeBits (uint16_t regAdd, uint8_t data, uint8_t length, uint8_t bitStart);
	uint8_t writeByte (uint16_t regAdd, uint8_t data);
	uint8_t writeBytes(uint16_t regAdd, uint8_t* data, uint8_t length);
	
	uint8_t showAdd(void);
	
	private:
	char devAdd, memSize;
	void i2c_delay();
	
	//uint8_t I2c_Init (void);
	uint8_t I2C_Device_Select (uint8_t _slave_address, uint8_t _direction);
	uint8_t I2C_Memory_Select (uint8_t _memory_address);
	uint8_t I2C_Read(uint8_t *_i2c_data, uint8_t _i2c_mode);
	uint8_t I2C_Write(uint8_t _i2c_data, uint8_t _i2c_mode);
	uint8_t I2C_Master_Write(uint8_t _slave_address, uint16_t memory_address, uint8_t memory_size );
	uint8_t I2C_Master_Read(uint8_t _slave_address, uint16_t memory_address, uint8_t memory_size );

	void I2C_Init();
	void I2C_Start();
	void I2C_Restart();
	void I2C_Stop();
	uint8_t I2C_Write_Raw(uint8_t Data);
	uint8_t I2C_Read_Raw(uint8_t Last);
	uint8_t I2C_SET_MEM (uint16_t memory_address, uint8_t memory_size);
	

	
};


i2c::i2c (uint8_t Address, uint8_t Size)
:devAdd (Address), memSize(Size)
{
}



uint8_t i2c::init(void){
	i2cScl = 0;                        //Set Outputs to 0
	i2cSda = 0;

	i2cSclDir = 0;                //Configure SDA and SCL as Input
	i2cSdaDir = 0;
	
	return(0);

}



uint8_t i2c::showAdd(void){
	
	return devAdd;
}


uint8_t i2c::readBit(uint16_t regAdd, uint8_t *data, uint8_t bitNum ){
	uint8_t b = 0;
	uint8_t count = 0;

	count = readByte(regAdd, &b);
	*data = b & (1 << bitNum);
	return count;
	
}

uint8_t i2c::readBits(uint16_t regAdd, uint8_t *data, uint8_t length, uint8_t bitStart  ){
	uint8_t count = 0;
	uint8_t mask = 0;
	uint8_t b;

	if ((count = readByte(regAdd, &b)) != 0) {
		mask = ((1 << length) - 1) << (bitStart - length + 1);
		b &= mask;
		b >>= (bitStart - length + 1);
		*data = b;
	}

	return count;
	
}


uint8_t i2c::readByte(uint16_t regAdd, uint8_t* data){
	uint8_t  _data;

	//addSize = getAddSize (devAddr);

	I2C_Master_Read( devAdd , regAdd, memSize);
	I2C_Read( &_data,I2C_RECEIVE_SINGLE);
	*data = _data;
	return 1;
}

uint8_t i2c::readBytes(uint16_t regAdd, uint8_t* data, uint8_t length){
	uint8_t i;

	//addSize = getAddSize (devAddr);

	I2C_Master_Read( devAdd , regAdd, memSize);
	for(i = 0; i<( length - 1); i++ ){
		I2C_Read( &data[i],I2C_RECEIVE_CONTINUE);
	}
	I2C_Read( &data[i], I2C_RECEIVE_END);

	return i;
	
}


uint8_t i2c::writeBit(uint16_t regAdd, uint8_t data, uint8_t bitNum ){
	uint8_t b = 0;

	readByte(regAdd, &b );
	//b = (dat != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
	if (data == 1){  b = b | (1 << bitNum); }
	else{ b = b & ~(1 << bitNum) ;     }


	return writeByte(regAdd, b );

}


uint8_t i2c::writeBits(uint16_t regAdd, uint8_t data, uint8_t length, uint8_t bitStart  ){
	uint8_t b = 0;
	uint8_t mask = 0;

	if (readByte(regAdd, &b ) != 0) { //get current dat
		mask = ((1 << length) - 1) << (bitStart - length + 1);
		data <<= (bitStart - length + 1); // shift dat into correct position
		data &= mask; // zero all non-important bits in dat
		b &= ~(mask); // zero all important bits in existing byte
		b |= data; // combine dat with existing byte
		return writeByte(regAdd, b);
	}
	else {  return 0;  }


}


uint8_t  i2c::writeByte(uint16_t regAdd, uint8_t data){
	

	//addSize = getAddSize (devAddr);

	I2C_Master_Write(devAdd, regAdd, memSize);
	I2C_Write( data, I2C_SEND_END);
	return 1;
}


uint8_t i2c::writeBytes(uint16_t regAdd , uint8_t *data, uint8_t length) {
	uint8_t i;


	//addSize = getAddSize (devAddr);

	I2C_Master_Write(devAdd, regAdd, memSize);
	for (i = 0; i< ( length - 1); i++){ I2C_Write( data[i],I2C_SEND_CONTINUE); }
	I2C_Write(  data[i],I2C_SEND_END);

	return i;
}


void i2c::i2c_delay(){
	_delay_us(10);
}

uint8_t i2c::I2C_Device_Select (uint8_t _slave_address, uint8_t _direction){
	// Send Start consitiom
	I2C_Start();

	//Send slave address and read/write
	_slave_address =_slave_address << 1;
	if (_direction == 1)  {  _slave_address = _slave_address | 0x01;  }
	
	I2C_Write_Raw( _slave_address);
	return(0);
}

uint8_t i2c::I2C_Memory_Select (uint8_t _memory_address){

	I2C_Write_Raw( _memory_address);
	I2C_Stop();
	return(0);
}


uint8_t i2c::I2C_Read(uint8_t *_i2c_data, uint8_t _i2c_mode){

	switch(_i2c_mode){
		case(0x00):{
			*_i2c_data = I2C_Read_Raw(0);
			I2C_Stop();
			return(I2C_OK );

		}
		case(0x01):{
			*_i2c_data = I2C_Read_Raw(1);
			return(I2C_OK );

		}
		default: return(I2C_ERROR);
	}


}
uint8_t i2c::I2C_Write(uint8_t _i2c_data, uint8_t _i2c_mode){

	I2C_Write_Raw(_i2c_data);
	switch(_i2c_mode){
		case(0x00):{
			I2C_Stop();
			return(I2C_OK);

		}
		case(0x01):{

			return(I2C_OK);

		}
		default: return(I2C_ERROR);
	}

}

uint8_t i2c::I2C_Master_Write(uint8_t _slave_address, uint16_t memory_address, uint8_t memory_size ){

	// Send Start consitiom
	I2C_Start();
	_slave_address =_slave_address << 1;
	I2C_Write_Raw( _slave_address);
	return(I2C_SET_MEM( memory_address, memory_size ));

}

uint8_t i2c::I2C_Master_Read(uint8_t _slave_address, uint16_t memory_address, uint8_t memory_size ){
	
	// Send Start consitiom
	I2C_Start();
	_slave_address =_slave_address << 1;
	I2C_Write_Raw( _slave_address);
	I2C_SET_MEM( memory_address, memory_size );

	_slave_address = _slave_address | 0x01;
	I2C_Start();
	I2C_Write_Raw(_slave_address);

	return(0);
}


void i2c::I2C_Start() {

	i2cSclDir = 0;
	i2cSdaDir = 0;
	i2c_delay();

	i2cSdaDir = 1;
	i2cSda = 0;
	i2c_delay();
	i2cSclDir = 1;
	i2cScl = 0;
	i2c_delay();
}

void i2c::I2C_Restart() {
	i2cSdaDir = 0;
	i2c_delay();
	i2cSclDir = 0;
	i2c_delay();
	i2cSdaDir = 1;
	i2cSda = 0;
	i2c_delay();
	i2cSclDir = 1;
	i2cScl = 0;
	i2c_delay();

}

void i2c::I2C_Stop(){

	i2cSclDir = 1;
	i2cScl = 0;
	i2cSdaDir = 1;
	i2cSda = 0;
	i2c_delay();
	i2cSclDir = 0;
	i2c_delay();
	i2cSdaDir = 0;
	delay_ms(10);

}


uint8_t i2c::I2C_Write_Raw(uint8_t Data){
	uint8_t bit_mask;
	uint8_t local_ack = 0;
	for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1) {
		if(Data & bit_mask){
			i2cSdaDir = 0;
		}
		else{
			i2cSdaDir = 1;
			i2cSda = 0;
		}
		i2c_delay();
		i2cSclDir = 0;
		i2c_delay();
		i2cSclDir = 1;
		i2cScl = 0;                                                                //Set SCL Low
		i2c_delay();
	}
	i2cSdaDir = 0;
	i2c_delay();
	i2cSclDir = 0;
	i2c_delay();

	if (i2cSdaPin)
	local_ack = 1;
	i2c_delay();
	i2cSclDir = 1;
	i2cScl = 0;
	i2c_delay();
	return (local_ack);
}

uint8_t i2c::I2C_Read_Raw(uint8_t Last){
	uint8_t bit_mask;
	uint8_t Data = 0;
	//uint8_t local_ack;

	i2cSdaDir = 0;
	i2c_delay();
	for(bit_mask=0x80;bit_mask;bit_mask=bit_mask>>1){
		i2cSclDir = 0;
		i2c_delay();
		i2cSdaDir = 0;
		if(i2cSdaPin)
		Data = Data | bit_mask;
		i2cSclDir = 1;
		i2cScl = 0;
		i2c_delay();
	}

	if (!Last){
		i2cSdaDir = 0;
	}
	else{
		i2cSdaDir = 1;
		i2cSda = 0;
	}
	i2c_delay();
	i2cSclDir = 0;
	i2c_delay();
	i2cSclDir = 1;
	i2cScl = 0;
	i2c_delay();
	return (Data);

}

uint8_t i2c::I2C_SET_MEM (uint16_t memory_address, uint8_t memory_size){
	uint8_t add_lo, add_hi; //add_higher, add_highest;

	switch (memory_size){
		case(0x00):{
			add_lo = Lo(memory_address);
			I2C_Write_Raw(add_lo);
			return(I2C_OK);
		}
		case(0x01):{
			add_lo = Lo(memory_address);
			add_hi = Hi(memory_address);
			I2C_Write_Raw(add_hi);
			I2C_Write_Raw(add_lo);
			return(I2C_OK);
		}

		case(0x02):{
			
		}
		case(0x03):{
			
			
		}
		default: return(I2C_ERROR);
	}


}



#endif //usingI2Cdev

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
//   NRF24L01
//////////////////////////////////////////////////////////////////////////////////
#ifdef usingNrf24l01

#define _SCK            PORTB_B0
#define _SDI            PINB_B1
#define _SDO            PORTB_B2
#define _slaveSelectPin PORTB_B3
#define _chipEnablePin  PORTB_B4


#define _SCK_DDR            DDRB_B0
#define _SDI_DDR            DDRB_B1
#define _SDO_DDR            DDRB_B2
#define _slaveSelectPin_DDR DDRB_B3
#define _chipEnablePin_DDR  DDRB_B4


#define true  1
#define false 0

#define HIGH 1
#define LOW  0


#define RH_NRF24_MAX_PAYLOAD_LEN 32                                                /// This is the maximum number of bytes that can be carried by the nRF24.   We use some for headers, keeping fewer for RadioHead messages
#define RH_NRF24_HEADER_LEN 4                                                      /// The length of the headers we add.   The headers are inside the nRF24 payload
#define RH_NRF24_MAX_MESSAGE_LEN (RH_NRF24_MAX_PAYLOAD_LEN-RH_NRF24_HEADER_LEN)    /// This is the maximum RadioHead user message length that can be supported by this library. Limited by  the supported message lengths in the nRF24


// SPI Command names
#define RH_NRF24_COMMAND_R_REGISTER                        0x00
#define RH_NRF24_COMMAND_W_REGISTER                        0x20
#define RH_NRF24_COMMAND_ACTIVATE                          0x50 // only on RFM73 ?
#define RH_NRF24_COMMAND_R_RX_PAYLOAD                      0x61
#define RH_NRF24_COMMAND_W_TX_PAYLOAD                      0xa0
#define RH_NRF24_COMMAND_FLUSH_TX                          0xe1
#define RH_NRF24_COMMAND_FLUSH_RX                          0xe2
#define RH_NRF24_COMMAND_REUSE_TX_PL                       0xe3
#define RH_NRF24_COMMAND_R_RX_PL_WID                       0x60
#define RH_NRF24_COMMAND_W_ACK_PAYLOAD(pipe)               (0xa8|(pipe&0x7))
#define RH_NRF24_COMMAND_W_TX_PAYLOAD_NOACK                0xb0
#define RH_NRF24_COMMAND_NOP                               0xff

// Register names
#define RH_NRF24_REGISTER_MASK                             0x1f
#define RH_NRF24_REG_00_CONFIG                             0x00
#define RH_NRF24_REG_01_EN_AA                              0x01
#define RH_NRF24_REG_02_EN_RXADDR                          0x02
#define RH_NRF24_REG_03_SETUP_AW                           0x03
#define RH_NRF24_REG_04_SETUP_RETR                         0x04
#define RH_NRF24_REG_05_RF_CH                              0x05
#define RH_NRF24_REG_06_RF_SETUP                           0x06
#define RH_NRF24_REG_07_STATUS                             0x07
#define RH_NRF24_REG_08_OBSERVE_TX                         0x08
#define RH_NRF24_REG_09_RPD                                0x09
#define RH_NRF24_REG_0A_RX_ADDR_P0                         0x0a
#define RH_NRF24_REG_0B_RX_ADDR_P1                         0x0b
#define RH_NRF24_REG_0C_RX_ADDR_P2                         0x0c
#define RH_NRF24_REG_0D_RX_ADDR_P3                         0x0d
#define RH_NRF24_REG_0E_RX_ADDR_P4                         0x0e
#define RH_NRF24_REG_0F_RX_ADDR_P5                         0x0f
#define RH_NRF24_REG_10_TX_ADDR                            0x10
#define RH_NRF24_REG_11_RX_PW_P0                           0x11
#define RH_NRF24_REG_12_RX_PW_P1                           0x12
#define RH_NRF24_REG_13_RX_PW_P2                           0x13
#define RH_NRF24_REG_14_RX_PW_P3                           0x14
#define RH_NRF24_REG_15_RX_PW_P4                           0x15
#define RH_NRF24_REG_16_RX_PW_P5                           0x16
#define RH_NRF24_REG_17_FIFO_STATUS                        0x17
#define RH_NRF24_REG_1C_DYNPD                              0x1c
#define RH_NRF24_REG_1D_FEATURE                            0x1d

/// These register masks etc are named wherever possible   corresponding to the bit and field names in the nRF24L01 Product Specification

#define RH_NRF24_MASK_RX_DR                                0x40                  /// #define RH_NRF24_REG_00_CONFIG     0x00
#define RH_NRF24_MASK_TX_DS                                0x20
#define RH_NRF24_MASK_MAX_RT                               0x10
#define RH_NRF24_EN_CRC                                    0x08
#define RH_NRF24_CRCO                                      0x04
#define RH_NRF24_PWR_UP                                    0x02
#define RH_NRF24_PRIM_RX                                   0x01

#define RH_NRF24_ENAA_P5                                   0x20                  /// #define RH_NRF24_REG_01_EN_AA      0x01
#define RH_NRF24_ENAA_P4                                   0x10
#define RH_NRF24_ENAA_P3                                   0x08
#define RH_NRF24_ENAA_P2                                   0x04
#define RH_NRF24_ENAA_P1                                   0x02
#define RH_NRF24_ENAA_P0                                   0x01

#define RH_NRF24_ERX_P5                                    0x20                  /// #define RH_NRF24_REG_02_EN_RXADDR   0x02
#define RH_NRF24_ERX_P4                                    0x10
#define RH_NRF24_ERX_P3                                    0x08
#define RH_NRF24_ERX_P2                                    0x04
#define RH_NRF24_ERX_P1                                    0x02
#define RH_NRF24_ERX_P0                                    0x01

#define RH_NRF24_AW_3_BYTES                                0x01                  /// #define RH_NRF24_REG_03_SETUP_AW     0x03
#define RH_NRF24_AW_4_BYTES                                0x02
#define RH_NRF24_AW_5_BYTES                                0x03

#define RH_NRF24_ARD                                       0xf0                  /// #define RH_NRF24_REG_04_SETUP_RETR    0x04
#define RH_NRF24_ARC                                       0x0f

#define RH_NRF24_RF_CH                                     0x7f                   /// #define RH_NRF24_REG_05_RF_CH   0x05

#define RH_NRF24_CONT_WAVE                                 0x80                   /// #define RH_NRF24_REG_06_RF_SETUP    0x06
#define RH_NRF24_RF_DR_LOW                                 0x20
#define RH_NRF24_PLL_LOCK                                  0x10
#define RH_NRF24_RF_DR_HIGH                                0x08
#define RH_NRF24_PWR                                       0x06
#define RH_NRF24_PWR_m18dBm                                0x00
#define RH_NRF24_PWR_m12dBm                                0x02
#define RH_NRF24_PWR_m6dBm                                 0x04
#define RH_NRF24_PWR_0dBm                                  0x06
#define RH_NRF24_LNA_HCURR                                 0x01

#define RH_NRF24_RX_DR                                     0x40                    /// #define RH_NRF24_REG_07_STATUS                             0x07
#define RH_NRF24_TX_DS                                     0x20
#define RH_NRF24_MAX_RT                                    0x10
#define RH_NRF24_RX_P_NO                                   0x0e
#define RH_NRF24_STATUS_TX_FULL                            0x01

#define RH_NRF24_PLOS_CNT                                  0xf0                   /// #define RH_NRF24_REG_08_OBSERVE_TX                         0x08
#define RH_NRF24_ARC_CNT                                   0x0f

#define RH_NRF24_RPD                                       0x01                   /// #define RH_NRF24_REG_09_RPD                                0x09

#define RH_NRF24_TX_REUSE                                  0x40                   /// #define RH_NRF24_REG_17_FIFO_STATUS                        0x17
#define RH_NRF24_TX_FULL                                   0x20
#define RH_NRF24_TX_EMPTY                                  0x10
#define RH_NRF24_RX_FULL                                   0x02
#define RH_NRF24_RX_EMPTY                                  0x01

#define RH_NRF24_DPL_ALL                                   0x3f                   /// #define RH_NRF24_REG_1C_DYNPD                              0x1c
#define RH_NRF24_DPL_P5                                    0x20
#define RH_NRF24_DPL_P4                                    0x10
#define RH_NRF24_DPL_P3                                    0x08
#define RH_NRF24_DPL_P2                                    0x04
#define RH_NRF24_DPL_P1                                    0x02
#define RH_NRF24_DPL_P0                                    0x01

#define RH_NRF24_EN_DPL                                    0x04                   /// #define RH_NRF24_REG_1D_FEATURE                            0x1d
#define RH_NRF24_EN_ACK_PAY                                0x02
#define RH_NRF24_EN_DYN_ACK                                0x01

#define RH_BROADCAST_ADDRESS 0xFF


//////////////////////////////////////////////





///////////////////////////////////////////////

char  _thisAddress = RH_BROADCAST_ADDRESS ;
char  _promiscuous;     // bool

char  _rxHeaderTo  = RH_BROADCAST_ADDRESS;
char  _rxHeaderFrom = RH_BROADCAST_ADDRESS;
char  _rxHeaderId;
char  _rxHeaderFlags;

char  _txHeaderTo = RH_BROADCAST_ADDRESS;
char  _txHeaderFrom = RH_BROADCAST_ADDRESS;
char  _txHeaderId    = 0;
char  _txHeaderFlags = 0;
char  _lastRssi;

unsigned int   _rxBad = 0;
unsigned int  _rxGood = 0;
unsigned int  _txGood = 0;

typedef enum {

	RHModeInitialising = 0,     ///< Transport is initialising. Initial default value until init() is called..
	RHModeSleep,               ///< Transport hardware is in low power sleep mode (if supported)
	RHModeIdle,                ///< Transport is idle.
	RHModeTx,                  ///< Transport is in the process of transmitting a message.
	RHModeRx                   ///< Transport is in the process of receiving a message.
} RHMode;

RHMode  _mode = RHModeInitialising;


typedef enum {

	DataRate1Mbps = 0,   ///< 1 Mbps
	DataRate2Mbps,       ///< 2 Mbps
	DataRate250kbps      ///< 250 kbps
	
} DataRate;

/// \brief Convenient values for setting transmitter power in setRF()
/// These are designed to agree with the values for RF_PWR in RH_NRF24_REG_06_RF_SETUP
/// To be passed to setRF();

typedef enum {

	TransmitPowerm18dBm = 0,        ///< On nRF24, -18 dBm
	TransmitPowerm12dBm,            ///< On nRF24, -12 dBm
	TransmitPowerm6dBm,             ///< On nRF24, -6 dBm
	TransmitPower0dBm,              ///< On nRF24, 0 dBm
	// Sigh, different power levels for the same bit patterns on RFM73:
	// On RFM73P-S, there is a Tx power amp, so expect higher power levels, up to 20dBm. Alas
	// there is no clear documentation on the power for different settings :-(
	RFM73TransmitPowerm10dBm = 0,   ///< On RFM73, -10 dBm
	RFM73TransmitPowerm5dBm,        ///< On RFM73, -5 dBm
	RFM73TransmitPowerm0dBm,        ///< On RFM73, 0 dBm
	RFM73TransmitPower5dBm          ///< On RFM73, 5 dBm. 20dBm on RFM73P-S2 ?

} TransmitPower;


//Software SPI fuction


class nrf24 {
	   
	   public:
	            //NRF24;
				
			    char init();                                                 /// Initialises this instance and the radio module connected to it.  Set the chip enable and chip select pins to output LOW, HIGH respectively.
			    char readRegister(char reg);                              /// Reads a single register from the NRF24
			    char writeRegister(char reg, char val);                   /// Writes a single byte to the NRF24, and at the ame time reads the current STATUS register
			    char burstReadRegister(char reg, char* dest, char len);   /// Reads a number of consecutive registers from the NRF24 using burst read mode
				char burstWriteRegister(char reg, char* src, char len);   /// Write a number of consecutive registers using burst write mode
				char statusRead();                                           /// Reads and returns the device status register NRF24_REG_02_DEVICE_STATUS
				char setChannel(char channel);                               /// Sets the transmit and receive channel number.  The frequency used is (2400 + channel) MHz
				char setOpMode(char mode);                                   /// Sets the chip configuration that will be used to set  the NRF24 NRF24_REG_00_CONFIG register when in Idle mode. This allows you to change some  chip configuration for compatibility with libraries other than this one.
				char setNetworkAddress(char* address, char len);             /// Sets the Network address.
                char setRF(DataRate data_rate, TransmitPower power);         /// Sets the data rate and transmitter power to use. Note that the nRF24 and the RFM73 have different
                void setModeIdle();                                          /// Sets the radio in power down mode, with the configuration set to the
                void setModeRx();                                            /// Sets the radio in RX mode.
                void setModeTx();                                            /// Sets the radio in TX mode.
                char send(const char* dat, char len);                        /// Sends data to the address set by setTransmitAddress()
                char waitPacketSent();                                       /// Blocks until the current message (if any)
                char isSending();                                            /// Indicates if the chip is in transmit mode and
                char printRegisters();                                        /// Prints the value of all chip registers
				char available();                                             /// Checks whether a received message is available.
                char receive(char* buf, char* len);                             /// Turns the receiver on if it not already on.  If there is a valid message available, copy it to buf and return true   It is recommended that you call it in your main loop.
                char maxMessageLength();                                     /// The maximum message length supported by this driver, return The maximum message length supported by this driver
                char sleep();                                                /// Sets the radio into Power Down mode.
                
    protected:
                char flushTx();                                              /// Flush the TX FIFOs, return the value of the device status register
                char flushRx();                                              /// Flush the RX FIFOs , return the value of the device status register
                void validateRxBuf();                                        /// Examine the revceive buffer to determine whether the message is for this node
                void clearRxBuf();                                           /// Clear our local receive buffer

       private:
                char _configuration = RH_NRF24_EN_CRC | RH_NRF24_CRCO;             ///  This idle mode chip configuration  and Default: 2 byte CRC enabled;
                char _bufLen;                                                      /// Number of octets in the buffer
                char _buf[RH_NRF24_MAX_PAYLOAD_LEN];                               /// The receiver/transmitter buffer
                char _rxBufValid;                                                  ///True when there is a valid message in the buffer
                
				void spiInit(void);
				char spiTransfer(char _reg_data);
				char spiCommand(char command);
				char spiRead(char reg);
				char spiWrite(char reg, char val);
				char spiBurstRead(char reg, char* dest, char len);
				char spiBurstWrite(char reg, char* src, char len);
      };

void comdelay(){  Delay_us(10);}

//NRF24::NRF24 
	
void nrf24::spiInit(void){
	
	_SCK_DDR             = 1;         
	_SDI_DDR             = 0;
	_SDO_DDR             = 1;
	_slaveSelectPin_DDR  = 1;
	_chipEnablePin_DDR   = 1;
	
	_chipEnablePin  = LOW;
	_SCK = LOW;
	_slaveSelectPin = HIGH;


}

char nrf24::spiTransfer(char _reg_data){
	char i;

	for(i=0; i < 8; i++){

        if ((_reg_data & 128 ) == 128 ) {  _SDO = 1; }
		else {  _SDO = 0; }
		
		_SCK = HIGH;
		comdelay();
		
		_reg_data = _reg_data  <<  1;      // rotate register/data
		_reg_data = _reg_data + _SDI;

		_SCK = LOW;

	}
	comdelay();
	return _reg_data;
}



char nrf24::spiCommand(char command) {        // Low level commands for interfacing with the device
	char status;
	//ATOMIC_BLOCK_START;
	_slaveSelectPin =  LOW;
	status = spiTransfer(command);
	_slaveSelectPin = HIGH;
	//ATOMIC_BLOCK_END;
	return status;
}

char nrf24::spiRead(char reg){
	char val;
	//ATOMIC_BLOCK_START;
	_slaveSelectPin = LOW;
	spiTransfer(reg); // Send the address, discard the status
	val = spiTransfer(0); // The written value is ignored, reg value is read
	_slaveSelectPin = HIGH;
	//ATOMIC_BLOCK_END;
	return val;
}


char nrf24::spiWrite(char reg, char val) {
	char status = 0;

	//ATOMIC_BLOCK_START;
	_slaveSelectPin = LOW;
	status = spiTransfer(reg); // Send the address
	spiTransfer(val); // New value follows
	_slaveSelectPin = HIGH;
	//ATOMIC_BLOCK_END;
	return status;
}


char nrf24::spiBurstRead(char reg, char* dest, char len) {
	char status = 0, i;
	//ATOMIC_BLOCK_START;

	_slaveSelectPin = LOW;
	status = spiTransfer(reg); // Send the start address
	for(i=0; i<len; i++){
		dest[i] = spiTransfer(0xff);
	}
	_slaveSelectPin = HIGH;
	
	//ATOMIC_BLOCK_END;
	return status;
}


char nrf24::spiBurstWrite(char reg, char* src, char len) {
	char status = 0, i;
	//ATOMIC_BLOCK_START;
	
	_slaveSelectPin =  LOW;
	status = spiTransfer(reg); // Send the start address
	for(i=0; i<len; i++){
	    spiTransfer(src[i]);
	}
	_slaveSelectPin =  HIGH;

	//ATOMIC_BLOCK_END;
	return status;
}


char nrf24::init() {


	spiInit();
	
	// Clear interrupts
	writeRegister(RH_NRF24_REG_07_STATUS, RH_NRF24_RX_DR | RH_NRF24_TX_DS | RH_NRF24_MAX_RT);
	// Enable dynamic payload length on all pipes
	writeRegister(RH_NRF24_REG_1C_DYNPD, RH_NRF24_DPL_ALL);
	// Enable dynamic payload length, disable payload-with-ack, enable noack
	writeRegister(RH_NRF24_REG_1D_FEATURE, RH_NRF24_EN_DPL | RH_NRF24_EN_DYN_ACK);
	// Test if there is actually a device connected and responding
	// CAUTION: RFM73 and version 2.0 silicon may require ACTIVATE
	if (readRegister(RH_NRF24_REG_1D_FEATURE) != (RH_NRF24_EN_DPL | RH_NRF24_EN_DYN_ACK))
	{
	      spiWrite(RH_NRF24_COMMAND_ACTIVATE, 0x73);
		// Enable dynamic payload length, disable payload-with-ack, enable noack
		writeRegister(RH_NRF24_REG_1D_FEATURE, RH_NRF24_EN_DPL | RH_NRF24_EN_DYN_ACK);
		if (readRegister(RH_NRF24_REG_1D_FEATURE) != (RH_NRF24_EN_DPL | RH_NRF24_EN_DYN_ACK))
		return false;
	}


	// Make sure we are powered down
	setModeIdle();

	// Flush FIFOs
	flushTx();
	flushRx();

	setChannel(2);                                        // The default, in case it was set by another app without powering down
	setRF(DataRate2Mbps, TransmitPower0dBm);


	return true;
}

// Use the register commands to read and write the registers
char nrf24::readRegister(char reg)
{
	return spiRead((reg & RH_NRF24_REGISTER_MASK) | RH_NRF24_COMMAND_R_REGISTER);
}

char nrf24::writeRegister(char reg, char val)
{
	return spiWrite((reg & RH_NRF24_REGISTER_MASK) | RH_NRF24_COMMAND_W_REGISTER, val);
}

char nrf24::burstReadRegister(char reg, char* dest, char len)
{
	return spiBurstRead((reg & RH_NRF24_REGISTER_MASK) | RH_NRF24_COMMAND_R_REGISTER, dest, len);
}

char nrf24::burstWriteRegister(char reg, char* src, char len)
{
	return spiBurstWrite((reg & RH_NRF24_REGISTER_MASK) | RH_NRF24_COMMAND_W_REGISTER, src, len);
}

char nrf24::statusRead()
{
	// status is a side-effect of NOP, faster than reading reg 07
	return spiCommand(RH_NRF24_COMMAND_NOP);
}

char nrf24::flushTx()
{
	return spiCommand(RH_NRF24_COMMAND_FLUSH_TX);
}

char nrf24::flushRx()
{
	return spiCommand(RH_NRF24_COMMAND_FLUSH_RX);
}

char nrf24::setChannel(char channel)
{
	writeRegister(RH_NRF24_REG_05_RF_CH, channel & RH_NRF24_RF_CH);
	return true;
}

char nrf24::setOpMode(char mode)
{
	_configuration = mode;
	return true;
}

char nrf24::setNetworkAddress(char* address, char len)
{
	if (len < 3 || len > 5)
	return false;

	// Set both TX_ADDR and RX_ADDR_P0 for auto-ack with Enhanced shockwave
	writeRegister(RH_NRF24_REG_03_SETUP_AW, len-2);        // Mapping [3..5] = [1..3]
	burstWriteRegister(RH_NRF24_REG_0A_RX_ADDR_P0, address, len);
	burstWriteRegister(RH_NRF24_REG_10_TX_ADDR, address, len);
	return true;
}

char nrf24::setRF(DataRate data_rate, TransmitPower power)
{
	char value = (power << 1) & RH_NRF24_PWR;
	// Ugly mapping of data rates to noncontiguous 2 bits:
	if (data_rate == DataRate250kbps)
	value |= RH_NRF24_RF_DR_LOW;
	else if (data_rate == DataRate2Mbps)
	value |= RH_NRF24_RF_DR_HIGH;
	// else DataRate1Mbps, 00

	// RFM73 needs this:
	value |= RH_NRF24_LNA_HCURR;

	writeRegister(RH_NRF24_REG_06_RF_SETUP, value);
	// If we were using auto-ack, we would have to set the appropriate timeout in reg 4 here
	// see NRF24::setRF()
	return true;
}

void nrf24::setModeIdle()
{
	if (_mode != RHModeIdle)
	{
		writeRegister(RH_NRF24_REG_00_CONFIG, _configuration);
		//digitalWrite(_chipEnablePin, LOW);
		_chipEnablePin = LOW;
		_mode = RHModeIdle;
	}
}

char nrf24::sleep()
{
	if (_mode != RHModeSleep)
	{
		writeRegister(RH_NRF24_REG_00_CONFIG, 0); // Power Down mode
		//digitalWrite(_chipEnablePin, LOW);
		_chipEnablePin = LOW;
		_mode = RHModeSleep;
	}
	return true;
}

void nrf24::setModeRx()
{
	if (_mode != RHModeRx){

		_chipEnablePin = LOW;
		writeRegister(RH_NRF24_REG_00_CONFIG, _configuration | RH_NRF24_PWR_UP | RH_NRF24_PRIM_RX);
		_chipEnablePin = HIGH;
		_mode = RHModeRx;
	}
}

void nrf24::setModeTx()
{
	if (_mode != RHModeTx) {
		
		_chipEnablePin = LOW;
		writeRegister(RH_NRF24_REG_00_CONFIG, _configuration | RH_NRF24_PWR_UP);
		_chipEnablePin = HIGH;
		_mode = RHModeTx;
	}
}

char nrf24::send(const char* dat, char len)
{ 
	char i;
	
	if (len > RH_NRF24_MAX_MESSAGE_LEN)
	return false;
	// Set up the headers
	_buf[0] = _txHeaderTo;
	_buf[1] = _txHeaderFrom;
	_buf[2] = _txHeaderId;
	_buf[3] = _txHeaderFlags;
	
//memcpy(_buf+RH_NRF24_HEADER_LEN, dat, len);
	for(i = 0; i < len ; i++){  
		_buf[RH_NRF24_HEADER_LEN + i] = dat[i];	
	}
	
	setModeTx();
	spiBurstWrite(RH_NRF24_COMMAND_W_TX_PAYLOAD_NOACK, _buf, len + RH_NRF24_HEADER_LEN);
	// Radio will return to Standby II mode after transmission is complete
	_txGood++;
	return true;
}

char nrf24::waitPacketSent() {
	char status;

	// If we are not currently in transmit mode, there is no packet to wait for
	if (_mode != RHModeTx)
	return false;

	// Wait for either the Data Sent or Max ReTries flag, signalling the
	// end of transmission
	// We dont actually use auto-ack, so prob dont expect to see RH_NRF24_MAX_RT
	

	
	
	while (!((status = statusRead()) & (RH_NRF24_TX_DS | RH_NRF24_MAX_RT)))


	/////////////////////////////
	//YIELD;
	//////////////////////////////

	// Must clear RH_NRF24_MAX_RT if it is set, else no further comm
	writeRegister(RH_NRF24_REG_07_STATUS, RH_NRF24_TX_DS | RH_NRF24_MAX_RT);
	if (status & RH_NRF24_MAX_RT)
	flushTx();
	setModeIdle();
	// Return true if data sent, false if MAX_RT
	return status & RH_NRF24_TX_DS;
}

char nrf24::isSending()
{
	return !(readRegister(RH_NRF24_REG_00_CONFIG) & RH_NRF24_PRIM_RX) &&
	!(statusRead() & (RH_NRF24_TX_DS | RH_NRF24_MAX_RT));
}

char nrf24::printRegisters()
{
	#ifdef RH_HAVE_SERIAL
	// Iterate over register range, but don't process registers not in use.
	for (char r = RH_NRF24_REG_00_CONFIG; r <= RH_NRF24_REG_1D_FEATURE; r++)
	{
		if ((r <= RH_NRF24_REG_17_FIFO_STATUS) || (r >= RH_NRF24_REG_1C_DYNPD))
		{
			Serial.print(r, HEX);
			Serial.print(": ");
			char len = 1;
			// Address registers are 5 bytes in size
			if (    (RH_NRF24_REG_0A_RX_ADDR_P0 == r)
			|| (RH_NRF24_REG_0B_RX_ADDR_P1 == r)
			|| (RH_NRF24_REG_10_TX_ADDR    == r) )
			{
				len = 5;
			}
			char buf[5];
			burstReadRegister(r, buf, len);
			for (char j = 0; j < len; ++j)
			{
				Serial.print(buf[j], HEX);
				Serial.print(" ");
			}
			Serial.println("");
		}
	}
	#endif

	return true;
}

// Check whether the latest received message is complete and uncorrupted
void nrf24::validateRxBuf()
{
	if (_bufLen < 4)
	return; // Too short to be a real message
	// Extract the 4 headers
	_rxHeaderTo    = _buf[0];
	_rxHeaderFrom  = _buf[1];
	_rxHeaderId    = _buf[2];
	_rxHeaderFlags = _buf[3];
	
	if (_promiscuous || _rxHeaderTo == _thisAddress ||_rxHeaderTo == RH_BROADCAST_ADDRESS)
	{
		_rxGood++;
		_rxBufValid = true;
	}
}

char nrf24::available() {
	char len;
	if (!_rxBufValid)
	{
		if (_mode == RHModeTx)
		return false;
		

		
		setModeRx();
		if (readRegister(RH_NRF24_REG_17_FIFO_STATUS) & RH_NRF24_RX_EMPTY)
		return false;
		

		
		// Manual says that messages > 32 octets should be discarded
		len = spiRead(RH_NRF24_COMMAND_R_RX_PL_WID);
		if (len > 32)
		{
			flushRx();
			clearRxBuf();
			setModeIdle();
			return false;
		}
		// Clear read interrupt
		writeRegister(RH_NRF24_REG_07_STATUS, RH_NRF24_RX_DR);
		// Get the message into the RX buffer, so we can inspect the headers
		spiBurstRead(RH_NRF24_COMMAND_R_RX_PAYLOAD, _buf, len);
		_bufLen = len;
		// 140 microsecs (32 octet payload)
		validateRxBuf();
		if (_rxBufValid)
		setModeIdle(); // Got one
	}
	return _rxBufValid;
}

void nrf24::clearRxBuf()
{
	_rxBufValid = false;
	_bufLen = 0;
}

char nrf24::receive(char* buf, char* len)
{
	char i;
	
	if (!available())
	return false;
	if (buf && len)
	{
		// Skip the 4 headers that are at the beginning of the rxBuf
		if (*len > _bufLen-RH_NRF24_HEADER_LEN)
		*len = _bufLen-RH_NRF24_HEADER_LEN;
		
//memcpy(buf, _buf+RH_NRF24_HEADER_LEN, *len);
		for(i=0; i< *len; i++){
			buf[i] = _buf[RH_NRF24_HEADER_LEN+i];
		}
	}
	clearRxBuf(); // This message accepted and cleared
	return true;
}

char nrf24::maxMessageLength()
{
	return RH_NRF24_MAX_MESSAGE_LEN;
}


#endif     //usingNrf24l01


///////////////////////////////////////////////////////////////////////////////
// SIM 900
///////////////////////////////////////////////////////////////////////////////
#ifdef usingSim900

#ifndef usingUart
#define usingUart
#endif  //usingUart



uart _gsmModem;


char Ctrl_Z  = 0x1A;
#define endOfString  '\0'




class gsm {
	
	  public:
				//gsm_gsmModem ();
				uint8_t init(uint32_t buadrate);
				uint8_t getSimMemorySize(char* uartData);
				uint8_t getOperatorsName(char* uartData);
				
			    uint8_t readTextMessage(char* uartData, char* phoneNumber, uint8_t memAdd );
			    uint8_t sendTextMessage(char* uartData, char* phoneNumber);
			    uint8_t deleteTextMessage(uint8_t memAdd);
			    uint8_t makeACall(char* phoneNumber);
			    
				uint8_t gpsInit(void);
				uint8_t gpsReadMessage(char * _message, char mode);
			    
				
		private:
		       uint8_t getUartData(void);
		       uint8_t getRxData( uint8_t * _rxBuffer, uint8_t serialData );
			   uint8_t getRxData( uint8_t * _rxBuffer, uint8_t * serialData );
		       char textMessage[160]; 
				
				

};
			 
			 
//gsm_gsmModem::gsm_gsmModem;

uint8_t gsm::init( uint32_t buadrate){
uint8_t i;
uint8_t OK[] = "OK";

 	
	
	_gsmModem.init(buadrate);
	Delay_ms (100);
	
	_gsmModem.writeText("AT");
	_gsmModem.write(0x0D);
	Delay_ms (100);
	
	_gsmModem.writeText("AT");
	_gsmModem.write(0x0D);
	
    for(uint8_t k=0; k<5; k++)	{
	
        i = getRxData ((uint8_t *)textMessage  , OK);

	    for(i = 0; i<255; i++){
		     if ( ( textMessage[i] == 'O')&&( textMessage[i+1] == 'K') ){ 
				  _gsmModem.writeText("AT+CMGF=1");                           //Enable text mode
				  _gsmModem.write(0x0D);
				  Delay_ms(100);
				  return 1;
	         }
	    }
	
        Delay_ms(100);
    }
    return 0;
	
	
}

uint8_t gsm::getOperatorsName(char* uartData){
uint8_t i, j;	
	
	//UART1_Write_Text("AT+COPS?");
	//UART1_Write_Chr(CRT);
	_gsmModem.writeText("AT+COPS?");
	_gsmModem.write(0x0D);
	i = getUartData();
    
	for (i=0; i<160; i++){
		 
		 if ( textMessage[i] == '"')  {
			   i++;
			   for(j = 0; j< (160 - i); j++){
				     uartData[j] = textMessage[i+j];
					 if (textMessage[i+j + 1] == '"' )  return 1;
			   }
		 }
		
	}
	
	return 0;
	
	
}

uint8_t gsm::getSimMemorySize(char* uartData){
uint8_t i;

     //UART1_Write_Text("AT+CPMS=");
	 _gsmModem.writeText("AT+CPMS=");
	 
	 //UART1_Write_Chr('"');
	 //UART1_Write_Text("SM");
	 //UART1_Write_Chr('"');
	 _gsmModem.write('"');
	 _gsmModem.writeText("SM");
	 _gsmModem.write('"');
	 
	 
	 //UART1_Write_Chr(',');
	 _gsmModem.write(',');
	  
	 //UART1_Write_Chr('"');
	 //UART1_Write_Text("SM");
	 //UART1_Write_Chr('"');
	 _gsmModem.write('"');
	 _gsmModem.writeText("SM");
	 _gsmModem.write('"');
	
	 //UART1_Write_Chr(',');
	 _gsmModem.write(',');
	 
	 //UART1_Write_Chr('"');
	 //UART1_Write_Text("SM");
	 //UART1_Write_Chr('"');
	 _gsmModem.write('"');
	 _gsmModem.writeText("SM");
	 _gsmModem.write('"');
	 
     //UART1_Write_Chr(CRT);
	 _gsmModem.write(0x0D);
	 
     i = getUartData();

     for (i=0; i<160; i++){
	
	     if ( textMessage[i] == ':')  {
		       
			   for (i=i; i < 160; i++){
				    
					if ( textMessage[i] == ',')  {
						 i++;
						 uartData[0] = textMessage[i];
						 uartData[1] = textMessage[i+1];
						 uartData[2] = endOfString;
						 return 1;
					}
			   }  
		 }
	 }
	 
	 return 0;	
	
   
}
			
uint8_t gsm::readTextMessage(char* uartData, char* phoneNumber, uint8_t memAdd ){
uint8_t i, j;
char m[2];	

   for(i=0; i< sizeof(uartData); i++){
	   uartData [i+1] = 0x0D;
   }
   
   for(i=0; i < sizeof(phoneNumber); i++){
	   phoneNumber [i+1] = 0x0D;
   }
     
	if (memAdd < 10){
		m[0] = (char) memAdd + 48;
		//UART1_Write_Text("AT+CMGR =");
		//UART1_Write_Chr(m[0]);
		//UART1_Write_Chr(CRT);
		_gsmModem.writeText("AT+CMGR =");
		_gsmModem.write(m[0]);
		_gsmModem.write(0x0D);
	}
	else{ 
		  m[0] = ( (char) memAdd / 10 ) + 48;
		  m[1] = ( (char) memAdd % 10 ) + 48;
		  //UART1_Write_Text("AT+CMGR =");
		  ///UART1_Write_Chr(m[0]);
		  //UART1_Write_Chr(m[1]);
		  //UART1_Write_Chr(CRT);
		  _gsmModem.writeText("AT+CMGR =");
		  _gsmModem.write(m[0]);
		  _gsmModem.write(m[1]);
		  _gsmModem.write(0x0D);
	
	}

	i = getUartData();
	
	for (i=0; i<160; i++){ if  ( textMessage[i] == '"') goto case1;}
	return 0;
	
case1:
    i++;	                                                                        // "REC READ or UNREAD"
	for (i=i; i<160; i++){ if  ( textMessage[i] == '"') goto case2;}
	return 0;
	
case2:                     
    i++;                                                                           // "End of REC READ or UNREAD"
	for (i=i; i<160; i++){ if  ( textMessage[i] == '"') goto case3;}
	return 0;
	
case3:
    i++;
	for (j=0; j<20; j++){ 
		 phoneNumber[j] = textMessage[i+j];                                         //get phone number
		 if ( textMessage[i+j+1] == '"' ) break;
	}  
	
	i +=2;		
	for (i=i+j; i<160; i++){ if  ( textMessage[i] == '"') goto case4;}             // "              "
	return 0;
	
case4:
    i++;
	for (i=i; i<160; i++){ if  ( textMessage[i] == '"') goto case5;}              // "                 "
	return 0;
	
case5:
    i++;
	for (i=i; i<160; i++){ if  ( textMessage[i] == '"') goto case6;}             // "15/11/03, 21:39:05+04"    date and time
	return 0;
	
case6:
    i++;
    for (i=i; i<160; i++){ if  ( textMessage[i] == '"') goto case7;}            // "15/11/03, 21:39:05+04"    date and time
    return 0;
    
case7:
    i +=3;
	
	for (j=0; j<160; j++){ 
		uartData[j] = textMessage[i+j]; //get text message
		if ( textMessage[i+j+1] == 0x0D ) {
			 textMessage[i+j+2] = endOfString;
			 break;
			}
	} 
	
	j++; 
    return (j);
	
}

uint8_t gsm::sendTextMessage(char* uartData, char* phoneNumber){
uint8_t	 i;
	 
	
    _gsmModem.writeText("AT+CMGS=");
	_gsmModem.write('"');
	_gsmModem.writeText(phoneNumber);
	_gsmModem.write('"');
	_gsmModem.write(0x0D);
	
	_delay_ms(2000);
	for(i=0; i < 160; i++){
		if(uartData[i] == endOfString )	 break; 
		_gsmModem.write(uartData[i]);
	}
	
	_gsmModem.write(Ctrl_Z);
	return 1;	 

}

uint8_t gsm::deleteTextMessage(uint8_t memAdd){
char m[2];
	
	if (memAdd < 10){
		m[0] = (char) memAdd + 48;
		//UART1_Write_Text("AT+CMGD=");
		//UART1_Write_Chr(m[0]);
		//UART1_Write_Chr(CRT);
		_gsmModem.writeText("AT+CMGD=");
		_gsmModem.write(m[0]);
		_gsmModem.write(0x0D);
	}
	else{
		m[0] = ( (char) memAdd / 10 ) + 48;
		m[1] = ( (char) memAdd % 10 ) + 48;
		//UART1_Write_Text("AT+CMGD=");
		//UART1_Write_Chr(m[0]);
		//UART1_Write_Chr(m[1]);
		//UART1_Write_Chr(CRT);
		_gsmModem.writeText("AT+CMGD=");
		_gsmModem.write(m[0]);
		_gsmModem.write(m[0]);
		_gsmModem.write(0x0D);
		
	}

	return 1;
}

uint8_t gsm::makeACall(char* phoneNumber){
	
	return 1;
}

uint8_t  gsm::gpsInit(void){
	
	_gsmModem.writeText("AT+CGPSPWR=1");
	_gsmModem.write(0x0D);
	Delay_ms (200);
	
	_gsmModem.writeText("AT+CGPSRST=0");
	_gsmModem.write(0x0D);
	Delay_ms (200);
	
}
uint8_t  gsm::gpsReadMessage(char * _message, char mode ){
unsigned int uartTimeOut = 0;
uint32_t uartDataCtr = 0;
uint8_t i;
	
	_gsmModem.writeText("AT+CGPSINF=0");
	_gsmModem.write(0x0D);
	//Delay_ms (100);
	
	 
     uint8_t serialDataCtr  = 0;
     uint32_t serialTimeOut = 0;
     
     while (serialTimeOut < 60000){                               // get the first respose

	     if (_gsmModem.isDataReady() ) {
		     _message[serialDataCtr] =_gsmModem.read();
		     serialDataCtr++;
			
			 //if( (_message[serialDataCtr - 1] == 'O')&&(_message[serialDataCtr] == 'K') ) break;
		     serialTimeOut = 0;
	     }
	     serialTimeOut++;
	     Delay_us(5);
     }
     
     return serialDataCtr;
	
	
}

uint8_t gsm::getUartData(void){
	
unsigned int uartTimeOut = 0;
uint32_t uartDataCtr = 0;
uint8_t i;

		for(i=0; i<160; i++){ textMessage[i] = ' ';}   //clear uart recieve buffer

		for ( uartTimeOut = 0; uartTimeOut < 2000000; uartTimeOut++){

			
			if (_gsmModem.isDataReady()) { 	 // If data is received,
				                             
				 textMessage[ uartDataCtr] = _gsmModem.read();      // read the received data,
				 uartDataCtr++;
				 uartTimeOut = 0;

			}
			
			Delay_us(5);

		}

   return 1;
	
}

uint8_t gsm::getRxData( uint8_t * _rxBuffer, uint8_t serialData ){
	
	uint8_t serialDataCtr  = 0;
	uint32_t serialTimeOut = 0;
	
	while (serialTimeOut < 2000000){                               // get the first respose

		if (_gsmModem.isDataReady() ) {
			_rxBuffer[serialDataCtr] = _gsmModem.read();
			serialDataCtr++;
			if (serialDataCtr >= serialData ){  break;}
			serialTimeOut = 0;
		}
		serialTimeOut++;
		Delay_us(5);
	}
	
	return serialDataCtr;
}

uint8_t gsm::getRxData( uint8_t * _rxBuffer, uint8_t * serialData ){
	
uint8_t serialDataCtr  = 0;
uint32_t serialTimeOut = 0;
	
	while (serialTimeOut < 200000){                               // get the respose

		if (_gsmModem.isDataReady() ) {
			_rxBuffer[serialDataCtr] = _gsmModem.read();
			serialDataCtr++;
			if ((_rxBuffer[serialDataCtr-2] == serialData[0] )&&(_rxBuffer[serialDataCtr-1] == serialData[1] ) ){  return 1;}
			
			serialTimeOut = 0;
		}
		serialTimeOut++;
		Delay_us(1);
	}
	
	return 0;
}
#endif    // usingSim900						 
			 






///////////////////////////////////////////////////////////////////////////////
// SM 630
///////////////////////////////////////////////////////////////////////////////
#ifdef usingSm630

#ifndef usingUart
#define usingUart 
#endif  //usingUart

#define _sm630Head   0
#define _sm630Flag   2
#define _sm630Length 3

#define _sm630Command  0x10
#define _sm630Data     0x20
#define _sm630Last     0x21
#define _sm630Response 0x30

#define _sm630RxCorrect          0x01
#define _sm630RxError            0x02
#define _sm630OperationSuccess   0x31
#define _sm630FpDetected         0x32
#define _sm630TimeOut            0x33
#define _sm630ProcessFailure     0x34
#define _sm630ParameterError     0x35
#define _sm630FpMatch            0x37
#define _sm630FpNoMatch          0x38
#define _sm630FpFound            0x39
#define _sm630FpNotFound        0x3A

#define _sm630Error              0x00
#define _sm630TemplateError1     0xFD
#define _sm630TemplateError2     0xFE
#define _sm630FatalError         0xFF

#define SM630_FATAL_ERROR        0xFFFF
#define SM630_RECEIVE_ERROR      0xFFFE
#define SM630_OPERATION_SUCCESS  0xFFFD
#define SM630_TIME_OUT           0xFFFC
#define SM630_PROCESS_FAILURE    0xFFFB
#define SM630_PARAMETER_ERROR    0xFFFA
#define SM630_FP_MATCH           0xFFF9
#define SM630_FP_NO_MATCH        0xFFF8
#define SM630_FP_NOT_FOUND       0xFFF7
#define SM630_FP_FOUND           0xFFF6

uart _sm630;


class sm630 {
	
	public:

	//sm630 ();
	uint8_t init(uint32_t buadrate);
	uint8_t addFingerPrint(uint16_t add);
	uint8_t deleteFingerPrint(uint16_t add);
	uint8_t searchFingerPrint(uint16_t * id);
	uint8_t searchFingerPrintID(uint16_t id);
	uint8_t deleteDataBase(void);
	uint8_t uploadFingerPrintTemplate(uint8_t * _template, uint16_t add);
	
	uint8_t writeUserFlash (uint8_t * _txBuffer, uint16_t add, uint8_t bytes);   
	  
	//uint8_t downloadFingerPrintTemplate(uint8_t * template, uint16_t add);
	//uint8_t readUserFlash (uint8_t * template, uint16_t add, uint8_t bytes);
	//
	
	private:
	uint8_t getRxData ( uint8_t *_rxBuffer, uint8_t serialData );
	
	const uint8_t addPrintCmd[5]       =  {0x4D,0x58,0x10,0x03,0x40};                                //{0x4D,0x58,0x10, 0x03, 0x40,0x00,0x00,0xF8 };
	const uint8_t searchPrintCmd[10]   =  {0x4D,0x58,0x10,0x05,0x44,0x00,0x00,0x03,0x00,0x01}; 
	const uint8_t searchPrintIDCmd[5]  =  {0x4D,0x58,0x10,0x03,0x4B};                     //{0x4D,0x58,0x10,0x03,0x4B,0x00,0x00,0x03}
	const uint8_t deletePrintCmd[5]    =  {0x4D,0x58,0x10,0x03,0x42};                                  //{0x4D,0x58,0x10,0x03,0x42,0x00,0x00,0xFA };
	const uint8_t deleteDataBaseCmd[6] =  {0x4D,0x58,0x10, 0x01, 0x46,0xFC };
    const uint8_t rxCorrectCmd[6]      =  {0x4D,0x58,0x30,0x01,0x01,0xD7};
	const uint8_t uploadFPCmd [5]      =  {0x4D,0x58,0x10,0x03,0x52};     //{0x4D,0x58,0x10,0x03,0x52,0x00,0x00,0x0A}
    const uint8_t readUserFlashCmd[5]  =  {0x4D,0x58,0x10,0x04,0x62};         //0x4D,0x58,0x10,0x04,0x62,0x00,0x00,0x0A,0x25
	const uint8_t writeUserFlashCmd[5] =  {0x4D,0x58,0x10,0x06,0x64};         //{0x4D,0x58,0x10,0x06,0x64,0x00,0x00,0x02,0x21}
};

uint8_t sm630::init(uint32_t buadrate){
	_sm630.init(buadrate);    // initialize uart at 57600 buad rate
	
	return 0;
}


/*
The function returns the address or id of the finger print added when successful 
*/
uint8_t sm630::addFingerPrint(uint16_t ad_add){

uint8_t   i;
uint8_t rxBuffer[20];

uint8_t addPrintCmd0[3];

	  addPrintCmd0[0] =  Hi(ad_add);                                                                             // get high byte of address to add finger print
	  addPrintCmd0[1] =  Lo(ad_add);                                                                             // get low byte of address to add finger print
	  addPrintCmd0[2] = addPrintCmd0[0] + addPrintCmd0[1] + 0xF8 ;
	   
	 for (i=0; i<20; i++){ rxBuffer[i] = 0; }                                                                   // clear receive buffer (rxBuffer)
	 for (i=0; i<5; i++){ _sm630.write(addPrintCmd[i]);  }                                                      // send the add command to sm630
	 for (i=0; i<3; i++){ _sm630.write(addPrintCmd0[i]); } 
		 
	 getRxData( rxBuffer, 20);                                                                                  //get data 
	 
	  //for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	  //for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	  //for (i=0; i<7; i++){ rxBuffer3[i] = rxBuffer[i+13]; }
	  
	                                                     
	 if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )          { return _sm630RxError; }   //  return receive error
	 if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630ParameterError )  )         { return _sm630ParameterError; }   // return receive parameter error  
     if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630OperationSuccess) )         { return _sm630OperationSuccess; }
	 if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630ProcessFailure ) )          { return _sm630ProcessFailure; }   // return receive process failure
	 if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630TimeOut) )                  { return _sm630TimeOut; }   // Time out
	                
	 return 0xFF;                        // fatal Error
	
}

uint8_t sm630::deleteFingerPrint ( uint16_t del_add){
	
 uint8_t i;
 uint8_t deletePrintCmd0[3];
 uint8_t rxBuffer[20];
 	
	deletePrintCmd0[0] =  Hi(del_add);                                            //get high byte of address to add finger print
	deletePrintCmd0[1] =  Lo(del_add);											  // get low byte of address to add finger print
	deletePrintCmd0[2] = deletePrintCmd0[0] + deletePrintCmd0[1] + 0xFA;
	for (i=0; i<20; i++){ rxBuffer[i] = 0; }                                      // clear receive buffer (rxBuffer)
	for (i=0; i<5; i++){ _sm630.write(deletePrintCmd[i]);  }                      // send the add command to sm630    
	for (i=0; i<3; i++){ _sm630.write(deletePrintCmd0[i]); }
	
	getRxData( rxBuffer, 13);                                                                                  //get data
	
	//for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	//for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	//for (i=0; i<7; i++){ rxBuffer3[i] = rxBuffer[i+13]; }
	
	
	if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )          { return _sm630RxError; }   //  return receive error
	if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630ParameterError )  )         { return _sm630ParameterError; }   // return receive parameter error
	if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630OperationSuccess) )         { return _sm630OperationSuccess; }
	if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630ProcessFailure ) )          { return _sm630ProcessFailure; }   // return receive process failure
	if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630TimeOut) )                  { return _sm630TimeOut; }   // Time out
	
	return 0xFFFF;                        // fatal Error
	
}

uint8_t sm630::searchFingerPrint(uint16_t * id){
	 
 uint8_t i;
 uint8_t   rxBuffer[25];

	 for (i=0; i<25; i++){ rxBuffer[i] = 0; }  // clear receive buffer (rxBuffer)
	 
	 for (i=0; i<10; i++){  _sm630.write(searchPrintCmd[i]); }  //send the search command to sm630
	 
	 getRxData( rxBuffer, 22);                                                                                  //get data
	 
	 //for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	 //for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	 //for (i=0; i<9; i++){ rxBuffer3[i] = rxBuffer[i+13]; }
		  
	 if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )  { return SM630_RECEIVE_ERROR; }                                               //  return receive error 
	 if ( (rxBuffer[15]==_sm630Response) && (rxBuffer[18]==_sm630FpFound) )         {  *id = ((rxBuffer[19] << 8) +  rxBuffer[20]); return _sm630FpFound; }       // return fp  found
	 if ( (rxBuffer[15]==_sm630Response) && (rxBuffer[18]==_sm630FpNotFound )  )   {  *id = 0xFFF;                                 return _sm630FpNotFound; }   // return fp not found 		 
	 if ( (rxBuffer[15]==_sm630Response) && (rxBuffer[18]==_sm630ParameterError ) ) { return _sm630ParameterError; }                                              // return receive parameter error
	 if ( (rxBuffer[15]==_sm630Response) && (rxBuffer[18]==_sm630ProcessFailure ) ) { return _sm630ParameterError; }                                              // return receive process failure
	 if ( (rxBuffer[8] ==_sm630Response) && (rxBuffer[11]==_sm630TimeOut) )         { return _sm630TimeOut; }                                                     // Time out
		 
		 
	 return  0xFF;    //Fatal error
	 
	 
}

uint8_t sm630::searchFingerPrintID(uint16_t id){
    
uint8_t   i;
uint8_t rxBuffer[15];

uint8_t searchPrintIDCmd0[3];

	  searchPrintIDCmd0[0] =  Hi(id);                                                                             // get high byte of address to search for
	  searchPrintIDCmd0[1] =  Lo(id);                                                                             // get low byte of address to search for
	  searchPrintIDCmd0[2] = searchPrintIDCmd0[0] + searchPrintIDCmd0[1] + 0x03 ;
	   
	 for (i=0; i<15; i++){ rxBuffer[i] = 0; }                                                                   // clear receive buffer (rxBuffer)
	 for (i=0; i<5; i++){ _sm630.write(searchPrintIDCmd[i]);  }                                                      // send the add command to sm630
	 for (i=0; i<3; i++){ _sm630.write(searchPrintIDCmd0[i]); } 
		 
	 getRxData( rxBuffer, 13);                                                                                  //get data 
	 
	  //for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	  //for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	 
	  
	                                                     
	 if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )  { return _sm630RxError; }   //  return receive error
	 if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630FpMatch ) )         { return _sm630FpMatch; }   // return receive parameter error  
     if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630FpNoMatch ) )       { return _sm630FpNoMatch; }
	 
	 return 0xFF;                        // fatal Error
}
uint8_t sm630::deleteDataBase(void){
uint8_t i;
uint8_t   rxBuffer[15];

	for (i=0; i<15; i++){ rxBuffer[i] = 0; }  // clear receive buffer (rxBuffer)
	
	for (i=0; i<6; i++){   _sm630.write(deleteDataBaseCmd[i]); }  //send the delete DB command to sm630
	
	getRxData( rxBuffer, 13);                                                                                  //get data
	
	//for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	//for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	
	if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )  { return _sm630RxError; }   //  return receive error
	if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630OperationSuccess) ) { return _sm630OperationSuccess; }
	
	
	return SM630_FATAL_ERROR;                        // fatal Error
	

	
	
}
uint8_t sm630::uploadFingerPrintTemplate(uint8_t * _template, uint16_t add ){

 uint8_t   i;
 uint8_t rxBuffer[140];
 uint8_t uploadFPCmd0[3];

   uploadFPCmd0[0] =  Hi(add);                                                                             // get high byte of address to add finger print
   uploadFPCmd0[1] =  Lo(add);                                                                             // get low byte of address to add finger print
   uploadFPCmd0[2] =  uploadFPCmd0[0] + uploadFPCmd0[1] + 0x0A ;
   
   for (i=0; i<140; i++){ rxBuffer[i] = 0; }                                                                   // clear receive buffer (rxBuffer)
   for (i=0; i<5; i++){ _sm630.write(uploadFPCmd[i]);  }                                                      // send the add command to sm630
   for (i=0; i<3; i++){ _sm630.write(uploadFPCmd0[i]); }
  
   getRxData( rxBuffer, 139);  
   
                                                                                    //get data module rx correct + first pakage
   if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )   { return _sm630RxError; }   //  return receive error
   if ( (rxBuffer[_sm630Flag]!=_sm630Response) || (rxBuffer[4]!=_sm630RxCorrect) ) { return _sm630FatalError; }   //  return receive error	
   
   if ( (rxBuffer[8]!= 0x20) || (rxBuffer[9]!= 0x80) )          { return _sm630TemplateError1; }    
   for (i=0; i<128; i++){ _template[i] = rxBuffer[i+10]; }                 
	
   for (i=0; i<6; i++){ _sm630.write(rxCorrectCmd[i]);  }                                                      // send the rececive correct  command to sm630
  
   getRxData( rxBuffer, 133);
   if ( (rxBuffer[2]!= 0x21) || (rxBuffer[3]!= 0x80) )          { return _sm630TemplateError2; }  
  
   for (i=0; i<128; i++){ _template[i+128] = rxBuffer[i+4]; } 
                                                                               //get  Finger print template
   return _sm630OperationSuccess; 
   /* */
}

uint8_t sm630::writeUserFlash (uint8_t * _txBuffer, uint16_t add, uint8_t bytes){
	 
	 uint8_t   i;
	 uint8_t rxBuffer[15];

	 uint8_t writeUserFlashCmd0[3];
	 uint8_t checkSum;                                                                // clear receive buffer (rxBuffer)
	 if (bytes > 127) bytes = 127;
	 
	 writeUserFlashCmd0[0] =  Hi(add);                                                                             // get high byte of address to add finger print
	 writeUserFlashCmd0[1] =  Lo(add);																				// get low byte of address to add finger print
	 writeUserFlashCmd0[2] =  bytes;  
	                                                         
	 checkSum = writeUserFlashCmd0[0] + writeUserFlashCmd0[1] + writeUserFlashCmd0[2]  + 0x1F;                      //calculate checksum
	 for (i=0; i<bytes; i++){    checkSum =  checkSum + _txBuffer[i]; }                                                   
		
	 for (i=0; i<15; i++){ rxBuffer[i] = 0; }                                                                    // clear receive buffer (rxBuffer)
	 
	 for (i=0; i<5; i++){ _sm630.write(writeUserFlashCmd[i]);  }                                                 // send the write user flash command to sm630
	 for (i=0; i<3; i++){ _sm630.write(writeUserFlashCmd0[i]); }                                                 // send the write user flash command to sm630
	 for (i=0; i<bytes; i++){ _sm630.write(_txBuffer[i]); }                                                      //send data
	 _sm630.write(checkSum);                                                                                     //send checsum
	  
	 getRxData( rxBuffer, 13);                                                                                  //get data
	 
	 //for (i=0; i<6; i++){ rxBuffer1[i] = rxBuffer[i];   }
	 //for (i=0; i<7; i++){ rxBuffer2[i] = rxBuffer[i+6]; }
	
	 
	 if ( (rxBuffer[_sm630Flag]==_sm630Response) && (rxBuffer[4]==_sm630RxError) )          { return _sm630RxError; }   //  return receive error
	 if ( (rxBuffer[8]==_sm630Response) && (rxBuffer[11]==_sm630OperationSuccess) )         { return _sm630OperationSuccess; }
	
	 return _sm630Error;
}
/*
uint8_t downloadFingerPrintTemplate(uint8_t * template){
	
	
}
	
	

uint8_t readUserFlash (uint8_t * template){
	
	
}


*/


uint8_t sm630::getRxData( uint8_t * _rxBuffer, uint8_t serialData ){
	
 uint8_t serialDataCtr  = 0;
 uint32_t serialTimeOut = 0;
	
	while (serialTimeOut < 2000000){                               // get the first respose

		if (_sm630.isDataReady() ) {
			_rxBuffer[serialDataCtr] = _sm630.read();
			serialDataCtr++;
			if (serialDataCtr >= serialData ){  break;}
			serialTimeOut = 0;
		}
		serialTimeOut++;
		Delay_us(5);
	}
	
	return serialDataCtr;
}


#endif    // usingSm630

//////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
////
//
////////////////////////////////////////////////////////////


#ifdef usingKeypad4X4




uint8_t  readKeypad4X4 (void){
uint8_t keypadData = 255;
	
	keypadPort = 0x0F;
	keypadPortDirection  = 0xF0;
	Delay_us(5);
	

	if (keypadRow0==0){
		keypadData = 0;
		goto _keypadColumn;
	}
	else{
		if(keypadRow1==0){
			keypadData = 4;
			goto _keypadColumn;
		}
		else{
			if(keypadRow2==0){
				keypadData = 8;
				goto _keypadColumn;
			}
			else{
				if (keypadRow3==0){
					keypadData = 12;
					goto _keypadColumn;
				}
				else{
					//goto _keypadReturnKey;
					return 255;
				}
			}
		}
	}

	_keypadColumn:
	keypadPort = 0xF0;
	keypadPortDirection  = 0x0F;
	Delay_us(5);

	if (keypadCol0==0){
		keypadData = keypadData + 0;
		goto _keypadReturnKey;
	}
	else{
		if(keypadCol1==0){
			keypadData = keypadData + 1;
			goto _keypadReturnKey;
		}
		else{
			if( keypadCol2==0  ){
				keypadData = keypadData + 2;
				goto _keypadReturnKey;
			}
			else{
				if (keypadCol3==0){
					keypadData = keypadData + 3;
					goto _keypadReturnKey;
				}
				else{
					//keypadData = 255;
					return 255;
				}
			}
		}
	}

	_keypadReturnKey:

	return keypadData;

}


#endif
//////////////////////////////////////////////

#ifdef usingP10


#include <avr/interrupt.h>
#include <avr/pgmspace.h>


uint8_t scanPtr = 0;
uint8_t brightnessPercentage = 100;
uint8_t shiftCtr = 1;

bitVariable status;
#define shiftEnable    status.B0
#define enableDisplay  status.B1
#define LEFT  0
#define RIGHT 1
#define maxSROnRoll  ( maxDisplayRoll* 4   ) 
#define maxBitOnRoll ( maxDisplayCol * 16  )
#define maxCollBit   ( maxDisplayRoll * 32 )

char leftLoadRAM[maxBitOnRoll][2];
char displayRAM[maxBitOnRoll][maxSROnRoll];


void clockData (void);
void latchData (void);
void shiftDisplayLeft(char n);

void clockData (void){

	shiftClockPin = 0;
	shiftClockPin = 1;
}

void latchData (void){

	latchClockPin = 0;
	latchClockPin = 1;
}


void shiftData(char srData){
	uint8_t i=0;

	for(i=0; i<8; i++){
		
		if (srData&128) data1Pin = 1;
		else data1Pin = 0;
		
		clockData();
		srData = srData << 1;
	}

}


class p10{
	 
	       public:
	        //p10 (char columnNum, char rowNum );
            void init(char n, char BRT);
            char writeText (char *_message, char align);
			char scrollText(char *_message, char speed);
			void shiftDisplayLeft(char n);
			void clearDRAM(void);
			
		   private:
		      char loadChar(char ascii_ascii);
	          void scrolDelay(char myDelay);
	};

/*
p10::p10(char columnNum, char rowNum )
:maxDisplayCol (rowNum), maxDisplayRoll(columnNum)
{
	
}
*/

void p10::init(char FREQ, char BRT){
	
	enablePinDir   = 1;
	addressAPinDir = 1;
	addressBPinDir = 1;

	shiftClockPinDir = 1;
	latchClockPinDir = 1;
	data1PinDir = 1;
	
	enablePin   = 0;
	addressAPin = 0;
	addressBPin = 0;

	shiftClockPin = 1;
	latchClockPin = 1;
	data1Pin = 0;
	
	enableDisplay = 1;
	
	uint8_t i =  (uint8_t)(  F_CPU / ( 4 * PRESCALLER  * FREQ )) ;
	
	OCR2A = i;
	OCR2B  = ( BRT * i )/ 100 ;
	TCCR2A = 0b00000011;
	TCCR2B = 0b00001111;
	TIMSK2 = 0b00000101;
	
	enableGlobalInterrupt;
	
	
}
char p10::scrollText(char *_message , char speed){
	
	shiftCtr = 1;
	while (*_message != endOfString){
		shiftCtr--;
		if (shiftCtr == 0){
			shiftCtr = loadChar( *_message);
			_message++;
		}
		shiftDisplayLeft(1);
		scrolDelay( speed);
	}
	
	return 0;
}

char p10::writeText(char *_message, char align){
	unsigned int alignPtr=0;
	
	enableDisplay = 0;
	
	shiftCtr = 1;
	while ( 1 ){
		
		shiftCtr--;
		if (shiftCtr == 0){
			
			if  (*_message != endOfString ){
				shiftCtr = loadChar( *_message);
				_message++;
			}
			else{
				if(align == RIGHT){  enableDisplay = 1; return 0; }
			}
		}
		shiftDisplayLeft(1);
		if(align == LEFT){
			alignPtr++;
			if(alignPtr >= maxCollBit) { enableDisplay = 1;  return 0; }
		}
	}
	
	return 0;
}


void p10::scrolDelay(char myDelay){
	
	
	
	for(uint8_t i=0; i<myDelay; i++){
	   _delay_ms (1);
	}
}

void p10::clearDRAM(void){
	
	for (uint8_t i =0; i<maxBitOnRoll; i++){
		
		for (uint8_t j=0; j<maxSROnRoll; j++){
			displayRAM[i][j] = 0xFF;
			
		}
	}
}




void p10::shiftDisplayLeft(char n){

	uint8_t x, y;
	
	shiftEnable = 1;
	for (x=0 ; x<maxBitOnRoll; x++){
		
		for (y=0 ; y < maxSROnRoll-1; y++){
			displayRAM[x][y] = displayRAM[x][y] << 1;
			if (displayRAM[x][y+1] & 128) displayRAM[x][y] = displayRAM[x][y] | 0b00000001; else displayRAM[x][y] = displayRAM[x][y] & 0b11111110 ;
			
		}
		
		displayRAM[x][y] = displayRAM[x][y] << 1;
		if (leftLoadRAM[x][0] & 128) displayRAM[x][y] = displayRAM[x][y] | 0b00000001; else displayRAM[x][y] = displayRAM[x][y] & 0b11111110 ;
		
		leftLoadRAM[x][0] = leftLoadRAM[x][0] << 1;
		if (leftLoadRAM[x][1] & 128) leftLoadRAM[x][0] = leftLoadRAM[x][0] | 0b00000001; else leftLoadRAM[x][0] = leftLoadRAM[x][0] & 0b11111110 ;
		
		leftLoadRAM[x][1] = leftLoadRAM[x][1] << 1;
		leftLoadRAM[x][1] = leftLoadRAM[x][1] | 0b00000001;
		
	}
	
	
	shiftEnable = 0;
}


char p10::loadChar(char ascii_char){
	
	unsigned short int i,j,k;
	//serial.write(ascii_char);
	
	k = 0;
	j = 1;

	for (i= 0; i < 16; i++){
		leftLoadRAM[i][1] = pgm_read_byte ( &Arial_16X16_Code[(ascii_char - 32)][k] );
		leftLoadRAM[i][0] = pgm_read_byte ( &Arial_16X16_Code[(ascii_char - 32)][j] );
		k = k+2;
		j = j+2;
	}

	return ( pgm_read_byte ( &Arial_16X16_Code[(ascii_char - 32)][k] ) ) ;
	
}
/*
void p10::scrolDelay(char myDelay){
	for(uint8_t i=0; i<myDelay; i++){  _delay_ms (1); }
}
*/

ISR (TIMER2_OVF_vect) {
	uint8_t i,x, y;
	char data;
	
	for(y = 0; y < maxSROnRoll; y++){
		
		x= 15 - scanPtr;
		for(i=0; i<4; i++ ){
			data = displayRAM[x][y];
			shiftData(data);
			x = x - 4;
		}
	}

	switch(scanPtr){
		case(0):{ addressBPin = 1; addressAPin = 1;  scanPtr = 1; break; }
		case(1):{ addressBPin = 1; addressAPin = 0;  scanPtr = 2; break; }
		case(2):{ addressBPin = 0; addressAPin = 1;  scanPtr = 3; break; }
		case(3):{ addressBPin = 0; addressAPin = 0;  scanPtr = 0; break; }
	}
	
	latchData();
	if (enableDisplay == 1 ) enablePin = 1;
}

ISR (TIMER2_COMPB_vect) {
	
	enablePin = 0;
}


#endif
//////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////



#ifdef usingHC595LedMatrix
#include <avr/interrupt.h>


#define PRESCALLER 256.0 
uint8_t scanPtr = 0;
uint8_t shiftCtr = 1;

bitVariable status;
#define shiftEnable status.B0

char LoadRAM[8];
char DRAM[8][n595];
//char SRAM[8][n595];

char SRAM[8][n595] = {
	{ 0b00010000, 0b00111000 },
	{ 0b00110000, 0b01000100 },
	{ 0b00010000, 0b00000100 },
	{ 0b00010000, 0b00000100 },
	{ 0b00010000, 0b00111000 },
	{ 0b00010000, 0b01000000 },
	{ 0b00111000, 0b01111100 },
	{ 0b00000000, 0b00000000 }
};

//void scrolDelay(void){  Delay_ms(150);  }

/*
#define n595  2                 // numbers of 74HC595

#define enablePin    PORTB_B1
#define dataInPin    PORTB_B3
#define shiftClkPin  PORTB_B4
#define latchClkPin  PORTB_B5

#define enableDir    DDRB_B1
#define dataInDir    DDRB_B3
#define dhiftClkDir  DDRB_B4
#define latchClkDir  DDRB_B5

#define addAPin  PORTC_B0
#define addBPin  PORTC_B1
#define addCPin  PORTC_B2

#define addADir  DDRC_B0
#define addBDir  DDRC_B1
#define addCDir  DDRC_B2

*/

 void clockColumnData (void);
 void latchColumnData (void);
 void shiftColumnData(char srData);
 
class HC595LedMatrix {
	
	public:	
	void init(char FREQ, char BRT);
	char scrolText(char *_message, char speed);
	void shiftDisplayLeft(char n);
	void clearDRAM(void);
	void clearSRAM(void);
	
	private:
    char loadChar(char ascii);
	void scrolDelay(char myDelay);
	
	
};



void HC595LedMatrix::init(char FREQ, char BRT){
	
	
	shiftEnable  = 0;
	
	enableDir    = 1;
	dataInDir    = 1;
	shiftClkDir  = 1;
	latchClkDir  = 1;
	
	
	enablePin   = 0;
	dataInPin   = 0;
	latchClkPin = 1;
	shiftClkPin = 1;
	
	
	addAPin  = 1;
	addBPin  = 1;
	addCPin   =1;

	addADir   =1;
	addBDir   =1;
	addCDir   =1;
	
	
	uint8_t i =  (uint8_t)(  F_CPU / ( 8 *PRESCALLER*FREQ )) ;
	
	OCR2A = i;
	OCR2B  = ( BRT * i )/ 100 ;
	TCCR2A = 0b00000011;
	TCCR2B = 0b00001110;
	TIMSK2 = 0b00000101;
	
	enableGlobalInterrupt;     //enable global interrupts
	
	
}


char HC595LedMatrix::scrolText(char *_message , char speed){
	
	speed = 255 - speed;
	
	shiftCtr = 1;
	while (*_message != endOfString){
		shiftCtr--;
		if (shiftCtr == 0){
			shiftCtr = loadChar( *_message);
			_message++;
		}
		shiftDisplayLeft(1);
		scrolDelay(speed);
	}
	
	return 0;
}

void HC595LedMatrix::shiftDisplayLeft(char n){

	uint8_t x, y;
	
	shiftEnable = 1;
	for(x=0; x<8; x++){
		
		for(y=0; y<n595 - 1; y++){
			
			DRAM[x][y] = DRAM[x][y] << 1;
			if (DRAM[x][y+1] & 128) DRAM[x][y] = DRAM[x][y] | 0b00000001 ;
			else DRAM[x][y] = DRAM[x][y] & 0b11111110 ;
			
		}
		
		DRAM[x][y] = DRAM[x][y] << 1;
		
		if (LoadRAM[x] & 128) DRAM[x][y] = DRAM[x][y] | 0b00000001 ;
		else DRAM[x][y] = DRAM[x][y] & 0b11111110 ;
		
		LoadRAM[x] = LoadRAM[x] << 1;
		
	}
	
	shiftEnable = 0;
}

void HC595LedMatrix::clearDRAM(void){
	
	
	for (uint8_t x=0; x< 8; x++){
		
		for (uint8_t y=0; y< n595; y++){
			
			DRAM[x][y] = 0;
		}
		
	}
	
}

void HC595LedMatrix::clearSRAM(void){
	
	for (uint8_t x=0; x<8; x++){
		
		for (uint8_t y=0; y< n595; y++){  
			SRAM[x][y] = 0;
		}
		
	}
	
}

char HC595LedMatrix::loadChar(char ascii){
	uint8_t i=0;

	//serial.write(ascii);
	
	for ( i=0; i<8; i++){  LoadRAM[i] = charCode[ascii - 32][i];  }
	return  charCode[ascii - 32][i];
}


void HC595LedMatrix::scrolDelay(char myDelay){
	for(uint8_t i=0; i<myDelay; i++){  _delay_ms (1); }
}

void clockColumnData (void){

	shiftClkPin = 0;
	shiftClkPin = 1;
}

void latchColumnData (void){

	latchClkPin = 0;
	latchClkPin = 1;
}

void shiftColumnData(char srData){

	uint8_t i = 0;

	for(i=0; i<8; i++){
		
		if (srData&128) dataInPin = 1;
		else dataInPin = 0;
		
		clockColumnData();
		srData = srData << 1;
	}

}

ISR (TIMER2_OVF_vect ){
	
	if (shiftEnable == 0){                               // update screen ram when not shifting
		
		for(uint8_t x =0; x<8; x++){
			
			for(uint8_t y =0; y<n595; y++){
				SRAM[x][y] = DRAM[x][y];
			}
		}
		
	}
	

	for(uint8_t i = 0; i< n595; i++){  shiftColumnData ( 255 - SRAM[scanPtr][i] );  }
		
	if(scanPtr & 0x1 )  addAPin = 1; else addAPin = 0;
	if(scanPtr & 0x2 )  addBPin = 1; else addBPin = 0;
	if(scanPtr & 0x4 )  addCPin = 1; else addCPin = 0;
	  
	latchColumnData();
	
	scanPtr++;
	if (scanPtr >=8 )  scanPtr = 0;
	enablePin = 0;
}

ISR (TIMER2_COMPB_vect) {
	
	enablePin = 1;
}

#endif 

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////

#ifdef usingDs18b20

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
/*
//setup connection
#define ds1820Port PORTB
#define ds1820Dir  DDRB
#define ds1820Pin  PINB
#define ds1820Dq   PB4
*/
//commands



#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec

//stop any interrupt on read
#define DS18B20_STOPINTERRUPTONREAD 1

class ds1820{
	
	         public:
			 double read(void);
			 
			 private:
	         uint8_t reset(void);
	         void writebit(uint8_t bit);
			 uint8_t readbit(void);
			 void writebyte(uint8_t byte);
			 uint8_t readbyte(void);
	};


uint8_t ds1820::reset() {
	uint8_t i;

	//low for 480us
	ds1820Port &= ~ (1<<ds1820Dq); //low
	ds1820Dir |= (1<<ds1820Dq); //output
	_delay_us(480);

	//release line and wait for 60uS
	ds1820Dir &= ~(1<<ds1820Dq); //input
	_delay_us(60);

	//get value and wait 420us
	i = (ds1820Pin & (1<<ds1820Dq));
	_delay_us(420);

	//return the read value, 0=ok, 1=error
	return i;
}

/*
 * write one bit
 */
void ds1820::writebit(uint8_t bit){
	//low for 1uS
	ds1820Port &= ~ (1<<ds1820Dq); //low
	ds1820Dir |= (1<<ds1820Dq); //output
	_delay_us(1);

	//if we want to write 1, release the line (if not will keep low)
	if(bit)
		ds1820Dir &= ~(1<<ds1820Dq); //input

	//wait 60uS and release the line
	_delay_us(60);
	ds1820Dir &= ~(1<<ds1820Dq); //input
}

/*
 * read one bit
 */
uint8_t ds1820::readbit(void){
	uint8_t bit=0;

	//low for 1uS
	ds1820Port &= ~ (1<<ds1820Dq); //low
	ds1820Dir |= (1<<ds1820Dq); //output
	_delay_us(1);

	//release line and wait for 14uS
	ds1820Dir &= ~(1<<ds1820Dq); //input
	_delay_us(14);

	//read the value
	if(ds1820Pin & (1<<ds1820Dq))
		bit=1;

	//wait 45uS and return read value
	_delay_us(45);
	return bit;
}

/*
 * write one byte
 */
void ds1820::writebyte(uint8_t byte){
	uint8_t i=8;
	while(i--){
		writebit(byte&1);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
uint8_t ds1820::readbyte(void){
	uint8_t i=8, n=0;
	while(i--){
		n >>= 1;
		n |= (readbit()<<7);
	}
	return n;
}

/*
 * get temperature
 */
double ds1820::read() {
	uint8_t temperature_l;
	uint8_t temperature_h;
	double retd = 0;

	#if DS18B20_STOPINTERRUPTONREAD == 1
	cli();
	#endif

	reset(); //reset
	writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	writebyte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

	while(!readbit()); //wait until conversion is complete

	reset(); //reset
	writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	writebyte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	//read 2 byte from scratchpad
	temperature_l = readbyte();
	temperature_h = readbyte();

	#if DS18B20_STOPINTERRUPTONREAD == 1
	sei();
	#endif

	//convert the 12 bit value obtained
	retd = ( ( temperature_h << 8 ) + temperature_l ) * 0.0625;

	return retd;
}

#endif
////////////////////////////////////////////////////////////////////////////////////










 #endif //SAL_H