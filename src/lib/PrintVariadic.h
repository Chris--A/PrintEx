/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include "TypeTraits.h"
#include "OStream.h"

#ifndef HEADER_PRINTVARIADIC
    #define HEADER_PRINTVARIADIC

    #ifdef ISCPP11

        template< typename derived >
            struct PrintVariadic{

                derived &printx( void ){ return CRTPO; }

                template< typename T, typename... U >
                    derived &printx( const T& t, const U&... u ){
                        CRTPO << t;
                        return printx( u... );
                    }
        };
    #else
        template< typename derived > struct PrintVariadic{};
    #endif
#endif
