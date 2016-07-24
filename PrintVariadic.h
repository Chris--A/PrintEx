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

#include "TypeTraits.h"
#include "OStream.h"

#ifndef HEADER_PRINTVARIADIC
    #define HEADER_PRINTVARIADIC

    #ifdef ISCPP11

        template< typename derived >
            struct PrintVariadic{

                template< typename S >
                derived &printx_continue(  S s ){ return UNUSED_PARAM(s), CRTPO; }

                template< typename T, typename... U >
                    derived &printx( const T& t, const U&... u ){
                        return printx_continue( CRTPO << t, u... );
                    }

                template< typename S, typename T, typename... U >
                    derived &printx_continue( S s, const T& t, const U&... u ){
                        return printx_continue( s << t, u... );
                    }
        };
    #else
        template< typename derived > struct PrintVariadic{};
    #endif
#endif
