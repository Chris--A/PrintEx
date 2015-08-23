# `PrintEx` Library for Arduino ![Version 1.1.0](https://img.shields.io/badge/Version-1.1.0-blue.svg)

**Written by:** *Christopher Andrews*.  
**Copyright:** _**2013**_*(GString)*-_**2015**_*(PrintEx)*, *Christopher Andrews, Released under MIT licence*.

This library is the descendant of a library I wrote called `GString`.
This library allows extending any `Stream` or `Print` derived library with feature rich printing and formatting capabilities.

The `printf` implementation found in this library is unique. It has been built directly on top of the Arduino `Print` library rather than as a separate code base simply called from within. All the features found in **PrintEx** use a feature already implemented in `Print`. This means floating point support is actually using `Print::print( float );`. As a result, the implementation is not quite standard (can be standardized though), and contains additional functionality like support for EEPROM and PROGMEM data.

A sample of libraries which can be extended are as follows:
- [`Serial`](https://www.arduino.cc/en/Reference/Serial)
- [Ethernet (`EthernetClient`,`Server`)](https://www.arduino.cc/en/Reference/Ethernet) 
- [WiFi (`WiFiClient`, `Server`)](https://www.arduino.cc/en/Reference/WiFi)
- [`SoftwareSerial`](https://www.arduino.cc/en/Reference/SoftwareSerial)
- [`LiquidCrystal`](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [`Wire`](https://www.arduino.cc/en/Reference/Wire)
- [`SD`](https://www.arduino.cc/en/Reference/SD)
- Any other library that inherits `Print` or `Stream`. 

You can even create a library which provides the enhanced capabilities by default. Or alongside `Stream` for a bidirectional implementation.

### Contents:
- [*Basic Usage.*](#basic-usage)
  - [Enhancing any `Stream` or `Print` based object.](#1-enhancing-any-stream-or-print-based-object)
  - Using chainable functions.
  - `printf` formatting.
- [*Interfaces.*](#interfaces)
- [*Helpers & Tools.*](#helpers--tools)
- [*`printf` & `sprintf` formatting documentation.*](#printf--sprintf-documentation)
- [Custom configuration.](#custom-configuration)

---
## Basic Usage
#### 1. Enhancing any `Stream` or `Print` based object.
To extend an already existing object like `Serial`, or `EthernetClient` you'll need to make use of either `StreamEx` or `PrintEx`. 

- `StreamEx`  
This extends the `Print` interface while maintaining the ability to read. All existing `Print` and `Stream` functions are available for use. To use this class simply create a variable of type `StreamEx` and initialize it with your `Stream` based object.

  ```C++
  StreamEx myStream = Serial;
  ```
- `PrintEx`  
This extends the `Print` interface. Only existing and enhanced `Print` functions are available for use. The ability to read is not available, however if the object you want enhanced is a `Stream`, you can use it in combination with the `PrintEx` object. To use this class create a variable of type `PrintEx` and initialize it with your `Print` based object.

  ```C++
  PrintEx myPrint = Serial;
  ```
  
If you need to use any functions specific to the object you are using (not found in `Print` or `Stream`) you will have to use the real object. For example, `Serial` implements `begin()` which is not part of `Stream`:

```C++
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup(){
  Serial.begin(9600);
  mySerial.printf("The compile time & date is: %s, %s", __TIME__, __DATE__);
}

void loop() {}
```
  
#### 2. `concat()` & `concatln()`.

```C++
#include <PrintEx.h>

StreamEx serial = Serial;

void setup(){
  Serial.begin(9600);
  
  serial.repeat( '=', 20 )
        .concat("\nconcat(ln) test: ")
        .concatln(3.1415f, 3)
        .repeat( '=', 20 );
}

void loop() {}
```

#### 3. `printf` formatting.

```C++
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup() {
  Serial.begin(9600);
  mySerial.printf( "%20n\nFirst printf use!\n%20n", '=', '=' );
}

void loop() {}
```

Documentation for `printf` can be found [below](#printf--sprintf-documentation).

The API also provides `concat()` and `concatln()` for use with all `Print` derived objects.

---

## Interfaces
Type  | Description
------------- | -------------
`PrintEx`  | This object provides an easy method of enhancing other `Print` based objects with the capabilities provided by `PrintExtension`.
`StreamEx`  | This object provides an easy method of enhancing other `Stream` based objects with the capabilities provided by `PrintExtension` while maintaining the bidirectional interface.
`GString`  | This object provides printing and formatting capabilities for blocks of memory (SRAM). The object can be passed to other Print functions.
`EString`  | This is the EEPROM equivalent of `GString`. This essentially allows formatted printing of strings to the EEPROM. It also allows other `Print` based classes to print EEPROM data easily.
`PString`  | This is a PROGMEM read-only version of `GString`. It allows printing of flash based strings.
`PrintExtension`  | This is a core interface for `PrintEx`. It provides the formatting features such as `concat()` and `printf()`.
`NonStreamingIO`  | This interface provides an extension to the `Print` class. It allows IO capabilities for derived objects that may not be streams. As in, the data printed to the object is still available for use.
---

## Helpers & Tools

Object  | Description
------------- | -------------
`NothingYet`  | Don't expect much.

---
## `printf` & `sprintf` documentation.

```C++
	/****************************************************************
        sprintf, x.printf function.
            Prints formatted text.

            Formatting options use the following syntax:
                %[flags][width][length]specifier

            Flags:
                -:    Left-justify within the given field width; Right justification is the default.
                0:    When padding is specified, zeros are used instead of spaces.

            Width:
                (number):   Minimum number of characters to be printed.
                            If the value to be printed is shorter than this number,
                            the result is padded with blank spaces.
                            The value is not truncated even if the result is larger.

                *:  The width is not specified in the format string,
                    but as an additional integer value argument preceding
                    the argument that has to be formatted.

                Extra:

                    r:  When using 'r' to read the EEPROM the width is the number of
                        characters to read.

                    n:  Number of times to run repeat function.

            Length:
                l:  d, i use long instead of int.
                    u, x use unsigned long instead of unsigned int.
                    n    repeats a string.
            Specifier:
                s:    String ( null terminated ).
                p:    PROGMEM string. No formatting takes place, the string is printed directly.
                r:    EEPROM string. No formatting takes place, the string is printed directly.
                d:    Signed decimal integer ( 32bits max ).
                i:    Same as 'd'.
                u:    Unsigned decimal integer ( 32bits max ).
                f:    Decimal floating point number.
                x:    Unsigned decimal integer ( 32bits max ).
                c:    Character.
                n:    Repeat function ( default character, see length ).
                %:    Escape character for printing '%'
    ****************************************************************/
```
---

## Custom Configuration.
For normal use this section is not necessary. However the library can be tweaked if needed.

The available customizations can be used by defining one or a combination of the options listed below. They can be defined either in the *PrintExtension.h* file, or passed as a compiler option using `-D`. Unfortunately defining these in your sketch will not have any effect.
### GLobal library flags.
These settings affect all library functions that use the features described.

Define  | Action if defined
------------- | -------------
`PRINTEX_NO_SPRINTF`  | Do not override the global `sprintf` with a version supporting all the features present in PrintEx.
`PRINTEX_LARGE_COUNTER`  | Use a 16-bit value for print counters, instead of 8 bits (how many characters printed). If you do not care about the return count of print functions, leave the setting as is. This will allow more efficient code, however writes larger than 255 characters will have incorrect counts returned..

### `printf` specific flags.
These settings only affect the `printf` implementation. To avoid inclusion outside of the `printf`/`sprintf` implementation, simply do not use the `PrintEx` function providing the feature (The compiler will remove unused code).

Define  | Action if defined
------------- | -------------
`PRINTEX_NO_WIDTH_PARAM`  | The width parameter must be specified inline and cannot be set to `*` specifying an additional input for the width.
`PRINTEX_NO_PROGMEM`  | Do not include PROGMEM functionality (`%p`).
`PRINTEX_NO_EEPROM`  | Do not include EEPROM functionality (`%r`).
`PRINTEX_NO_FLOATING_POINT`  | Do not include support for floating point data (`%f`).
`PRINTEX_NO_REPEAT`  | Do not include character repeat functionality (`%n`).
`PRINTEX_NO_ERROR_CONDITION`  | Do not include error handling (`Error` is printed on bad inputs/failed operation).


