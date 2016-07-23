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

#include "OStream.h"
#include "IStream.h"
#include "PrintConcat.h"
#include "PrintRepeat.h"

#ifndef HEADER_STREAMEXTENSION
    #define HEADER_STREAMEXTENSION

    struct StreamExtension :
        Stream,
        PrintConcat<StreamExtension>,
        PrintRepeat<StreamExtension>,
        ios::OStreamBase<StreamExtension>,
        ios::IStreamBase<StreamExtension>,
        PrintVariadic<PrintExtension>
    {
        pft printf( const char *format, ... );
    };

    struct StreamEx : StreamExtension{

        StreamEx( Stream &in ) : stream(in) {}
        int available( void )               { return stream.available(); }
        void flush( void )                  { stream.flush(); }
        int peek( void )                    { return stream.peek(); }
        int read( void )                    { return stream.read(); }
        size_t write( uint8_t data )        { return stream.write(data); }
        Stream &stream;
    };

#endif
