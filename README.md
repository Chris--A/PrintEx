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
- `Any other library that inherits `Print` or `Stream`.


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
