/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include <inttypes.h>
#include "../../lib/PrintExtension.h"

#ifndef HEADER_BASE64WRITER
    #define HEADER_BASE64WRITER

    class Base64Writer : public PrintExtension{
        public:

            Base64Writer( Print &output ) : out( output ), cursor( 0x00 ) {}
            ~Base64Writer( void ) { flush(); }

            void flush();

            size_t write( uint8_t in );
            //size_t write( const uint8_t *u_Data, size_t s_Len );

        protected:

            void Step( void );
            void Convert( void );

            uint8_t data[ 0x04 ];
            Print &out;
            char cursor;
    };

#endif
