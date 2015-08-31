/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

//Uses CRTP macros.
#include "Globals.h"

#ifndef HEADER_PRINTREPEAT
    #define HEADER_PRINTREPEAT
	
	template< typename derived >
		class PrintRepeat{

			public:
				derived &repeat( const char *str, size_t size, unsigned char repeatCount ){
					while( repeatCount-- ) CRTPO.write( str, size );
					return CRTPO;
				}

				derived &repeatln( const char *str, size_t size, unsigned char repeatCount ){
					repeat( str, size, repeatCount );
					CRTPO.println();
					return CRTPO;
				}

				derived &repeat( const char *str, unsigned char repeatCount )
					{ return repeat( str, strlen(str), repeatCount ); }

				derived &repeatln( const char *str, unsigned char repeatCount )
					{ return repeatln( str, strlen(str), repeatCount ); }

				derived &repeat( const char &character, unsigned char count ){
					_repeat(character, count);
					return CRTPO;
				}

				derived &repeatln( const char &character, unsigned char count ){
					_repeat(character, count);
					CRTPO.println();
					return CRTPO;
				}
				
			protected:
			
				void _repeat( const char &character, unsigned char count ) { while( count-- ) CRTPO.write( character ); }
	};
	
#endif
