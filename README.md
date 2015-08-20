# `PrintEx` Library for Arduino ![Version 1.1.0](https://img.shields.io/badge/Version-1.1.0-blue.svg)

**Written by:** *Christopher Andrews*.  
Copyright 2015, Released under MIT licence.

This library allows extending any `Stream` or `Print` derived library with feature rich printing and formatting capabilities.

A sample of libraries which can be extended are as follows:
- `Serial`
- `Ethernet`/`EthernetClient`
- `Wifi`
- `LiquidCrystal`
- `Wire`
- `SD`
- Any other library that inherits `Print` or `Stream`. 

You can even create a library which provides the enhanced capabilities by default. Or alongside `Stream` for a bidirectional implementation.


### Contents:
- [*Basic Usage.*](#basic-usage)
- [*Interfaces.*](#interfaces)
- [*Helpers & Tools.*](#helpers--tools)
- [*`printf` & `sprintf` formatting documentation.*](#printf--sprintf-documentation)

---
## Basic Usage

#### 1. `printf` for `Serial` and other `Stream` based objects.

```C++
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup() {
  Serial.begin(9600);
  mySerial.printf( "%20n\nFirst printf use!\n%20n", '=', '=' );
}

void loop() {}
```

If you do not need the 'read' capabilities of `Stream` you can use `PrintEx` instead:  
`PrintEx serial = Serial;`

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
