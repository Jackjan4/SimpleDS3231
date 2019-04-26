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
- **Low memory footprint** - In the world of Arduinos memory is rare, so we always try to optimize away every unnecessary byte we can, while developing this library


## The DS3231

**"The DS3231 is a low-cost, extremely accurate I2C realtime clock (RTC) with an integrated temperature-compensated crystal oscillator (TCXO) and crystal."** - DS3231 datasheet

In other words the DS3231 is a real-time-clock that combines a bunch of very neat features. It can be powered by coin cell battery for years since it just uses 80uA when idling. It uses I2C to communicate with a microcontroller, so all you need is 2 wires to get things going.

The DS3231 features:
- 2 Alarm clocks that can trigger an interrupt pin in defined intervals
- A square wave output, that can be used as a clock source or for timed events
- A 32KHz output, that can also be used as a clock source for example
- A temperature sensor


Most people who use the DS3231 probably won't buy the chip as a standalone version. There are a couple of companies who packed the chip together with some supporting-peripherals onto a breakout-board. The most popular read-to-use board is seen in the picture below. It can be bought for around $5 from eBay or Aliexpress and features the DS3231 chip, support circuitry, a battery slot for a CR2032 coin cell and an EEPROM. This board is perfect to start with, but also has [some problems, which should be addressed first, before using it.](https://github.com/Jackjan4/SimpleDS3231/wiki/Problems-with-the-cheap-boards-from-eBay-&-Aliexpress!)
![DS3231 breakout board](https://www.wiltronics.com.au/wp-content/uploads/images/make-and-create/ds3231-high-precision-real-time-clock-module-bottom.jpg)


## Download & Installation


## Getting Started

4 lines of code is everything you need to get things running.

```c++
#include "DS3232.h"

DS3231 rtc;

void setup() {

    // Initialize the DS3231
    rtc.begin();
    
    // Set RTC time in 24-hour-mode
    //           year, month, date, day, hour, minutes, seconds
    rtc.setTime24(19, 4, 22, DS3231::TUESDAY, 13, 24, 33);

}

void loop() {

}
```

The library includes many more features, see the [documentation](https://github.com/Jackjan4/SimpleDS3231/wiki) or the [code reference]().
## Documentation

[SimpleDS3231 has a rich documentation that can be found in its GitHub wiki.](https://github.com/Jackjan4/SimpleDS3231/wiki)

We also have a [code reference]() where every method of the library is documented.

## Supported Microcontrollers

SimpleDS3231 is build to work with as many microcontrollers as possible but due to the differences in behavior of some microcontrollers it cannot be guaranteed to work with every specific MCU out there. SimpleDS3231 was build with AVR architecture (Arduino Uno, Nano, ...) in mind so these boards have the best chance to work.

SimpleDS3231 was tested and confirmed to work on the following boards:

- Arduino Leonardo
- SparkFun Pro Micro 3.3V/8MHz


Can't find your board in this list or using the library throws errors? Create an issue with detailed information about your enviromment and we will try to help you.

## Credits

- Jan "[Jackjan4](https://github.com/Jackjan4)"
