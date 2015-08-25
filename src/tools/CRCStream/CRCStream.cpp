/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#include "CRCStream.h"

typedef CRCStream::CRC CRC;

const uint32_t crc_table[ 0x10 ] PROGMEM = {
	0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
	0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

void crc32Byte( CRC &crc, uint8_t data )
	{
		uint8_t index;
		index = crc ^ data;
		crc = pgm_read_dword( crc_table + ( index & 0x0F ) ) ^ ( crc >> 4 );
		index = crc ^ ( data >> 4 );
		crc = pgm_read_dword( crc_table + ( index & 0x0F ) ) ^ ( crc >> 4 );
	}	

int CRCStream::read( void )
	{ 
		const int readValue = stream.read();
		if( readValue != -1 ) crc32Byte( in, ( uint8_t ) readValue );
		return readValue; 
	}	
	
size_t CRCStream::write( uint8_t data )
	{
		crc32Byte( out, data );
		return stream.write( data );			
	}
