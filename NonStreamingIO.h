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

#include "Globals.h"
#include "Arduino.h"

#ifndef HEADER_NONSTREAMINGIO
    #define HEADER_NONSTREAMINGIO

    /***************************************************************************
        NonStreamingIO Class.
            This interface provides an extension to the Print class.
            It allows IO capabilities for derived objects that may not
            be streams. As in, the data printed to the object is still
            available for use.

            This class does not directly do any reading, it provides a start
            and end pointer of data written, which can then be used by Print
            to re-print the data.
    ***************************************************************************/

    class NonStreamingIO{
        public:

            size_t count( void ) const { return len; }

            NonStreamingIO &operator =( uint8_t *t )
                {
                    start = t;
                    len = 0;
                    return *this;
                }

            template< typename T >
                inline void assign( const T *data, const uint16_t length )
                    {
                        start = ( uint8_t* ) data;
                        len = length;
                    }

            uint8_t *start;
            uint16_t len;

        protected:
            CONSTEXPR NonStreamingIO( uint8_t *data ) : start( data ) , len( 0 )                                 {}
            CONSTEXPR NonStreamingIO( uint8_t *data, const unsigned int length ) : start( data ) , len( length ) {}
        private:
    };

#endif
