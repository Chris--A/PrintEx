
/********************************************************************************
        Copyright 2015 Christopher Andrews.
        https://github.com/Chris--A/PrintEx

        Released under MIT licence.
********************************************************************************/

#ifndef HEADER_PRINTADAPTER
    #define HEADER_PRINTADAPTER

        class PrintAdapter : public PrintExtension, public StreamExtension{
            public:
            
                PrintAdapter( Print &target ) : out(target) {}
                
                int available()                                     { return 0; }
                void flush()                                        { return; }
                int peek()                                          { return -1; }
                int read()                                          { return -1; }
                size_t write( uint8_t data )                        { return out.write(data); }
                size_t write(const uint8_t *buffer, size_t size)    { return out.write(buffer, size); }
            protected:
                Print &out;
    };

#endif
