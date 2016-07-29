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

#ifndef HEADER_PRINTCONCAT
    #define HEADER_PRINTCONCAT

    template< typename derived >
        struct PrintConcat{

            template< typename T >
                _INLINE_ derived &operator +=( const T &t )
                    { return CRTPO.concat( t ); }

            template< typename T >
                _INLINE_ derived &concat( const T &t )
                    { return CRTPO.print( t ), CRTPO; }

            template< typename T >
                _INLINE_ derived &concat( const T &t, const int i )
                    { return CRTPO.print( t, i ) CRTPO; }

            _INLINE_ derived &concatln()
                { return CRTPO.println(), CRTPO; }

            template< typename T >
                _INLINE_ derived &concatln( const T &t )
                    { return CRTPO.println( t ), CRTPO; }

            template< typename T >
                _INLINE_ derived &concatln( const T &t, const int i )
                    { return CRTPO.println( t, i ), CRTPO; }
    };

#endif
