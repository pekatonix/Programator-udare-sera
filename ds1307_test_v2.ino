// Copyright (C) 2019 My Free Software Regulation
// Anyone who understands has the right to develop this sketch
// Programator pentru udare la ora fixa in sera
// Partea de ceas este din exemplul de ceas din biblioteca RTClib
// by Pekatonix / http:pekatonix.ro / Targu Mures, 2/05/2019


#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // (RS, EN, D4, D5, D6, D7)
RTC_DS1307 rtc;

int Relay = 8;

const int OnHour = 5; // Definire ora de pornire
const int OnMin = 30;
const int OffHour = 6; // Definire ora de oprire
const int OffMin = 30;

void setup () {
    lcd.begin(16, 2);
   pinMode(Relay, OUTPUT);
   digitalWrite(Relay, HIGH); // Iesirea pentru releu este definita pentru modul de releu de 5V (functionare cu logica inversa)
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop () {
    DateTime now = rtc.now();
	  now = rtc.now();
   lcd.setCursor(0,0);
  lcd.print("TIME:");
	lcd.setCursor(6,0);                 
	if(now.hour() < 10)
 {
	lcd.print("0");
	}
	lcd.print(now.hour(), DEC); //Print hour
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
	
	  if (now.hour() == OnHour && now.minute() == OnMin)
	  {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT ON");
    lcd.setCursor(3,1);
    lcd.print("Water ON");
    }
   
    else if(now.hour() == OffHour && now.minute() == OffMin)
    {
      digitalWrite(Relay,HIGH);
      Serial.println("LIGHT OFF");
      lcd.setCursor(3,1);
      lcd.print("Water OFF");
    }
}
