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
