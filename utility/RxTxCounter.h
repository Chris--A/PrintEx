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

#ifndef HEADER_RXTXCOUNTER
    #define HEADER_RXTXCOUNTER

    class RxTxCounter : public Stream{

        public:
            RxTxCounter( Stream &host ) : stream( host ), input( 0 ), output( 0 ) { return; }

            int available( void ) { return stream.available(); }
            void flush( void ) { stream.flush(); }
            int peek( void ) { return stream.peek(); }

            unsigned int getTx() { return output; }
            unsigned int getRx() { return input; }

            int read( void ){
                int result = stream.read();
                if( result != -1 ) ++input;
                return result;
            }

            size_t write( uint8_t data ){
                return output += 1, stream.write( data );
            }
        protected:
            Stream &stream;
            unsigned int input;
            unsigned int output;
    };

#endif
