/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#ifndef HEADER_MEMORYPRINTER
    #define HEADER_MEMORYPRINTER
	
	#if __cplusplus < 201103L || !defined(__GXX_EXPERIMENTAL_CXX0X__)
		#define CONSTEXPR
	#else
		#define CONSTEXPR constexpr
	#endif	

    #include "NonStreamingIO.h"
    #include "PrintExtension.h"

    /***************************************************************************
        EEPROMPrinter Class.
            An IO class for Print functionality targeting EEPROM memory.
    ***************************************************************************/
    #ifdef __AVR__
        #include <avr/eeprom.h>
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
