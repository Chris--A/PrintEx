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
	
	template< typename derived > struct OStreamManipulator;
	
	struct OStream{

		OStream( Print &host ) : out(host) {}
		
		/** Handle manipulators. **/
		template< typename T >
			OStream operator<< ( const OStreamManipulator<T> &manip ){
				manip.run(*this);
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
			- c-strings (pointers and arrays).
		***/
		template< 
			typename T,
			typename = typename enable_if< 
				!is_fundamental<T>::value &&
				!is_base_of<OStreamManipulator<T>,T>::value
			>::type>
		OStream operator<< ( const T &data ){
			out.print( data );
			return *this;
		}

		Print &out;
		OStreamParams params;
	};
	
	template< typename derived >
		struct OStreamManipulator{
			void run(OStream &os) const { static_cast< const derived* >(this)->run(os); }
	};		
	
	struct _bin : OStreamManipulator< _bin >{ void run(OStream &os) const { os.params.base = BIN; } };
	struct _oct : OStreamManipulator< _oct >{ void run(OStream &os) const { os.params.base = OCT; } };
	struct _dec : OStreamManipulator< _dec >{ void run(OStream &os) const { os.params.base = DEC; } };
	struct _hex : OStreamManipulator< _hex >{ void run(OStream &os) const { os.params.base = HEX; } };
	struct _endl : OStreamManipulator< _endl >{ void run(OStream &os) const { os.out.println(); } };
	struct _ends : OStreamManipulator< _ends >{ void run(OStream &os) const { os.out.print('\0'); } };
	
	static const _bin bin;
	static const _oct oct;
	static const _dec dec;
	static const _hex hex;	
	static const _endl endl;
	static const _ends ends;
	
	struct precision : OStreamManipulator< precision >{
		CONSTEXPR precision( unsigned char in ) : val(in) {}
		void run(OStream &os) const { os.params.precision = val; }
		const unsigned char val;
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
