/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#ifndef HEADER_GLOBALS
    #define HEADER_GLOBALS

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
        #define PRINTF_NO_PROGMEM
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

#endif
