// SimpleDS3231 was started by Jan Roslan <Jackjan@protonmail.com>
// https://github.com/Jackjan4/SimpleDS3231
// Made with love & released to the public domain! Enjoy!

#include <Wire.h>
#include "DS3231.h"
#include <Arduino.h>
#include <stdio.h>




// ==== General functions ====

/**
 *
 */
void DS3231::begin() {
    // We are joining the bus as a master
    Wire.begin();
}



/**
 *
 */
void DS3231::begin(uint8_t i2c_address) {
    // Change I2C address
    DS3231_ADDRESS = i2c_address;

    begin();
}



/**
 *
 */
void DS3231::setTime24(uint8_t year, uint8_t month, uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds) {

    /// Calculate values
    //year
    uint8_t tenYear = year / 10;
    uint8_t singleYear = year % 10;

    // month
    uint8_t tenMonth = month / 10;
    uint8_t singleMonth = month % 10;

    // date
    uint8_t tenDate = date / 10;
    uint8_t singleDate = date % 10;

    // hours
    uint8_t singleHour = hours % 10;

    // minutes
    uint8_t tenMinute = minutes / 10;
    uint8_t singleMinute = minutes % 10;

    // seconds
    uint8_t tenSecond = seconds / 10;
    uint8_t singleSecond = seconds % 10;

    goToRegisterOpen(0x00);

    /// Write Registers
    // Register 00 - Seconds
    Wire.write((tenSecond << 4) + singleSecond);

    // Register 01 - Minutes
    Wire.write((tenMinute << 4) + singleMinute);

    // Register 02 - Hours
    uint8_t hourVal;
    if (hours >= 20) {
        hourVal = 1;
        hourVal <<= 1;
    } else if (hours >= 10) {
        hourVal = 1;
    }
    Wire.write((hourVal << 4) + singleHour);

    // Register 03 - Day
    Wire.write(day);

    // Register 04 - Date
    Wire.write((tenDate << 4) + singleDate);

    // Register 05 - Month
    Wire.write((tenMonth << 4) + singleMonth);

    // Register 06 - Year
    Wire.write((tenYear << 4) + singleYear);

    Wire.endTransmission();
}



/**
 * Returns the year from the DS3231
 */
uint8_t DS3231::getYear() {
    uint8_t val = getRegister(0x06);

    uint8_t tenYear = val >> 4;
    uint8_t singleYear = val - (tenYear << 4);

    return tenYear * 10 + singleYear;
}



/**
 * Returns the year from the DS3231
 */
uint8_t DS3231::getMonth() {
    uint8_t val = getRegister(0x05);

    uint8_t tenMonth = val >> 4;
    uint8_t singleMonth = val - (tenMonth << 4);

    return tenMonth * 10 + singleMonth;
}



/**
 * Returns the year from the DS3231
 */
uint8_t DS3231::getDate() {
    uint8_t val = getRegister(0x04);

    uint8_t tenDate = val >> 4;
    uint8_t singleDate = val - (tenDate << 4);

    return tenDate * 10 + singleDate;
}



/**
 * Returns the day of the week from the DS3231
 */
inline uint8_t DS3231::getDow() {
    return getRegister(0x03);
}



/**
 * Returns the year from the DS3231
 */
uint8_t DS3231::getHours() {

    // TODO: Handle 12-hour mode

    // check hour mode

    // 24 hour mode
    uint8_t val = getRegister(0x02);

    uint8_t tenHour = val >> 4;
    uint8_t singleHour = val - (tenHour << 4);

    return 10 * tenHour + singleHour;
    
}



/**
 * Returns the minutes from the DS3231
 */
uint8_t DS3231::getMinutes() {
    uint8_t val = getRegister(0x01);

    uint8_t tenMinute = val >> 4;
    uint8_t singleMinute = val - (tenMinute << 4);

    return tenMinute * 10 + singleMinute;
}



/**
 * Returns the year from the DS3231
 */
uint8_t DS3231::getSeconds() {
    uint8_t val = getRegister(0x00);

    uint8_t tenSecond = val >> 4;
    uint8_t singleSecond = val - (tenSecond << 4);

    return tenSecond * 10 + singleSecond;
}



/**
 * Returns a string which represents the current time.
 * Can for example by printed into the console or used on other displays.
 * Formatting: DD.MM.YYYY HH:MM:SS
 * For a more textual representation, use getTimeStringText().
 * Parameters:
 * monthBeforeDate - Changes the formatting to MM.DD.YYYY HH:MM:SS which is common in the US for example.
 * useAmPm - Displays the time in 12-hour-mode
 */ 
