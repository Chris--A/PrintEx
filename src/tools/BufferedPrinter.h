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
