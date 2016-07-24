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

#ifndef HEADER_CRCSTREAM
    #define HEADER_CRCSTREAM

    enum CRC_STREAM_ID{ CRC_INPUT, CRC_OUTPUT };

    class CRCStream : public Stream, public PrintExtension{
        public:
            typedef unsigned long CRC;
            CRCStream( Stream &host )
                : stream( host ), in( ~0L ), out( in ) {}
            unsigned long getCRC( CRC_STREAM_ID id )   { return ~( id ? out : in ); }
            void resetCRC( CRC_STREAM_ID id )          { ( id ? out : in ) = ~0L; }
            int available()                            { return stream.available(); }
            void flush()                               { stream.flush(); }
            int peek()                                 { return stream.peek(); }
            int read();
            size_t write( uint8_t data );
        protected:
            Stream &stream;
            CRC in;
            CRC out;
    };

#endif
