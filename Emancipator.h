/*
 This library works for both the Arduino's Atmega328P and general AVR micro-controllers (most especially ATmega16), using specific "#define".
 
APPLICATIONS:

*** LedBlink
*** DigitalClock
*** Robot
*** Home Automation
*** DISPLAY BOARDS
*** ShiftRegisters
*** Ultrasonic Sensor
*** Liquid Crystal Display (LCD) - m x n
*** Graphic Liquid Crystal Display (GLCD) - m x n
*** IIC/TWI
*** keypad4X4
*** PORTS
*** UART
*** USART
*** Analog-to-Digital Conversion (ADC)
*** nRf24L01
*** Sim900
*** SM630
*** P10
*** 75HC595LedMatrix
*** ds18b20

Copyright (c) 2017 IDIAGHE EMANCIPATOR EMMANUEL. All right reserved.
*/



#ifndef Emancipator_h
#define Emancipator_h

#ifdef usingGeneralAVR

#include "afrouno.h"

#endif

#ifdef usingArduino

#include "Arduino.h"

#endif

/***********************************************************************************
***********************      LED_BLINK(HelloEmancipator)      **********************                         
***********************            for ARDUINO ONLY           **********************
***********************************************************************************/

#ifdef usingLedBlink

class Led 
{
public: 
Led(int pin);
void fast();
void slow();

private:
int _pin;
};

Led::Led(int pin){
pinMode(pin, OUTPUT);
_pin = pin; }

void Led::slow(){
digitalWrite(_pin, HIGH);
  delay(500);
  digitalWrite(_pin, LOW);
  delay(500);
  digitalWrite(_pin, HIGH);
  delay(500);
  digitalWrite(_pin, LOW);
  delay(500);
  digitalWrite(_pin, HIGH);
  delay(500);
  digitalWrite(_pin, LOW);
  delay(500);  }

void Led::fast(){
digitalWrite(_pin, HIGH);
  delay(200);
  digitalWrite(_pin, LOW);
  delay(200);
  digitalWrite(_pin, HIGH);
  delay(200);
  digitalWrite(_pin, LOW);
  delay(200);
  digitalWrite(_pin, HIGH);
  delay(200);
  digitalWrite(_pin, LOW);
  delay(200);  }

#endif //usingLedBlink



#ifdef usingWiFiLCD

#include <ESP8266WiFi.h>
#include "FS.h"
#include <LiquidCrystal.h>


String emailbutton = "off";
String lastdata;
String DsTable;             //Discarded parts if the Strings......
String tmtxt1;              //Strings from the Web....
String tmtxt2;
String stheDate;            //System Start Time...
String theDate;             // The current TimeStamp from Google....
boolean got_text = false;   //Print the Text to LCD if true......
unsigned long ulReqcount;                            // how often has a valid page been requested
unsigned long ulReconncount;                         // how often did we connect to WiFi
unsigned long Dfsize;                                // size of the datalog file

const char* ssid;
const char* password;



ADC_MODE(ADC_VCC);

// needed to avoid link error on ram check
extern "C" 
{
#include "user_interface.h"
}
// Create an instance of the server on Port 80-89 = Sensor 1 - 10
WiFiServer server(80);
WiFiClient client;

void wsysreset()
{
  //Perform challenge to user before getting here to reboot !!!
  //Make an attempt to send mail or other backup of log files then reboot
    ESP.restart();
}

lcd.begin(16, 2);
LiquidCrystal lcd (2,14,16,5,4,0);


void disp()
{
WiFi.mode(WIFI_STA);
  delay(1000);
   
  lcd.clear();
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(1000);  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    lcd.print(".");
  }
  server.begin();
 delay(500); }

#endif





/****************************************************************
*********************   HOME AUTOMATION   ***********************
***************         for ARDUINO ONLY      *******************
****************************************************************/

#ifdef usingHomeAutomation

//PinNum has a maximum value of 4

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
MDNSResponder mdns;
ESP8266WebServer server(80);

String currentPage = "";
String feedback = "";

#if (PinNum < 1 || PinNum > 4)
#error PinNum has a maximum value of 4
#endif

void Home_Init (void);

