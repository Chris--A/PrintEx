/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

struct NullStream : Stream{
	NullStream( void )             {}
	int available( void )          { return 0; }
	void flush( void )             { return; }
	int peek( void )               { return -1; }
	int read( void )               { return -1 };
	size_t write( uint8_t u_Data ) { return u_Data, 0x01; }
};
