/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
********************************************************************************/

#ifndef HEADER_NULLSTREAM
    #define HEADER_NULLSTREAM

	struct NullStream : Stream, PrintExtension{
		NullStream()                 {}
		int available()              { return 0; }
		void flush()                 { return; }
		int peek()                   { return -1; }
		int read()                   { return -1; }
		size_t write( uint8_t data ) { return (void)data, 0x01; }
	};

#endif