class Home
{
	public:
	Home();
	void run();
	void init();
	void HTML();
	void socket1On();
	void socket2On();
	void socket3On();
	void socket4On();
	void socket1Off();
	void socket2Off();
	void socket3Off();
	void socket4Off();
	void IPconfigure();
	
	
	};
	
	Home::Home()
	{}
		
	void Home::init()
	{
		server.begin();
	}
	
	void Home::HTML()
	{
		server.on("/", [](){
			server.send(200, "text/html", webPage);
			Serial.println("...Ready");
			delay(100);
		});
	}
	
	void Home::run(){
		server.handleClient();
	}

	void Home::IPconfigure(){
		delay(1000);
		Serial.begin(9600);
		Serial.println();
		Serial.print("Configuring access point...");
		WiFi.softAP(ssid, password);

		IPAddress myIP = WiFi.softAPIP();
		Serial.print("AP IP address: ");
		Serial.println(myIP);

		if (mdns.begin("esp8266", WiFi.localIP())) {
			Serial.println("MDNS responder started");
			Serial.println(WiFi.localIP());
		}}
		
		void Home::socket1On()
		{
			#if (PinNum >= 1 && PinNum <= 4)
			{
				server.on("/socket1On", []() {
					feedback = "<p><b>GPIO 1 is ON</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO1, HIGH);
					Serial.println("GPIO1 is on");
					delay(1000);
				});
			}
				#endif
		}
		
		void Home::socket1Off()
		{
			#if (PinNum >= 1 && PinNum <= 4)
			{
			server.on("/socket1Off", []() {
				feedback = "<p><b>GPIO 1 is OFF</b></p>";
				currentPage = webPage + feedback;
				server.send(200, "text/html", currentPage);
				digitalWrite(GPIO1, LOW);
				Serial.println("GPIO1 is off");
				delay(1000);
			});
			}
			#endif
		}
		
		void Home::socket2On()
		{
			#if (PinNum >= 2 && PinNum <= 4)
			{
				server.on("/socket2On", []() {
					feedback = "<p><b>GPIO 2 is ON</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO2, HIGH);
					Serial.println("GPIO2 is on");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home::socket2Off()
		{
			#if (PinNum >= 2 && PinNum <= 4)
			{
				server.on("/socket2Off", []() {
					feedback = "<p><b>GPIO 2 is OFF</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO2, LOW);
					Serial.println("GPIO2 is off");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home::socket3On()
		{
			#if (PinNum >= 3 && PinNum <= 4)
			{
				server.on("/socket3On", []() {
					feedback = "<p><b>GPIO 3 is ON</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO3, HIGH);
					Serial.println("GPIO3 is on");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home::socket3Off()
		{
			#if (PinNum >= 3 && PinNum <= 4)
			{
				server.on("/socket3Off", []() {
					feedback = "<p><b>GPIO 3 is OFF</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO3, LOW);
					Serial.println("GPIO3 is off");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home::socket4On()
		{
			#if (PinNum == 4)
			{
				server.on("/socket4On", []() {
					feedback = "<p><b>GPIO 4 is ON</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO4, HIGH);
					Serial.println("GPIO4 is on");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home::socket4Off()
		{
			#if (PinNum == 4)
			{
				server.on("/socket4Off", []() {
					feedback = "<p><b>GPIO 4 is OFF</b></p>";
					currentPage = webPage + feedback;
					server.send(200, "text/html", currentPage);
					digitalWrite(GPIO4, LOW);
					Serial.println("GPIO4 is off");
					delay(1000);
				});
			}
			#endif
		}
		
		void Home_Init()
		{
			#if (PinNum == 1)
			{
				pinMode(GPIO1, OUTPUT);
				digitalWrite(GPIO1, LOW);
			}
            #endif
            #if (PinNum == 2)
            {
	            pinMode(GPIO1, OUTPUT);
	            digitalWrite(GPIO1, LOW);
				pinMode(GPIO2, OUTPUT);
				digitalWrite(GPIO2, LOW);
            }
            #endif
			#if (PinNum == 3)
			{
				pinMode(GPIO1, OUTPUT);
				digitalWrite(GPIO1, LOW);
				pinMode(GPIO2, OUTPUT);
				digitalWrite(GPIO2, LOW);
				pinMode(GPIO3, OUTPUT);
				digitalWrite(GPIO3, LOW);
			}
			#endif
			#if (PinNum == 4)
			{
				pinMode(GPIO1, OUTPUT);
				digitalWrite(GPIO1, LOW);
				pinMode(GPIO2, OUTPUT);
				digitalWrite(GPIO2, LOW);
				pinMode(GPIO3, OUTPUT);
				digitalWrite(GPIO3, LOW);
				pinMode(GPIO4, OUTPUT);
				digitalWrite(GPIO4, LOW);
			}
			#endif
		}


#endif



/****************************************************************
**************************   ROBOT   ****************************
******************   for ARDUINO ONLY    ************************
****************************************************************/

#ifdef usingEmancipatorBot

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
MDNSResponder mdns;
ESP8266WebServer server(80);


void Robot_Init (void);
void Robot_StandBy(void);
void Robot_DisEngage(void);
void Robot_MotorForward(void);
void Robot_MotorBackward(void);
void Robot_MotorLeftward(void);
void Robot_MotorRightward(void);
void Robot_Stop(void);
void Robot_Gear_1(void);
void Robot_Gear_2(void);
void Robot_Gear_3(void);
void Robot_Gear_4(void);


class Connect
{
public:
Connect();
void init();
void driveHTML();
void driveStandBy();
void driveBackward();
void driveForward();
void driveRightward();
void driveLeftward();
void driveGear1();
void driveGear2();
void driveGear3();
void driveGear4();
void driveStop();
void driveDisengage();
void IPconfigure();
void run();

private:

};

Connect::Connect()
{}
	
void Connect::init(){
server.begin();
}

void Connect::driveHTML()
{
	server.on("/", [](){
		server.send(200, "text/html", webPage);
		Serial.println("...Ready");
		delay(100);
	});
}

void Connect::driveStandBy()
{
	server.on("/standby", [](){
		server.send(200, "text/html", webPage);
		Robot_StandBy();
		Serial.println("STANDBY");
		delay(100);
	});
}

void Connect::driveBackward()
{
server.on("/backward", [](){
	server.send(200, "text/html", webPage);
	Robot_MotorBackward();
	Serial.println("BACKWARD");
	delay(100);
});  
}


void Connect::driveForward()
{
	server.on("/forward", [](){
		server.send(200, "text/html", webPage);
		Robot_MotorForward();
		Serial.println("FORWARD");
		delay(100);
	});
}

void Connect::driveRightward()
{
	server.on("/right", [](){
		server.send(200, "text/html", webPage);
		Robot_MotorRightward();
		Serial.println("RIGHTWARD");
		delay(100);
	});
}

void Connect::driveLeftward()
{
	server.on("/left", [](){
		server.send(200, "text/html", webPage);
		Robot_MotorLeftward();
		Serial.println("LEFTWARD");
		delay(100);
	});
}

void Connect::driveGear1()
{
	server.on("/gear1", [](){
		server.send(200, "text/html", webPage);
		Robot_Gear_1();
		Serial.println("GEAR 1");
		delay(100);
	});
}

void Connect::driveGear2()
{
	server.on("/gear2", [](){
		server.send(200, "text/html", webPage);
		Robot_Gear_2();
		Serial.println("GEAR 2");
		delay(100);
	});
}

void Connect::driveGear3()
{
	server.on("/gear3", [](){
		server.send(200, "text/html", webPage);
		Robot_Gear_3();
		Serial.println("GEAR 3");
		delay(100);
	});
}

void Connect::driveGear4()
{
	server.on("/gear4", [](){
		server.send(200, "text/html", webPage);
		Robot_Gear_4();
		Serial.println("GEAR 4");
		delay(100);
	});
}
void Connect::driveStop()
{
	server.on("/stop", [](){
		server.send(200, "text/html", webPage);
		Robot_Stop();
		Serial.println("STOP");
		delay(100);
	});
}

void Connect::driveDisengage()
{
	server.on("/disengage", [](){
		server.send(200, "text/html", webPage);
		Robot_DisEngage();
		Serial.println("DISENGAGED");
		delay(100);
	});
}

void Connect::run(){
server.handleClient();
}

void Connect::IPconfigure(){
  delay(1000);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
     Serial.println(WiFi.localIP());
  }}


void Robot_Init (void){
	pinMode(PWMA, OUTPUT);
	digitalWrite(PWMA, LOW);
	
	pinMode(AIN1, OUTPUT);
	digitalWrite(AIN1, LOW);
	
	pinMode(AIN2, OUTPUT);
	digitalWrite(AIN2, LOW);
	
	pinMode(STBY, OUTPUT);
	digitalWrite(STBY, LOW);
	
	pinMode(PWMB, OUTPUT);
	digitalWrite(PWMB, LOW);
	
	pinMode(BIN1, OUTPUT);
	digitalWrite(BIN1, LOW);
	
	pinMode(BIN2, OUTPUT);
	digitalWrite(BIN2, LOW);
}
void Robot_StandBy(void){
	digitalWrite(STBY, HIGH);
}
void Robot_DisEngage(void){
	digitalWrite(STBY, LOW);
}
void Robot_MotorForward(){
	analogWrite(PWMA, FWDspeed);
	analogWrite(PWMB, FWDspeed);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
void Robot_MotorBackward(){
	analogWrite(PWMA, BCKspeed);
	analogWrite(PWMB, BCKspeed);
	digitalWrite(AIN1, HIGH);
	digitalWrite(AIN2, LOW);
	digitalWrite(BIN1, HIGH);
	digitalWrite(BIN2, LOW);
}
void Robot_MotorLeftward(){
	analogWrite(PWMA, LFTspeed);
	analogWrite(PWMB, LFTspeed);
	digitalWrite(AIN1, HIGH);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
void Robot_MotorRightward(){
	analogWrite(PWMA, RHTspeed);
	analogWrite(PWMB, RHTspeed);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, HIGH);
	digitalWrite(BIN2, HIGH);
}
void Robot_Stop(void){
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, LOW);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, LOW);
}
void Robot_Gear_1(){
	analogWrite(PWMA, SpeedG1);
	analogWrite(PWMB, SpeedG1);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
void Robot_Gear_2(){
	analogWrite(PWMA, SpeedG2);
	analogWrite(PWMB, SpeedG2);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
void Robot_Gear_3(){
	analogWrite(PWMA, SpeedG3);
	analogWrite(PWMB, SpeedG3);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
void Robot_Gear_4(){
	analogWrite(PWMA, SpeedG4);
	analogWrite(PWMB, SpeedG4);
	digitalWrite(AIN1, LOW);
	digitalWrite(AIN2, HIGH);
	digitalWrite(BIN1, LOW);
	digitalWrite(BIN2, HIGH);
}
 
#endif  //usingEmancipatorBot



/****************************************************************
*****************  ULTRASONIC SENSOR   **************************
*****************  for ATmega16 ONLY   **************************
****************************************************************/

#ifdef usingUSonic

#include <avr/io.h>
#include <avr/interrupt.h>
#include <inttypes.h>
#include <util/delay.h>

 void usound_init(void);

 uint32_t readDistance(void);

void usound_init(void)
{
	US_DDR |= (1 << US_TRIGER)|(0 << US_ECHO);
	US_PIN |= (1<<US_ECHO);
}

uint32_t readDistance(void)
{
	uint8_t readStatus=0;
	uint32_t disTime=0;

	_delay_us(2);
	US_PORT |= (1 << US_TRIGER);
	_delay_us(10);
	US_PORT &= ~(1 << US_TRIGER);

	
	while(readStatus == 0)
	{
		while(US_PIN&(1<<US_ECHO))
		{
			disTime++;
			readStatus = 1;
		}
	}	

	return disTime * 0.00862;
}
 #endif //usingUsonic
 
 
 
 /******************************************************************
 ***************** P10 DISPLAY BOARDS *****************************
 *****************  FOR ARDUINO ONLY  ******************************
 ******************************************************************/
 
 #ifdef usingSerialP10
 
 #include <avr/io.h>
 #include <util/delay.h>
 
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>
#include <EEPROMAnything.h>
 
 DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
 
 char message1[max_char];
 char message2[max_char];
 char message3[max_char];
 char message4[max_char];
 char message5[max_char];
 char message6[max_char];
 char message7[max_char];
 char r_char;
 byte index = 0;
 int count = 0;
 int i;
 
 void ScanDMD()
 {
	 dmd.scanDisplayBySPI();
 }

 class P10
 {
	 public:
	 void start(void);
	 void input(void);
	 void ask(void);
	 void scroll(void);
	 
	 private:
	 
	 };
 
	 
void P10::start(void)
{
	Timer1.initialize( 5000 );
	Timer1.attachInterrupt( ScanDMD );

	dmd.clearScreen( true );
	Serial.begin(9600);

	Serial.println("Send any command to enter UPDATE mode");
	delay(10000);

	EEPROM_readAnything(0, message1);
	EEPROM_readAnything(72, message2);
	EEPROM_readAnything(82, message3);
	EEPROM_readAnything(92, message4);
	EEPROM_readAnything(102, message5);
	EEPROM_readAnything(112, message6);
	EEPROM_readAnything(183, message7);
}
void P10::input(void)
{
	if(Serial.available())
	{
		index=0;
		count++;
	}

	while(Serial.available() > 0)
	{
		dmd.clearScreen(true);

		if(count == 1)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				index++;
			}
		}
		
		if(count == 2)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message1[index] = r_char;
				index++;
			}
		}
		
		if(count == 3)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message2[index] = r_char;
				index++;
			}
		}
		
		if(count == 4)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message3[index] = r_char;
				index++;
			}
		}
		
		if(count == 5)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message4[index] = r_char;
				index++;
			}
		}
		
		if(count == 6)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message5[index] = r_char;
				index++;
			}
		}
		
		if(count == 7)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message6[index] = r_char;
				index++;
			}
		}
		
		if(count == 8)
		{
			if(index < (max_char-1))
			{
				r_char = Serial.read();
				message7[index] = r_char;
				index++;
			}
		}
	}

	if(count == 1) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg1);}
	if(count == 2) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg2);}
	if(count == 3) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg3);}
	if(count == 4) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg4);}
	if(count == 5) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg5);}
	if(count == 6) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg6);}
	if(count == 7) {
		Serial.println();
		Serial.println();
		delay(1000);
	Serial.println(inputMsg7);}
	if(count == 8) {
		for(int k=0;k<101;k++){
			Serial.println(k);
			Serial.print("%");
			delay(50);
		}
		delay(1000);
		Serial.println();
		Serial.println();
		EEPROM_writeAnything(0, message1);
		EEPROM_writeAnything(72, message2);
		EEPROM_writeAnything(82, message3);
		EEPROM_writeAnything(92, message4);
		EEPROM_writeAnything(102, message5);
		EEPROM_writeAnything(112, message6);
		EEPROM_writeAnything(183, message7);
		Serial.println("MESSAGE UPDATED!");
		count = 9;
	}
}

