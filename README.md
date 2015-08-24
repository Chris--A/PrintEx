# `PrintEx` Library for Arduino ![Version 1.1.0](https://img.shields.io/badge/Version-1.1.0-blue.svg)

**Written by:** *Christopher Andrews*.  
**Copyright:** _**2013**_*(GString)*-_**2015**_*(PrintEx)*, *Christopher Andrews, Released under MIT licence*.

This library is the descendant of a library I wrote called `GString`.
This library allows extending any `Stream` or `Print` derived library with feature rich printing and formatting capabilities. You can even create a library which provides the enhanced capabilities by default. Or alongside `Stream` for a bidirectional implementation.

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

## Contents:
- [*Basic Usage.*](#basic-usage)
  - [Enhancing any `Stream` or `Print` based object](#1-enhancing-any-stream-or-print-based-object).
  - [Using chainable functions](#using-chainable-functions).
  - [`printf` formatting](#printf-formatting).
- [*Interfaces.*](#interfaces)
- [*Helpers & Tools.*](#helpers--tools)
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
  
#### 2. Using chainable functions.

Every interface using this library incorporates an additional set of functions specifically designed for creating a chain like syntax. For example a series of `print()`/`println()` calls can be replaced with a chain.

The functions provided are as follows:

Member  | Description
------------- | -------------
`concat(...)`  | This functions exactly the same as `print()` however it does not return a count of bytes printed, but a reference to the calling object. This allows a chain of calls to be written.
`concatln(...)`  | This is the `println()` equivalent of `concat()`.
`repeat(char,count)`  | Writes a character `count` times to the output.
`repeatln(char,count)`  | This is almost the same as `repeat()` however it also appends a new line at the end of the repeated character (`\r\n`).
`repeat(str,repeatCount)`  | Writes a string (`str) `repeatCount` times to the output. The string must be null terminated.
`repeatln(str,repeatCount)`  | Similar to `repeat(str, repeatCount)`, just appends a new line at the end.
`repeat(str,size,repeatCount)`  | Writes a string `repeatCount` times to the output. The length of the string is specified by `size`. This allows writing part of a stirng or one that is not null terminated.
`repeatln(str,size,repeatCount)`  | Similar to `repeat(str, size, repeatCount)`, just appends a new line at the end.

Here is the basic idea behind chaining. Typically you'd be limited to writing code like this:

```C++
Serial.print( "ADC0 value: " );
Serial.println( analogRead(A0), DEC );
```

Now, when using a PrintEx based object you can replace the code with:

```C++
mySerial.concat( "ADC0 value: " ).concatln( analogRead(A0), DEC );
```

The usefulness of these functions is determined by your coding preference. Only `repeat()` and `repeatln()` are providing new functionality in terms of actual printing.

```C++
#include <PrintEx.h>

StreamEx serial = Serial;

void setup(){
  Serial.begin(9600);
  
  serial.repeatln( '=', 20 )
        .concat("Chainable functions test: ")
        .concatln(3.1415f, 3)
        .repeat( '=', 20 );
}

void loop() {}
```

#### 3. `printf` formatting.

Formatting options use the following syntax:  
`%[flags][width][length]specifier`

Each element and thier set of options is described in the tables below.  

- **Flags**  
  One or more of the flags below can be used. However each one used must be in the order used in this table.

  Flag  | Description
  ------------- | -------------
  `-` | Left-justify within the given field width; Right justification is the default.
  `0` | When padding is specified, zeros are used instead of spaces.
  
- **Width**  
  This option allows padding out data. It is also used to specify data for custom routines. 

  Value  | Description
  ------------- | -------------
  `(number)` | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
  `*` | The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
  
  ---
  Some specifiers require additional data provided using the `width` parameter.
  
  Specifier  | Description
  ------------- | -------------
  `%r` | The number of characters to read from the EEPROM.
  `%n` | Number of times to run repeat function.
  
- **Length**  
  This only has one value: `l`. If this value is present the behaviour of certain specifiers is changed.

  Specifier  | Description
  ------------- | -------------
  `%d` or `%i` | Use `long` instead of `int`.
  `%u` or `%x` | Use `unsigned long` instead of `unsigned int`.
  `%n` | Repaet a string, instead of a character.
  
- **Specifiers**
  
    Name  | Description
  ------------- | -------------
  `s` | String ( null terminated ).
  `p` | PROGMEM string. No formatting takes place, the string is printed directly.
  `r` | EEPROM string. No formatting takes place, the string is printed directly.
  `d` | Signed decimal integer ( 32bits max ).
  `i` | Same as `d`.
  `u` | Unsigned decimal integer ( 32bits max ).
  `f` | Decimal floating point number.
  `x` | Unsigned decimal integer ( 32bits max ).
  `c` | Character.
  `n` | Repeat function ( default character, see length ).
  `%` | Escape character for printing `%`.

```C++
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup() {
  Serial.begin(9600);
  mySerial.printf( "%20n\nFirst printf use!\n%20n", '=', '=' );
}

void loop() {}
```

---

## Interfaces
Type  | Description
------------------------------- | -------------
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
`DualWriter`  | Allows calling multiple `Print` interfaces through a single object.
`NullStream`  | A data stream to nowhere.
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


