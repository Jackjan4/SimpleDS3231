This is a fork of JeeLab's fantastic real time clock library for Arduino.

For details on using this library with an RTC module like the DS1307, see the guide at: https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/overview

To download. click the DOWNLOADS button to the right, and rename the uncompressed folder RTClib.

Place the RTClib folder in your <i>arduino_sketch_folder/libraries/</i> folder. 
You may need to create the libraries subfolder if its your first library. 
Restart the IDE.

<b>Basic functions</b>  (see libraries/examples of how to use):
-  .begin
-  .adjust
-  .isrunning
-  .now

<b>DS1307 specific functions:</b>
-  .readnvram <br>
-  .writenvram
-  .readSqwPinMode
-  .writeSqwPinMode

<b>PCF8523 specific functions:</b>
-  .writeSqwPinMode

<b>DS3231 specific functions:</b>
-  .getTemperature
-  .getA1Time
-  .setA1Time
-  .setAlarm1Simple
-  .turnOnAlarm
-  .turnOffAlarm
-  .checkAlarmEnabled
-  .checkIfAlarm
  
<B> Millis (software RTC) specific functions:</b> 
-  .checkRollover

##Compatibility  
DS3231 functionality tested on Arduino Pro Mini (Jan 8, 2016 - MrAlvin)

For other compatibility details see https://github.com/adafruit/RTClib

<b>ToDo: </b>
 - debug Alarm2
 - make DS3231 SQW functon calls similar to DS1307 function calls

