
// ports
// uart
// adc


#ifndef HAL
#define HAL_H 1

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     usingBuiltin Function
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	


typedef struct
{
	char B0:1;
	char B1:1;
	char B2:1;
	char B3:1;
	char B4:1;
	char B5:1;
	char B6:1;
	char B7:1;
} bitVariable, bitVar;

#define REGISTER_BIT(rg,bt) ((volatile bitVariable*)&rg)->B##bt

////////////////////////////////////////////////////////////////////////////////////////////////
#if defined (__AVR_ATmega16__) || (__AVR_ATmega16A__) || (__AVR_ATmega32__)|| (__AVR_ATmega32A__)|| (__AVR_ATmega1284P__)

#define DDRA_B0 REGISTER_BIT(DDRA,0)
#define DDRA_B1 REGISTER_BIT(DDRA,1)
#define DDRA_B2 REGISTER_BIT(DDRA,2)
#define DDRA_B3 REGISTER_BIT(DDRA,3)
#define DDRA_B4 REGISTER_BIT(DDRA,4)
#define DDRA_B5 REGISTER_BIT(DDRA,5)
#define DDRA_B6 REGISTER_BIT(DDRA,6)
#define DDRA_B7 REGISTER_BIT(DDRA,7)
#define PORTA_B0 REGISTER_BIT(PORTA,0)
#define PORTA_B1 REGISTER_BIT(PORTA,1)
#define PORTA_B2 REGISTER_BIT(PORTA,2)
#define PORTA_B3 REGISTER_BIT(PORTA,3)
#define PORTA_B4 REGISTER_BIT(PORTA,4)
#define PORTA_B5 REGISTER_BIT(PORTA,5)
#define PORTA_B6 REGISTER_BIT(PORTA,6)
#define PORTA_B7 REGISTER_BIT(PORTA,7)
#define PINA_B0 REGISTER_BIT(PINA,0)
#define PINA_B1 REGISTER_BIT(PINA,1)
#define PINA_B2 REGISTER_BIT(PINA,2)
#define PINA_B3 REGISTER_BIT(PINA,3)
#define PINA_B4 REGISTER_BIT(PINA,4)
#define PINA_B5 REGISTER_BIT(PINA,5)
#define PINA_B6 REGISTER_BIT(PINA,6)
#define PINA_B7 REGISTER_BIT(PINA,7)

#define DDRB_B0 REGISTER_BIT(DDRB,0)
#define DDRB_B1 REGISTER_BIT(DDRB,1)
#define DDRB_B2 REGISTER_BIT(DDRB,2)
#define DDRB_B3 REGISTER_BIT(DDRB,3)
#define DDRB_B4 REGISTER_BIT(DDRB,4)
#define DDRB_B5 REGISTER_BIT(DDRB,5)
#define DDRB_B6 REGISTER_BIT(DDRB,6)
#define DDRB_B7 REGISTER_BIT(DDRB,7)
#define PORTB_B0 REGISTER_BIT(PORTB,0)
#define PORTB_B1 REGISTER_BIT(PORTB,1)
#define PORTB_B2 REGISTER_BIT(PORTB,2)
#define PORTB_B3 REGISTER_BIT(PORTB,3)
#define PORTB_B4 REGISTER_BIT(PORTB,4)
#define PORTB_B5 REGISTER_BIT(PORTB,5)
#define PORTB_B6 REGISTER_BIT(PORTB,6)
#define PORTB_B7 REGISTER_BIT(PORTB,7)
#define PINB_B0 REGISTER_BIT(PINB,0)
#define PINB_B1 REGISTER_BIT(PINB,1)
#define PINB_B2 REGISTER_BIT(PINB,2)
#define PINB_B3 REGISTER_BIT(PINB,3)
#define PINB_B4 REGISTER_BIT(PINB,4)
#define PINB_B5 REGISTER_BIT(PINB,5)
#define PINB_B6 REGISTER_BIT(PINB,6)
#define PINB_B7 REGISTER_BIT(PINB,7)

