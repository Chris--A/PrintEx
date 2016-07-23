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

#include "NonStreamingIO.h"
#include "PrintExtension.h"

#ifndef HEADER_MEMORYPRINTER
    #define HEADER_MEMORYPRINTER

    /***************************************************************************
        EEPROMPrinter Class.
            An IO class for Print functionality targeting EEPROM memory.
    ***************************************************************************/
    #ifdef __AVR__
        typedef struct EEPROMPrinter : NonStreamingIO, PrintExtension, Printable{
            template< typename T >
                CONSTEXPR EEPROMPrinter( const T dataPtr )
                    : NonStreamingIO( ( uint8_t* ) dataPtr ) {}

            template< typename T >
                CONSTEXPR EEPROMPrinter( const T dataPtr, const unsigned int length )
                    : NonStreamingIO( ( uint8_t* ) dataPtr, length ) {}

            size_t write( uint8_t data );
            size_t printTo(Print& p) const;
        } EString;
    #endif


    /***************************************************************************
        SRAMPrinter Class.
            An IO class for Print functionality targeting SRAM memory.
    ***************************************************************************/

    typedef struct SRAMPrinter : NonStreamingIO, PrintExtension{
        template< typename T >
            CONSTEXPR SRAMPrinter( const T dataPtr )
                : NonStreamingIO( ( uint8_t* ) dataPtr ) {}

        template< typename T >
            CONSTEXPR SRAMPrinter( const T dataPtr, const unsigned int length )
                : NonStreamingIO( ( uint8_t* ) dataPtr, length ) {}

        operator char*( void ) { return start[ len++ ] = '\0', ( char* ) start; }

        void end( void ) { start[ len++ ] = '\0'; }
        size_t write( uint8_t data );
    } GString;

    /***************************************************************************
        PROGMEMPrinter Class.
            This class encapsulates PROGMEM functionality.
    ***************************************************************************/
    #ifdef __AVR__
        typedef struct PROGMEMPrinter : Printable{
            template< typename T >
                CONSTEXPR PROGMEMPrinter( const T dataPtr ) : start( ( uint8_t* ) dataPtr ) {}

            PROGMEMPrinter &operator =( uint8_t *t ) { return start = t, *this; }
            size_t printTo(Print& p) const;

            uint8_t *start;
        } PString;
    #endif
#endif
