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

// Requires:
// Globals.h
// TypeTraits.h
#include "MemoryPrinter.h"

#ifndef HEADER_ISTREAM
    #define HEADER_ISTREAM

    namespace ios{

        #ifndef ISCPP11
            template< typename derived > struct IStreamBase{};
        #else

        template<typename derived>
            struct IStream{

                IStream( derived &host ) : input(host) {}

                template< typename T >
                    typename enable_if<is_integer<T>::value, IStream>::type operator>> ( T &t ){
                        t = input.parseInt();
                        return *this;
                }

                template< typename T >
                    typename enable_if<is_float<T>::value, IStream>::type operator>> ( T &t ){
                        t = input.parseFloat();
                        return *this;
                }

                IStream operator>> ( String &string ){
                        string = input.readString();
                        return *this;
                }

                //Direct buffer reading, will stop on timeout.
                //NonStreamingIO::len is modified to reflect the number of characters read.
                template<
                    typename T,
                    typename = typename enable_if< !is_same<T,GString>::value >::type
                >
                    typename enable_if<is_base_of<NonStreamingIO,T>::value, IStream>::type operator>> ( T &t ){
                        int len = t.len;
                        t.len = 0;
                        char readBuff;
                        for( int index = 0 ; index < len ; ++index ){
                            if( !input.readBytes(&readBuff, 1) ) break;
                            t.write(readBuff);
                        }
                        return *this;
                }

                //GString (SRAM) specific buffer handling.
                _INLINE_ IStream operator>> ( GString &g ){
                        input.readBytes(g.start, g.len);
                        return *this;
                }
/*
                //Array streaming.
                template< typename T, unsigned N >
                    IStream operator>> ( T (&t)[N] ){
                        for( auto el : t ) *this >> el;
                        return *this;
                }*/

                derived &input;
        };

        //Entry point for an IStream chain.
        template< typename derived >
            struct IStreamBase{
                template< typename T >
                    IStream<derived> operator>> ( T &data ){
                        IStream<derived> is( *static_cast<derived*>( this ) );
                        return is >> data;
                }
        };
        #endif
    };

#endif