char* DS3231::getTimeString() {
	static char buffer[21];
	
	sprintf(buffer, "%02d.%02d.20%d %02d:%02d:%02d", getDate(), getMonth(), getYear(), getHours(),getMinutes(),getSeconds());
	return buffer;
}



/**
 *
 */
void DS3231::setAlarm1(uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t seconds, uint8_t alarm_mask) {

    /// Calculate values
    // date
    uint8_t tenDate = date / 10;
    uint8_t singleDate = date % 10;

    // hours
    uint8_t singleHour = hours % 10;

    // minutes
    uint8_t tenMinute = minutes / 10;
    uint8_t singleMinute = minutes % 10;

    // seconds
    uint8_t tenSecond = seconds / 10;
    uint8_t singleSecond = seconds % 10;

    // Navigate to Register 07
    goToRegisterOpen(0x07);

    /// Write Registers
    // Register 07 - Seconds
    uint8_t regSec = (tenSecond << 4) + singleSecond;
	// Set Alarm Mask Bit 
    bitWrite(regSec, 7, alarm_mask & 0x01);
    Wire.write(regSec);

    // Register 08 - Minutes
    uint8_t regMin = (tenMinute << 4) + singleMinute;
	// Set Alarm Mask Bit 
    bitWrite(regMin, 7, ((alarm_mask) >> 1) & 0x01);
    Wire.write(regMin);

    // Register 09 - Hours
    uint8_t hourVal;
    if (hours >= 20) {
        hourVal = 1;
        hourVal <<= 1;
    } else if (hours >= 10) {
        hourVal = 1;
    }
    uint8_t regHour = (hourVal << 4) + singleHour;
	// Set Alarm Mask Bit 
    bitWrite(regHour, 7, ((alarm_mask) >> 2) & 0x01);
    Wire.write(regHour);
	
	// Check if Date or Day - DY/DT
	// Register 0A
	if (((alarm_mask) >> 4) & 0x01) {
		// Day
	} else {
		// Date
        uint8_t regDate = (tenDate << 4) + singleDate;
	    // Set Alarm Mask Bit 
        bitWrite(regDate, 7, ((alarm_mask) >> 3) & 0x01);

        // Set DT bit to zero to set Date of month check
        regDate |= (1 << 6);
        Wire.write(regDate);
	}

    Wire.endTransmission();
}



/**
 *
 */
void DS3231::setAlarm2(uint8_t date, uint8_t day, uint8_t hours, uint8_t minutes, uint8_t alarm_mask) {

    /// Calculate values
    // date
    uint8_t tenDate = date / 10;
    uint8_t singleDate = date % 10;

    // hours
    uint8_t singleHour = hours % 10;

    // minutes
    uint8_t tenMinute = minutes / 10;
    uint8_t singleMinute = minutes % 10;

    // Navigate to Register 0B
    goToRegisterOpen(0x0B);

    /// Write Registers
    // Register 0B - Minutes
    uint8_t regMin = (tenMinute << 4) + singleMinute;
	// Set Alarm Mask Bit 
    bitWrite(regMin, 7, alarm_mask & 0x01);
    Wire.write(regMin);

    // Register 0C - Hours
    uint8_t hourVal;
    if (hours >= 20) {
        hourVal = 1;
        hourVal <<= 1;
    } else if (hours >= 10) {
        hourVal = 1;
    }
    uint8_t regHour = (hourVal << 4) + singleHour;
	// Set Alarm Mask Bit 
    bitWrite(regHour, 7, ((alarm_mask) >> 1) & 0x01);
    Wire.write(regHour);
	
	// Check if Date or Day - DY/DT
	// Register 0A
	if (((alarm_mask) >> 3) & 0x01) {
		// Day
	} else {
		// Date
        uint8_t regDate = (tenDate << 4) + singleDate;
	    // Set Alarm Mask Bit 
        bitWrite(regDate, 7, ((alarm_mask) >> 2) & 0x01);

        // Set DT bit to zero to set Date of month check
        regDate |= (1 << 6);
        Wire.write(regDate);
	}

    Wire.endTransmission();
}



// === Temperature functions ===

/**
 *
 */
double DS3231::getTemperature() {
    double result;

    // Temperature Register 1 (0x11) & 2 (0x12)
    goToRegister(0x11);
    Wire.requestFrom(DS3231_ADDRESS, (uint8_t) 2);

    // Integer part
    result = Wire.read();

    uint8_t fractionPart = Wire.read();
    fractionPart >>= 6;

    return result + 0.25 * fractionPart;
}



