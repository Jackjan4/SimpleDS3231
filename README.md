# SimpleDS3231

A powerful but also beginner-friendly library that enables support for the DS3231 Real-Time-Clock module.


## Motivation

I (Jan) created this library due to the fact that most other libraries for the DS3231 are either missing important features (such as the alarm) or are difficult to use for beginners that don't know how to fiddle with registers.

Unhappy with this situation I created SimpleDS3231 with the goal to be the ultimate library for the DS3231 featuring:

- **Easy syntax**
- **Rich documentation**
- **Beginner friendly** - SimpleDS3231 features a rich documentation and a straightforward syntax
- **Complete feature set** - While keeping things simple, this library supports all of the features the DS3231 has to offer (like temperature sensor, alarms, Square-wave, ...)
- **Advanced features** - Advanced users can use special functions like direct-register-access-functions to speak directly to the DS3231 registers
- **Support for EEPROM** - The EEPROM that is included on some DS3231 boards found on eBay/Aliexpress is supported by this library to save data onto the DS3231 that can be stored for years with a coin cell battery


## The DS3231

**"The DS3231 is a low-cost, extremely accurate I2C realtime clock (RTC) with an integrated temperaturecompensated crystal oscillator (TCXO) and crystal."** - DS3231 datasheet

