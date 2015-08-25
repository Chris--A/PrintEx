/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
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
