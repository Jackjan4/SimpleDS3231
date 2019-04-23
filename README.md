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

**"The DS3231 is a low-cost, extremely accurate I2C realtime clock (RTC) with an integrated temperature-compensated crystal oscillator (TCXO) and crystal."** - DS3231 datasheet

In other words the DS3231 is a real-time-clock that combines a bunch of very neat features. It can be powered by coin cell battery for years since it just uses 80uA when idling. It uses I2C to communicate with a microcontroller, so all you need is 2 wires to get things going.

The DS3231 features:
- 2 Alarm clocks that can trigger an interrupt pin in defined intervals
- A square wave output, that can be used as a clock source or for timed events
- A 32KHz output, that can also be used as a clock source for example
- A temperature sensor


Most people who use the DS3231 probably won't buy the chip as a standalone version. There are a couple of companies who packed the chip together with some supporting-peripherals onto a breakout-board. The most popular read-to-use board is seen in the picture below. It can be bought for around $5 from eBay or Aliexpress and features the DS3231 chip, support circuitry, a battery slot for a CR2032 coin cell and an EEPROM. This board is perfect to start with, but also has some problems, which should be addressed first, before using it.