void P10::scroll(void)
{
	if (count == 9 || count ==0)
	{
		delay(500);
		dmd.selectFont(Arial_Black_16);
		dmd.drawMarquee(message1,70,(32*DISPLAYS_ACROSS)-1,0);
		long start=millis();
		long timer=start;
		boolean ret=false;
		while(!ret){
			if ((timer+30) < millis()) {
				ret=dmd.stepMarquee(-1,0);
				timer=millis();
			}
		}

		dmd.clearScreen(true);
		delay(500);

		dmd.selectFont(Arial_Black_16);
		dmd.drawString(0,0,"ANYTHING...",17,GRAPHICS_NORMAL);
		delay(5000);
		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawBox(0,0,95,15,GRAPHICS_NORMAL );
		dmd.drawMarquee(message2,9,7,0);
		//dmd.drawString(0,0,"PEPP. SOUP  ",11,GRAPHICS_NORMAL);
		delay(5000);
		long start6=millis();
		long timer6=start6;
		boolean ret6=false;
		while(!ret6){
			if ((timer6+30) < millis()) {
				ret6=dmd.stepMarquee(-1,0);
				timer6=10;
			}
		}

		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawBox(0,0,95,15,GRAPHICS_NORMAL );
		dmd.drawMarquee(message3,9,7,0);
		//dmd.drawString(30,1,"HARP    ",15,GRAPHICS_NORMAL);
		delay(5000);
		long start7=millis();
		long timer7=start7;
		boolean ret7=false;
		while(!ret7){
			if ((timer7+30) < millis()) {
				ret7=dmd.stepMarquee(-1,0);
				timer7=10;
			}
		}

		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawBox(0,0,95,15,GRAPHICS_NORMAL );
		dmd.drawMarquee(message4,9,7,0);
		//dmd.drawString(20,0,"STOUT   ",15,GRAPHICS_NORMAL);
		delay(5000);
		long start8=millis();
		long timer8=start8;
		boolean ret8=false;
		while(!ret8){
			if ((timer8+30) < millis()) {
				ret8=dmd.stepMarquee(-1,0);
				timer8=10;
			}
		}

		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawBox(0,0,95,15,GRAPHICS_NORMAL );
		dmd.drawMarquee(message5,9,7,0);
		//dmd.drawString(15,0,"GULDER  ",8,GRAPHICS_NORMAL);
		delay(5000);
		long start9=millis();
		long timer9=start9;
		boolean ret9=false;
		while(!ret9){
			if ((timer9+30) < millis()) {
				ret9=dmd.stepMarquee(-1,0);
				timer9=10;
			}
		}

		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawBox(0,0,95,15,GRAPHICS_NORMAL );
		dmd.drawMarquee(message6,9,7,0);
		//dmd.drawString(10,0,"HEINEKEN  ",10,GRAPHICS_NORMAL);
		delay(5000);
		long start0=millis();
		long timer0=start0;
		boolean ret0=false;
		while(!ret0){
			if ((timer0+30) < millis()) {
				ret0=dmd.stepMarquee(-1,0);
				timer0=10;
			}
		}

		dmd.clearScreen(true);

		dmd.selectFont(Arial_Black_16);
		dmd.drawMarquee(message7,70,(32*DISPLAYS_ACROSS)-1,0);
		long start3=millis();
		long timer3=start3;
		boolean ret3=false;
		while(!ret3){
			if ((timer3+30) < millis()) {
				ret3=dmd.stepMarquee(-1,0);
				timer3=millis();
			}
		}
		delay(100);
		count = 0;
	}
}
 
 #endif
 
 
 
 /********************************************************************
 ************************** USING P10  *******************************
 ***********************  using Arduino  *****************************
 ********************************************************************/
 
 #ifdef usingP10Display
 