/**
 *
 */
inline double DS3231::getTemperatureFahrenheit() {
	return (getTemperature() * 1.8) + 32;
}



/// ==== Square Wave functions ====

/**
 * Activates the square-wave output on the INT/SQW pin
 * This disables the possibility to use alarm interrupts
 * The use alarm interrupts again, deactivateSquareWave() must be called first
 */
void DS3231::activateSquareWave() {

    // Control Register
    uint8_t regVal = getRegister(0x0E);

    // Set Interrupt Control bit to 0 (INTCN)
    regVal &= ~(1 << 2);

    // Write new values to register
    writeRegister(0x0E, regVal);
}



/**
 * Deactivates the square-wave output on the INT/SQW pin.
 * This enables the possibility to use alarm interrupts.
 * To use the Square-Wave-output again, use activateSquareWave()
 */
void DS3231::deactivateSquareWave() {

    // Control Register
    uint8_t regVal = getRegister(0x0E);

    // Set Interrupt Control bit to 1 (INTCN)
    regVal |= (1 << 2);

    // Write new values to register
    writeRegister(0x0E, regVal);
}



/**
 * Turns on Alarm 1
 */
inline void DS3231::turnOnAlarm1() {
    turnOnAlarm(1);
}



/**
 * Turns off Alarm 1
 */
inline void DS3231::turnOffAlarm1() {
    turnOffAlarm(1);
}



/**
 * Turns on Alarm 2
 */
inline void DS3231::turnOnAlarm2() {
	turnOnAlarm(2);
}



/**
 * Turns off Alarm 2
 */
inline void DS3231::turnOffAlarm2() {
    turnOffAlarm(2);
}



/**
 * Turns off the given alarm
 */
void DS3231::turnOffAlarm(uint8_t alarm) {
	// no-op if user input is incorrect
	if (alarm > 2) return;

    // Control register
    uint8_t regVal = getRegister(0x0E);

    // Set Alarm Interrupt Enable bit to 0 (AXIE)
    regVal &= ~(1 << (alarm - 1));

    writeRegister(0x0E, regVal);

    // Also clear Alarm Flag in Status register
    clearAlarmFlag(alarm);
}



/**
 * Turns on the given alarm
 */
void DS3231::turnOnAlarm(uint8_t alarm) {
	// no-op if user input is incorrect
	if (alarm > 2) return;
	
	// 
	deactivateSquareWave();

    // Control register
    uint8_t regVal = getRegister(0x0E);

    // Set Alarm Interrupt Enable bit to 1 (AXIE)
    regVal |= (1 << (alarm - 1));

    writeRegister(0x0E, regVal);

    // Also clear Alarm Flag in Status register
    clearAlarmFlag(alarm);
}



/**
 * Returns the value of the given register.
 * You do NOT need to navigate to the register beforehand!
 */
uint8_t DS3231::getRegister(uint8_t reg) {
	// no-op if register is not in DS3231 range
	if (reg > 0x12) return;
    goToRegister(reg);
	
	// Convert to uint8_t or we would get a compiler-warning
    Wire.requestFrom(DS3231_ADDRESS, (uint8_t) 1);
    return Wire.read();
}



/**
 * Write the given byte to the given register
 */
void DS3231::writeRegister(uint8_t reg, uint8_t val) {
	// no-op if register is not in DS3231 range
	if (reg > 0x12) return;
    goToRegisterOpen(reg);
    Wire.write(val);
    Wire.endTransmission();
}



/**
 * Moves the I2C register-pointer to the given register
 */
void DS3231::goToRegister(uint8_t reg) {
	// no-op if register is not in DS3231 range
	if (reg > 0x12) return;
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission();
}



/**
 * Moves the I2C register-pointer to the given register (without closing the connection) on the DS3231
 */
void DS3231::goToRegisterOpen(uint8_t reg) {
	// no-op if register is not in DS3231 range
	if (reg > 0x12) return;
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(reg);
}


/**
 * 
 */
void DS3231::clearAlarmFlag(uint8_t alarm) {
	// no-op if user input is incorrect
	if (alarm > 2) return;
	
    uint8_t reg = getRegister(0x0F);
    reg &= ~(1 << (alarm - 1));
    writeRegister(0x0F, reg);
}


/**
 * 
 */
inline void DS3231::resetAlarm(uint8_t alarm) {
	clearAlarmFlag(alarm);
}