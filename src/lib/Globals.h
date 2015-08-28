/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#ifndef HEADER_GLOBALS
    #define HEADER_GLOBALS
	
	#if __cplusplus < 201103L || !defined(__GXX_EXPERIMENTAL_CXX0X__)
		#define CONSTEXPR
	#else
		#define ISCPP11
		#define CONSTEXPR constexpr
	#endif
	
    #ifndef _INLINE_
        #define _INLINE_  __attribute__( ( always_inline ) ) inline
    #endif
	
#endif