#include <SPI.h>
#include <DMD.h>
#include <TimerOne.h>

#ifdef usingEEPROM
#include <EEPROMAnything.h>
#endif

#ifdef Font
#if (Font == 1)
#include "Arial_black_16.h"
#endif
#if (Font == 2)
#include "Arial14.h"
#endif
#if (Font == 3)
#include "Droid_Sans_12.h"
#endif
#if (Font == 4)
#include "Droid_Sans_16.h"
#endif
#if (Font == 5)
#include "Droid_Sans_24.h"
#endif
#if (Font == 6)
#include "SystemFont5x7.h"
#endif
#endif

#ifndef Font
 #error "Please Select a Font"
#endif
 
 
 
 
 
#endif
 
 
 /********************************************************************
 ********************    SHIFT REGISTERS    **************************
 ********************  for ATmega16 ONLY    **************************
 ********************************************************************/
 /*
 This section of the library allows for maximum of 4 shift registers with
 HC595_DDR:  Data Direction Register
 HC595_PORT: Port
 HC595_DS1_POS:    Data pin for ShiftRegister 1,etc.
 HC595_SH1_CP_POS: Shift/Clock pin for for ShiftRegister 1,etc.
 HC595_ST_CP_POS:  Common Latch pin for all ShiftRegisters
 */
 
 #ifdef usingShiftRegister
 
 #include <avr/io.h>
 #include <util/delay.h>
 
 #ifdef DefaultSet
 
 #define HC595_DDR 	  DDRB
 #define HC595_4_DDR  DDRD
 #define HC595_PORT   PORTB
 #define HC595_4_PORT PORTD

 #define HC595_DS1_POS       PB0
 #define HC595_DS2_POS       PB1
 #define HC595_DS3_POS       PB2
 #define HC595_DS4_POS       PB3
 #define HC595_SH1_CP_POS    PB4
 #define HC595_SH2_CP_POS    PB5
 #define HC595_SH3_CP_POS    PB6
 #define HC595_ST_CP_POS     PB7
 #define HC595_4_SH4_CP_POS  PD7
 