#define DDRC_B0 REGISTER_BIT(DDRC,0)
#define DDRC_B1 REGISTER_BIT(DDRC,1)
#define DDRC_B2 REGISTER_BIT(DDRC,2)
#define DDRC_B3 REGISTER_BIT(DDRC,3)
#define DDRC_B4 REGISTER_BIT(DDRC,4)
#define DDRC_B5 REGISTER_BIT(DDRC,5)
#define DDRC_B6 REGISTER_BIT(DDRC,6)
#define DDRC_B7 REGISTER_BIT(DDRC,7)
#define PORTC_B0 REGISTER_BIT(PORTC,0)
#define PORTC_B1 REGISTER_BIT(PORTC,1)
#define PORTC_B2 REGISTER_BIT(PORTC,2)
#define PORTC_B3 REGISTER_BIT(PORTC,3)
#define PORTC_B4 REGISTER_BIT(PORTC,4)
#define PORTC_B5 REGISTER_BIT(PORTC,5)
#define PORTC_B6 REGISTER_BIT(PORTC,6)
#define PORTC_B7 REGISTER_BIT(PORTC,7)
#define PINC_B0 REGISTER_BIT(PINC,0)
#define PINC_B1 REGISTER_BIT(PINC,1)
#define PINC_B2 REGISTER_BIT(PINC,2)
#define PINC_B3 REGISTER_BIT(PINC,3)
#define PINC_B4 REGISTER_BIT(PINC,4)
#define PINC_B5 REGISTER_BIT(PINC,5)
#define PINC_B6 REGISTER_BIT(PINC,6)
#define PINC_B7 REGISTER_BIT(PINC,7)

#define DDRD_B0 REGISTER_BIT(DDRD,0)
#define DDRD_B1 REGISTER_BIT(DDRD,1)
#define DDRD_B2 REGISTER_BIT(DDRD,2)
#define DDRD_B3 REGISTER_BIT(DDRD,3)
#define DDRD_B4 REGISTER_BIT(DDRD,4)
#define DDRD_B5 REGISTER_BIT(DDRD,5)
#define DDRD_B6 REGISTER_BIT(DDRD,6)
#define DDRD_B7 REGISTER_BIT(DDRD,7)
#define PORTD_B0 REGISTER_BIT(PORTD,0)
#define PORTD_B1 REGISTER_BIT(PORTD,1)
#define PORTD_B2 REGISTER_BIT(PORTD,2)
#define PORTD_B3 REGISTER_BIT(PORTD,3)
#define PORTD_B4 REGISTER_BIT(PORTD,4)
#define PORTD_B5 REGISTER_BIT(PORTD,5)
#define PORTD_B6 REGISTER_BIT(PORTD,6)
#define PORTD_B7 REGISTER_BIT(PORTD,7)
#define PIND_B0 REGISTER_BIT(PIND,0)
#define PIND_B1 REGISTER_BIT(PIND,1)
#define PIND_B2 REGISTER_BIT(PIND,2)
#define PIND_B3 REGISTER_BIT(PIND,3)
#define PIND_B4 REGISTER_BIT(PIND,4)
#define PIND_B5 REGISTER_BIT(PIND,5)
#define PIND_B6 REGISTER_BIT(PIND,6)
#define PIND_B7 REGISTER_BIT(PIND,7)

#define pin0 PORTA_B0
#define pin1 PORTA_B1
#define pin2 PORTA_B2
#define pin3 PORTA_B3
#define pin4 PORTA_B4
#define pin5 PORTA_B5
#define pin6 PORTA_B6
#define pin7 PORTA_B7

#define pin8  PORTB_B0
#define pin9  PORTB_B1
#define pin10 PORTB_B2
#define pin11 PORTB_B3
#define pin12 PORTB_B4
#define pin13 PORTB_B5
#define pin14 PORTB_B6
#define pin15 PORTB_B7

