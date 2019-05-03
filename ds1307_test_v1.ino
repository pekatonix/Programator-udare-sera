// Copyright (C) 2019 My Free Software Regulation
// Anyone who understands has the right to develop this sketch
// Programator pentru udare la ora fixa in sera
// Partea de ceas este din exemplul de ceas din biblioteca RTClib
// Iesirea pentru releu este definita pentru un LED. Pentru un modul de releu de 5V se inverseaza nivelele logice LOW si HIGH

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

char daysOfTheWeek[7][12] = {"Duminica", "Luni", "Marti", "Miercuri", "Joi", "Vineri ", "Sambata"};

int Relay = 4;

const int OnHour = 21; // Definire ora de pornire
const int OnMin = 33;
const int OffHour = 21; // Definire ora de oprire
const int OffMin = 34;

void setup () {
   Serial.begin(57600);
   pinMode(Relay, OUTPUT);
   digitalWrite(Relay, HIGH);
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
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
  
    Serial.println();
    delay(3000);
	
	  if (now.hour() == OnHour && now.minute() == OnMin)
	  {
    digitalWrite(Relay,LOW);
    Serial.println("LIGHT ON");
    }
   
    else if(now.hour() == OffHour && now.minute() == OffMin)
    {
      digitalWrite(Relay,HIGH);
      Serial.println("LIGHT OFF");
    }
}
