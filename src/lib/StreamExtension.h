/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
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