#define pin16 PORTC_B0
#define pin17 PORTC_B1
#define pin18 PORTC_B2
#define pin19 PORTC_B3
#define pin20 PORTC_B4
#define pin21 PORTC_B5
#define pin22 PORTC_B6
#define pin23 PORTC_B7

#define pin24 PORTD_B0
#define pin25 PORTD_B1
#define pin26 PORTD_B2
#define pin27 PORTD_B3
#define pin28 PORTD_B4
#define pin29 PORTD_B5
#define pin30 PORTD_B6
#define pin31 PORTD_B7

#endif
////////////////////////////////////////////////////////////////////////////////////////////////

#if defined (__AVR_ATmega8__)||(__AVR_ATmega48__)||(__AVR_ATmega88P__)||(__AVR_ATmega328P__)

#define DDRB_B0 REGISTER_BIT(DDRB,0)
#define DDRB_B1 REGISTER_BIT(DDRB,1)
#define DDRB_B2 REGISTER_BIT(DDRB,2)
#define DDRB_B3 REGISTER_BIT(DDRB,3)
#define DDRB_B4 REGISTER_BIT(DDRB,4)
#define DDRB_B5 REGISTER_BIT(DDRB,5)
#define DDRB_B6 REGISTER_BIT(DDRB,6)
#define DDRB_B7 REGISTER_BIT(DDRB,7)
#define PORTB_B0 REGISTER_BIT(PORTB,0)
#define PORTB_B1 REGISTER_BIT(PORTB,1)
#define PORTB_B2 REGISTER_BIT(PORTB,2)
#define PORTB_B3 REGISTER_BIT(PORTB,3)
#define PORTB_B4 REGISTER_BIT(PORTB,4)
#define PORTB_B5 REGISTER_BIT(PORTB,5)
#define PORTB_B6 REGISTER_BIT(PORTB,6)
#define PORTB_B7 REGISTER_BIT(PORTB,7)
#define PINB_B0 REGISTER_BIT(PINB,0)
#define PINB_B1 REGISTER_BIT(PINB,1)
#define PINB_B2 REGISTER_BIT(PINB,2)
#define PINB_B3 REGISTER_BIT(PINB,3)
#define PINB_B4 REGISTER_BIT(PINB,4)
#define PINB_B5 REGISTER_BIT(PINB,5)
#define PINB_B6 REGISTER_BIT(PINB,6)
#define PINB_B7 REGISTER_BIT(PINB,7)

#define DDRC_B0 REGISTER_BIT(DDRC,0)
#define DDRC_B1 REGISTER_BIT(DDRC,1)
#define DDRC_B2 REGISTER_BIT(DDRC,2)
#define DDRC_B3 REGISTER_BIT(DDRC,3)
#define DDRC_B4 REGISTER_BIT(DDRC,4)
#define DDRC_B5 REGISTER_BIT(DDRC,5)
#define DDRC_B6 REGISTER_BIT(DDRC,6)
#define DDRC_B7 REGISTER_BIT(DDRC,7)
#define PORTC_B0 REGISTER_BIT(PORTC,0)
#define PORTC_B1 REGISTER_BIT(PORTC,1)
#define PORTC_B2 REGISTER_BIT(PORTC,2)
#define PORTC_B3 REGISTER_BIT(PORTC,3)
#define PORTC_B4 REGISTER_BIT(PORTC,4)
#define PORTC_B5 REGISTER_BIT(PORTC,5)
#define PORTC_B6 REGISTER_BIT(PORTC,6)
#define PORTC_B7 REGISTER_BIT(PORTC,7)
#define PINC_B0 REGISTER_BIT(PINC,0)
#define PINC_B1 REGISTER_BIT(PINC,1)
#define PINC_B2 REGISTER_BIT(PINC,2)
#define PINC_B3 REGISTER_BIT(PINC,3)
#define PINC_B4 REGISTER_BIT(PINC,4)
#define PINC_B5 REGISTER_BIT(PINC,5)
#define PINC_B6 REGISTER_BIT(PINC,6)
#define PINC_B7 REGISTER_BIT(PINC,7)


