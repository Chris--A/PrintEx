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

#ifndef HEADER_OSTREAM
    #define HEADER_OSTREAM

    namespace ios{

        #ifndef ISCPP11
            template< typename derived > struct OStreamBase{};
        #else

        struct OStreamParams{
            CONSTEXPR OStreamParams()
                :    base( DEC ),
                    precision( 2 ) {}

            unsigned char base;      //Base for integer printing.
            unsigned char precision; //Floating point precision.
        };

        /*************************************************************************************************
            OStream manipulators.
        *************************************************************************************************/

        template< typename derived >
            struct OStreamManipulator{
                template<typename T> void run(T &os) const { static_cast< const derived* >(this)->run(os); }
        };

        struct _bin : OStreamManipulator< _bin >{ template<typename T> void run(T &os) const { os.params.base = BIN; } };
        struct _oct : OStreamManipulator< _oct >{ template<typename T> void run(T &os) const { os.params.base = OCT; } };
        struct _dec : OStreamManipulator< _dec >{ template<typename T> void run(T &os) const { os.params.base = DEC; } };
        struct _hex : OStreamManipulator< _hex >{ template<typename T> void run(T &os) const { os.params.base = HEX; } };
        struct _endl : OStreamManipulator< _endl >{ template<typename T> void run(T &os) const { os.out.println(); } };
        struct _ends : OStreamManipulator< _ends >{ template<typename T> void run(T &os) const { os.out.print('\0'); } };

        static const _bin bin;
        static const _oct oct;
        static const _dec dec;
        static const _hex hex;
        static const _endl endl;
        static const _ends ends;

        struct precision : OStreamManipulator< precision >{
            CONSTEXPR precision( unsigned char in ) : val(in) {}
            template<typename T> void run(T &os) const { os.params.precision = val; }
            const unsigned char val;
        };

        struct repeat : OStreamManipulator< repeat >{
            CONSTEXPR repeat( const char in, unsigned char count ) : val(in), times(count) {}
            template<typename T> void run(T &os) const { os.out.repeat( val, times ); }
            const char val;
            const int times;
        };


        /*************************************************************************************************
            OStream implementation.
        *************************************************************************************************/

        template< typename derived >
            struct OStream{

                OStream( derived &host ) : out(host) {}
				OStream( derived &host, const OStreamParams &params ) : out(host), params{params} {}
		
                /** Internal hook for global streaming. **/
                //inline OStream operator<< ( const OStreamParams &params ){
				//	this.params = params;
                //    return *this;
                //}
				

                /** Handle manipulators. **/
                template< typename T >
                    OStream operator<< ( const OStreamManipulator<T> &manip ){
                        manip.run(*this);
                        return *this;
                }

                /** A specialization for integer data. **/
                template< typename T >
                    typename enable_if<
                        is_integer<T>::value &&
                        !is_same<T,char>::value
                    , OStream>::type operator<< ( const T &data ){
                        out.print( data, params.base );
                        return *this;
                }

                /** A specialization for floating point data. **/
                template< typename T >
                    typename enable_if<is_float<T>::value, OStream>::type operator<< ( const T &data ){
                        out.print( data, params.precision );
                        return *this;
                }

                /***
                    This substitution accepts:
                    - Printable derived objects.
                    - PROGMEM strings implemented using F() macros.
                    - c-strings (pointers and arrays), String objects.
                ***/
                template<
                    typename T,
                    typename = typename enable_if<
                        (!is_fundamental<T>::value ||
                        is_same<T,char>::value) &&
                        !is_base_of<OStreamManipulator<T>,T>::value
                    >::type>
                OStream operator<< ( const T &data ){
                    out.print( data );
                    return *this;
                }


                //Array streaming.
                /*template< typename T, unsigned N >
                    typename enable_if<!is_same<typename ArrayInfo<T>::UnderlyingType,char>::value,OStream>::type operator<< ( T (&t)[N] ){
                        for( auto el : t ) *this << el;
                        return *this;
                }*/

                derived &out;
                OStreamParams params;
        };


        //Entry point for an OStream chain.
        template< typename derived >
            struct OStreamBase{
                template< typename T >
                    OStream<derived> operator<< ( const T &data ){
                        OStream<derived> os( CRTPO );
                        return os << data;
                }
        };
        #endif
    }; //namespace ios

#endif
