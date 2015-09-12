/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
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
		:	public Print,
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