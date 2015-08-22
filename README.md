# `PrintEx` Library for Arduino ![Version 1.1.0](https://img.shields.io/badge/Version-1.1.0-blue.svg)

**Written by:** *Christopher Andrews*.  
**Copyright:** _**2013**_*(GString)*-_**2015**_*(PrintEx)*, *Christopher Andrews, Released under MIT licence*.

This library is the descendant of a library I wrote called `GString`
This library allows extending any `Stream` or `Print` derived library with feature rich printing and formatting capabilities.

A sample of libraries which can be extended are as follows:
- [`Serial`](https://www.arduino.cc/en/Reference/Serial)
- [**Ethernet** (`EthernetClient`,`Server`)](https://www.arduino.cc/en/Reference/Ethernet) 
- [**WiFi** (`WiFiClient`, `Server`)](https://www.arduino.cc/en/Reference/WiFi)
- [`SoftwareSerial`](https://www.arduino.cc/en/Reference/SoftwareSerial)
- `LiquidCrystal`
- [`Wire`](https://www.arduino.cc/en/Reference/Wire)
- [`SD`](https://www.arduino.cc/en/Reference/SD)
- Any other library that inherits `Print` or `Stream`. 

You can even create a library which provides the enhanced capabilities by default. Or alongside `Stream` for a bidirectional implementation.

### Contents:
- [*Basic Usage.*](#basic-usage)
  - Enhancing any `Stream` or `Print` based object.
  - `concat()` & `concatln()`.
  - `printf` formatting.
- [*Interfaces.*](#interfaces)
- [*Helpers & Tools.*](#helpers--tools)
- [*`printf` & `sprintf` formatting documentation.*](#printf--sprintf-documentation)

---
## Basic Usage
#### 1. Enhancing any `Stream` or `Print` based object.
To extend an already existing object like `Serial`, or `EthernetClient` you'll need to make use of either `StreamEx` or `PrintEx`. 

- `StreamEx`  
This extends the `Print` interface while maintaining the ability to read. All exisiting `Print` & `Stream` functions are available for use. To use this class simply create a variable of type `StreamEx` and initialize it with your `Stream` based object.
  ```
  StreamEx myStream = Serial;
  ```
- `PrintEx`  
This extends the `Print` interface. Only existing and enhanced `Print` functions are available for use. The ability to read is not available, however if the object you want enhanced is a `Stream`, you can use it in combination with the `PrintEx` object. To use this class create a variable of type `PrintEx` and initialize it with your `Print` based object.
  ```
  PrintEx myPrint = Serial;
  ```
#### 2. `concat()` & `concatln()`.

```
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
`PrintEx`  | This object provides an easy method of enhancing other `Print` based objects with the capabilites provided by `PrintExtension`.
`StreamEx`  | This object provides an easy method of enhancing other `Stream` based objects with the capabilites provided by `PrintExtension` while maintaining the bidirectional interface.
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