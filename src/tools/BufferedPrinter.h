/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#ifndef HEADER_BUFFEREDPRINTER
    #define HEADER_BUFFEREDPRINTER

	template< unsigned length >
		class BufferedPrinter : public PrintExtension{
			public:
				using Print::write;
				BufferedPrinter( Print &output ) : output( output ), cursor( 0x00 ) {}
				~BufferedPrinter() { flush(); }
		   
				void flush(){
					if( cursor ) output.write( buffer, cursor );
					cursor = 0x00;
				}
		  
				size_t write( const byte *buffer, size_t size ){
					size_t count = size;
					while( count-- ) write( *buffer++ );
					return size;
				}
	  
				size_t write( byte data ){
					if( cursor == length ) flush();
					buffer[ cursor++ ] = data;
					return 0x01;
				}
				
			protected:
				Print    &output;
				byte     buffer[ length ];
				uint16_t cursor;
	};

#endif