#endif

#ifndef NumOfReg

#error NUMBER OF REGISTERS NOT SPECIFIED (NumOfReg)

#endif

#if (NumOfReg > 4)

#error MAXIMUM OF 4 SHIFT REGISTERS

#endif
 
 
 class HC595
 {
	 public:
	 HC595(void);
	 void init(void);
	 void HC595WRITE(int Reg1, int Reg2, int Reg3, int Reg4);
	 
	 private:
	 void HC595Latch(void);
	 void HC595Pulse1(void);
	 void HC595Pulse2(void);
	 void HC595Pulse3(void);
	 void HC595Pulse4(void);
	 void Write1(uint8_t data1);
	 void Write2(uint8_t data2);
	 void Write3(uint8_t data3);
	 void Write4(uint8_t data4);
	 };
 
 
 HC595::HC595(void)
 {}

 void HC595::init(void)
 {
	 #if (NumOfReg == 1)
	 {
		 HC595_DDR|=((1<<HC595_SH1_CP_POS)|(1<<HC595_DS1_POS)|(1<<HC595_ST_CP_POS));
		 
		 #define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
		 #define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))
	 }
	 #endif
     #if (NumOfReg == 2)
	 {
		 HC595_DDR|=((1<<HC595_SH1_CP_POS)|(1<<HC595_SH2_CP_POS)|(1<<HC595_DS1_POS)|(1<<HC595_DS2_POS)|(1<<HC595_ST_CP_POS));
		 
		  #define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
		  #define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))

		  #define HC595Data2High() (HC595_PORT|=(1<<HC595_DS2_POS))
		  #define HC595Data2Low() (HC595_PORT&=(~(1<<HC595_DS2_POS)))
	 }
	 #endif
	 #if (NumOfReg == 3)
	 {
		 HC595_DDR|=((1<<HC595_SH1_CP_POS)|(1<<HC595_SH2_CP_POS)|(1<<HC595_SH3_CP_POS)|(1<<HC595_DS1_POS)|(1<<HC595_DS2_POS)|(1<<HC595_DS3_POS)|(1<<HC595_ST_CP_POS));
		 
		  #define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
		  #define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))

		  #define HC595Data2High() (HC595_PORT|=(1<<HC595_DS2_POS))
		  #define HC595Data2Low() (HC595_PORT&=(~(1<<HC595_DS2_POS)))

		  #define HC595Data3High() (HC595_PORT|=(1<<HC595_DS3_POS))
		  #define HC595Data3Low() (HC595_PORT&=(~(1<<HC595_DS3_POS)))
	 }
	 #endif
	 #if (NumOfReg == 4)
	 {
		 HC595_DDR|=((1<<HC595_SH1_CP_POS)|(1<<HC595_SH2_CP_POS)|(1<<HC595_SH3_CP_POS)|(1<<HC595_ST_CP_POS)|(1<<HC595_DS1_POS)|(1<<HC595_DS2_POS)|(1<<HC595_DS3_POS)|(1<<HC595_DS4_POS));
		 HC595_4_DDR|=(1<<HC595_4_SH4_CP_POS);

		 #define HC595Data1High() (HC595_PORT|=(1<<HC595_DS1_POS))
		 #define HC595Data1Low() (HC595_PORT&=(~(1<<HC595_DS1_POS)))

		 #define HC595Data2High() (HC595_PORT|=(1<<HC595_DS2_POS))
		 #define HC595Data2Low() (HC595_PORT&=(~(1<<HC595_DS2_POS)))

		 #define HC595Data3High() (HC595_PORT|=(1<<HC595_DS3_POS))
		 #define HC595Data3Low() (HC595_PORT&=(~(1<<HC595_DS3_POS)))

		 #define HC595Data4High() (HC595_PORT|=(1<<HC595_DS4_POS))
		 #define HC595Data4Low() (HC595_PORT&=(~(1<<HC595_DS4_POS)))
	 }
	 #endif
 }
 
 void HC595::HC595WRITE(int Reg1, int Reg2, int Reg3, int Reg4)
 {
	 #if (NumOfReg == 1)
	 {
		 Write1(Reg1);
	 }
	 #endif
	 #if (NumOfReg == 2)
	 {
		 Write1(Reg1);
		 Write2(Reg2);
	 }
	 #endif
	 #if (NumOfReg == 3)
	 {
		 Write1(Reg1);
		 Write2(Reg2);
		 Write3(Reg3);
	 }
	 #endif
	 #if (NumOfReg == 4)
	 {
		 Write1(Reg1);
		 Write2(Reg2);
		 Write3(Reg3);
		 Write4(Reg4);
	 }
	 #endif
	 
	 HC595Latch();
 }
 
 
 void HC595::HC595Latch()
 {
	 //Common Latch for all Shift Registers
	 HC595_PORT|=(1<<HC595_ST_CP_POS);//HIGH
	 _delay_loop_1(1);

	 HC595_PORT&=(~(1<<HC595_ST_CP_POS));//LOW
	 _delay_loop_1(1);
 }


 void HC595::HC595Pulse1()
 {
	 #if (NumOfReg >= 1 && NumOfReg <= 4)
	 {
		  //Pulse the 1st Shift Clock
		  HC595_PORT|=(1<<HC595_SH1_CP_POS);//HIGH

		  HC595_PORT&=(~(1<<HC595_SH1_CP_POS));//LOW
	 }
	 #endif
 }

 void HC595::HC595Pulse2()
 {
	 #if (NumOfReg >= 2 && NumOfReg <= 4)
	 {
	 //Pulse the 2nd Shift Clock
	 HC595_PORT|=(1<<HC595_SH2_CP_POS);//HIGH

	 HC595_PORT&=(~(1<<HC595_SH2_CP_POS));//LOW
	 }
	 #endif
 }

 void HC595::HC595Pulse3()
 {
	 #if (NumOfReg >= 3 && NumOfReg <= 4)
	 {
	 //Pulse the 3rd Shift Clock
	 HC595_PORT|=(1<<HC595_SH3_CP_POS);//HIGH

	 HC595_PORT&=(~(1<<HC595_SH3_CP_POS));//LOW
	 }
	 #endif
 }

 void HC595::HC595Pulse4()
 {
	 #if (NumOfReg == 4)
	 {
	 //Pulse the 4th Shift Clock
	 HC595_4_PORT|=(1<<HC595_4_SH4_CP_POS);//HIGH

	 HC595_4_PORT&=(~(1<<HC595_4_SH4_CP_POS));//LOW
	 }
	 #endif
 }
 
 void HC595::Write1(uint8_t data1)
 {
	 #if(NumOfReg >= 1 && NumOfReg <= 4)
	 {
	 //Send each 8 bits serially
	 //Order is MSB first
	 for(uint8_t i=0;i<8;i++)
	 {
		 //Output the data on DS line according to the
		 //Value of MSB
		 if(data1 & 0b10000000)
		 {
			 HC595Data1High();
		 }
		 else
		 {
			 HC595Data1Low();
		 }
		 HC595Pulse1();
		 data1=data1<<1;
	 }
	 }
	 #endif
	 //This function writes the 1st shift register
 }

 void HC595::Write2(uint8_t data2)
 {
	 #if (NumOfReg >= 2 && NumOfReg <= 4)
	 {
	 for(uint8_t j=0;j<8;j++)
	 {
		 if(data2 & 0b10000000)
		 {
			 HC595Data2High();
		 }
		 else
		 {
			 HC595Data2Low();
		 }
		 HC595Pulse2();
		 data2=data2<<1;
	 }
	 }
	 #endif
	 //This function writes the 2nd shift register
 }

 void HC595::Write3(uint8_t data3)
 {
	 #if (NumOfReg >= 3 && NumOfReg <= 4)
	 {
	 for(uint8_t k=0;k<8;k++)
	 {
		 if(data3 & 0b10000000)
		 {
			 HC595Data3High();
		 }
		 else
		 {
			 HC595Data3Low();
		 }
		 HC595Pulse3();
		 data3=data3<<1;
	 }
	 }
	 #endif
	 //This function writes the 3rd shift register
 }

 void HC595::Write4(uint8_t data4)
 {
	 #if (NumOfReg == 4)
	 {
	 for(uint8_t l=0;l<8;l++)
	 {
		 if(data4 & 0b10000000)
		 {
			 HC595Data4High();
		 }
		 else
		 {
			 HC595Data4Low();
		 }
		 HC595Pulse4();
		 data4=data4<<1;
	 }
	 }
	 #endif
	 //This function writes the 4th shift register
 }
 
 
 
 
 
