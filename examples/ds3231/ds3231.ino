// Date, Time, Alarm and Temperature functions using a DS3231 RTC connected via I2C and Wire lib

#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const char* months[] = {"January", "February", "March", "April", "May", "June", "July", "August","September", "October", "November", "December"};


DateTime tt;  //variable of type DateTime


void setup () {

#ifndef ESP8266
    while (!Serial); // for Leonardo/Micro/Zero
#endif

    Serial.begin(57600);
  
  
    if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);   // sketch halts in an endless loop
  }
  
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  
    //set the RTC date & time - to the time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
 
    // set the RTC date & time - to any time you choose example 
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));      // would set to January 21, 2014 at 3:00:00 (3am)
    // rtc.adjust(DateTime(2015, 2, 28, 14, 50, 00));   // would set to February 28, 2015 at 14:50:00 (2:50pm)
  }
  
  //get time 
  tt = rtc.now();
  
  //get temperature 
  float c = rtc.getTemperature();

  //print temperature
  Serial.print("temperature: ");
  Serial.print(c);
  Serial.println("* C");
  
  //set alarm 1
  rtc.setAlarm1Simple(tt.hour(), tt.minute() + 1 );
  rtc.turnOnAlarm(1);
  if (rtc.checkAlarmEnabled(1)) {
    Serial.print("Alarm 1 set to ");
    Serial.print(tt.hour());
    Serial.print(":");
    Serial.println(tt.minute() + 1);
  }

}//setup()


void loop () {
 
    
    //get time 
    tt = rtc.now(); // read the time from the DS3231 RTC chip
    
    Serial.print(tt.year(), DEC);
    Serial.print('/');
    Serial.print(tt.month(), DEC);
    Serial.print('/');
    Serial.print(tt.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[tt.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(tt.hour(), DEC);
    Serial.print(':');
    Serial.print(tt.minute(), DEC);
    Serial.print(':');
    Serial.print(tt.second(), DEC);
    Serial.println();
    
    Serial.print(" since midnight 1/1/1970 = ");
    Serial.print(tt.unixtime());
    Serial.print("s = ");
    Serial.print(tt.unixtime() / 86400L);
    Serial.println("d");
    
    // calculate a date which is 7 days and 30 seconds into the future
    DateTime future (tt + TimeSpan(7,12,30,6));
    
    Serial.print(" now + 7d + 30s: ");
    Serial.print(future.year(), DEC);
    Serial.print('/');
    Serial.print(future.month(), DEC);
    Serial.print('/');
    Serial.print(future.day(), DEC);
    Serial.print(' ');
    Serial.print(future.hour(), DEC);
    Serial.print(':');
    Serial.print(future.minute(), DEC);
    Serial.print(':');
    Serial.print(future.second(), DEC);
    Serial.println();
    
    Serial.println();
    
	
  // check (in software) to see if Alarm 1 has been triggered
    if (rtc.checkIfAlarm(1)) {
      Serial.println("Alarm 1 Triggered");
    }
    
    delay(3000); 
}//loop()
