// Programator pentru udare la ora fixa in sera
// Copyright (C) 2019 My Free Software Regulation
// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
// by Pekatonix / http:pekatonix.ro / Targu Mures, 2/05/2019

#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x3F, 16, 2);

int Relay = 8;

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

    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void loop () {
    DateTime now = rtc.now();
    now = rtc.now();
    
    lcd.setCursor(0,0);
    lcd.print("TIME:");
    lcd.setCursor(6,0);
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

  lcd.setCursor(0,1);
  lcd.print("Water status:");
     if (now.hour() == OnHour1 && now.minute() == OnMin1)
   {
    digitalWrite(Relay,LOW);
    lcd.setCursor(13,1);
    lcd.print("ON ");
    }
   
    else if(now.hour() == OffHour1 && now.minute() == OffMin1)
    {
      digitalWrite(Relay,HIGH);
      lcd.setCursor(13,1);
      lcd.print("OFF");
    }
  
      if (now.hour() == OnHour2 && now.minute() == OnMin2)
    {
    digitalWrite(Relay,LOW);
    lcd.setCursor(13,1);
    lcd.print("ON ");
    }
   
    else if(now.hour() == OffHour2 && now.minute() == OffMin2)
    {
      digitalWrite(Relay,HIGH);
      lcd.setCursor(13,1);
      lcd.print("OFF");
    }  
}