#endif  //usingShiftRegister
 
 
/********************************************************
******************** USART ******************************
*********************************************************/
#ifdef usingUSART

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>	
#include <util/delay.h>
#define BAUD_PRESCALE (((F_CPU / (BAUDRATE * 16UL))) - 1)

void USART_Init(unsigned long);	
char USART_RxChar();
void USART_TxChar(char);
void USART_SendString(const char*);


void USART_Init(unsigned long BAUDRATE)
{ 
	UCSRB |= (1 << RXEN) | (1 << TXEN);	
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	
	UBRRL = BAUD_PRESCALE;
	UBRRH = (BAUD_PRESCALE >> 8);
}

char USART_RxChar()
{
	while (!(UCSRA & (1 << RXC)));
	return(UDR);
}

void USART_TxChar(char data)
{
	UDR = data;	
	while (!(UCSRA & (1<<UDRE)));
}

void USART_SendString(const char *str)
{
	int i=0;																	
	while (str[i]!=0)
	{
		USART_TxChar(str[i]);
		i++;
	}
}

#endif




/*******************************************************
******************** GSM ******************************
*******************************************************/
#ifdef usingGSM

void call(const char*);
void sendSMS(const char*, const char*);

void call(const char *phone_no)
{
	_delay_ms(500);
	USART_Init(9600);
	_delay_ms(200);
	USART_SendString("AT\r");
	_delay_ms(1000);
	USART_SendString("ATD");
	USART_SendString(phone_no);
	USART_SendString("\r");
	_delay_ms(20000);
	USART_SendString("ATH\r");
}

