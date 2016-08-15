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

#include "OStream.h"
#include "IStream.h"
#include "PrintConcat.h"
#include "PrintRepeat.h"
#include "StreamIterate.h"

#ifndef HEADER_STREAMEXTENSION
    #define HEADER_STREAMEXTENSION

    struct StreamExtension :
        Stream,
        PrintConcat<StreamExtension>,
        PrintRepeat<StreamExtension>,
        ios::OStreamBase<StreamExtension>,
        ios::IStreamBase<StreamExtension>,
        PrintVariadic<PrintExtension>,
		StreamIteration<PrintExtension>
    {
        pft printf( const char *format, ... );
    };

    //Forward declaration as StreamEx uses StreamExWrap
    template<typename T> struct StreamExWrap;

    struct StreamEx : StreamExtension{

        StreamEx( Stream &in ) : stream(in) {}
        int available( void )               { return stream.available(); }
        void flush( void )                  { stream.flush(); }
        int peek( void )                    { return stream.peek(); }
        int read( void )                    { return stream.read(); }
        size_t write( uint8_t data )        { return stream.write(data); }

        template<typename T>
        static StreamExWrap<T> &wrap( T &t ){
            return *transform<StreamExWrap<T>*, T*>(&t);
        }

        Stream &stream;
    };

    template<typename T>
    struct StreamExWrap :
            PrintConcat< StreamExWrap<T> >,
            PrintRepeat< StreamExWrap<T> >,
            ios::OStreamBase< StreamExWrap<T> >,
            ios::IStreamBase< StreamExWrap<T> >,
            PrintVariadic< StreamExWrap<T> >,
			StreamIteration< StreamExWrap<T> >,
            T{

        /***
            Constructors are provided to allow passing through parameters to wrapped type.
        ***/
        StreamExWrap() : T() {}

        template<typename A> StreamExWrap( A a ) : T(a) {}
        template<typename A, typename B> StreamExWrap( A a, B b ) : T(a, b) {}
        template<typename A, typename B, typename C> StreamExWrap( A a, B b, C c ) : T(a, b, c) {}
        template<typename A, typename B, typename C, typename D> StreamExWrap( A a, B b, C c, D d ) : T(a, b, c, d) {}
        template<typename A, typename B, typename C, typename D, typename E> StreamExWrap( A a, B b, C c, D d, E e ) : T(a, b, c, d, e) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F> StreamExWrap( A a, B b, C c, D d, E e, F f ) : T(a, b, c, d, e, f) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G> StreamExWrap( A a, B b, C c, D d, E e, F f, G g ) : T(a, b, c, d, e, f, g) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> StreamExWrap( A a, B b, C c, D d, E e, F f, G g, H h ) : T(a, b, c, d, e, f, g, h) {}

        template<typename A> StreamExWrap( A &a ) : T(a) {}
        template<typename A, typename B> StreamExWrap( A &a, B &b ) : T(a, b) {}
        template<typename A, typename B, typename C> StreamExWrap( A &a, B &b, C &c ) : T(a, b, c) {}
        template<typename A, typename B, typename C, typename D> StreamExWrap( A &a, B &b, C &c, D &d ) : T(a, b, c, d) {}
        template<typename A, typename B, typename C, typename D, typename E> StreamExWrap( A &a, B &b, C &c, D &d, E &e ) : T(a, b, c, d, e) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F> StreamExWrap( A &a, B &b, C &c, D &d, E &e, F &f ) : T(a, b, c, d, e, f) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G> StreamExWrap( A &a, B &b, C &c, D &d, E &e, F &f, G &g ) : T(a, b, c, d, e, f, g) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> StreamExWrap( A &a, B &b, C &c, D &d, E &e, F &f, G &g, H &h ) : T(a, b, c, d, e, f, g, h) {}

        /***
            printf function.
            Pass through allowing use of PrintExtension::printf.
        ***/

        pft printf( const char *format, ... ){
            va_list vList;
            va_start( vList, format );
            PrintEx p = *this;
            const pft p_Return = p._printf( format, vList );
            va_end( vList );
            return p_Return;
        }

        #ifndef PRINTEX_NO_PROGMEM
            pft printf( const __FlashStringHelper *format, ... ){
                va_list vList;
                va_start( vList, format );
                PrintEx p = *this;
                const pft p_Return = p._printf( format, strlen_P((const char*)format)+1, vList );
                va_end( vList );
                return p_Return;
            }
        #endif

    };
#endif