#define DDRD_B0 REGISTER_BIT(DDRD,0)
#define DDRD_B1 REGISTER_BIT(DDRD,1)
#define DDRD_B2 REGISTER_BIT(DDRD,2)
#define DDRD_B3 REGISTER_BIT(DDRD,3)
#define DDRD_B4 REGISTER_BIT(DDRD,4)
#define DDRD_B5 REGISTER_BIT(DDRD,5)
#define DDRD_B6 REGISTER_BIT(DDRD,6)
#define DDRD_B7 REGISTER_BIT(DDRD,7)
#define PORTD_B0 REGISTER_BIT(PORTD,0)
#define PORTD_B1 REGISTER_BIT(PORTD,1)
#define PORTD_B2 REGISTER_BIT(PORTD,2)
#define PORTD_B3 REGISTER_BIT(PORTD,3)
#define PORTD_B4 REGISTER_BIT(PORTD,4)
#define PORTD_B5 REGISTER_BIT(PORTD,5)
#define PORTD_B6 REGISTER_BIT(PORTD,6)
#define PORTD_B7 REGISTER_BIT(PORTD,7)
#define PIND_B0 REGISTER_BIT(PIND,0)
#define PIND_B1 REGISTER_BIT(PIND,1)
#define PIND_B2 REGISTER_BIT(PIND,2)
#define PIND_B3 REGISTER_BIT(PIND,3)
#define PIND_B4 REGISTER_BIT(PIND,4)
#define PIND_B5 REGISTER_BIT(PIND,5)
#define PIND_B6 REGISTER_BIT(PIND,6)
#define PIND_B7 REGISTER_BIT(PIND,7)


#define pin8  PORTB_B0
#define pin9  PORTB_B1
#define pin10 PORTB_B2
#define pin11 PORTB_B3
#define pin12 PORTB_B4
#define pin13 PORTB_B5
#define pin14 PORTB_B6
#define pin15 PORTB_B7

#define pin16 PORTC_B0
#define pin17 PORTC_B1
#define pin18 PORTC_B2
#define pin19 PORTC_B3
#define pin20 PORTC_B4
#define pin21 PORTC_B5
#define pin22 PORTC_B6
#define pin23 PORTC_B7

#define pin24 PORTD_B0
#define pin25 PORTD_B1
#define pin26 PORTD_B2
#define pin27 PORTD_B3
#define pin28 PORTD_B4
#define pin29 PORTD_B5
#define pin30 PORTD_B6
#define pin31 PORTD_B7