void sendSMS(const char *phone_no, const char *message)
{
	_delay_ms(500);
	USART_Init(9600);
	_delay_ms(200);
	USART_SendString("AT+CMGF=1\r");
	_delay_ms(1000);
	USART_SendString("AT+CMGS=");
	USART_SendString(phone_no);
	USART_SendString("\r");
	_delay_ms(2000);
	USART_SendString(message);
	_delay_ms(1000);
	USART_TxChar(0x1A);  //Ctrl+Z
	USART_SendString("\r");
}

#endif


/********************************************************
******************   DIGITAL CLOCK   ********************
***************    for ATmega16 ONLY    *****************
********************************************************/
#ifdef usingDigitalClock

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t H0;
uint8_t H1;
uint8_t M0;
uint8_t M1;
uint8_t rtcHour;
uint8_t rtcData[8];
uint8_t rtcTime[15];
uint8_t year            = 20;
const char* MONTH[][13] = {"         ","JANUARY  ","   FEB.  ","  MARCH  ","  APRIL  ","    MAY  ","   JUNE  ","   JULY  ","AUGUST  ","  SEPT.  ","OCTOBER ","NOVEMBER ","DECEMBER "};
const char* DOW[][8]    = {"         ","  SUNDAY   ","  MONDAY   ","  TUESDAY   "," WEDNESDAY  ","  THURSDAY  ","  FRIDAY   "," SATURDAY    "};


