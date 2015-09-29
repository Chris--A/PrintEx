# `PrintEx` Library for Arduino ![Version 1.1.8](https://img.shields.io/badge/Version-1.1.8-blue.svg)

**Written by:** *Christopher Andrews*.  
**Copyright:** _**2013**_*(`GString`)*-_**2015**_*(`PrintEx`)*, *Christopher Andrews, Released under MIT licence*.

**Supported Platforms**:   
![Basic Arduino](https://img.shields.io/badge/Arduino-AVR-brightgreen.svg) 
![Arduino Zero](https://img.shields.io/badge/Arduino_Zero-SAMD-yellowgreen.svg)
![Arduino Due](https://img.shields.io/badge/Arduino_Due-SAM-orange.svg)
![ESP8266](https://img.shields.io/badge/ESP8266-Xtensa-yellow.svg)

## About

This library is the descendant of a library I wrote called `GString`.
This library allows extending any `Stream` or `Print` derived library with feature rich printing and formatting capabilities. You can directly use streaming (in & out), `printf`, chainable interfaces and repitition. You can even create a library which provides the enhanced capabilities by default. Or alongside `Stream` for a bidirectional implementation.

The `printf` implementation found in this library is unique. It has been built directly on top of the Arduino `Print` library rather than as a separate code base simply called from within. All the features found in `printf` use a feature already implemented in `Print`. This means floating point support is actually using `Print::print( float );`. It also contains additional functionality like support for _EEPROM_/_PROGMEM_ data, repetition and chaining calls.

This tool set also replaces the globally available version of `sprintf` with a version providing all the features of this library. Included in this package is a selection of helper objects I have created over the years. These include tools for validation, security, stability, and diagnostics.

A sample of Arduino libraries which can be extended are as follows:
- [`Serial`](https://www.arduino.cc/en/Reference/Serial)
- [Ethernet (`EthernetClient`,`Server`)](https://www.arduino.cc/en/Reference/Ethernet) 
- [WiFi (`WiFiClient`, `Server`)](https://www.arduino.cc/en/Reference/WiFi)
- [`SoftwareSerial`](https://www.arduino.cc/en/Reference/SoftwareSerial)
- [`LiquidCrystal`](https://www.arduino.cc/en/Reference/LiquidCrystal)
- [`Wire`](https://www.arduino.cc/en/Reference/Wire)
- [`SD`](https://www.arduino.cc/en/Reference/SD)
- Any other library that inherits `Print` or `Stream`.

## Contents:

*A limited number of features require C\+\+11, the Arduino Zero & ESP8266 already has this enabled, however the rest of the supported cores will have to wait for the release of IDE 1.6.6, if you do not want to wait, there is some info [here](http://arduino.land/FAQ/content/2/49/en/can-c11-be-used-with-arduino.html) explaining how to enable C\+\+11.*

- [Basic Usage.](#basic-usage).
  - [Enhancing any `Stream` or `Print` based object](#1-enhancing-any-stream-or-print-based-object).
  - [Streaming data (in/out)](#2-streaming-inout). ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg)
  - [Using chainable functions](#3-using-chainable-functions).
  - [`printf` formatting](#4-printf-formatting).
- [Helpers & Tools](#helpers--tools). 
- [Core Interfaces](#core-interfaces).
- [Custom Configuration](#custom-configuration).

---
## Basic Usage
#### 1. Enhancing any `Stream` or `Print` based object.
To extend an already existing object like `Serial`, or `EthernetClient` you'll need to make use of either `StreamEx` or `PrintEx`. 

**Note:** This section does not apply to streaming functionality, it is available by default (see the [next section](#2-streaming-inout) for more info).

- `StreamEx`  
This extends the `Print` interface while maintaining the ability to read. All existing `Print` and `Stream` functions are available for use. To use this class simply create a variable of type `StreamEx` and initialize it with your `Stream` based object.

  ```Arduino
  StreamEx myStream = Serial;
  ```
  
- `PrintEx`  
This extends the `Print` interface. Only existing and enhanced `Print` functions are available for use. The ability to read is not available, however if the object you want enhanced is a `Stream`, you can use it in combination with the `PrintEx` object. To use this class create a variable of type `PrintEx` and initialize it with your `Print` based object.

  ```Arduino
  PrintEx myPrint = Serial;
  ```
  
If you need to use any functions specific to the object you are using (not found in `Print` or `Stream`) you will have to use the real object. For example, `Serial` implements `begin()` which is not part of `Stream`:

```Arduino
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup(){
  Serial.begin(9600);
  mySerial.printf("The compile time & date is: %s, %s", __TIME__, __DATE__);
}

void loop() {}
```

#### 2. Streaming (in/out).

##### NOTE: Streaming is a C++11 only feature, you can enable it manually or wait for the IDE version 1.6.6 where is has been enabled by default.  

Streaming functionality is built into the PrintEx library, however you do not need to extend your object to use it (this will be done automatically). You can use any `Print` or `Stream` based object directly. Of course, a `Print` library does not have read capabilities and can only stream out data.

The benefit of streaming is, the code produced is smaller than the equivalent written using multiple `print()`/`println()` statements.

```Arduino
#include <PrintEx.h>

using namespace ios;

void setup(){

  Serial.begin( 9600 );

  //Stream out formatted data.
  Serial << "A hexidecimal number: " << hex << 43981 << endl;

  //Read two objects from Serial.
  int a;
  float f;
  Serial >> a >> f;
}

void loop(){}
```

Built in manipulators are listed below. If you do not include the namespace `ios` you will need to prefix these manipulators accordingly: `ios::hex`.

Manipulator  | Description
------------- | -------------
**`bin`** | Sets an output stream to print integers in binary.
**`oct`** | Sets an output stream to print integers in octal format.
**`dec`** | Sets an output stream to print integers in base 10.
**`hex`** | Sets an output stream to print integers in hexidecimal base.
**`precision`** | Takes a single parameter: Sets the output stream to print floating point data with a certain precision (decimal places).
**`endl`** | Prints a new line.
**`repeat`** | Accepts two parameters: the item to print, and how many times to repeat. The item can be a character or string.

Stream buffers can be used to read data directly, for instance, you can stream a string directly into EEPROM:

```Arduino
EString e( 0, 10 );  //Create a buffer starting at EEPROM cell 0, with 10 bytes length.
Serial >> e;
  ```

An alternative method for streaming data out uses the function `printx` (only available from extended interfaces ![C++11 Only!](https://img.shields.io/badge/Requires-C++11-orange.svg)). It uses the same manipulators above:

```Arduino
PrintEx printer = Serial;
printer.printx( "A hexidecimal number: ", hex, 4398, endl );
```

#### 3. Using chainable functions.

Every interface using this library incorporates an additional set of functions specifically designed for creating a chain like syntax. For example a series of `print()`/`println()` calls can be replaced with a chain.

The functions provided are as follows:

Member  | Description
------------- | -------------
**`concat(...)`**  | This functions exactly the same as `print()` however it does not return a count of bytes printed, but a reference to the calling object. This allows a chain of calls to be written.
**`concatln(...)`**  | This is the `println()` equivalent of `concat()`.
**`repeat(char,count)`**  | Writes a character `count` times to the output.
**`repeatln(char,count)`**  | This is almost the same as `repeat()` however it also appends a new line at the end of the repeated character (`\r\n`).
**`repeat(str,repeatCount)`**  | Writes a string (`str) `repeatCount` times to the output. The string must be null terminated.
**`repeatln(str,repeatCount)`**  | Similar to `repeat(str, repeatCount)`, just appends a new line at the end.
**`repeat(str,size,repeatCount)`**  | Writes a string `repeatCount` times to the output. The length of the string is specified by `size`. This allows writing part of a string or one that is not null terminated.
**`repeatln(str,size,repeatCount)`**  | Similar to `repeat(str, size, repeatCount)`, just appends a new line at the end.

Here is the basic idea behind chaining. Typically you'd be limited to writing code like this:

```Arduino
Serial.print( "ADC0 value: " );
Serial.println( analogRead(A0), DEC );
```

Now, when using a PrintEx based object you can replace the code with:

```Arduino
mySerial.concat( "ADC0 value: " ).concatln( analogRead(A0), DEC );
```

The usefulness of these functions is determined by your coding preference. Only `repeat()` and `repeatln()` are providing new functionality in terms of actual printing.

```Arduino
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

#### 4. `printf` formatting.

This library has a custom `printf` method for use with all interfaces found in this library. It is not as complete as a standard implementation, however it does support some custom features specific to Arduino. Basic support for the precision parameter is available, however it only affects floating point data. To request further implementation, please open an issue [here](https://github.com/Chris--A/PrintEx/issues).

Formatting options use the following syntax:  
`%[flags][width][.precision][length]specifier`

Each element and their set of options is described in the tables below.  

- **Flags**  
  One or more of the flags below can be used. However each one used must be in the order used in this table.

  Flag  | Description
  ------------- | -------------
  **`-`** | Left-justify within the given field width; Right justification is the default.
  **`0`** | When padding is specified, zeros are used instead of spaces.
  
- **Width**  
  This option allows padding out data. It is also used to specify data for custom routines. 

  Value  | Description
  ------------- | -------------
  **`(number)`** | Minimum number of characters to be printed. If the value to be printed is shorter than this number, the result is padded with blank spaces. The value is not truncated even if the result is larger.
  **`*`** | The width is not specified in the format string, but as an additional integer value argument preceding the argument that has to be formatted.
  
  ---
  Some specifiers require additional data provided using the `width` parameter.
  
  Specifier  | Description
  ------------- | -------------
  **`r`** | The number of characters to read from the EEPROM.
  **`n`** | Number of times to run repeat function.
  
- **Precision**

  To use this option the precision value must be preceeded by a period ('.'). This option only affects floating point data. Its value is the number of decimal places to use. For additional precision support (non floating point data), please open an issue to request this feature.

- **Length**

  This only has one value: `l` (not the number one, but the alphabetical letter 'l'). If this value is present the behaviour of certain specifiers is changed.

  Specifier  | Description
  ------------- | -------------
  **`d`** or **`i`** | Use `long` instead of `int`.
  **`u`** or **`x`** | Use `unsigned long` instead of `unsigned int`.
  **`n`** | Repeat a string, instead of a character.
  
- **Specifiers**
  
    **Name**  | **Description**
  ------------- | -------------
  **`s`** | String ( null terminated ).
  **`p`** | PROGMEM string. No formatting takes place, the string is printed directly.
  **`r`** | EEPROM string. No formatting takes place, the string is printed directly.
  **`d`** | Signed decimal integer ( 32bits max ).
  **`i`** | Same as **`d`**.
  **`u`** | Unsigned decimal integer ( 32bits max ).
  **`f`** | Decimal floating point number.
  **`x`** | Unsigned decimal integer ( 32bits max ).
  **`c`** | Character.
  **`n`** | Repeat function ( default character, see length ).
  **`%`** | Escape character for printing **`%`**.

```Arduino
#include <PrintEx.h>

StreamEx mySerial = Serial;

void setup() {
  Serial.begin(9600);
  mySerial.printf( "%20n\nFirst printf use!\n%20n", '=', '=' );
}

void loop() {}
```

---

## Helpers & Tools
All of these objects have the PrintEx functionality built in, there is no need to use `PrintEx` or `StreamEx` with these.

#### *The helpers and tools documentation is still under construction. This is just an overview of what is available.*

Object  | Description
------------- | -------------
**`BufferedPrinter`**  | Useful for buffering output to send all at once, or to prevent sending 'packets' or transfers that are too long for the interface.
**`DualPrinter`**  | Allows calling multiple `Print` interfaces through a single object.
**`Base64Encoder`**  | Any input this object receives is converted using Base64 encoding and written to its assigned `Print` interface.
**`URIEncoder`**  | Anything printed to this object will be URI encoded based on strictness. It supports URL encoding, HTML forms, and encoding the entire stream.
**`CRCStream`**  | This object calculates a running CRC for the input and output data streams of a `Stream` object associated with it.
**`RxTxCoutner`**  | This object keeps track of how much data passes through its interfaces.
**`NullStream`**  | A data stream with origins unknown.
---

## Core Interfaces

The objects listed in this section provide the core functionality for all interfaces inherting `PrintExtension`.

Type  | Description
------------- | -------------
**`PrintEx`**  | This object provides an easy method of enhancing other `Print` based objects with the capabilities provided by `PrintExtension`.
**`StreamEx`**  | This object provides an easy method of enhancing other `Stream` based objects with the capabilities provided by `PrintExtension` while maintaining the bidirectional interface.
**`GString`**  | This object provides printing and formatting capabilities for blocks of memory (SRAM). The object can be passed to other Print functions.
**`EString`**  | This is the EEPROM equivalent of `GString`. This essentially allows formatted printing of strings to the EEPROM. It also allows other `Print` based classes to print EEPROM data easily.
**`PString`**  | This is a PROGMEM read-only version of `GString`. It allows printing of flash based strings.
**`PrintExtension`**  | This is a core interface for `PrintEx`. It provides the formatting features such as `concat()` and `printf()`. It also includes `OStream` which provides streaming capabilites (output only).
**`StreamExtension`**  | This core library encapsulates the functionality found in the `PrintExtension` interface, however it also provides an `IStream` interface allowing streaming into arbitrary elements.
**`NonStreamingIO`**  | This interface provides an extension to the `Print` class. It allows IO capabilities for derived objects that may not be streams. As in, the data printed to the object is still available for use.
---

## Custom Configuration.
For normal use this section is not necessary. However the library can be tweaked if needed.

The available customizations can be used by defining one, or a combination of the options listed below. They can be defined either in the *PrintExtension.h* file, or passed as a compiler option using `-D`. Unfortunately defining these in your sketch will not have any effect.
### Global library flags.
These settings affect all library functions that use the features described.

Define  | Action if defined
------------- | -------------
**`PRINTEX_NO_SPRINTF`**  | Do not override the global `sprintf` with a version supporting all the features present in PrintEx.
**`PRINTEX_LARGE_COUNTER`**  | Use a 16-bit value for print counters, instead of 8 bits (how many characters printed). If you do not care about the return count of print functions, leave the setting as is. This will allow more efficient code, however writes larger than 255 characters will have incorrect counts returned..

### `printf` specific flags.
These settings only affect the `printf` implementation. To avoid inclusion outside of the `printf`/`sprintf` implementation, simply do not use the `PrintEx` function providing the feature (The compiler will remove unused code).

Define  | Action if defined
------------- | -------------
**`PRINTEX_NO_WIDTH_PARAM`**  | The width parameter must be specified inline and cannot be set to `*` specifying an additional input for the width.
**`PRINTEX_NO_PRECISION_PARAM`** | Do not use precision handling (currently only affects floating point resolution).
**`PRINTEX_NO_PROGMEM`**  | Do not include PROGMEM functionality (`%p`).
**`PRINTEX_NO_EEPROM`**  | Do not include EEPROM functionality (`%r`).
**`PRINTEX_NO_FLOATING_POINT`**  | Do not include support for floating point data (`%f`).
**`PRINTEX_NO_REPEAT`**  | Do not include character repeat functionality (`%n`).
**`PRINTEX_NO_ERROR_CONDITION`**  | Do not include error handling (`Error` is printed on bad inputs/failed operation).


