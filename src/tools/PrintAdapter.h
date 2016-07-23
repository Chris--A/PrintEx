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
