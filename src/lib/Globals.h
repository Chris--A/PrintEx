/********************************************************************************
        Copyright 2016 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released using: GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007

        You should have received a copy of the licence with the software
        package. You can also view a copy of the full licence here:
        https://github.com/Chris--A/PrintEx/blob/master/LICENSE

        The only exception to the licence applies when a piece of software
        used within PrintEx, and uses a less restrictive licence or is
        public domain. However, these items will be marked accordingly
        with a link or reference of its origins.

        The exception mentioned in the above paragraph only applies to the
        particular lines of code that may be licensed differently, and does
        not remove the GNU GPLv3 restrictions from the remainder of the
        source which contains these items, or other source files used in
        conjunction with them.

********************************************************************************/

#ifndef HEADER_GLOBALS
    #define HEADER_GLOBALS

	/***
		Platform specific configurations.
		Do not modify the contents below.
	***/

    /*** Arduino Zero specific ***/
    #ifdef ARDUINO_SAMD_ZERO //ARDUINO_ARCH_SAMD
        #include <cstdarg>
    #endif

    /*** ESP8266 specific ***/
    #ifdef ARDUINO_ARCH_ESP8266
        #ifndef PRINTEX_NO_SPRINTF
            #define PRINTEX_NO_SPRINTF
        #endif
    #endif

    /*** AVR specific ***/
    #ifdef __AVR__
        #include <avr/eeprom.h>
    #endif

    /*** Non AVR boards ***/
    #ifndef __AVR__
        /*** An exception for ESP8266 boards. ***/
        #ifndef ARDUINO_ARCH_ESP8266
            #define PRINTF_NO_PROGMEM
        #endif
        #define PRINTF_NO_EEPROM
    #endif

    //Allows performance optimisations on C++98 compatible code, when using C++11.
    #if __cplusplus < 201103L || !defined(__GXX_EXPERIMENTAL_CXX0X__)
        #define CONSTEXPR
    #else
        #define ISCPP11
        #define CONSTEXPR constexpr
    #endif

    //More than just a hint.
    #ifndef _INLINE_
        #define _INLINE_  __attribute__( ( always_inline ) ) inline
    #endif

    //Helpers for CRTP interfaces.
    #define CRTPO (*static_cast<derived*>(this))
    #define CRTPP (static_cast<derived*>(this))
    #define CRTPCP (static_cast<derived*>(this))

    #define UNUSED_PARAM(x) (void)x

#endif
