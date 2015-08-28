/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#include "TypeTraits.h"


#ifndef HEADER_OSTREAM
    #define HEADER_OSTREAM
	
	#ifndef ISCPP11
		template< typename derived > struct OStreamBase{};
	#else

	struct OStreamParams{
		CONSTEXPR OStreamParams() 
			:	base( DEC ),
				precision( 2 ) {}
				
		unsigned char base;      //Base for integer printing.
		unsigned char precision; //Floating point precision.
	};

	template< typename derived >
		struct OStreamManipulator{
			void updateParams(OStreamParams &params) const { static_cast< const derived* >( this )->updateParams( params ); }
	};

	struct _bin : OStreamManipulator< _bin >{ void updateParams(OStreamParams &params) const { params.base = BIN; } };
	struct _oct : OStreamManipulator< _oct >{ void updateParams(OStreamParams &params) const { params.base = OCT; } };
	struct _dec : OStreamManipulator< _dec >{ void updateParams(OStreamParams &params) const { params.base = DEC; } };
	struct _hex : OStreamManipulator< _hex >{ void updateParams(OStreamParams &params) const { params.base = HEX; } };

	static const _bin bin;
	static const _oct oct;
	static const _dec dec;
	static const _hex hex;	
	
	struct precision : OStreamManipulator< precision >{
		CONSTEXPR precision( unsigned char in ) : val(in) {}
		void updateParams(OStreamParams &params) const { params.precision = val; }
		const unsigned char val;
	};
	
	struct _endl{};
	static const _endl endl;
	
	template< typename T > struct is_manipulator{
		enum{
			value = is_same<_bin, T>::value ||
					is_same<_oct, T>::value ||
					is_same<_dec, T>::value ||
					is_same<_hex, T>::value ||
					is_same<precision, T>::value,
		};
	};

	struct OStream{

		OStream( Print &host ) : out(host) {}
		
		/** Handle manipulators. **/
		template< typename T > 
			OStream operator<< ( const OStreamManipulator<T> &manip ){
				manip.updateParams( params );
				return *this;
			}
			
		/** A specialization for endl. Should be a manipulator. **/
		OStream operator<< ( const _endl &e ){
			out.println();
			return *this;
		}
						
		/** A specialization for string literals. **/
		template< typename T, unsigned N > 
			OStream operator<< ( const T (&data)[N] ){
				out.print( data );
				return *this;
		}

		/** A specialization for integer data. **/
		template< typename T >
		typename enable_if<is_integer<T>::value, OStream>::type operator<< ( const T &data ){
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
			- c-strings (not string literals, pointers to null-terminated char arrays).
		***/
		template< 
			typename T,
			typename = typename enable_if< 
				!is_array<T>::value && 
				!is_fundamental<T>::value && 
				!is_manipulator<T>::value >::type >
		OStream operator<< ( const T &data ){
			out.print( data );
			return *this;
		}

		Print &out;
		OStreamParams params;
	};
	
	//Entry point for an OStream chain.
	template< typename derived >
		struct OStreamBase{
			template< typename T > 
				OStream operator<< ( const T &data ){
					OStream os( *static_cast<derived*>( this ) );
					return os << data;
				}
	};	
	#endif
#endif
