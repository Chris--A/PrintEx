/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#include "URIEncoder.h"

const char URIChars[] PROGMEM = {
	'!', '*', '\'', '(', ')', ';', ':', '@', '&', '=', '+', '$', ',', '/', '?', '#', '[', ']', ' '
};

size_t URIEncoder::write( uint8_t data ){

	bool found = false;
	
	if( mode != URI_ALL ){
		for( unsigned char index = 0 ; index < sizeof(URIChars) ; ++index ){
			if( pgm_read_byte( URIChars + index ) == data ) found = true;
		}
	}else
		found = true;
	
	if( found ){
	
		if( data == ' ' && mode == URI_WWWFORM ) return out.write( '+' );
		out.write( '%' );
		out.print( data, HEX );
		return 0x03;
	}else
		return out.write( data );
}