lcd display (16,2);

class Blink
{
	public:
	Blink(void);
	void timerInit(void);
	void on(void);
	
	private:
	void AM_on(void);
	void PM_on(void);
};

Blink::Blink(void)
{}

void Blink::timerInit(void)
{
	BlinkTimer_DDR|=((1<<BlinkTimer_AM)|(1<<BlinkTimer_PM)|(1<<BlinkTimer_BLINK));
	BlinkTimer_PORT = 0x00;
	
	//1000ms
	sei();
	
	TCCR1B = (1<<CS12);
	TIMSK =  (1<<OCIE1A);

	OCR1A = 62500;
}

void Blink::PM_on(void)
{
	BlinkTimer_PORT = (1<<BlinkTimer_PM);
}

void Blink::AM_on(void)
{
	BlinkTimer_PORT = (1<<BlinkTimer_AM);
}

void Blink::on(void)
{
	BlinkTimer_PORT ^= (1<<BlinkTimer_BLINK);
}


class Time
{
	public:
	Time(void);
	void DispProtocol(void);
	void Convert(void);
	void LcdDisplay(void);
	
	private:
	
	};


Time::Time(void)
{}

void Time::DispProtocol(void)
{
	display.init();
	delay_ms(100);
	
	display.writeText(0,0,"SYSTEM STARTUP..");
	delay_ms(1000);
	display.clear();
	for (uint8_t i=0;i<101;i++)
	{
		display.writeText(0,0,"UPDATING TIME...");
		display.writeDec(1,7,i);
		display.writeText(1,10,"%");
		_delay_ms(50);
	}
	delay_ms(1000);
	display.clear();
	_delay_ms(500);
}


void Time::LcdDisplay(void)
{
	/******** Displays Initialization protocols
	as well as Day, Month, Date and Year of the RTC *******/
	
	display.writeText(0,3,DOW[0][rtcTime[6]]);
	
	if (rtcTime[10]==0 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][10]);
	} 
	else if(rtcTime[10]==1 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][11]);
	}
	else if (rtcTime[10]==2 && rtcTime[11]==1)
	{
		display.writeText(1,0,MONTH[0][12]);
	}
	else
	{
		display.writeText(1,0,MONTH[0][rtcTime[10]]);
	}
	
	display.writeDec(1,9,rtcTime[9]);
	display.writeDec(1,10,rtcTime[8]);
	display.writeText(1,11,",");
	display.writeDec(1,12,year);
	display.writeDec(1,14,rtcTime[13]);
	display.writeDec(1,15,rtcTime[12]);
	_delay_ms(10);
}

void Time::Convert(void)
{
	/****** This converts the RTC Data from BCD to Decimal, as well as controls
	                          AM and PM indicators ******/
	
	if (((rtcData[2] > 0b00010010) & (rtcData[2] < 0b00100000)) | (rtcData[2] > 0b00100001))
	{
		rtcHour = (rtcData[2] % 0b00010010);
		BlinkTimer_PORT = (1<<BlinkTimer_PM); // PM indicator
	}
	else if (rtcData[2] == 0b00000000)
	{
		rtcHour = 0b00010010;
		BlinkTimer_PORT = (1<<BlinkTimer_AM); //AM indicator
	}
	else if (rtcData[2] == 0b00100000)
	{
		rtcHour = 0b00001000;
		BlinkTimer_PORT = (1<<BlinkTimer_PM); // PM indicator
	}
	else if (rtcData[2] == 0b00100001)
	{
		rtcHour = 0b00001001;
		BlinkTimer_PORT = (1<<BlinkTimer_PM); // PM indicator
	}
     else if (rtcData[2] == 0b00010010)
    {
        BlinkTimer_PORT = (1<<BlinkTimer_PM); //PM indicator
    }
	else
	{ 
		rtcHour = rtcData[2];
		BlinkTimer_PORT = (1<<BlinkTimer_AM);
	}
	
	rtcTime[0]   =  ( rtcData[0] & 0b00001111);  //second
	rtcTime[1]   = (( rtcData[0] >> 4) & 0b00000111);
	
	rtcTime[2]   =  ( rtcData[1] & 0b00001111);  //minute
	rtcTime[3]   = (( rtcData[1] >> 4) & 0b00000111);
	
	rtcTime[4]   =  ( rtcHour & 0b00001111);     //Hour
	rtcTime[5]   = (( rtcHour >> 4) & 0b00000111);
	
	rtcTime[6]   =  ( rtcData[3] & 0b00001111);  //day of week
	rtcTime[7]   = (( rtcData[3] >> 4) & 0b00000111);
	
	rtcTime[8]   =  ( rtcData[4] & 0b00001111);  //date
	rtcTime[9]   = (( rtcData[4] >> 4) & 0b00000111);
	
	rtcTime[10]  =  ( rtcData[5] & 0b00001111);  //month
	rtcTime[11]  = (( rtcData[5] >> 4) & 0b00000111);
	
	rtcTime[12]  =  ( rtcData[6] & 0b00001111);  //year
	rtcTime[13]  = (( rtcData[6] >> 4) & 0b00000111);
	
    M0 = rtcTime[2];
	M1 = rtcTime[3];
	H0 = rtcTime[4];
	H1 = rtcTime[5];
}

#endif

#endif  //Emancipator_H