#endif
////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     usingPort
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef usingPort
 
 
 
 #if defined (__AVR_ATmega16__) || (__AVR_ATmega16A__) || (__AVR_ATmega32__)|| (__AVR_ATmega1284P__)
     #define pinMode(pinName, bitMode)      { if(pinName==PORTA_B0)DDRA_B0=bitMode; if(pinName==PORTA_B1)DDRA_B1=bitMode; if(pinName==PORTA_B2)DDRA_B2=bitMode; if(pinName==PORTA_B3)DDRA_B3=bitMode; if(pinName==PORTA_B4)DDRA_B4=bitMode; if(pinName==PORTA_B5)DDRA_B5=bitMode; if(pinName==PORTA_B6)DDRA_B6=bitMode; if(pinName==PORTA_B7)DDRA_B7=bitMode;  if(pinName==PORTB_B0)DDRB_B0=bitMode; if(pinName==PORTB_B1)DDRB_B1=bitMode; if(pinName==PORTB_B2)DDRB_B2=bitMode; if(pinName==PORTB_B3)DDRB_B3=bitMode; if(pinName==PORTB_B4)DDRB_B4=bitMode; if(pinName==PORTB_B5)DDRB_B5=bitMode; if(pinName==PORTB_B6)DDRB_B6=bitMode; if(pinName==PORTB_B7)DDRB_B7=bitMode; if(pinName==PORTC_B0)DDRC_B0=bitMode; if(pinName==PORTC_B1)DDRC_B1=bitMode; if(pinName==PORTC_B2)DDRC_B2=bitMode; if(pinName==PORTC_B3)DDRC_B3=bitMode; if(pinName==PORTC_B4)DDRC_B4=bitMode; if(pinName==PORTC_B5)DDRC_B5=bitMode; if(pinName==PORTC_B6)DDRC_B6=bitMode; if(pinName==PORTC_B7)DDRC_B7=bitMode; if(pinName==PORTD_B0)DDRD_B0=bitMode; if(pinName==PORTD_B1)DDRD_B1=bitMode; if(pinName==PORTD_B2)DDRD_B2=bitMode; if(pinName==PORTD_B3)DDRD_B3=bitMode; if(pinName==PORTD_B4)DDRD_B4=bitMode; if(pinName==PORTD_B5)DDRD_B5=bitMode; if(pinName==PORTD_B6)DDRD_B6=bitMode; if(pinName==PORTD_B7)DDRD_B7=bitMode;  }
 #endif


 #if defined (__AVR_ATmega8__) ||(__AVR_ATmega8A__) || (__AVR_ATmega48__) || (__AVR_ATmega88P__)||(__AVR_ATmega328P__)
     #define pinMode(pinName, bitMode)      { if ((pinName==PORTB_B0)||(pinName==PINB_B0))DDRB_B0=bitMode; if((pinName==PORTB_B1)||(pinName==PINB_B1))DDRB_B1=bitMode; if((pinName==PORTB_B2)||(pinName==PINB_B2))DDRB_B2=bitMode; if((pinName==PORTB_B3)||(pinName==PINB_B3))DDRB_B3=bitMode; if((pinName==PORTB_B4)||(pinName==PINB_B4))DDRB_B4=bitMode; if((pinName==PORTB_B5)||(pinName==PINB_B5))DDRB_B5=bitMode; if((pinName==PORTB_B6)||(pinName==PINB_B6))DDRB_B6=bitMode; if((pinName==PORTB_B7)||(pinName==PINB_B7))DDRB_B7=bitMode; if(pinName==PORTC_B0)DDRC_B0=bitMode; if(pinName==PORTC_B1)DDRC_B1=bitMode; if(pinName==PORTC_B2)DDRC_B2=bitMode; if(pinName==PORTC_B3)DDRC_B3=bitMode; if(pinName==PORTC_B4)DDRC_B4=bitMode; if(pinName==PORTC_B5)DDRC_B5=bitMode; if(pinName==PORTC_B6)DDRC_B6=bitMode; if(pinName==PORTC_B7)DDRC_B7=bitMode; if(pinName==PORTD_B0)DDRD_B0=bitMode; if(pinName==PORTD_B1)DDRD_B1=bitMode; if(pinName==PORTD_B2)DDRD_B2=bitMode; if(pinName==PORTD_B3)DDRD_B3=bitMode; if(pinName==PORTD_B4)DDRD_B4=bitMode; if(pinName==PORTD_B5)DDRD_B5=bitMode; if(pinName==PORTD_B6)DDRD_B6=bitMode; if(pinName==PORTD_B7)DDRD_B7=bitMode;   }
 #endif

 #define digitalWritePin(pinName, bitData)   pinName =     bitData
 #define digitalReadPin( portPin)            portPin

 #if defined (__AVR_ATmega16__) || (__AVR_ATmega16A__) || (__AVR_ATmega32__)|| (__AVR_ATmega1284P__)
     #define portMode(portName, portData)  {  if ( ( portName == PORTA)||( portName == PINA) ) DDRA = portData;   if ((portName == PORTB)||( portName == PINB))DDRB = portData; if((portName == PORTC)||( portName == PINC))DDRC = portData; if ((portName == PORTD)||( portName == PIND))  DDRD = portData;}
 #endif

 #if defined (__AVR_ATmega8__) ||(__AVR_ATmega8A__) || (__AVR_ATmega48__) || (__AVR_ATmega88P__)|| (__AVR_ATmega328P__)
  //#define portMode(portName, portData)  {    if ( portName == PORTB) DDRB = portData; if ( portName == PORTC) DDRC = portData; if ( portName == PORTD) DDRD = portData;}
 #endif

 #define digitalWritePort(portName, portData)   portName = portData
 #define digitalReadPort(portName)             portName




