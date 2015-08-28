/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#include "Globals.h"

#ifndef HEADER_TYPETRAITS
    #define HEADER_TYPETRAITS
	
	/***********************************************************************************************
		select template.
			If V is true, type is T, otherwise U.
	***********************************************************************************************/
				
	template< bool V, typename T, typename U > struct select { typedef U type; };
	template<typename T, typename U > struct select<true,T,U>{ typedef T type; };
		
	/***********************************************************************************************
		enable_if template.
			If V is true, type is T, otherwise type is undefined.
			
			Warning: Arduino IDE versions below 1.5.7 do not have GCC 4.8.1 which includes
			support for SFINAE. This template will not work in these IDE's.
	***********************************************************************************************/
	
	#ifdef ISCPP11
		template< bool V, typename T = void > struct enable_if{};
	#else
		template< bool V, typename T > struct enable_if{};
	#endif
	template< typename T > struct enable_if< true, T >{ typedef T type; };	

	/***********************************************************************************************
		is_same structure.
			This is the same as CompareType(), but allows using the value in constant expressions.
	***********************************************************************************************/
		
	template < typename T, typename U > struct is_same{ enum { value = false }; };
	template < typename T > struct is_same< T, T >    { enum { value = true }; };
		
	/***********************************************************************************************
		is_integer structure.
			'value' will be set to true if t is a integer type ( 8 to 64 bit, signed / unsigned ).
			This is the compile time constant version of IsIntType(). 
	***********************************************************************************************/
		
	template< typename T >
		struct is_integer{
			enum{
				V8    = is_same< T, uint8_t >::value  || is_same< T, int8_t >::value,
				V16   = is_same< T, uint16_t >::value || is_same< T, int16_t >::value,
				V32   = is_same< T, uint32_t >::value || is_same< T, int32_t >::value,
				V64   = is_same< T, uint64_t >::value || is_same< T, int64_t >::value,
				value = V8 || V16 || V32 || V64
			};
	};
	
	template< typename T > struct is_float{ enum{ value = is_same< T, float >::value || is_same< T, double >::value || is_same< T, long double >::value }; };
	template< typename T > struct is_number{ enum{ value = is_float< T >::value || is_integer< T >::value }; };
	template< typename T > struct is_bool{ enum{ value = is_same< T, bool >::value }; };
	template< typename T > struct is_fundamental{ enum{ value = is_number<T>::value || is_bool<T>::value }; };

	/*** is_pointer can allow generic template functions to discriminate based on whether a template type is a pointer. ***/
	template< typename T > struct is_pointer{ enum{ value = false }; };      //Not a pointer.
	template< typename T > struct is_pointer<T*>{ enum{ value = true }; };   //A standard pointer.
	template< typename T > struct is_pointer<T*&>{ enum{ value = true }; };  //A reference to a pointer (is still considered a pointer in usage due to reference semantics).

	
	/* *************************************************************************************
		is_array structure.
			Useful to disambiguate T *t, and T(&t)[N] situations.
			Switch use over to ArrayInfo as it exposes more information.
	************************************************************************************* */
				
	template< typename T > struct is_array{ enum { value = false }; };
	template< typename T, size_t N > struct is_array< T[N] > { enum { value = true }; };			
	template< typename T, size_t A, size_t N > struct is_array< T[A][N] > { enum { value = true }; };
	template< typename T, size_t B, size_t A, size_t N > struct is_array< T[B][A][N] > { enum { value = true }; };
	
	
	/* *************************************************************************************
		is_base_of structure.
			Determines whether D is derived from B.
	************************************************************************************* */
	
	template<class B, class D, typename C = void> struct is_base_of;

	template<class B, class D>
		struct is_base_of<B,D,typename enable_if<
			!is_array<D>::value && 
			!is_fundamental<D>::value && 
			!is_pointer<D>::value>::type
		>{
		  template< typename T > struct dummy{};
		  struct Child : D, dummy<int> {};
		  static B* Check (B*);
		  template< typename T > static char Check (dummy<T>*);
		  static const bool value = (sizeof(Check((Child*)0)) == sizeof(B*));
	};

	template<class B, class D>
		struct is_base_of<B,D,typename enable_if<
			is_array<D>::value || 
			is_fundamental<D>::value || 
			is_pointer<D>::value>::type
		>{ 
		static const bool value = 0; 
	};		
	
#endif
