/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
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
                    { return CRTPO.print( t ), CRTPP; }

            template< typename T >
                _INLINE_ derived &concat( const T &t, const int i )
                    { return CRTPO.print( t, i ) CRTPP; }

            template< typename T >
                _INLINE_ derived &concatln( const T &t )
                    { return CRTPO.println( t ), CRTPP; }

            template< typename T >
                _INLINE_ derived &concatln( const T &t, const int i )
                    { return CRTPO.println( t, i ), CRTPP; }
    };

#endif