#endif  //end usingPort
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   usingUart
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef usingUart

void UART1_Init(uint32_t buadrate);
uint8_t UART1_Data_Ready(void);
void UART1_Write(uint8_t txData);
void UART1_Write_Chr(char txData);
void UART1_Write_Text(const char* txData);
uint8_t UART1_Read(void);

class uart {
	
	public:
	
	void init(uint32_t buadrate);
	void write(uint8_t uartData);
	void writeText(const char * uartString);
	void writeText(const char * uartString, char type);
	void writeLine(const char * uartString);
	void writeHex( uint8_t hexData);
	void writeDec(uint16_t decData);
	
	uint8_t read(void );
	uint8_t readText(char *uartString );
	//uint8_t readText(char *uartString, char *endString );
	
	uint8_t isDataReady(void);
	
	private:
	//uint32_t buadrateData;
	
	

};

void uart::init( uint32_t buadrate){
	UART1_Init(buadrate);
}

void uart::writeHex( uint8_t hexData){
	char hexCode[] = { '0', '1', '2', '3',  '4',  '5' , '6',  '7' , '8',  '9' , 'A',  'B' , 'C',  'D' , 'E',  'F'   };
	char string[] = "  ";

	string [0] = hexCode [ (( hexData >> 4) &  0x0F ) ];
	string [1] = hexCode [ ( hexData & 0x0F) ];
	UART1_Write_Text(string);
	
}

void uart::writeDec(uint16_t decData){

char string[] = "     ";
    if (decData<=255){
	    string[0] =   ( (char)decData / 100 )       + 48;
	    string[1] = ( ( (char)decData % 100 ) / 10) + 48;
	    string[2] = ( ( (char)decData % 100 ) % 10) + 48;
		string[3] =  endOfString;
		string[4] =  endOfString;
        if ((string[0] == 48)&&(string[1]==48)&&(string[2]==48) ){
	        //string[0];
		    string[1] =  endOfString;
	        string[2] =  endOfString;
			string[3] =  endOfString;
			string[4] =  endOfString;
	     }
	     else{
		      if ( (string[0] == 48)&&(string[1]==48) ){
			        string[0] =  string[2];
			        string[1] =  endOfString;
			        string[2] =  endOfString;
					string[3] =  endOfString;
					string[4] =  endOfString;
		      }
		       else{
			         if ( string[0] == 48){
				          string[0] =  string[1];
				          string[1] =  string[2];;
				          string[2] =  endOfString;
						  string[3] =  endOfString;
						  string[4] =  endOfString;
			         }
		       }
          }
	}
	else{
		  string[0] =       (char)(decData / 10000 ) + 48;
		  string[1] =      (char)((decData % 10000 ) / 1000) + 48;
		  string[2] =     (char)(((decData % 10000 ) % 1000) / 100)  + 48;
		  string[3] =    (char)((((decData % 10000 ) % 1000) % 100) / 10)  + 48;
		  string[4] =    (char)((((decData % 10000 ) % 1000) % 100) % 10)  + 48;
		  
		  if ((string[0] == 48)&&(string[1]==48) ){
			  string[0] = string[2];
			  string[1] = string[3];
			  string[2] = string[4];
			  string[3] =  endOfString;
			  string[4] =  endOfString;
			  
			  
		  }
		  else{
			  if ( (string[0] == 48) ){
				  string[0] = string[1];
				  string[1] = string[2];
				  string[2] = string[3];
				  string[3] = string[4];
				  string[4] =  endOfString;
			  }
			  
		  }
		
		
		
		
	}
	UART1_Write_Text(string);
	
}

void uart::write(uint8_t uartData){
	UART1_Write_Chr(uartData);
}

