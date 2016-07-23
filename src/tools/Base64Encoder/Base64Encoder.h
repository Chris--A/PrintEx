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

#include <inttypes.h>
#include "../../lib/PrintExtension.h"

#ifndef HEADER_BASE64ENCODER
    #define HEADER_BASE64ENCODER

    class Base64Encoder : public PrintExtension{
        public:

            Base64Encoder( Print &output ) : out( output ), cursor( 0x00 ) {}
            ~Base64Encoder( void ) { flush(); }

            void flush();

            size_t write( uint8_t in );
            //size_t write( const uint8_t *u_Data, size_t s_Len );

        protected:

            void Step( void );
            void Convert( void );

            uint8_t data[ 0x04 ];
            Print &out;
            unsigned char cursor;
    };

#endif
