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

/********************************************************************************
    PrintEx feature inclusion constants.

    Define these constants below to disable certain features.

    #define PRINTEX_NO_WIDTH_PARAM
    #define PRINTEX_NO_PRECISION_PARAM
    #define PRINTEX_NO_PROGMEM
    #define PRINTEX_NO_EEPROM
    #define PRINTEX_NO_FLOATING_POINT
    #define PRINTEX_NO_REPEAT
    #define PRINTEX_NO_ERROR_CONDITION
    #define PRINTEX_NO_SPRINTF
    #define PRINTEX_LARGE_COUNTER
********************************************************************************/

#include "Arduino.h"
#include "PrintConcat.h"
#include "PrintRepeat.h"
#include "PrintVariadic.h"
#include "OStream.h"

#ifndef HEADER_PRINTEXTENSION
    #define HEADER_PRINTEXTENSION

    typedef size_t pft;

    #ifdef PRINTEX_LARGE_COUNTER
        typedef uint16_t pfct;
    #else
        typedef uint8_t pfct;
    #endif

    class PrintExtension
        :   public Print,
            public PrintConcat<PrintExtension>,
            public PrintRepeat<PrintExtension>,
            public ios::OStreamBase<PrintExtension>,
            public PrintVariadic<PrintExtension>{
        public:

            pft printf( const char *format, ... );

        protected:

            friend class StreamExtension;
            pft _printf( const char *format, const va_list &v_List );

            // Global sprintf replacement. To keep old version define PRINTEX_NO_SPRINTF (does not affect x.printf();)
            #ifndef PRINTEX_NO_SPRINTF
                friend int sprintf( char * str, const char * format, ... );
            #endif

        private:
            void cwrite( uint8_t data, pfct &counter );
    };


    struct PrintEx : PrintExtension{
        PrintEx( Print& in ) : out(in)    { return; }
        size_t write( uint8_t data )      { return out.write( data ); }
        Print &out;
    };

#endif