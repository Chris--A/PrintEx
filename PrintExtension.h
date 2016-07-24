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

/********************************************************************************
    PrintEx feature inclusion constants.

    Define these constants below to disable certain features.

    #define PRINTEX_NO_WIDTH_PARAM
    #define PRINTEX_NO_PRECISION_PARAM
    #define PRINTEX_NO_PROGMEM
    #define PRINTEX_NO_EEPROM
    #define PRINTEX_NO_FLOATING_POINT
    #define PRINTEX_NO_REPEAT
    #define PRINTEX_NO_ERROR_CONDITION
    #define PRINTEX_NO_SPRINTF
    #define PRINTEX_LARGE_COUNTER
********************************************************************************/

#include "Arduino.h"
#include "PrintConcat.h"
#include "PrintRepeat.h"
#include "PrintVariadic.h"
#include "OStream.h"

#ifndef HEADER_PRINTEXTENSION
    #define HEADER_PRINTEXTENSION

    typedef size_t pft;

    #ifdef PRINTEX_LARGE_COUNTER
        typedef uint16_t pfct;
    #else
        typedef uint8_t pfct;
    #endif

    class PrintExtension
        :   public Print,
            public PrintConcat<PrintExtension>,
            public PrintRepeat<PrintExtension>,
            public ios::OStreamBase<PrintExtension>,
            public PrintVariadic<PrintExtension>{
        public:

            pft printf( const char *format, ... );

        protected:

            friend class StreamExtension;
            template<typename T> friend struct PrintExWrap;

            pft _printf( const char *format, const va_list &v_List );

        private:
            void cwrite( uint8_t data, pfct &counter );
    };

    //Forward declaration as PrintEx uses PrintExWrap
    template<typename T> struct PrintExWrap;

    struct PrintEx : PrintExtension{
        PrintEx( Print& in ) : out(in)    { return; }
        size_t write( uint8_t data )      { return out.write( data ); }
        Print &out;

        template<typename T>
        static PrintExWrap<T> &wrap( T &t ){
            return *transform<PrintExWrap<T>*, T*>(&t);
        }
    };

    template<typename T>
    struct PrintExWrap :
            PrintConcat< PrintExWrap<T> >,
            PrintRepeat< PrintExWrap<T> >,
            ios::OStreamBase< PrintExWrap<T> >,
            PrintVariadic< PrintExWrap<T> >,
            T{

        /***
            Constructors are provided to allow passing through parameters to wrapped type.
        ***/
		PrintExWrap() : T() {}
		
        template<typename A> PrintExWrap( A a ) : T(a) {}
        template<typename A, typename B> PrintExWrap( A a, B b ) : T(a, b) {}
        template<typename A, typename B, typename C> PrintExWrap( A a, B b, C c ) : T(a, b, c) {}
        template<typename A, typename B, typename C, typename D> PrintExWrap( A a, B b, C c, D d ) : T(a, b, c, d) {}
        template<typename A, typename B, typename C, typename D, typename E> PrintExWrap( A a, B b, C c, D d, E e ) : T(a, b, c, d, e) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F> PrintExWrap( A a, B b, C c, D d, E e, F f ) : T(a, b, c, d, e, f) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G> PrintExWrap( A a, B b, C c, D d, E e, F f, G g ) : T(a, b, c, d, e, f, g) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> PrintExWrap( A a, B b, C c, D d, E e, F f, G g, H h ) : T(a, b, c, d, e, f, g, h) {}

        template<typename A> PrintExWrap( A &a ) : T(a) {}
        template<typename A, typename B> PrintExWrap( A &a, B &b ) : T(a, b) {}
        template<typename A, typename B, typename C> PrintExWrap( A &a, B &b, C &c ) : T(a, b, c) {}
        template<typename A, typename B, typename C, typename D> PrintExWrap( A &a, B &b, C &c, D &d ) : T(a, b, c, d) {}
        template<typename A, typename B, typename C, typename D, typename E> PrintExWrap( A &a, B &b, C &c, D &d, E &e ) : T(a, b, c, d, e) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F> PrintExWrap( A &a, B &b, C &c, D &d, E &e, F &f ) : T(a, b, c, d, e, f) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G> PrintExWrap( A &a, B &b, C &c, D &d, E &e, F &f, G &g ) : T(a, b, c, d, e, f, g) {}
        template<typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H> PrintExWrap( A &a, B &b, C &c, D &d, E &e, F &f, G &g, H &h ) : T(a, b, c, d, e, f, g, h) {}

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
    };
	
	// Global sprintf replacement. To keep old version define PRINTEX_NO_SPRINTF (does not affect x.printf();)
	#ifndef PRINTEX_NO_SPRINTF
		#define sprintf(buff, str, ...) GString(buff).printf(str, __VA_ARGS__);
	#endif	

#endif