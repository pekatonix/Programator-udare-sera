// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte sensorPin[] = {8, 9, 10};
byte ledPin[] = {11, 12, 13}; // number of leds = numbers of sensors
const byte sensors = 3;
int level = 0; 
int motor = A3;
int Relay = 7;

const int OnHour1 = 23; // Definire ora de pornire dimineata
const int OnMin1 = 00;
const int OffHour1 = 23; // Definire ora de oprire dimineata
const int OffMin1 = 15;
const int OnHour2 = 5; // Definire ora de pornire seara
const int OnMin2 = 00;
const int OffHour2 = 5; // Definire ora de oprire seara
const int OffMin2 = 30;

void setup () {
  lcd.begin();
  lcd.backlight();  
   pinMode(Relay, OUTPUT);
   digitalWrite(Relay, HIGH);
   pinMode(motor, OUTPUT);

    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
	for(int i = 0; i < sensors; i++) {
     pinMode(sensorPin[i], INPUT); 
     pinMode(ledPin[i], OUTPUT);
  }
}

void loop () {
    DateTime now = rtc.now();
    now = rtc.now();
	
	  level = 0; 
  for(int i = 0; i < sensors; i++) {
     if(digitalRead(sensorPin[i]) == LOW) {
        digitalWrite(ledPin[i], HIGH);
        level = sensors - i;
     } else {
       digitalWrite(ledPin[i], LOW);       
     }    
  }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ORA:");
    lcd.setCursor(4,0);
    lcd.print(now.hour(), DEC);
    lcd.print(':');
    if(now.minute() < 10)
 {
  lcd.print("0");
  }
  lcd.print(now.minute(), DEC); //Print min
  lcd.print(':');
  if(now.second() < 10)
 {
  lcd.print("0");
  }
  lcd.print(now.second(), DEC); //Print sec
    delay(1000);

 // lcd.setCursor(13,0);
 // lcd.print("Water status:");
     if (now.hour() == OnHour1 && now.minute() == OnMin1)
   {
    digitalWrite(Relay,LOW);
    lcd.setCursor(13,0);
    lcd.print("ON ");
    }
   
    else if(now.hour() == OffHour1 && now.minute() == OffMin1)
    {
      digitalWrite(Relay,HIGH);
      lcd.setCursor(13,0);
      lcd.print("OFF");
    }
  
      if (now.hour() == OnHour2 && now.minute() == OnMin2)
    {
    digitalWrite(Relay,LOW);
    lcd.setCursor(13,0);
    lcd.print("ON ");
    }
   
    else if(now.hour() == OffHour2 && now.minute() == OffMin2)
    {
      digitalWrite(Relay,HIGH);
      lcd.setCursor(13,0);
      lcd.print("OFF");
    }  
	
	  lcd.setCursor(0,1);
	  lcd.print("Nivel bazin: ");  
  switch(level) {
     case 1:
      lcd.print("Max");
      digitalWrite(motor, HIGH);
      break;
     case 2:
       lcd.print("Int");
       digitalWrite(motor, LOW);
       break;
     case 3:
       lcd.print("Min");
       digitalWrite(motor, LOW);
       break;
     default:
      lcd.print("Gol"); 
      digitalWrite(motor, LOW);   
      break;
  }
  delay(50);
}