void uart::writeText(const char * uartString){
	
	UART1_Write_Text(uartString);
}

void uart::writeLine(const char * uartString){
	UART1_Write_Text(uartString);
	UART1_Write_Chr(0x0D);
	UART1_Write_Chr(0x0A);
}

void uart::writeText(const char * uartString, char type){
char str[3]= "  ";	
	if (type == DEC){                          //hex 
		 while (*uartString != endOfString){
		        
				UART1_Write_Text("0x");
				Byte2String(*uartString, str);
				UART1_Write_Text(str);
				UART1_Write(' ');
		        uartString++;
	    }
	}
	
	if (type == HEX){                          //hex
		while (*uartString != endOfString){
			
			UART1_Write_Text("0x");
			Byte2Hex(*uartString, str);
			UART1_Write_Text(str);
			UART1_Write(' ');
			uartString++;
		}
	}
}

uint8_t uart::read(void ){
	return ( UART1_Read() );
}

uint8_t uart::readText(char *uartString ){
	
	uint16_t  serial_time_out;
	uint8_t serial_data_ctr;
	
	serial_time_out = sizeof(uartString);
	
	for (serial_data_ctr=0; serial_data_ctr< serial_time_out ; serial_data_ctr++){ uartString[serial_data_ctr] = 0; }

	serial_data_ctr = 0;
	serial_time_out = 0;
	while (serial_time_out<65000){

		if (UART1_Data_Ready()) {
			uartString[serial_data_ctr] = UART1_Read();
			serial_data_ctr++;
			serial_time_out = 0;
		}
		serial_time_out++;
		_delay_us(10);
	}
	
	return 0;
}



