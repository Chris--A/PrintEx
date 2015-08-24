/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include "Base64Encoder.h"

const char b64[] PROGMEM = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

void Base64Encoder::flush(){

    if( !cursor ) return;
    Convert();
    switch( cursor ){
        case 1:    data[ 0x02 ] = '=';
        case 2:    data[ 0x03 ] = '=';
    }
    Step();
}

size_t Base64Encoder::write( uint8_t in ){

    if( cursor == 0x03 ){
        Convert();
        Step();
    }
    data[ cursor++ ] = in;
    return 0x01;
}

void Base64Encoder::Step(){

    out.write( data, 0x04 );
    memset( data, 0x00, 0x04 );
    cursor = 0x00;
}

void Base64Encoder::Convert(){

    union{
        uint8_t Input[ 0x03 ];
        struct{
            unsigned int D : 0x06;
            unsigned int C : 0x06;
            unsigned int B : 0x06;
            unsigned int A : 0x06;
        } out;
    } B64C = { { data[ 2 ], data[ 1 ], data[ 0 ] } };

    data[ 0x00 ] = pgm_read_byte( &b64[ B64C.out.A ] );
    data[ 0x01 ] = pgm_read_byte( &b64[ B64C.out.B ] );
    data[ 0x02 ] = pgm_read_byte( &b64[ B64C.out.C ] );
    data[ 0x03 ] = pgm_read_byte( &b64[ B64C.out.D ] );
}


    /*size_t Base64Encoder::write( const uint8_t *u_data, size_t s_Len )
        {
            while( s_Len > 0x03 ){


            }



            while( s_Len-- ){

                if( cursor == 0x03 ){

                    Convert();


                }
                data[ cursor++ ] = u_data;
            }


            if( cursor == 0x03 ){
                Convert();
                Step();
            }
            data[ cursor++ ] = u_data;
            return 0x01;
        }    */

//EOF

