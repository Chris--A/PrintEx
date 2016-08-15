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

    #include "MemoryPrinter.h"

    #define CHAR_PERCENT       '%'
    #define CHAR_NULL          '\0'
    #define CHAR_MINUS         '-'
    #define CHAR_ZERO          '0'
    #define CHAR_NINE          '9'
    #define CHAR_SPACE         ' '
    #define CHAR_STAR          '*'
    #define CHAR_HASH          '#'
    #define CHAR_PERIOD        '.'

    #define CHAR_c             'c'
    #define CHAR_d             'd'
    #define CHAR_F             'F'
    #define CHAR_f             'f'
    #define CHAR_i             'i'
    #define CHAR_l             'l'
    #define CHAR_n             'n'
    #define CHAR_p             'p'
    #define CHAR_q             'q'
    #define CHAR_r             'r'
    #define CHAR_S             'S'
    #define CHAR_s             's'
    #define CHAR_t             't'
    #define CHAR_u             'u'
    #define CHAR_x             'x'
    #define CHAR_X             'X'

    #define PAD_RIGHT           1
    #define PAD_ZERO            2

    #define PRINTF_CONVERT_BUFFER_LEN   24
    #define PRINTF_ERROR_MESSAGE        "Error" //F("Error") may be used also.

    #ifdef printf
        #undef printf
    #endif

    /***
        PrintExtension printf() functionality.
    ***/

    pft PrintExtension::PRINTF_ALIAS( const char *format, ... ){
        va_list vList;
        va_start( vList, format );
        const pft p_Return = _printf( format, vList );
        va_end( vList );
        return p_Return;
    }

    #ifndef PRINTEX_NO_PROGMEM
        pft PrintExtension::PRINTF_ALIAS( const __FlashStringHelper *format, ... ){
            va_list vList;
            va_start( vList, format );
            const pft p_Return = _printf( format, strlen_P((const char*)format)+1, vList );
            va_end( vList );
            return p_Return;
        }

        pft PrintExtension::_printf( const __FlashStringHelper *format, const int count, const va_list &vList ){
            char buffer[count];
            return _printf( strcpy_P( buffer, (const char*)format ), vList );
        }
    #endif


    /***
        Global printf() functionality.
    ***/

    #ifndef PRINTEX_NO_STDOUT

        //Storage location for 'stdout' Print pointer.
        Print *_stdout __attribute__((weak)) = (Print*) 0x00;

        pft PRINTF_ALIAS( const char *format, ... ){
            if( !_stdout ) return 0;
            va_list vList;
            va_start( vList, format );
            const pft p_Return = PrintEx(*_stdout)._printf( format, vList );
            va_end( vList );
            return p_Return;
        }

        #ifndef PRINTEX_NO_PROGMEM
            pft PRINTF_ALIAS( const __FlashStringHelper *format, ... ){
                if( !_stdout ) return 0;
                va_list vList;
                va_start( vList, format );
                const pft p_Return = PrintEx(*_stdout)._printf( format, strlen_P((const char*)format)+1, vList );
                va_end( vList );
                return p_Return;
            }
        #endif
    #endif

    /****************************************************************
        GetParam_XXX functions.
            The variations below proved to be far more efficient
            than using va_arg() directly in printf() when compiled
            on an AVR.
    ****************************************************************/

    uint32_t GetParam_uint( const va_list &vList, const bool b16 ){
        if( b16 )
            return va_arg( vList, unsigned int );
        else
            return va_arg( vList, uint32_t );
    }

    int GetParam_int( const va_list &vList ) __attribute__((noinline));
    int GetParam_int( const va_list &vList ){
        return va_arg( vList, int );
    }


    /****************************************************************
        cwrite function.
            Helper for printf.
    ****************************************************************/

    inline void PrintExtension::cwrite( const uint8_t &data, pfct &counter ){
        write( data );
        ++counter;
    }


    /****************************************************************
        sprintf, x.printf function.
            Prints formatted text.

            Formatting options use the following syntax:
                %[flags][width][.precision][length]specifier

            Flags:
                -:    Left-justify within the given field width; Right justification is the default.
                0:    When padding is specified, zeros are used instead of spaces.

            Width:
                (number):   Minimum number of characters to be printed.
                            If the value to be printed is shorter than this number,
                            the result is padded with blank spaces.
                            The value is not truncated even if the result is larger.

                *:  The width is not specified in the format string,
                    but as an additional integer value argument preceding
                    the argument that has to be formatted.

                Extra:

                    q:  When using '%q' to read the EEPROM the width is the number of
                        characters to read.

                    r:  Number of times to run repeat function.

            Precision:

                .(number): If a precision value is needed, it must be prefixed by a period character ('.').
                           This parameter only affects the precision of floating point values. ('f' specifier).

            Length:

                l:  d, i use long instead of int.
                    u, x use unsigned long instead of unsigned int.
                    r    repeats a string.

            Specifier:

                s:    String ( null terminated ).
                S:    PROGMEM string. No formatting takes place, the string is printed directly.
                q:    EEPROM string. No formatting takes place, the string is printed directly.
                d:    Signed decimal integer ( 32bits max ).
                i:    Same as 'd'.
                u:    Unsigned decimal integer ( 32bits max ).
                f:    Decimal floating point number.
                F:    Same as 'f'.
                x:    Unsigned decimal integer ( 32bits max ).
                X:    Same as 'x'
                c:    Character.
                r:    Repeat function ( default character, see length ).
                n:    Parameter is a signed int*. The current output count will be written to pointer.
                p:    Will write a pointer address. It is a hexadecimal print out formatted to 0x0000
                %:    Escape character for printing '%'
    ****************************************************************/

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wattributes"
    bool formatTest( const char *&format, const char test ) __attribute__((always_inline));
    bool formatTest( const char *&format, const char test ){
        return *format == test ? ++format, true : false;
    }
    #pragma GCC diagnostic pop

    //Used to parse the width and precision parameters.
    void parseValue( const char *&format, unsigned int &total ){
        for ( ; *format >= CHAR_ZERO && *format <= CHAR_NINE; ++format )(total *= 10) += *format - CHAR_ZERO;
    }


    pft PrintExtension::_printf( const char *format, const va_list &vList ){
        unsigned int   width;
        pfct           pad;
        pfct           counter = 0x00;
        unsigned char  buffer[ PRINTF_CONVERT_BUFFER_LEN ];            //Buffer for conversions.

        for( ; *format ; ++format ){

            if( formatTest( format, CHAR_PERCENT ) ){
                width = pad = 0x00;

                bool largeType = false;

                if( *format == CHAR_NULL )         --format;
                else if( *format == CHAR_PERCENT ) cwrite( *format, counter );
                else{

                    //Check for left justify & '0' pad specifier.
                    if( formatTest( format, CHAR_MINUS ) ) pad = PAD_RIGHT;
                    if( formatTest( format, CHAR_ZERO ) )  pad |= PAD_ZERO;

                    //Check for passed length.
                    #ifndef PRINTF_NO_WIDTH_PARAM
                        if( formatTest( format, CHAR_STAR ) ) width = ( unsigned int ) GetParam_int( vList );
                        else //Width provided in format specifier (drop to parseValue below).
                    #endif

                    //Calculate padding width (if not provided as an extra parameter).
                    parseValue( format, width );

                    //Determine pad character and give the working buffer a printable interface.
                    char    padChar = ( pad & PAD_ZERO ) ? CHAR_ZERO : CHAR_SPACE;
                    GString convertStr( buffer );

                    //Grab precision specifier.
                    #if !defined(PRINTF_NO_FLOATING_POINT) && !defined(PRINTEX_NO_PRECISION_PARAM)
                        unsigned int precision = 0x00;
                        if( formatTest( format, CHAR_PERIOD ) ) parseValue( format, precision );
                    #endif

                    //Get length flag if for larger types.
                    if( formatTest( format, CHAR_l ) ) largeType = true;

                    //Print a pointer.
                    if( *format == CHAR_p ){
                        counter += write("0x");
                        padChar = CHAR_ZERO;
                        width = width >= sizeof(int*) ? width : sizeof(int*);
                    }

                    //String.
                    if( *format == CHAR_s ){
                        char *c_Parameter = ( char* ) GetParam_int( vList );
                        convertStr.assign( c_Parameter, strlen( c_Parameter ) );

                    //Return counter function.
                    }else if( *format == CHAR_n ){
                        *(signed int*) GetParam_int( vList ) = counter;
                        continue;

                    //PROGMEM functionality.
                    #ifndef PRINTF_NO_PROGMEM
                        }else if( *format == CHAR_S ){
                            counter += print( PString( ( void* ) GetParam_int( vList ) ) );
                            continue;
                    #endif

                    //EEPROM handling.
                    #ifndef PRINTF_NO_EEPROM
                        }else if( *format == CHAR_q ){
                            counter += print( EString( ( void* ) GetParam_int( vList ), width ) );
                            continue;
                    #endif

                    //Repeat function.
                    #ifndef PRINTF_NO_REPEAT
                        }else if( *format == CHAR_r ){
                            const int i_Data = GetParam_int( vList );
                            while( width-- ){
                                if( largeType ) counter += print( ( char* ) i_Data );
                                else            counter += print( ( char ) i_Data );
                            }
                            continue;
                    #endif

                    //Signed decimal integer.
                    }else if( *format == CHAR_d ||  *format == CHAR_i ){
                        if( largeType ) convertStr.print( va_arg( vList, int32_t ), DEC );
                        else            convertStr.print( ( int32_t ) GetParam_int( vList ), DEC );

                    //Unsigned integer.
                    }else if( *format == CHAR_u ){
                        if( largeType ) convertStr.print( GetParam_uint( vList, false ), DEC );
                        else            convertStr.print( ( uint32_t ) GetParam_uint( vList, true ), DEC );

                    //Floating point data.
                    #ifndef PRINTF_NO_FLOATING_POINT
                        }else if( *format == CHAR_f || *format == CHAR_F ){
                            #ifndef PRINTEX_NO_PRECISION_PARAM
                                convertStr.print( va_arg( vList, double ), precision );
                            #else
                                convertStr.print( va_arg( vList, double ) );
                            #endif
                    #endif

                    //Unsigned hexadecimal integer.
                    }else if( *format == CHAR_x || *format == CHAR_X || *format == CHAR_p ){
                        if( largeType ) convertStr.print( GetParam_uint( vList, false ), HEX );
                        else            convertStr.print( ( uint32_t ) GetParam_uint( vList, true ), HEX );

                    //Character.
                    }else if(  *format == CHAR_c ){
                        *buffer = ( char ) GetParam_int( vList );
                        //This is cheaper than printing.
                        convertStr.assign( buffer, 1 );

                    #if ( defined( PRINTF_NO_EEPROM ) || defined( PRINTF_NO_FLOATING_POINT ) || defined( PRINTF_NO_PROGMEM ) ) && !defined( PRINTF_NO_ERROR_CONDITION )
                        }else{
                            convertStr.print( PRINTF_ERROR_MESSAGE );
                    #else
                        }
                    #endif

                    //Calculate remaining padding.
                    const pft len = convertStr.count();
                    if( len >= width )    width = 0x00;
                    else                width -= len;

                    //Pad left if right justified.
                    if( !( pad & PAD_RIGHT ) ){
                        _repeat( padChar, width );
                        counter += width;
                        width = 0;
                    }

                    counter += write( ( unsigned char* ) ( char* ) convertStr, len );

                    //Pad right if left justified.
                    _repeat( padChar, width );
                    counter += width;
                }
            }else //Standard character, write out.
                cwrite( *format, counter );
        }
        return counter;
    }

