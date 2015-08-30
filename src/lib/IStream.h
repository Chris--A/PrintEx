/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

// Requires: 
// Globals.h
// TypeTraits.h

#ifndef HEADER_ISTREAM
    #define HEADER_ISTREAM
	
	namespace ios{
	
		#ifndef ISCPP11
			template< typename derived > struct IStreamBase{};
		#else
		
		template<typename derived>
			struct IStream{

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
