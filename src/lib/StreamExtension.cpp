
#include "Arduino.h"
#include "PrintExtension.h"
#include "StreamExtension.h"


        pft StreamExtension::printf( const char *format, ... ){
            va_list vList;
            va_start( vList, format );

            PrintEx printer = *this;
            const pft p_Return = printer._printf( format, vList );
            va_end( vList );
            return p_Return;
        };
