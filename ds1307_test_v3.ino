// Programator pentru udare la ora fixa in sera
// Partea de ceas este din exemplul de ceas din biblioteca RTClib
// by Pekatonix / http:pekatonix.ro / Targu Mures, 2/05/2019

#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // (RS, EN, D4, D5, D6, D7)
RTC_DS1307 rtc;

int Relay = 8;

const int OnHour1 = 18; // Definire ora de pornire dimineata
const int OnMin1 = 30;
const int OffHour1 = 18; // Definire ora de oprire dimineata
const int OffMin1 = 32;
const int OnHour2 = 18; // Definire ora de pornire seara
const int OnMin2 = 34;
const int OffHour2 = 18; // Definire ora de oprire seara
const int OffMin2 = 36;

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
     rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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
	
	  if (now.hour() == OnHour1 && now.minute() == OnMin1)
	  {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT ON");
    lcd.setCursor(3,1);
    lcd.print("Water ON");
    }
   
    else if(now.hour() == OffHour1 && now.minute() == OffMin1)
    {
      digitalWrite(Relay,HIGH);
      Serial.println("LIGHT OFF");
      lcd.setCursor(3,1);
      lcd.print("Water OFF");
    }
	
		  if (now.hour() == OnHour2 && now.minute() == OnMin2)
	  {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT ON");
    lcd.setCursor(3,1);
    lcd.print("Water ON");
    }
   
    else if(now.hour() == OffHour2 && now.minute() == OffMin2)
    {
      digitalWrite(Relay,HIGH);
      Serial.println("LIGHT OFF");
      lcd.setCursor(3,1);
      lcd.print("Water OFF");
    }
}
