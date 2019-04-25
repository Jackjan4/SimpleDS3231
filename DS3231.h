// SimpleDS3231 was started by Jan Roslan <Jackjan@protonmail.com>
// https://github.com/Jackjan4/SimpleDS3231
// Made with love & released to the public domain! Enjoy!

#ifndef _SIMPLEDS3132_H_
#define _SIMPLEDS3132_H_

//#include <Arduino.h>

class DS3231 {
   public:
    uint8_t DS3231_ADDRESS = 0x68;

    static const uint8_t ALARM1_ONCE_PER_SECOND = 0b1111;
    static const uint8_t ALARM1_SECONDS_MATCH = 0b1110;
    static const uint8_t ALARM1_MINUTES_SECONDS_MATCH = 0b1100;
    static const uint8_t ALARM1_HOURS_MINUTES_SECONDS_MATCH = 0b1000;
    static const uint8_t ALARM1_DATE_HOURS_MINUTES_SECONDS_MATCH = 0b00000;
    static const uint8_t ALARM1_DAY_HOURS_MINUTES_SECONDS_MATCH = 0b10000;
	
    static const uint8_t ALARM2_ONCE_PER_MINUTE = 0b111;
    static const uint8_t ALARM2_MINUTES_MATCH = 0b110;
    static const uint8_t ALARM2_HOURS_MINUTES_MATCH = 0b100;
    static const uint8_t ALARM2_DATE_HOURS_MINUTES_MATCH = 0b0000;
    static const uint8_t ALARM2_DAY_HOURS_MINUTES_MATCH = 0b1000;
	
    static const uint8_t SQUAREWAVE_1HZ = 0b00;
    static const uint8_t SQUAREWAVE_1024KHZ = 0b01;
    static const uint8_t SQUAREWAVE_4096KHZ = 0b10;
    static const uint8_t SQUAREWAVE_8192KHZ = 0b11;

    // Constructor
    DS3132();




	// ==== Temperature Functions ====

    /** 
	 *  Gets the temperature from the DS3231 in Celsius.
	 *  The temperature is updated every 64 seconds and when the device powers on.
	 */
    double getTemperature();
	
	
	
	/**
	 * Gets the temperature from the DS3231 in Fahrenheit.
	 * The temperature is updated every 64 seconds and when the device powers on.
	 */
	 double getTemperatureFahrenheit();
	 
 
 

	// ==== General Functions ===

    /**	
	 *  Initializes the DS3231 device
	 */
    void begin();

    /** 
	 *  Initializes the DS3231
	 *  Also changes the address with which the library tries to communicate with the DS3231
	 *  Only use this variant of begin when you changed the I2C address on the DS3231.
	 */
    void begin(uint8_t i2c_address);




    // ==== Time functions ====

    /**
	 *  Adjusts the devices time to the given date.
	 *  This function will set the device to 24-hour-mode so this date should be formatted accordingly
	 *  Year - The year to be set: Allowed values: 00-99
	 *  Month - The month to be set: Allowed values: 01-12
	 *  Date - The date to be set: Allowed values: 01-31
	 *  Day - The day of the week to be set: Allowed values: 1-7
	 *  Hours - The hours to be set: Allowed values: 00-23
	 *  Minutes - The minutes to be set: Allowed values: 00-59
	 *  Seconds - The seconds to be set: Allowed values: 00-59
	 */
    void setTime24(uint8_t year, uint8_t month, uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds);

    /**
	  * Returns the year from the DS3231
	  */
    uint8_t getYear();

    /**
	  * Returns the month from the DS3231
	  */
    uint8_t getMonth();

    /**
	 * Returns the date from the DS3231
	 */
    uint8_t getDate();

    /**
	 * Returns the day of the week from the DS3231
	 */
    uint8_t getDow();

    /**
	 * Returns the seconds from the DS3231
	 */
    uint8_t getHours();

    /**
	 * Returns the seconds from the DS3231
	 */
    uint8_t getMinutes();

    /**
	  * Returns the seconds from the DS3231
	  */
    uint8_t getSeconds();
	
	
	/**
	 *
	 */
	char* getTimeString();




    // ==== Alarm functions ====

    /**
	 * Sets the Alarm 1 to the given values in 24-hour-mode
	 */
    void setAlarm1(uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t alarm_mask);



    /**
	 * Sets the Alarm 2 to the given values in 24-hour-mode
	 */
    void setAlarm2(uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t alarm_mask);



    /**
	  * Turns on Alarm 1
	  */
    void turnOnAlarm1();



    /**
	  * Turns off Alarm 1
	  */
    void turnOffAlarm1();



    /**
	 * Turns on Alarm 2
	 */
    void turnOnAlarm2();



    /**
	 * Turns off Alarm 2
	 */
    void turnOffAlarm2();



    /**
	 *
	 */
    void turnOffAlarm(uint8_t alarm);



	/**
	 *
	 */
    void turnOnAlarm(uint8_t alarm);



    /**
     *  Clears the alarm flag of the given alarm
     */
    void clearAlarmFlag(uint8_t alarm);



    /**
	 * Resets the given alarm (clear the alarm flag of the given alarm)
	 */
    void resetAlarm(uint8_t alarm);



    // ==== Square Wave functions ====

    /**
	 *
	 */
    void activateSquareWave();
	
	/**
	 *
	 */
    void deactivateSquareWave();




    // ==== Register functions ====

    /**
	 * Returns the value of a register
	 */
    uint8_t getRegister(uint8_t reg);

    /**
	 * Writes a byte to a register
	 */
    void writeRegister(uint8_t reg, uint8_t val);



   private:
    // Helper-function to quickly access a register on the DS3231
    void goToRegister(uint8_t reg);

    // Helper-function to quicly access a register (without closing the connection) on the DS3231
    void goToRegisterOpen(uint8_t reg);
};

#endif
