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
        This code mimics part of the C++11 standard library which provides
        meta-programming decision making. This is a minimal implementation
        and does not consider newer types such as nullptr_t and char32_t,
        which would be uncommon in basic Arduino applications.

        Add an issue to the tracker listed above to request these features.
********************************************************************************/

#include "Globals.h"

#ifndef HEADER_TYPETRAITS
    #define HEADER_TYPETRAITS

    struct NullType{};

    /***
        transform function.
            This will safely convert unrelated types.
    ***/

    template< typename U, typename T > U transform( T t ){
        union{ T _t; U _u; } _t = { t };
        return _t._u;
    }

    /***
        integral_constant implementation sourced from cppreference.com
        http://en.cppreference.com/w/cpp/types/integral_constant
		
		Modified for PrintEx
    ***/

    template<class T, T v>
    struct integral_constant {
		#ifdef ISCPP11	
			static constexpr T value = v;
			typedef T value_type;
			typedef integral_constant type;
			constexpr operator value_type() const noexcept { return value; }
			constexpr value_type operator()() const noexcept { return value; }  //Added to C++ standard library in C++14
		#else
			enum{ value = v };
		#endif
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    /***
        select template.
        If V is true, type is T, otherwise U.
    ***/

    template< bool V, typename T, typename U > struct select { typedef U type; };
    template<typename T, typename U > struct select<true,T,U>{ typedef T type; };


    /***
        enable_if template.
            Similar to select, however if V is false, then type is undefined.

            Warning: Arduino IDE versions below 1.5.7 do not have GCC 4.8.1 which includes
            support for SFINAE. This template will not work in these IDE's.
            However you can use it to generate errors in C++98 when conditions aren't met.

            C++11: T can be omitted and `void` will be used.
    ***/

    #ifdef ISCPP11
        template< bool V, typename T = void > struct enable_if{};
    #else
        template< bool V, typename T > struct enable_if{}; //C++98 must provide all template parameters.
    #endif
    template< typename T > struct enable_if< true, T >{ typedef T type; };

    /***
        is_same structure.
        The template takes two types.
        If T is the same type as U value is true, otherwise false.
    ***/

    template < typename T, typename U > struct is_same : false_type{};
    template < typename T > struct is_same< T, T > : true_type{};

    template< typename T >
        struct is_integer{
            enum{
                V8    = is_same< T, char >::value || is_same< T, unsigned char >::value  || is_same< T, signed char >::value,
                V16   = is_same< T, unsigned int >::value || is_same< T, signed int >::value,
                V32   = is_same< T, unsigned long >::value || is_same< T, signed long >::value,
                V64   = is_same< T, unsigned long long >::value || is_same< T, signed long long >::value,
                value = V8 || V16 || V32 || V64
            };
    };

    template< typename T > struct is_float{ enum{ value = is_same< T, float >::value || is_same< T, double >::value || is_same< T, long double >::value }; };
    template< typename T > struct is_number{ enum{ value = is_float< T >::value || is_integer< T >::value }; };
    template< typename T > struct is_bool{ enum{ value = is_same< T, bool >::value }; };
    template< typename T > struct is_fundamental{ enum{ value = is_number<T>::value || is_bool<T>::value }; };

    template< typename T > struct is_pointer : false_type{};        //Not a pointer.
    template< typename T > struct is_pointer<T*> : true_type{};        //A standard pointer.
    template< typename T > struct is_pointer<T*&> : true_type{};    //A reference to a pointer (is still considered a pointer in usage due to reference semantics).

    template< typename T > struct is_reference : false_type{};
    template< typename T > struct is_reference< T& > : true_type{};

    template< typename T > struct is_array : false_type{};
    template< typename T, size_t N > struct is_array< T[N] > : true_type{};

    template< typename T > struct array_elements{ enum { value = 0 }; };
    template< typename T, size_t N > struct array_elements< T[N] >{ enum { value = N }; };

    template< typename T > struct array_dimensions{ enum { value = 0 }; };
    template< typename T, size_t N > struct array_dimensions< T[N] >{ enum { value = 1 + array_dimensions<T>::value }; };

    template< typename T > struct is_const : false_type{};
    template< typename T > struct is_const<const T> : true_type{};
    template< typename T > struct is_const<const T&> : true_type{};


    /***
        is_function implementation sourced from cppreference.com
        http://en.cppreference.com/w/cpp/types/is_function
    ***/

    #ifdef ISCPP11
        // primary template
        template<class>
        struct is_function : false_type { };

        // specialization for regular functions
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)> : true_type {};

        // specialization for variadic functions such as printf
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)> : true_type {};

        // specialization for function types that have cv-qualifiers
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)volatile> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const volatile> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)volatile> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const volatile> : true_type {};

        // specialization for function types that have ref-qualifiers
        template<class Ret, class... Args>
        struct is_function<Ret(Args...) &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)volatile &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const volatile &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......) &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)volatile &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const volatile &> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...) &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)volatile &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args...)const volatile &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......) &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)volatile &&> : true_type {};
        template<class Ret, class... Args>
        struct is_function<Ret(Args......)const volatile &&> : true_type {};
    #endif

    /***
        is_object structure.
            Determines whether T is an object.
    ***/

	#ifdef ISCPP11
		template< typename T > struct is_object{ enum { value = !is_function<T>::value || !is_pointer<T>::value || !is_array<T>::value || !is_fundamental<T>::value }; };
	#else
		template< typename T > struct is_object{ enum { value = !is_pointer<T>::value || !is_array<T>::value || !is_fundamental<T>::value }; };
	#endif
		
    /***
        is_base_of structure.
            Determines whether D is inherited by B.
    ***/

    #ifdef ISCPP11
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
#endif
