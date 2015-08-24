/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include <inttypes.h>
#include "../../lib/PrintExtension.h"

#ifndef HEADER_URIENCODER
    #define HEADER_URIENCODER
	
	enum URI_MODE{ URI_STANDARD, URI_WWWFORM, URI_ALL };
	
	class URIEncoder : public PrintExtension{
		public:
		
			URIEncoder( Print &host, URI_MODE uriMode = URI_STANDARD ) : out( host ), mode( uriMode ) {}
			
			size_t write( uint8_t data );	//Derived from Print.
			
			URI_MODE URIMode()               { return ( URI_MODE ) mode; }
			void URIMode( URI_MODE uriMode ) { mode = uriMode; }
			
		protected:
			Print &out;
			char mode;
	};
	
#endif
	
//EOF