uint8_t uart::isDataReady(void){
	
	return ( UART1_Data_Ready() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined (__AVR_ATmega8__)||(__AVR_ATmega16__)||(__AVR_ATmega16A__)||(__AVR_ATmega32__)

void UART1_Init(uint32_t buadrate){
	uint16_t mybuadrate;
	
	mybuadrate = (uint16_t) ( ( F_CPU / (buadrate * 16) ) - 1 ) ;  //Calculate buad from buadrate
	UBRRL = uint8_t ( mybuadrate % 256 ); //5
	UBRRH = uint8_t ( mybuadrate / 256 );  //0;
	
	UCSRA = 0x00;
	UCSRC = (1<<URSEL) | (1<<UCSZ1) | (1<<UCSZ0); // Enable 8-data bit, 1-stop bit
	UCSRB = (1<<RXEN) | (1<<TXEN);                //Enable receiver and transmitter
	
}



uint8_t UART1_Data_Ready(void){
	if ( UCSRA & (1<<RXC) )  return 1;
	else   return 0;
}

void UART1_Write(uint8_t txData){
	while ( !(UCSRA & (1<<UDRE))  ) { ;}
	UDR = txData;
}

void UART1_Write_Chr(char txData){
	while ( !(UCSRA & (1<<UDRE))  ) { ;}
	UDR = txData;
}


void UART1_Write_Text(const char* txData){
/*	char txdata;
	uint16_t i = 0;
	
	txdata = txData[0];
	
	while(txdata != '\0'){
		txdata = *(txData+i);
		UART1_Write((uint8_t)txdata);
		i++;
	}
	*/

uint8_t txdata;
uint16_t i = 0;
while(txData[i] != '\0'){
	txdata = (uint8_t)txData[i];
	UART1_Write(txdata);
	i++;
}

}


void UART1_Write_Line(const char* txData){
	uint8_t txdata, i = 0;
	while(txData[i] != '\0'){
		txdata = (uint8_t)txData[i];
		UART1_Write(txdata);
		i++;
	}
	UART1_Write(0x0D);
	
}


uint8_t UART1_Read(void){
	if ( UCSRA & (1<<RXC) )  return UDR;
	else   return 0;
}

#endif
///////////////////////////////////////////////////////////////////////////////////////////

#if defined (__AVR_ATmega328P__) || (__AVR_ATmega88P__)|| (__AVR_ATmega1284P__)

void UART1_Init(uint32_t buadrate){
	uint16_t mybuadrate;
	mybuadrate = (uint16_t) ( ( F_CPU / (buadrate * 16) ) - 1 ) ;  //Calculate buad from buadrate
	UBRR0L = uint8_t ( mybuadrate % 256 ); //5
	UBRR0H = uint8_t ( mybuadrate / 256 );  //0;
	
	UCSR0A = 0x00;
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // Enable 8-data bit, 1-stop bit
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);                //Enable receiver and transmitter
}


uint8_t UART1_Data_Ready(void){
	if ( UCSR0A & (1<<RXC0) )  return 1;
	else   return 0;
}

void UART1_Write(uint8_t txData){
	while ( !(UCSR0A & (1<<UDRE0))  ) { ;}
	UDR0 = txData;
}

void UART1_Write_Chr(char txData){
	while ( !(UCSR0A & (1<<UDRE0))  ) { ;}
	UDR0 = txData;
}

void UART1_Write_Text(const char* txData){
	uint8_t txdata, i = 0;
	while(txData[i] != '\0'){
		txdata = (uint8_t)txData[i];
		UART1_Write(txdata);
		i++;
	}
}

uint8_t UART1_Read(void){
	if ( UCSR0A & (1<<RXC0) )  return UDR0;
	else   return 0;
	
}


#endif  //defined (__AVR_ATmega328P__)
/////////////////////////////////////////////////////////////////////


#endif //usingUart


////////////////////////////////////////////////////////////////////
#if defined (__AVR_ATmega328P__) || (__AVR_ATmega88P__)|| (__AVR_ATmega1284P__)

#ifdef usingUart2

class uart2{
	
	public:
	void init(uint32_t buadrate);
	uint8_t isDataReady(void);
	void write (uint8_t txData);
	uint8_t read(void);
	
};

void uart2::init(uint32_t buadrate){
	uint16_t mybuadrate;
	mybuadrate = (uint16_t) ( ( F_CPU / (buadrate * 16) ) - 1 ) ;  //Calculate buad from buadrate
	UBRR1L = uint8_t ( mybuadrate % 256 ); //5
	UBRR1H = uint8_t ( mybuadrate / 256 );  //0;
	
	UCSR1A = 0x00;
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10); // Enable 8-data bit, 1-stop bit
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);                //Enable receiver and transmitter
}


uint8_t uart2::isDataReady(void){
	if ( UCSR1A & (1<<RXC1) )  return 1;
	else   return 0;
}

void uart2::write(uint8_t txData){
	while ( !(UCSR1A & (1<<UDRE1))  ) { ;}
	UDR1 = txData;
}



uint8_t uart2::read(void){
	if ( UCSR1A & (1<<RXC1) )  return UDR1;
	else   return 0;
	
}


#endif
//////////////////////////////////////////////////////////////////////
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//   usingADC
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined (__AVR_ATmega8__)||(__AVR_ATmega16__)||(__AVR_ATmega16A__)||(__AVR_ATmega32__)||(__AVR_ATmega328P__)

#ifdef usingADC

#define VREFF_INTOFF 0
#define VREFF_AVCC   1
#define VREFF_RESV   2
#define VREFF_256    3


void analogRefInit( uint8_t vreff){
	
	ADMUX = (vreff << 6);  //(1<<REFS1)|(1<<REFS0);
	ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0);
	//SFIOR  = (1<<4);
	
}

uint16_t analogeReadPin(uint8_t ch){

	ch &= 0b00000111;  // AND operation with 7
	
	ADMUX = (ADMUX & 0xF8)|ch; // clears the bottom 3 bits before ORing
	
	ADCSRA |= (1<<ADSC);           // start single conversion
	
	while(ADCSRA & (1<<ADSC));    // wait for conversion to complete
	return (ADC);
}

#endif



#endif //usingAdc

#endif //HAL_H
