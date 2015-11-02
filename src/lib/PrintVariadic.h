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

				template< typename S >
                derived &printx_continue(  S s ){ return CRTPO; }

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
