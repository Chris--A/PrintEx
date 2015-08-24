/********************************************************************************
    Copyright 2015 Christopher Andrews.
    https://github.com/Chris--A/PrintEx

    Released under MIT licence.
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
