// Code by JeeLabs http://news.jeelabs.org/code/
// Released to the public domain! Enjoy!

// Merged DS3231 functions from: github/coobro/RTClib  by  MrAlvin 2012-02-27
// Alarm code for DS3231 heavily used/modified from Eric Ayars DS3231 library  by  Coobro
// Eric Ayars code is located at: http://hacks.ayars.org/2011/04/ds3231-real-time-clock.html

#ifndef _SIMPLEDS3132_H_
#define _SIMPLEDS3132_H_

#include <Arduino.h>
class DS3132 {
	
	public:
	
	// Initializes the DS3132 
	begin();
	
	// Gets the temperature from the DS3132 in Celsius.
	getTemperature();
	
}


#endif // _RTCLIB_H_
